﻿using System.Net;
using System.Net.Sockets;
using System;
using System.Threading;

namespace SDK.Lib
{
    public class NetTCPClient
    {
        // 发送和接收的超时时间
        public int m_connectTimeout = 5000;
        // 超时值（以毫秒为单位）。如果将该属性设置为 1 到 499 之间的值，该值将被更改为 500。默认值为 0，指示超时期限无限大。指定 -1 还会指示超时期限无限大。
        //public int m_sendTimeout = 5000;
        //public int m_revTimeout = 0;

        public string m_ip;
        public int m_port;

        protected Socket m_socket = null;
        protected ClientBuffer m_clientBuffer;
        protected bool m_brecvThreadStart;      // 接收线程是否启动
        protected bool m_isConnected;

        protected MEvent m_msgSendEndEvent;       // 当前所有的消息都发送出去了，通知等待线程
        protected MMutex m_sendMutex;   // 读互斥

        public NetTCPClient(string ip = "localhost", int port = 5000)
        {
            m_brecvThreadStart = false;
            m_isConnected = false;
            m_msgSendEndEvent = new MEvent(false);
            m_sendMutex = new MMutex(false, "NetTCPClient_SendMutex");

            m_ip = ip;
            m_port = port;

            m_clientBuffer = new ClientBuffer();
            m_clientBuffer.setEndian(SystemEndian.msServerEndian);     // 设置服务器字节序
        }

        public ClientBuffer clientBuffer
        {
            get
            {
                return m_clientBuffer;
            }
        }

        public bool brecvThreadStart
        {
            get
            {
                return m_brecvThreadStart;
            }
            set
            {
                m_brecvThreadStart = value;
            }
        }

        public bool isConnected
        {
            get
            {
                return m_isConnected;
            }
        }

        public MEvent msgSendEndEvent
        {
            get
            {
                return m_msgSendEndEvent;
            }
            set
            {
                m_msgSendEndEvent = value;
            }
        }

        // 是否可以发送新的数据，上一次发送的数据是否发送完成，只有上次发送的数据全部发送完成，才能发送新的数据
        public bool canSendNewData()
        {
            return (m_clientBuffer.sendBuffer.bytesAvailable == 0);
        }

        // 设置接收缓冲区大小，和征途服务器对接，这个一定要和服务器大小一致，并且一定要是 8 的整数倍，否则在消息比较多，并且一个包发送过来的时候，会出错
        public void SetRevBufferSize(int size)
        {
            m_socket.ReceiveBufferSize = size;      // ReceiveBufferSize 默认 8096 字节
            m_clientBuffer.SetRevBufferSize(size);
        }

        // 连接服务器
        public bool Connect(string address, int remotePort)
        {
            if (m_socket != null && m_socket.Connected)
            {
                return true;
            }
            try
            {
                //获得远程服务器的地址
                IPAddress remoteAdd = IPAddress.Parse(address);
                IPEndPoint ipe = new IPEndPoint(remoteAdd, remotePort);
                // 创建socket
                m_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // 开始连接
                IAsyncResult result = m_socket.BeginConnect(ipe, new System.AsyncCallback(ConnectionCallback), m_socket);
                // 这里做一个超时的监测，当连接超过5秒还没成功表示超时
                bool success = result.AsyncWaitHandle.WaitOne(m_connectTimeout, true);
                if (!success)
                {
                    //超时
                    //Disconnect(0);
                    Ctx.m_instance.m_logSys.log("socket connect Time Out");
                }
                else
                {
                    // 设置建立链接标识
                    m_isConnected = true;
                    // 打印端口信息
                    string ipPortStr;

                    ipPortStr = string.Format("local IP: {0}, Port: {1}", ((IPEndPoint)m_socket.LocalEndPoint).Address.ToString(), ((IPEndPoint)m_socket.LocalEndPoint).Port.ToString());
                    Ctx.m_instance.m_logSys.log(ipPortStr);

                    ipPortStr = string.Format("Remote IP: {0}, Port: {1}", ((IPEndPoint)m_socket.RemoteEndPoint).Address.ToString(), ((IPEndPoint)m_socket.RemoteEndPoint).Port.ToString());
                    Ctx.m_instance.m_logSys.log(ipPortStr);
                }
            }
            catch (System.Exception e)
            {
                // 连接失败
                Ctx.m_instance.m_logSys.error(e.Message);
                return false;
            }

            return true;
        }

