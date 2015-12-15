# -*- coding: utf-8 -*-

'''
@brief terrain pack
'''
"""
implement cmd str
"""

import os
import subprocess
import shutil
from xml.dom.minidom import Document

from Pack.Frame.Config import Config

'''
'''
class CmdLine(object):
    '''
           裁剪一张地形图片
    '''
    @staticmethod
    def execOneCrop():
        #convertim -crop 128x128 %%k "dest.jpg"
        cmd = ParamInfo.pInstance.m_convCmd + ' -crop ' + str(ParamInfo.pInstance.m_cropWidth) + 'x' + str(ParamInfo.pInstance.m_cropWidth) + ' ' + ParamInfo.pInstance.curSrcfileDir() + ' ' + ParamInfo.pInstance.curDestFileDir()
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
        
    @staticmethod
    def execIdentify():
        #identify -format "size is %Wx%H" input.bmp
        cmd = ParamInfo.pInstance.m_identCmd + ' -format \"size is %Wx%H\" ' + ParamInfo.pInstance.curSrcfileDir()
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
        
        retStr = handle.stdout.read()
        retStr = retStr.decode('utf-8')
        splitList = retStr.split()[2].split('x')
        ParamInfo.pInstance.m_curSrcWidth = int(splitList[0])
        ParamInfo.pInstance.m_curSrcHeight = int(splitList[1])
        
        return cmd
    
    '''
            生成缩略图
    '''
    @staticmethod
    def exeScale():
        #convertim -resize 200x100 -quality 80 src.jpg dest.jpg
        #convertim -resize 10% -quality 80 src.jpg dest.jpg
        #if ParamInfo.pInstance.m_thumbnailsquality == 100:
        #    cmd = ParamInfo.pInstance.m_convCmd + ' -resize ' + str(ParamInfo.pInstance.m_thumbnailsWidth) + 'x' + str(ParamInfo.pInstance.m_thumbnailsHeight) + ' ' + ParamInfo.pInstance.curSrcfileDir() + ' ' + ParamInfo.pInstance.curThumbnailsFileName()
        #else:
        #    cmd = ParamInfo.pInstance.m_convCmd + ' -resize ' + str(ParamInfo.pInstance.m_thumbnailsWidth) + 'x' + str(ParamInfo.pInstance.m_thumbnailsHeight) + ' -quality ' + str(ParamInfo.pInstance.m_thumbnailsquality) + ' ' + ParamInfo.pInstance.curSrcfileDir() + ' ' + ParamInfo.pInstance.curThumbnailsFileName()
        
        if ParamInfo.pInstance.m_thumbnailsquality == 100:
            cmd = ParamInfo.pInstance.m_convCmd + ' -resize ' + str(ParamInfo.pInstance.m_thumbnailsscale) + '%' + ' ' + ParamInfo.pInstance.curSrcfileDir() + ' ' + ParamInfo.pInstance.curThumbnailsFileName()
        else:
            cmd = ParamInfo.pInstance.m_convCmd + ' -resize ' + str(ParamInfo.pInstance.m_thumbnailsscale) + '%' + ' -quality ' + str(ParamInfo.pInstance.m_thumbnailsquality) + ' ' + ParamInfo.pInstance.curSrcfileDir() + ' ' + ParamInfo.pInstance.curThumbnailsFileName()
        
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
    
    @staticmethod
    def execSwift():
        #identify -format "size is %Wx%H" input.bmp
        cmd = 'java -jar %s xml2lib %s.xml %s.swc' % (ParamInfo.pInstance.m_swift, ParamInfo.pInstance.m_swiftFullXmlFile, ParamInfo.pInstance.m_swiftFullSwcFile)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
    
    @staticmethod
    def exec7z():
        cmd = '"%s" e -y %s.swc -o%s *.swf' % (ParamInfo.pInstance.m_7z, ParamInfo.pInstance.m_swiftFullSwcFile, ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName)
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()

