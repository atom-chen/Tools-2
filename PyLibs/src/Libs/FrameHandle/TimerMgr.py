﻿using LuaInterface;
using System;
using System.Collections.Generic;

/**
 * @brief 定时器管理器
 */
namespace SDK.Lib
{
    public class TimerMgr : DelayHandleMgrBase
    {
        protected List<TimerItemBase> m_timerList = new List<TimerItemBase>();     // 当前所有的定时器列表

        public TimerMgr()
        {
            
        }

        protected override void addObject(IDelayHandleItem delayObject, float priority = 0.0f)
        {
            // 检查当前是否已经在队列中
            if (m_timerList.IndexOf(delayObject as TimerItemBase) == -1)
            {
                if (bInDepth())
                {
                    base.addObject(delayObject, priority);
                }
                else
                {
                    m_timerList.Add(delayObject as TimerItemBase);
                }
            }
        }

        protected override void removeObject(IDelayHandleItem delayObject)
        {
            // 检查当前是否在队列中
            if (m_timerList.IndexOf(delayObject as TimerItemBase) != -1)
            {
                (delayObject as TimerItemBase).m_disposed = true;
                if (bInDepth())
                {
                    base.removeObject(delayObject);
                }
                else
                {
                    foreach (TimerItemBase item in m_timerList)
                    {
                        if (UtilApi.isAddressEqual(item, delayObject))
                        {
                            m_timerList.Remove(item);
                            break;
                        }
                    }
                }
            }
        }

        // 从 Lua 中添加定时器，这种定时器尽量整个定时器周期只与 Lua 通信一次
        public void addTimer(TimerItemBase delayObject, float priority = 0.0f)
        {
            this.addObject(delayObject, priority);
        }

        public void addTimer(LuaTable luaTimer)
        {
            LuaTable table = luaTimer["pthis"] as LuaTable;
            LuaFunction function = luaTimer["func"] as LuaFunction;

            TimerItemBase timer = new TimerItemBase();
            timer.m_totalTime = Convert.ToSingle(luaTimer["totaltime"]);
            timer.setLuaFunctor(table, function);

            this.addTimer(timer);
        }

        public void removeTimer(TimerItemBase timer)
        {
            this.removeObject(timer);
        }

        public void Advance(float delta)
        {
            incDepth();

            foreach (TimerItemBase timerItem in m_timerList)
            {
                if (!timerItem.getClientDispose())
                {
                    timerItem.OnTimer(delta);
                }

                if (timerItem.m_disposed)        // 如果已经结束
                {
                    removeObject(timerItem);
                }
            }

            decDepth();
        }
    }
}