        // 异步连接回调
        void ConnectionCallback(System.IAsyncResult ar)
        {
            try
            {
                // 与服务器取得连接
                m_socket.EndConnect(ar);
                m_isConnected = true;
                // 设置选项
                m_socket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.NoDelay, true);
                SetRevBufferSize(8096);
                // 设置 timeout
                //m_socket.SendTimeout = m_sendTimeout;
                //m_socket.ReceiveTimeout = m_revTimeout;

                if (!MacroDef.NET_MULTHREAD)
                {
                    Receive();
                }

                // 连接成功，通知
                // 这个在主线程中调用
                Ctx.m_instance.m_sysMsgRoute.push(new SocketOpenedMR());
            }
            catch (System.Exception e)
            {
                // 错误处理
                if (e.GetType() == typeof(SocketException))
                {
                    if (((SocketException)e).SocketErrorCode == SocketError.ConnectionRefused)
                    {
                        // 输出日志
                        Ctx.m_instance.m_logSys.log(e.Message);
                    }
                    else
                    {
                        // 输出日志
                        Ctx.m_instance.m_logSys.log(e.Message);
                    }
                }
                else
                {
                    // 输出日志
                    Ctx.m_instance.m_logSys.error(e.Message);
                }

                //Disconnect();
            }
        }

        // 接受数据
        public void Receive()
        {
            // 只有 socket 连接的时候才继续接收数据
            if (m_socket.Connected)
            {
                // 接收从服务器返回的信息
                IAsyncResult asyncSend = m_socket.BeginReceive(m_clientBuffer.dynBuff.buff, 0, (int)m_clientBuffer.dynBuff.capacity, SocketFlags.None, new System.AsyncCallback(ReceiveData), 0);

                //checkThread();

                //bool success = asyncSend.AsyncWaitHandle.WaitOne(m_revTimeout, true);
                //if (!success)
                //{
                //    Ctx.m_instance.m_logSys.asyncLog(string.Format("RecvMsg Timeout {0} ", m_revTimeout));
                //}
            }
        }

        // 接收头消息
        void ReceiveData(System.IAsyncResult ar)
        {
            if (!checkAndUpdateConnect())        // 如果连接完成后直接断开，这个时候如果再使用 m_socket.EndReceive 这个函数就会抛出异常
            {
                return;
            }

            //checkThread();

            if (m_socket == null)        // SocketShutdown.Both 这样关闭，只有还会收到数据，因此判断一下
            {
                return;
            }

            int read = 0;
            try
            {
                read = m_socket.EndReceive(ar);          // 获取读取的长度

                if (read > 0)
                {
                    Ctx.m_instance.m_logSys.log("接收到数据 " + read.ToString());
                    m_clientBuffer.dynBuff.size = (uint)read; // 设置读取大小
                    m_clientBuffer.moveDyn2Raw();             // 将接收到的数据放到原始数据队列
                    m_clientBuffer.moveRaw2Msg();             // 将完整的消息移动到消息缓冲区
                    Receive();                  // 继续接收
                }
            }
            catch (System.Exception e)
            {
                // 输出日志
                Ctx.m_instance.m_logSys.error(e.Message);
                Ctx.m_instance.m_logSys.error("接收数据出错");
                //Disconnect(0);
            }
        }