'''
parameter info
'''
class ParamInfo(object):
    #single
    pInstance = None
    
    @classmethod
    def instance(cls):
        if cls.pInstance is None:
            cls.pInstance = cls()
            
        return cls.pInstance
    
    def __init__(self):
        self.m_srcRootPath = ''     #根目录
        self.m_destRootPath = ''    #最终生成文件根目录
        
        self.m_cropWidth = 128      #裁剪的宽度
        self.m_cropHeight = 128     #裁剪的高度
        self.m_gridWidth = 32      #格子的宽度
        self.m_gridHeight = 32     #格子的高度
        
        self.m_convCmd = 'convertim.exe'    #裁剪指令
        self.m_identCmd = 'identify.exe'    #查看图像信息
        self.m_7z = '7z.exe'
        self.m_swift = 'Swift.jar'
        self.m_destTplFileName = 'dest.jpg' #生成的模板文件名字，地形 jpg 压缩
        
        #下面的参数都是闭包数据
        #self.m_curSrcFolder = ''       #当前文件夹
        self.m_curSrcFile = ''         #当前文件
        
        self.m_curSrcWidth = ''        #原始文件宽度
        self.m_curSrcHeight = ''       #原始文件高度
        
        self.m_swiftFullXmlFile = ''    #
        self.m_swiftFullSwcFile = ''    #
        self.m_bStopPt = False          # 是否有阻挡点信息
        
        #配置引用数据
        self.m_srcFolder2DestFolderMap = {} #源文件夹到目标文件夹映射

        #内部定义使用
        self.xmlFolderName = 'aterxml'                    #地形材质和地形配置文件文件夹目录
        self.XmlSwfFolderName = 'aterxmlswf'              #地形地形材质和场景配置打包swf文件文件夹目录
        self.batXmlFolderName = 'aterbatxml'              #打包中间文件文件夹目录
        
        # 战斗地形打包配置信息
        self.m_bfight = False;    # 是不是战斗地图
        #self.m_addLeftGrid = 0    # 左边增加的格子
        #self.m_addRightGrid = 0   # 右边增加的格子
        #self.m_terGridSize = 140  # 战斗地形格子大小
        self.m_bJustXml = False     # 仅仅导出 xml 配置文件，资源不再打包
        
        #self.m_thumbnailsWidth = 32  # 缩略图宽度
        #self.m_thumbnailsHeight = 32  # 缩略图高度
        self.m_thumbnailsscale = 20 # 图像缩放比例
        self.m_thumbnailsquality = 80 # 缩略图 imagemagic 压缩质量
        self.m_thumbnailsFolderName = 'tthumbnails'  # 缩略图图片所在的目录
        
        # 每一个包中 floor 的个数
        self.m_floorperpack = 4
        
        # 生成的图像大小配置文件句柄
        self.m_handleImageWH = None
        self.m_strImageWHFileName = 'Config/ImageWH.txt'
        self.m_firImage = True     # 是否是第一行配置
        
    # 当前裁剪图片的恩见完整路径
    def curSrcfileDir(self):
        return self.m_srcRootPath + '/' + self.m_curSrcFile
    
    #当前裁剪后图片完整的名字
    def curDestFileDir(self):
        #dotidx = self.m_curSrcFile.find('.')
        #srcfilenamenoext = self.m_curSrcFile
        #if dotidx != -1:
            #srcfilenamenoext = self.m_curSrcFile[0:dotidx]
        
        return self.m_destRootPath + '/' + self.m_srcFolder2DestFolderMap[self.m_curSrcFile].m_tplFileName + '/' + self.m_destTplFileName
    
    #当前裁剪图片裁剪后的目录
    def curDestFolderName(self):
        #dotidx = self.m_curSrcFile.find('.')
        #srcfilenamenoext = self.m_curSrcFile
        #if dotidx != -1:
            #srcfilenamenoext = self.m_curSrcFile[0:dotidx]
        return self.m_destRootPath + '/' + self.m_srcFolder2DestFolderMap[self.m_curSrcFile].m_tplFileName
    
    # 当前缩略图文件完整路径加名字
    def curThumbnailsFileName(self):
        return os.path.join(self.m_destRootPath, self.m_thumbnailsFolderName, 'ttb' + self.m_srcFolder2DestFolderMap[self.m_curSrcFile].m_tplFileName[1:] + '.jpg')

