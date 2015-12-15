# -*- coding: utf-8 -*-

#from subprocess import Popen, PIPE
import subprocess
import os
#import time;
from xml.dom.minidom import Document
#import string

#import sys  
# 获得系统默认编码格式  
#sysCharType = sys.getfilesystemencoding()

import traceback
import glob
import sys
import shutil

from Pack.Frame.Logger import Logger
from Pack.Frame.Config import Config

'''
特效图片资源打包脚本
'''

'''定义一个可以存放图片偏移量和尺寸的类型'''
class PngInfo:
    def __init__(self, x, y, width, height, package):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.package = package
       
'''根据图片裁剪后信息生成xml配置文件'''      
class PngXml:
    def __init__(self, pngCut, genxmldir, xmlName, genNewPngDir):
        self.pngCut = pngCut
        self.genxmldir = genxmldir
        self.xmlName = xmlName
        self.genNewPngDir = genNewPngDir
    
    def createXml(self):
        '''生成供as3代码读取的xml配置文件开始'''
        pngInfoList = self.pngCut.getCutInfo()
        packageInfoList = self.pngCut.getPackageInfo(self.xmlName)
        if(len(packageInfoList) == 0):
            Logger.instance().loggerESubPro("特效模型: " + self.xmlName + ' 生成xml文件失败，获取裁剪好的图片为空!')
            return
        doc = Document()
        root = doc.createElement('insDef')
        root.setAttribute('displayModle', '3')
        root.setAttribute('name', self.xmlName)
        root.setAttribute('overwrite', '1')
        root.setAttribute('type', '3')
       
        disPlayModel = doc.createElement('displayModel')
        disPlayModel.setAttribute('act', '0')
        disPlayModel.setAttribute('xcount', '%s' % len(pngInfoList))
        disPlayModel.setAttribute('framerate', '%s' % len(pngInfoList))
        disPlayModel.setAttribute('repeat', 'false')
       
        sprite = doc.createElement('sprite')
        sprite.setAttribute('angle', '0')
        for png, package in zip(pngInfoList, packageInfoList):
            #Logger.instance().loggerESubPro ('x=%s y=%s width=%s height=%s mediaPaht=%s' % \
            #(png.x, png.y, png.width, png.height, package))
            mapdata = doc.createElement('mapdata')
            mapdata.setAttribute('xorig', '%s' % png.x)
            mapdata.setAttribute('yorig', '%s' % png.y)
            mapdata.setAttribute('width', png.width)
            mapdata.setAttribute('height', png.height)
            mapdata.setAttribute('mediaPath', package)
            sprite.appendChild(mapdata)
       
        doc.appendChild(root)
        root.appendChild(disPlayModel)
        disPlayModel.appendChild(sprite)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\%s' % (self.genxmldir, self.xmlName)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        
    def createPackageXml(self, effectXmlSwf):
        '''生成打包资源的xml配置文件开始'''
        
        # 检测如果配置文件没有生成，就直接退出函数
        xmlFullName = '%s\\%s.xml' % (self.genxmldir, self.xmlName)
        if not os.path.isfile(xmlFullName):
            return
       
        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file', '%s\\%s.xml' % \
                               (self.genxmldir, self.xmlName ))
        byteArray.setAttribute('class', 'art.cfg.%s' % self.xmlName)
        
        doc.appendChild(root)
        root.appendChild(byteArray)
       
        '''生成的xml写入文件'''
        xmlFullName = '%s\\x%s' % (self.genNewPngDir, self.xmlName)
        fHandle = open('%s.xml' % xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()

        swfName = 'x%s.swf' % (self.xmlName)
        '''根据生成的xml打包as3用的xml成最终的swf包'''
        #os.popen('java -jar %s xml2lib %s.xml %s.swc' % (jar, xmlFullName, xmlFullName)).read()
        handle = subprocess.Popen('java -jar %s xml2lib %s.xml %s.swc' % (jar, xmlFullName, xmlFullName), shell=True, stdout=subprocess.PIPE)
        handle.wait()
        cmd = '"%s" e -y %s.swc -o%s *.swf' % (z7z, xmlFullName, self.genNewPngDir)
        #os.popen(cmd).read()
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
        open('%s\\%s' % (effectXmlSwf, swfName), 'wb').write(open('%s\\library.swf' % self.genNewPngDir, 'rb').read())
        os.remove('%s\\library.swf' % self.genNewPngDir)
        os.remove('%s.swc' % xmlFullName)
        #os.remove('%s.xml' % xmlFullName)
        Logger.instance().loggerESubPro ('打第 xml包 %s 完成' % swfName)
        
    def createBat(self):
        '''生成批处理文件,直接 输出'''
        txt = open('%s\\bat.example' % self.genNewPngDir, 'r').read()
        fHandle = open('%s\\x%s.bat' % (self.genNewPngDir, self.xmlName), 'w')
        fHandle.write(txt)
        fHandle.close()
    def createClass2Png(self, effectSwf):
        '''生成as3类对应的图片资源xml配置文件和对应批处理打包文件'''
        index = 0
        nameIndex = 0
        for pngList in self.pngCut.getPackage(self.xmlName):
           
            '''生成xml'''
            doc = Document()
            root = doc.createElement('lib')
            root.setAttribute('allowDomain', '*')
            
            for png in pngList:
                byteArray = doc.createElement('bitmapdata')
                
                #pngName = png.split('\\')[-1].split('.')[0]\
                #         .split('_')[1].lstrip('0')
                #if(pngName == ''):
                #   pngName = '0'
                
                byteArray.setAttribute('file',  png)
                if(bcompress):
                    byteArray.setAttribute('compression', compress)
                    byteArray.setAttribute('quality', '%s' % quality)
                byteArray.setAttribute('class', 'art.scene.e0%s' % nameIndex)
                root.appendChild(byteArray)
                nameIndex += 1
            doc.appendChild(root)

            '''拼接对应文件名称'''
            fileName = '%s\\%s_0_0_%s' % (self.genNewPngDir, self.xmlName, index)
            '''生成的xml写入文件'''
            
            fHandle = open('%s.xml' % fileName, 'w')
            fHandle.write(str(doc.toprettyxml(indent = "  ", encoding="UTF-8"), encoding='utf-8'))
            fHandle.close()
            swfName = '%s_0_0_%s.swf' % (self.xmlName, index)
            '''根据生成的xml打包成最终的swf包'''
            #os.popen('java -jar %s xml2lib %s.xml %s.swc' % (jar, fileName, fileName)).read()
            handle=subprocess.Popen('java -jar %s xml2lib %s.xml %s.swc' % (jar, fileName, fileName), shell=True, stdout=subprocess.PIPE)
            handle.wait();
            cmd= '"%s" e -y %s.swc -o%s *.swf' % (z7z, fileName, self.genNewPngDir)
            #os.popen(cmd).read()
            handle=subprocess.Popen(cmd)
            handle.wait();
            open('%s\\%s' % (effectSwf, swfName), 'wb').write(open('%s\\library.swf' % self.genNewPngDir, 'rb').read())
            os.remove('%s\\library.swf' % self.genNewPngDir)
            os.remove('%s.swc' % fileName)
            #os.remove('%s.xml' % fileName)
            Logger.instance().loggerESubPro ('打第 %d 包 %s 完成' % (index, swfName))
            
            index = index + 1
      
       
'''裁剪图片处理'''
class PngCut:
    def __init__(self, dirname, genNewPngDir):
        self.dirname = dirname
        self.genNewPngDir = genNewPngDir
    def __joinPath(self, dirname):
        pathList = []
        ls=os.listdir(dirname)
        ls.sort()
        for filename in ls:
            '''将路径和文件名拼接'''
            temp = os.path.join('%s\\%s' % (dirname, filename))
            pathList.append(temp)
        
        return pathList
    
    # 枚举图片文件用这个
    def __joinFiles(self, dirname):
        pathList = []
        os.chdir(dirname)
        #ls = glob.glob('*.png')
        #ls = glob.glob('*.jpg')
        ls = glob.glob('*.%s' % extName)
        ls.sort()
        for filename in ls:
            '''将路径和文件名拼接'''
            temp = os.path.join('%s\\%s' % (dirname, filename))
            pathList.append(temp)
        return pathList
        
    def getCutInfo(self):
        pngInfoList = []
       
        for path in self.__joinFiles(self.dirname):
            '''调用外部程序执行拼接的cmd'''
            #cmd = '%s %s -trim info:-' % (CONVERTCMD, path)
            if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale != 100:
                cmd = '%s %s -filter Lanczos -resize %s%% -trim info:-' % (CONVERTCMD, path, Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale)
            else:
                cmd = '%s %s -trim info:-' % (CONVERTCMD, path)
            #out = os.popen(cmd).read()
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            #out = handle.stdout.read().decode(sysCharType).encode('utf-8')
            out = handle.stdout.read()
            out = out.decode('utf-8')
            outList = out.split()
            
            #如果颜色值是 0x00000000 ，那么返回的 xyList 中是 - 号
            addidx = outList[3].find('+')
            
            if addidx != -1:
                xyList = outList[3].split('+')
            else:
                xyList = outList[3].split('-')
            whList = outList[2].split('x')
            # 如果全是一个透明的颜色，那么这个地方计算是有问题的，但是透明是看不到的，计算错误页没问题
            x = int(int(xyList[1]) - int(xyList[0].split('x')[0])/2)
            y = int(int(xyList[2]) - int(xyList[0].split('x')[1])/2)
            
            # 如果缩放，还需要修正左上角位置和宽度高度信息
            # bug: 这样会累积误差的
            #if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale != 100:
            #    x = int(x * float(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale)/100)
            #    y = int(y * float(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale)/100)
            #    whList[0] = str(int(float(whList[0]) * float(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale)/100))
            #    whList[1] = str(int(float(whList[1]) * float(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale)/100))
            #Logger.instance().loggerESubPro 'x: %d, y: %d' % (x, y)
            #Logger.instance().loggerESubPro ('x=%s, y=%s width=%s height=%s _x=%d y=%d' %\
            #(xyList[1], xyList[2], whList[0], whList[1], x, y))
          
            pi = PngInfo(x, y, whList[0], whList[1], 0)
            pngInfoList.append(pi)
        return pngInfoList
    def cut(self, xmlName):
        '''创建相应的文件夹'''
        newdir = '%s\\%s\\0' % (self.genNewPngDir.rstrip("\\cut_png"), xmlName)
        if os.path.isdir(newdir):
            Logger.instance().loggerESubPro ('%s 已经存在，可能已裁剪好图片了。' % newdir)
            return
        
        os.makedirs(newdir)
        for path in self.__joinFiles(self.dirname):
            if(packType == 0):
                # 是否需要缩放
                if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale == 100:
                    cmd = '%s -trim +repage -strip -depth 8 %s %s' % (CONVERTCMD, path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
                else:
                    cmd = '%s -filter Lanczos -resize %s%% -trim -strip -depth 8 +repage %s %s' % (CONVERTCMD, str(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale), path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
                    
            elif(packType == 1):
                # 获取切割区域
                if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale == 100:
                    cmd = '%s %s -trim info:-' % (CONVERTCMD, path)
                else:
                    cmd = '%s %s -filter Lanczos -resize %s%% -trim info:-' % (CONVERTCMD, path, str(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale))
                handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
                handle.wait()
                out = handle.stdout.read()
                out = out.decode('utf-8')
                outList = out.split()
                
                #如果颜色值是 0x00000000 ，那么返回的 xyList 中是 - 号
                addidx = outList[3].find('+')
            
                if addidx != -1:
                    xyList = outList[3].split('+')
                else:
                    xyList = outList[3].split('-')

                whList = outList[2].split('x')
                
                if addidx == -1:
                    topx = 0
                    topy = 0
                    
                    botx = 1
                    boty = 1
                else:
                    # 转换到局部空间
                    # 左上角坐标
                    topx = int(xyList[1]) - int(xyList[0].split('x')[0])/2
                    topy = int(xyList[2]) - int(xyList[0].split('x')[1])/2
                    # 右小角坐标
                    botx = topx + int(whList[0])
                    boty = topy + int(whList[1])
                
                minx = 10000
                miny = 10000
                
                # 包围盒子
                if(minx > topx):
                    minx = topx
                if(minx > -topx):
                    minx = topx
                if(minx > botx):
                    minx = botx
                if(minx > -botx):
                    minx = -botx
                    
                if(miny > topy):
                    miny = topy
                if(miny > -topy):
                    miny = topy
                if(miny > boty):
                    miny = boty
                if(miny > -boty):
                    miny = -boty

                if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale == 100:
                    cmd = '%s -crop %sx%s+%s+%s +repage -strip -depth 8 %s %s' % (CONVERTCMD, (-minx) * 2, (-miny) * 2, minx + int(xyList[0].split('x')[0])/2, miny + int(xyList[0].split('x')[1])/2, path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
                else:
                    cmd = '%s -filter Lanczos -resize %s%% -crop %sx%s+%s+%s +repage -strip -depth 8 %s %s' % (CONVERTCMD, str(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale), (-minx) * 2, (-miny) * 2, minx + int(xyList[0].split('x')[0])/2, miny + int(xyList[0].split('x')[1])/2, path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
            elif(packType == 2):
                if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale == 100:
                    cmd = '%s %s -trim info:-' % (CONVERTCMD, path)
                else:
                    cmd = '%s %s -filter Lanczos -resize %s%% -trim info:-' % (CONVERTCMD, path, str(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale))
                handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
                handle.wait()
                out = handle.stdout.read()
                out = out.decode('utf-8')
                outList = out.split()
                
                #如果颜色值是 0x00000000 ，那么返回的 xyList 中是 - 号
                addidx = outList[3].find('+')
            
                if addidx != -1:
                    xyList = outList[3].split('+')
                else:
                    xyList = outList[3].split('-')

                whList = outList[2].split('x')
                
                # 转换到局部空间
                # 左上角坐标
                topx = int(xyList[0].split('x')[0])/2 - packWidth/2
                topy = int(xyList[0].split('x')[1])/2 - packHeight/2

                if Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale == 100:
                    cmd = '%s -crop %sx%s+%s+%s +repage -strip -depth 8 %s %s' % (CONVERTCMD, packWidth, packHeight, topx, topy, path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
                else:
                    cmd = '%s -filter Lanczos -resize %s%% -crop %sx%s+%s+%s +repage -strip -depth 8 %s %s' % (CONVERTCMD, str(Config.instance().m_effCfg.modelparamDic[Config.instance().m_effCfg.m_curkey].m_scale), packWidth, packHeight, topx, topy, path, '%s\\%s' % (newdir,  path.split('\\')[-1]))
            #os.popen(cmd)
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            
            #再无损压缩一下
            if bpngout:
                cmd = "%s %s" % (pngout, '%s\\%s' % (newdir,  path.split('\\')[-1]))
                #handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
                handle = subprocess.Popen(cmd, shell=True)
                handle.wait()
                
            Logger.instance().loggerESubPro ('裁剪图片%s完成' % path)
       
        #for index in range(len(pathList)):
        #   cmd = 'convertim -trim +repage %s %s' % (pathList[index], newPathList[index])
    def getPackageInfo(self, xmlName):
        '''获取每个png图片应该在哪个包里'''
        sizeList = []
        
        pathList = self.__joinPath('%s\\%s\\0' % \
                                   (self.genNewPngDir.rstrip("\\cut_png"), xmlName))
        totalSize = 0
        index = 0
    
        for path in pathList:
            #out = os.popen('%s %s' % (CONVERTIDENT, path)).read()
            cmd = '%s %s %s' % (CONVERTIDENT, '-format "%b"', path)
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            out = handle.stdout.read()
            out = out.decode('utf-8')
            if len(out) == 0:
                Logger.instance().loggerESubPro ('错误 查看裁剪好的图片为空!')
                return sizeList
            
            #size = out.split()[6].rstrip('B').rstrip('K')
            # 注意 out 好像是后面添加了 \r\n ，需要在原有的基础上减去这两个字符串，然后再减去 B
            idx = len(out) - 3
            size = out[0:idx]
            Logger.instance().loggerESubPro (path + " byte: " + size)
            
            #size = float(size)/1024    # 这个地方除以 1024 ，不是 1000
            
            # 添加日志
            #Logger.instance().loggerESubPro (path + ' kbyte: ' + str(size))
            
            #Logger.instance().loggerESubPro('out:%s, size:%s' % (out, size))
            if(totalSize + float(size)) > MAX_SIZE:
                totalSize = 0
                index += 1
            totalSize += float(size)
            mediaPath = '%s_0_0_%u.swf' % (xmlName, index)
            sizeList.append(mediaPath)
        return sizeList
    def getPackage(self, xmlName):
        '''获取每个包里面包含的png图片'''
        pngList = []
        packageList = []
        
        pathList = self.__joinPath('%s\\%s\\0' % (self.genNewPngDir, xmlName))
        totalSize = 0
        #index = 0
        
        for path in pathList:
            #out = os.popen('identify %s' % path).read()
            #handle = subprocess.Popen(('%s %s' % (CONVERTIDENT, path)), shell=True, stdout=subprocess.PIPE)
            cmd = '%s %s %s' % (CONVERTIDENT, '-format "%b"', path)
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait();
            out = handle.stdout.read();
            out = out.decode('utf-8')
            if len(out) == 0:
                Logger.instance().loggerESubPro ('错误 查看裁剪好的图片为空!')
                return packageList
            #size = out.split()[6].split('KB')[0]
            
            # 注意 out 好像是后面添加了 \r\n ，需要在原有的基础上减去这两个字符串，然后再减去 B
            idx = len(out) - 3
            size = out[0:idx]
            Logger.instance().loggerESubPro (path + " byte: " + size)
           
            if(totalSize + float(size)) > MAX_SIZE:
                packageList.append(pngList[:])
                del pngList[:]
                totalSize = 0
                
            totalSize += float(size)
            pngList.append(path)
        
        packageList.append(pngList[:])    
        return packageList
           
           
'''打包模型'''
def modelPack(config):
    '''声明全局变量'''
#     dirname = 'F:\\common\\pack\\eff\\火雨特效'  # 美术给的资源的原始目录
#     genxmldir = 'F:\\common\\pack\eff'  # 生成的给AS3代码读取的xml的目录
#     xmlName = 'e1710'
#     genNewPngDir = 'F:\\common\\pack\\eff\\cut_png' #打包的目录
#     effectSwf = 'F:\\common\\pack\\eff\\effect_swf'  #放打包好的特效swf文件
#     effectXmlSwf = 'F:\\common\\pack\\eff\\effect_xml_swf'  #放打包好的配置swf文件
    
    dirname = config.m_effCfg.dirname  # 美术给的资源的原始目录
    genxmldir = config.m_effCfg.genxmldir  # 生成的给AS3代码读取的xml的目录
    xmlName = config.m_effCfg.xmlName
    genNewPngDir = config.m_effCfg.genNewPngDir #打包的目录
    #effectSwf = config.m_effCfg.effectSwf  #放打包好的特效swf文件
    effectXmlSwf = config.m_effCfg.effectXmlSwf  #放打包好的配置swf文件
    
    pngCut = PngCut(dirname, genNewPngDir)
   
    pngCut.cut(xmlName)
    if(packType == 0):  # 只有 0 的时候才是需要输出 xml 的
        pngXml = PngXml(pngCut, genxmldir, xmlName, genNewPngDir)
        pngXml.createXml()
        pngXml.createPackageXml(effectXmlSwf)
    #pngXml.createBat()
    #pngXml.createClass2Png(effectSwf)

    #Logger.instance().loggerESubPro ('恭喜打包成功！！！！！！')
    #pngCut.getPackage(xmlName)
    
# 打包接口
def startPack(config):
    global MAX_SIZE
    MAX_SIZE = config.m_effCfg.MAX_SIZE * 1024      # 使用字节进行比较
    global CONVERTCMD
    CONVERTCMD = config.m_commonCfg.CONVERTCMD
    global z7z
    z7z= config.m_commonCfg.z7z
    global jar
    jar = config.m_commonCfg.jar
    global bpngout
    bpngout = config.m_effCfg.bpngout
    #bpngout = config.bpngout
    global pngout
    pngout = config.m_commonCfg.pngout
    global bcompress
    bcompress = config.m_effCfg.bcompress #是否压缩
    global quality
    quality = config.m_effCfg.quality  #压缩比率
    global CONVERTIDENT
    CONVERTIDENT=config.m_commonCfg.CONVERTIDENT
    global packType
    packType = config.m_effCfg.packType
    global packWidth
    packWidth = config.m_effCfg.packWidth
    global packHeight
    packHeight = config.m_effCfg.packHeight
    
    global extName
    extName = config.m_effCfg.extName
    
    global compress
    #初始化变量
    if bcompress:
        compress = 'true'
    else:
        compress = 'false'
    
    # 初始化必要目录
    if not os.path.exists(config.m_effCfg.effectSwf):
        os.makedirs(config.m_effCfg.effectSwf)
    if not os.path.exists(config.m_effCfg.effectXmlSwf):
        os.makedirs(config.m_effCfg.effectXmlSwf)
    
    #特效直接从配置文件读取目录遍历，特效目录可能是双层目录
    #modellist = os.listdir(config.m_effCfg.srcrootdir)
    #for model in modellist:
    #    if model in config.m_effCfg.srcn2destn.keys():
    #遍历所有配置文件中的目录
    for (k,v) in config.m_effCfg.srcn2destn.items():
        if os.path.isdir(config.m_effCfg.srcrootdir + '/' + k):
            config.m_effCfg.dirname = config.m_effCfg.srcrootdir + "/"  + k        
            config.m_effCfg.xmlName = v
            config.m_effCfg.m_curkey = k
            try:
                modelPack(config)
                #raise Exception()
            except:
                # 错误输出
                traceback.print_exc()
                sys.stderr.write('model error: ' + config.m_effCfg.dirname + '\n')
                sys.stderr.flush()
                # 删除必要的数据
                if os.path.isdir(config.m_effCfg.destrootdir + '/' + config.m_effCfg.xmlName):
                    shutil.rmtree(config.m_effCfg.destrootdir + '/' + config.m_effCfg.xmlName)
        else:
            Logger.instance().loggerESubPro("cannot find dir" + config.m_effCfg.srcrootdir + '/' + k)
    
    Logger.instance().loggerESubPro ('恭喜打包成功！！！！！！')

MAX_SIZE = 150 * 1024
CONVERTCMD = 'F:/common/programfile/ImageMagick-6.8.1-Q8/convertim.exe'
z7z= 'F:\\common\\programfile\\7-Zip\\7z.exe'
jar = 'F:\\common\\programfile\\swift\\Swift.jar'
bpngout = True
#bpngout = False
pngout = 'F:\\common\\programfile\\pngout\\pngout.exe'
bcompress = False #是否压缩
compress='true' #是否压缩
quality=80  #压缩比率
packType = 0    # 打包类型 0: 就是正常特效打包  1: 就是中心点位置不变 2 中心点位置不变情况下指定宽度和高度
packWidth = 50  # packType = 2 的时候表示宽度
packHeight = 50 # packType = 2 的时候表示高度
CONVERTIDENT = 'D:/ProgramFiles/ImageMagick-6.8.0-Q8/identify.exe'
extName = 'png' # 资源扩展名字