        // 发送消息
        public void Send()
        {
            using (MLock mlock = new MLock(m_sendMutex))
            {
                if (!checkAndUpdateConnect())
                {
                    return;
                }

                //checkThread();

                if (m_socket == null)
                {
                    return;
                }

                if (m_clientBuffer.sendBuffer.bytesAvailable == 0)     // 如果发送缓冲区没有要发送的数据
                {
                    if (m_clientBuffer.sendTmpBuffer.circularBuffer.size > 0)      // 如果发送临时缓冲区有数据要发
                    {
                        m_clientBuffer.getSocketSendData();
                    }

                    if (m_clientBuffer.sendBuffer.bytesAvailable == 0)        // 如果发送缓冲区中确实没有数据
                    {
                        if (MacroDef.NET_MULTHREAD)
                        {
                            m_msgSendEndEvent.Set();        // 通知等待线程，所有数据都发送完成
                        }
                        return;
                    }
                }

                try
                {
                    Ctx.m_instance.m_logSys.log(string.Format("开始发送字节数 {0} ", m_clientBuffer.sendBuffer.bytesAvailable));

                    IAsyncResult asyncSend = m_socket.BeginSend(m_clientBuffer.sendBuffer.dynBuff.buff, (int)m_clientBuffer.sendBuffer.position, (int)m_clientBuffer.sendBuffer.bytesAvailable, 0, new System.AsyncCallback(SendCallback), 0);
                    //bool success = asyncSend.AsyncWaitHandle.WaitOne(m_sendTimeout, true);
                    //if (!success)
                    //{
                    //    Ctx.m_instance.m_logSys.asyncLog(string.Format("SendMsg Timeout {0} ", m_sendTimeout));
                    //}
                }
                catch (System.Exception e)
                {
                    if (MacroDef.NET_MULTHREAD)
                    {
                        m_msgSendEndEvent.Set();        // 发生异常，通知等待线程，所有数据都发送完成，防止等待线程不能解锁
                    }
                    // 输出日志
                    Ctx.m_instance.m_logSys.error(e.Message);
                    //Disconnect(0);
                }
            }
        }

        //发送回调
        private void SendCallback(System.IAsyncResult ar)
        {
            using (MLock mlock = new MLock(m_sendMutex))
            {
                if (!checkAndUpdateConnect())
                {
                    return;
                }

                //checkThread();

                try
                {
                    int bytesSent = m_socket.EndSend(ar);
                    Ctx.m_instance.m_logSys.log(string.Format("结束发送字节数 {0} ", bytesSent));

                    if (m_clientBuffer.sendBuffer.length < m_clientBuffer.sendBuffer.position + (uint)bytesSent)
                    {
                        Ctx.m_instance.m_logSys.log(string.Format("结束发送字节数错误 {0}", bytesSent));
                        m_clientBuffer.sendBuffer.setPos(m_clientBuffer.sendBuffer.length);
                    }
                    else
                    {
                        m_clientBuffer.sendBuffer.setPos(m_clientBuffer.sendBuffer.position + (uint)bytesSent);
                    }

                    if (m_clientBuffer.sendBuffer.bytesAvailable > 0)     // 如果上一次发送的数据还没发送完成，继续发送
                    {
                        Send();                 // 继续发送数据
                    }
                }
                catch (System.Exception e)
                {
                    // 输出日志
                    Ctx.m_instance.m_logSys.error(e.Message);
                    //Disconnect(0);
                }
            }
        }

        // 关闭连接
        public void Disconnect(int timeout = 0)
        {
            // 关闭之后 m_socket.Connected 设置成 false
            if (m_socket != null)
            {
                if (m_socket.Connected)
                {
                    m_socket.Shutdown(SocketShutdown.Both);
                    //m_socket.Close(timeout);  // timeout 不能是 0 ，是 0 含义未定义
                    if (timeout > 0)
                    {
                        m_socket.Close(timeout);
                    }
                    else
                    {
                        m_socket.Close();
                    }
                }
                else
                {
                    m_socket.Close();
                }

                m_socket = null;
            }
        }
        
        // 检查并且更新连接状态
        protected bool checkAndUpdateConnect()
        {
            if (m_socket != null && !m_socket.Connected)
            {
                if (m_isConnected)
                {
                    Ctx.m_instance.m_sysMsgRoute.push(new SocketCloseedMR());
                }
                m_isConnected = false;
            }

            return m_isConnected;
        }

        protected bool checkThread()
        {
            if(Ctx.m_instance.m_netMgr.isNetThread(Thread.CurrentThread.ManagedThreadId))
            {
                return true;
            }

            return false;
        }
    }
}