'''
'''
class TerrainCrop(object):
    '''
    crop all terrain
    '''
    @staticmethod
    def terraincrop():
        #allfiles = os.listdir(ParamInfo.pInstance.m_srcRootPath)
        #for filename in allfiles:
        #    ParamInfo.pInstance.m_curSrcFile = filename
        #    CmdLine.execOneCrop()
        #创建目标文件夹，如果之前存在，就删除，如果不能删除，将会出错
        if os.path.exists(ParamInfo.pInstance.curDestFolderName()):
            shutil.rmtree(ParamInfo.pInstance.curDestFolderName(), )
        os.makedirs(ParamInfo.pInstance.curDestFolderName())
        CmdLine.execOneCrop()
    
    '''
    更改剪切后图片的名字，进行排序
    '''
    @staticmethod
    def terrainRename():
        #如果之前有操作过，结果里面的文件已经被修改过，就有可能出现错误
        allfiles = os.listdir(ParamInfo.pInstance.curDestFolderName())
        for filename in allfiles:
            dotdix = filename.find('.')
            extname = filename[dotdix:]
            destname = filename[5:dotdix]
            destname = str(int(destname) + 10000)
            os.rename(ParamInfo.pInstance.curDestFolderName() + '/' + filename, ParamInfo.pInstance.curDestFolderName() + '/' + destname + extname)

    '''
    生成地形材质定义文件
    '''    
    @staticmethod
    def terrainTplXml():
        nobgpic = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_nobgpic
        #输出一个地形文件 %1 地形材质文件名字 %2 是地形宽度 %3 是地形高度    
        #计算原始图片大小，进行配置文件的输出
        CmdLine.execIdentify()
        
        oneparam = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_tplFileName
        twoparam = ParamInfo.pInstance.m_curSrcWidth
        threeparam = ParamInfo.pInstance.m_curSrcHeight
        
        base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName
        filename = oneparam + '.xml'
        
        xcnt = int(twoparam / ParamInfo.pInstance.m_cropWidth)
        ycnt = int(threeparam / ParamInfo.pInstance.m_cropHeight)
        
        xrem = int(twoparam % ParamInfo.pInstance.m_cropWidth)
        yrem = int(threeparam % ParamInfo.pInstance.m_cropHeight)
        
        filehandle = open(base_dir + '/' + filename, 'w')
        
        if xrem != 0:
            xcnt += 1

        if yrem != 0:
            ycnt += 1

        # bug 不能再减 1 ，range参数是指总共个数
        #xcnt -= 1
        #ycnt -= 1
        
        #图片的索引    
        picidx = 0
        #包的索引   
        packidx=0
        #包中图片索引 0 1 2 3 
        packpicidx=0
        #每一个包图片数  
        #piccntperone=4
        piccntperone = ParamInfo.pInstance.m_floorperpack
        
        filehandle.write('<definitions>\n')
        
        #每一个资源包四个图片，都是横着的
        #第一级遍历   
        for y in range(ycnt):
            #第二级遍历 
            for x in range(xcnt):
                if not nobgpic:
                    filehandle.write('    <materialDefinition name=\"' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '\" type=\"tile\" media="' + oneparam + '_' + str(packidx) + '.swf\">\n')
                    #filehandle.write('        <diffuse>art.scene.t' + str(packpicidx) + '</diffuse>\n')
                    filehandle.write('        <diffuse>art.scene.' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '</diffuse>\n')
                else:
                    filehandle.write('    <materialDefinition name=\"' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '\" type=\"tile\" media=\"\">\n')
                filehandle.write('    </materialDefinition>\n')
                
                #如果 picidx == 0 就不处理了 
                packpicidx += 1
                picidx += 1
                #remainder= picidx % piccntperone
                #不是第一张图片
                if picidx != 1:
                    #if remainder == 0:  # 下一个元素如果是一个包的开始，如果既是新的包的开始，也是新的行的开始，也走这里
                    if packpicidx == piccntperone:  # 下一个元素如果是一个包的开始，如果既是新的包的开始，也是新的行的开始，也走这里
                        packidx += 1
                        packpicidx = 0
                        #输出一个空行
                        if y == ycnt - 1:
                            if x != xcnt - 1:
                                filehandle.write('\n')
                        else:
                            filehandle.write('\n')
                    elif x == xcnt - 1:     # 下一个是是边界
                        packidx += 1
                        packpicidx = 0
                        #输出一个空行
                        if y != ycnt - 1:
                            filehandle.write('\n')

        filehandle.write('</definitions>')
        
        filehandle.close()
        
    '''
    生成地形材质打包文件
    '''    
    @staticmethod
    def terrainTplBatXml():
        tplname = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_tplFileName
        base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName
        
        #tplswfpath = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName
        batxmlpath = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName
        
        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file', '%s\\%s.xml' % (base_dir, tplname))
        byteArray.setAttribute('class', 'art.cfg.%s' % tplname)
        
        doc.appendChild(root)
        root.appendChild(byteArray)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\x%s' % (batxmlpath, tplname)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        swfName = 'x%s.swf' % (tplname)
        '''根据生成的xml打包as3用的xml成最终的swf包'''
        ParamInfo.pInstance.m_swiftFullXmlFile = xmlFullName
        ParamInfo.pInstance.m_swiftFullSwcFile = xmlFullName
        CmdLine.execSwift()
        CmdLine.exec7z()

        open('%s\\%s' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName, swfName), 'wb').write(open('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName), 'rb').read())
        os.remove('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName))
        os.remove('%s.swc' % xmlFullName)
        print ('打第 xml包 %s 完成' % swfName)

    '''
    @brief 阻挡点 swf 文件
    '''
    @staticmethod
    def stopPtBatXml():
        stopptname = ParamInfo.pInstance.m_srcRootPath + '/' + ParamInfo.pInstance.m_curSrcFile.split('.')[0] + '.mps' # 阻挡点文件名字
        if os.path.exists(stopptname):
            if os.path.isfile(stopptname):
                ParamInfo.pInstance.m_bStopPt = True
                # 生成打包的 xml 文件
                with open(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName + '/' + 's' + ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_terFileName + '.xml', 'w', encoding = 'utf8') as fHandle:
                    fHandle.write('<?xml version=\"1.0\" encoding=\"utf-8\"?>\n')
                    fHandle.write('<lib allowDomain=\"*\">\n')
                    fHandle.write('<bytearray file=\"' + stopptname + '\" class=\"art.cfg.' + 's' + ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_terFileName + '\"/>\n')
                    fHandle.write('</lib>')
                    fHandle.close()

        if ParamInfo.pInstance.m_bStopPt:
            scenename = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_terFileName
            base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName
        
            '''生成的xml写入文件'''
            xmlFullName = '%s\\s%s' % (base_dir, scenename)
    
            swfName = 's%s.swf' % (scenename)
            '''根据生成的xml打包as3用的xml成最终的swf包'''
            ParamInfo.pInstance.m_swiftFullXmlFile = xmlFullName
            ParamInfo.pInstance.m_swiftFullSwcFile = xmlFullName
            CmdLine.execSwift()
            CmdLine.exec7z()
    
            open('%s\\%s' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName, swfName), 'wb').write(open('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName), 'rb').read())
            os.remove('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName))
            os.remove('%s.swc' % xmlFullName)
            print ('打第 xml包 %s 完成' % swfName)

    '''
    生成地形定义文件
    '''    
    @staticmethod
    def terrainXml():
        #输出一个地形文件 %1 地形材质文件名字  %2 场景配置文件名字  %3 是地形宽度 %4 是地形高度    
        base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName
        oneparam = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_tplFileName
        twoparam = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_terFileName
        bfog = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_fog
        nobgpic = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_nobgpic
        
        threeparam = ParamInfo.pInstance.m_curSrcWidth
        fourparam = ParamInfo.pInstance.m_curSrcHeight
        
        #地形一半宽度
        halfwidth = int(threeparam/2)
        
        filename = twoparam + '.xml'
        
        xcnt = int(threeparam / ParamInfo.pInstance.m_cropWidth)
        ycnt = int(fourparam / ParamInfo.pInstance.m_cropHeight)
        
        xrem = int(threeparam % ParamInfo.pInstance.m_cropWidth)
        yrem = int(fourparam % ParamInfo.pInstance.m_cropHeight)
        
        if xrem != 0:
            xcnt += 1

        if yrem != 0:
            ycnt += 1

        # bug 不能减去 1 ，因为 range 参数指的是总的个数
        #xcnt -= 1
        #ycnt -= 1
        
        # 战斗地图特殊处理添加的变量，前面偏移大小
        xoff = 0
        fightpackidx = 5000
        fightpackpicidx = 0
        
        leftaddgridcnt = 0;
        rightaddgridcnt = 0;
        
        # 战斗地形需要前面和后面都添加 3 个格子
        if ParamInfo.pInstance.m_bfight:
            #xoff = ParamInfo.pInstance.m_addRightGrid * ParamInfo.pInstance.m_terGridSize
            xoff = halfwidth
            rightaddgridcnt = int(xoff/ParamInfo.pInstance.m_cropWidth)
            if xoff%ParamInfo.pInstance.m_cropWidth:
                rightaddgridcnt += 1
                
            #xoff = ParamInfo.pInstance.m_addLeftGrid * ParamInfo.pInstance.m_terGridSize
            xoff = halfwidth
            leftaddgridcnt = int(xoff/ParamInfo.pInstance.m_cropWidth)
            if xoff%ParamInfo.pInstance.m_cropWidth:
                leftaddgridcnt += 1
            
            xoff = leftaddgridcnt * ParamInfo.pInstance.m_cropWidth
            
        
        xpos = 0
        ypos = 0
        
        #图片的索引，全局计数的图片索引
        picidx = 0
        #包的索引   
        packidx = 0
        #包中图片索引 0 1 2 3 
        packpicidx = 0
        #每一个包图片数，现在这个从配置文件读取，如果到结尾不够 8 个，也从新的包开始
        #piccntperone = 4
        piccntperone = ParamInfo.pInstance.m_floorperpack
        filehandle = open(base_dir + '/' + filename, 'w')
        
        if bfog:
            filehandle.write('<scene gridsize=\"' + str(ParamInfo.pInstance.m_gridWidth) + '\" levelsize=\"20\" cubeSize=\"2000\" floorwidth=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" floordepth=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" fog=\"true\" isometric=\"2\" xoff=\"' + str(xoff) + '\" yoff=\"0\" pixelwidth=\"' + str(threeparam) + '\" pixelheight=\"' + str(fourparam) + '\" version=\"1\">\n')
        else:
            filehandle.write('<scene gridsize=\"' + str(ParamInfo.pInstance.m_gridWidth) + '\" levelsize=\"20\" cubeSize=\"2000\" floorwidth=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" floordepth=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" fog=\"false\" isometric=\"2\" xoff=\"' + str(xoff) + '\" yoff=\"0\" pixelwidth=\"' + str(threeparam) + '\" pixelheight=\"' + str(fourparam) + '\" version=\"1\">\n')
        filehandle.write('    <head>\n')
        if not nobgpic:
            filehandle.write('        <definitions src=\"ttb' + oneparam[1:] + '\"/>\n')    # 地形缩略图
            filehandle.write('        <definitions src=\"x' + oneparam + '\"/>\n')
        filehandle.write('        <definitions src=\"xct0\"/>\n')
        filehandle.write('        <definitions src=\"xet0\"/>\n')
        
        if ParamInfo.pInstance.m_bStopPt:
            filehandle.write('        <definitions src=\"s' + twoparam + '\"/>\n')
            
        filehandle.write('        <light id=\"Global light\" color=\"#FFFFFF\" intensity=\"100\"/>\n')
        filehandle.write('    </head>\n')
        filehandle.write('\n')
        filehandle.write('    <body>\n')
        filehandle.write('        <fog id=\"f1\" radius=\"300\" blurx=\"15\" blury=\"15\" border=\"50\"/>\n')
        
        #每一个资源包四个图片，都是横着的
        #第一级遍历   
        for y in range(ycnt):
            #第二级遍历 
            xpos = 0
            
            # 战斗地形特殊处理
            if ParamInfo.pInstance.m_bfight:
                fightpackpicidx = 0
                for leftx in range(leftaddgridcnt):
                    filehandle.write('        <floor id=\"' + oneparam + '_' + str(fightpackidx) + '_' + str(fightpackpicidx) + '\" src=\"' + '\" width=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" height=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" x=\"' + str(xpos + leftx * ParamInfo.pInstance.m_cropWidth) + '\" y=\"' + str(ypos) + '\"/>\n')
                    fightpackpicidx += 1
                fightpackidx += 1
                
                filehandle.write('\n')      # 添加间隔

            # 新的一行必然从新开始一个资源包
            for x in range(xcnt):
                if not nobgpic:
                    filehandle.write('        <floor id=\"' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '\" src=\"' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '\" width=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" height=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" x=\"' + str(xpos + xoff) + '\" y=\"' + str(ypos) + '\"/>\n')
                else:
                    filehandle.write('        <floor id=\"' + oneparam + '_' + str(packidx) + '_' + str(packpicidx) + '\" src=\"\" width=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" height=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" x=\"' + str(xpos + xoff) + '\" y=\"' + str(ypos) + '\"/>\n')
                
                xpos += ParamInfo.pInstance.m_cropWidth
                
                #如果 picidx == 0 就不处理了 
                packpicidx += 1
                picidx += 1
                #remainder= picidx % piccntperone
                if picidx != 1:
                    #if remainder == 0:  # 下一个是新的包开始，如果既是新的包的开始，又是新的行，也走这里，bug 这样判断如果新行中可能不足 piccntperone 个，但是也是满足一个包的条件
                    if packpicidx == piccntperone:  # 下一个是新的包开始，如果既是新的包的开始，又是新的行，也走这里
                        packidx += 1
                        packpicidx = 0
                        #输出一个空行
                        if y == ycnt - 1:
                            if x != xcnt - 1:
                                filehandle.write('\n')
                        else:
                            filehandle.write('\n')
                    elif x == xcnt - 1:     # 下一个是是边界
                        packidx += 1
                        packpicidx = 0
                        #输出一个空行
                        if y != ycnt - 1:
                            filehandle.write('\n')

            # 战斗地形特殊处理
            if ParamInfo.pInstance.m_bfight:
                fightpackpicidx = 0
                for rightx in range(rightaddgridcnt):
                    filehandle.write('        <floor id=\"' + oneparam + '_' + str(fightpackidx) + '_' + str(fightpackpicidx) + '\" src=\"' + '\" width=\"' + str(ParamInfo.pInstance.m_cropWidth) + '\" height=\"' + str(ParamInfo.pInstance.m_cropHeight) + '\" x=\"' + str(xpos + xoff + rightx * ParamInfo.pInstance.m_cropWidth) + '\" y=\"' + str(ypos) + '\"/>\n')
                    fightpackpicidx += 1
                fightpackidx += 1
                # 战斗场景输出换行
                if y != ycnt - 1:
                    filehandle.write('\n')

            ypos += ParamInfo.pInstance.m_cropHeight
        
        filehandle.write('    </body>\n')
        filehandle.write('</scene>')
        
        filehandle.close()

    '''
    生成地形场景打包文件
    '''    
    @staticmethod
    def terrainBatXml():
        scenename = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_terFileName
        srcxmlpath = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName
        base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName
        
        #sceneswfpath = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName

        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file', '%s\\%s.xml' % (srcxmlpath, scenename))
        byteArray.setAttribute('class', 'art.cfg.t%s' % scenename)
        
        doc.appendChild(root)
        root.appendChild(byteArray)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\x%s' % (base_dir, scenename)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        swfName = 'x%s.swf' % (scenename)
        '''根据生成的xml打包as3用的xml成最终的swf包'''
        ParamInfo.pInstance.m_swiftFullXmlFile = xmlFullName
        ParamInfo.pInstance.m_swiftFullSwcFile = xmlFullName
        CmdLine.execSwift()
        CmdLine.exec7z()

        open('%s\\%s' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName, swfName), 'wb').write(open('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName), 'rb').read())
        os.remove('%s\\library.swf' % (ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName))
        os.remove('%s.swc' % xmlFullName)
        print ('打第 xml包 %s 完成' % swfName)
        
    '''
    生成地形定义文件
    '''    
    @staticmethod
    def terrainMakeSwiftXml():
        base_dir = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName
        picpath = ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_tplFileName
        prefix = 'art.scene.t'
        
        #alldir = os.listdir(ParamInfo.pInstance.m_destRootPath)
        
        xmlfilehandle = None
        batfilehandle = None
        
        #直接赋值遍历的目录
        i = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_tplFileName
        #for i in alldir:
        #每一个包图片数  
        piccntperone = 4
        lessone = piccntperone - 1
        #当前遍历的文件数量，总共 total - 1 个，从 0 开始         
        curidx = 0
        #包中图片索引 0 1 2 3 
        packpicidx = 0
    
        #遍历这个文件，输出配置文件
        allfiles = os.listdir(picpath)
        for j in allfiles:
            remainder= curidx % piccntperone

            #向新文件中输出内容
            if remainder == 0:
                packpicidx = 0
                divisor = int(curidx / piccntperone)
                
                #如果目录不存在，先创建目录
                if not os.path.exists(base_dir + '/' + i):
                    os.makedirs(base_dir + '/' + i)
                filename = base_dir + '/' + i + '/' + i + '_' + str(divisor) + '.xml'
                #关闭之前的文件
                #if xmlfilehandle:
                #    xmlfilehandle.close()
                xmlfilehandle = open(filename, 'w')
                
                xmlfilehandle.write('<?xml version=\"1.0\" encoding=\"utf-8\"?>\n')
                xmlfilehandle.write('<lib allowDomain="*">\n')
                xmlfilehandle.write('    <bitmapdata file=\"' + picpath + '/' + j + '\" ' + 'class=\"' + prefix + str(packpicidx) + '\"/>\n')
                
                #输出 bat 文件
                filename = base_dir + '/' + i + '/' + i + '_' + str(divisor) + '.bat'
                #if batfilehandle:
                #    batfilehandle.close()
                batfilehandle = open(filename, 'w')
                batfilehandle.write('@echo on\n')
                
                batfilehandle.write('set base_dir=%~dp0\n')
                batfilehandle.write('%base_dir:~0,2%\n')
                batfilehandle.write('echo %base_dir%\n')
    
                batfilehandle.write('pushd %base_dir%\n')
    
                batfilehandle.write('if exist %swcterpath%\%~n0.swc del %swcterpath%\%~n0.swc\n')
    
                batfilehandle.write('pushd %respath%\n')
                batfilehandle.write('java -jar %swiftpath% xml2lib %base_dir%\%~n0.xml %%swcterpath%\%~n0.swc\n')
                batfilehandle.write('popd\n')
    
                batfilehandle.write('if exist %%swcterpath%%\library.swf del %%swcterpath%%\library.swf\n')
    
                batfilehandle.write('%z7% e %swcterpath%\%~n0.swc -o%swcterpath% *.swf\n')
    
                batfilehandle.write('if exist %swfterpath%\%~n0.swf del %swfterpath%\%~n0.swf\n')
    
                batfilehandle.write('copy %swcterpath%\library.swf %swfterpath%\%~n0.swf\n')
    
                batfilehandle.write('popd')
                batfilehandle.close()
            else:
                packpicidx += 1
                xmlfilehandle.write('    <bitmapdata file=\"' + picpath + '/' + j + '\" class=\"' + prefix + str(packpicidx) + '\"/>\n')
                if remainder == lessone:
                    #输出结尾符号
                    xmlfilehandle.write('</lib>')
                    xmlfilehandle.close()

            curidx += 1

        #最后加上结尾符号 
        if remainder != lessone:
            xmlfilehandle.write('</lib>')
            xmlfilehandle.close()

    '''
    生成地图缩略图
    '''
    @staticmethod
    def buildThumbnails():
        CmdLine.exeScale()
        

'''
main entry
'''        
def startPackTer():
    #实例化全局变量
    ParamInfo.instance();
    
    #初始化自己的参数
    ParamInfo.pInstance.m_srcRootPath = Config.instance().m_terCfg.srcrootdir
    ParamInfo.pInstance.m_destRootPath = Config.instance().m_terCfg.destrootdir
    ParamInfo.pInstance.m_cropWidth = Config.instance().m_terCfg.m_cropWidth
    ParamInfo.pInstance.m_cropHeight = Config.instance().m_terCfg.m_cropHeight
    ParamInfo.pInstance.m_gridWidth = Config.instance().m_terCfg.m_gridWidth
    ParamInfo.pInstance.m_gridHeight = Config.instance().m_terCfg.m_gridHeight
    ParamInfo.pInstance.m_srcFolder2DestFolderMap = Config.instance().m_terCfg.srcn2destn
    
    ParamInfo.pInstance.m_convCmd = Config.instance().m_commonCfg.CONVERTCMD
    ParamInfo.pInstance.m_identCmd = Config.instance().m_commonCfg.CONVERTIDENT
    ParamInfo.pInstance.m_7z = Config.instance().m_commonCfg.z7z
    ParamInfo.pInstance.m_swift = Config.instance().m_commonCfg.jar
    
    # 战斗地图特殊处理
    ParamInfo.pInstance.m_bfight = Config.instance().m_terCfg.m_bfight
    #ParamInfo.pInstance.m_addLeftGrid = Config.instance().m_terCfg.m_addLeftGrid
    #ParamInfo.pInstance.m_addRightGrid = Config.instance().m_terCfg.m_addRightGrid
    #ParamInfo.pInstance.m_terGridSize = Config.instance().m_terCfg.m_fightGridSize
    
    ParamInfo.pInstance.m_bJustXml = Config.instance().m_terCfg.m_bJustXml
    #ParamInfo.pInstance.m_thumbnailsWidth = Config.instance().m_terCfg.m_thumbnailsWidth
    #ParamInfo.pInstance.m_thumbnailsHeight = Config.instance().m_terCfg.m_thumbnailsHeight
    ParamInfo.pInstance.m_thumbnailsscale = Config.instance().m_terCfg.m_thumbnailsscale
    ParamInfo.pInstance.m_thumbnailsquality = Config.instance().m_terCfg.m_thumbnailsquality
    ParamInfo.pInstance.m_floorperpack = Config.instance().m_terCfg.m_floorperpack
    
    ParamInfo.pInstance.m_strImageWHFileName = Config.instance().m_terCfg.getImageWHFileName();
    
    #初始化目录
    if not os.path.exists(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName):
        os.makedirs(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.xmlFolderName)
        
    if not os.path.exists(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName):
        os.makedirs(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.XmlSwfFolderName)
        
    if not os.path.exists(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName):
        os.makedirs(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.batXmlFolderName)
        
    if not os.path.exists(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.m_thumbnailsFolderName):
        os.makedirs(ParamInfo.pInstance.m_destRootPath + '/' + ParamInfo.pInstance.m_thumbnailsFolderName)
    
    # 打开生成的图像配置文件
    ParamInfo.pInstance.m_handleImageWH = open(ParamInfo.pInstance.m_strImageWHFileName, 'wt', encoding='utf8')
    
    ParamInfo.pInstance.m_firImage = True
    #遍历目录裁剪
    #allfiles = os.listdir(ParamInfo.pInstance.m_srcRootPath)
    for (k, v) in ParamInfo.pInstance.m_srcFolder2DestFolderMap.items():
        #dotidx = filename.find('.')
        #srcfilenamenoext = filename
        #srcfilenameext = ''
        #if dotidx != -1:
            #srcfilenamenoext = filename[0:dotidx]
            #srcfilenameext = filename[dotidx + 1:]
        if os.path.isfile(ParamInfo.pInstance.m_srcRootPath + '/' + k):
            ParamInfo.pInstance.m_bStopPt = False
            ParamInfo.pInstance.m_curSrcFile = k
            
            nobgpic = ParamInfo.pInstance.m_srcFolder2DestFolderMap[ParamInfo.pInstance.m_curSrcFile].m_nobgpic
            
            if not ParamInfo.pInstance.m_bJustXml and not nobgpic:
                TerrainCrop.terraincrop()       #切割地图
                TerrainCrop.terrainRename()     #重命名切割后的地图片，进行排序

            TerrainCrop.terrainTplXml()     #生成地形材质配置文件，虽然没有图片的 nobgpic 的地图不需要这些配置文件，但是这个函数中生成一些配置数据，后面要用到的
            TerrainCrop.terrainTplBatXml()  #生成地形材质打包文件
            
            if not nobgpic:
                TerrainCrop.stopPtBatXml()  #阻挡点生成
            
            TerrainCrop.terrainXml()        #生成地形场景配置文件
            TerrainCrop.terrainBatXml()     #生成地形场景打包文件
            #TerrainCrop.terrainMakeSwiftXml()   #生成地形图片打包文件
            if not nobgpic:
                TerrainCrop.buildThumbnails()       #生成地形缩略图
            
            # 输出宽度和高度
            if ParamInfo.pInstance.m_firImage:
                outstr = v.m_tplFileName +'?w=' + str(ParamInfo.pInstance.m_curSrcWidth) + '?h=' + str(ParamInfo.pInstance.m_curSrcHeight) + '?cropw=' + str(ParamInfo.pInstance.m_cropWidth) + '?croph=' +str(ParamInfo.pInstance.m_cropHeight)
                ParamInfo.pInstance.m_firImage = False
            else:
                outstr = '\n' + v.m_tplFileName +'?w=' + str(ParamInfo.pInstance.m_curSrcWidth) + '?h=' + str(ParamInfo.pInstance.m_curSrcHeight) + '?cropw=' + str(ParamInfo.pInstance.m_cropWidth) + '?croph=' +str(ParamInfo.pInstance.m_cropHeight)
            ParamInfo.pInstance.m_handleImageWH.write(outstr)
    
    # 关闭文件
    ParamInfo.pInstance.m_handleImageWH.close() 
