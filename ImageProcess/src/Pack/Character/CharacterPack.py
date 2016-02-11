#coding=utf-8

'''
'''

#from subprocess import Popen, PIPE
import subprocess
import os
#import time;
from xml.dom.minidom import Document
#import string
import sys
import traceback
import shutil
import glob

from Pack.Frame.Logger import Logger
from Pack.Frame.Config import Config
from Pack.Frame.Rect import stRect

'''
模型资源打包脚本
'''
#import sys  
# 获得系统默认编码格式  
#sysCharType = sys.getfilesystemencoding()  
     
'''裁剪图片处理'''
class PngCut:
    def __init__(self, baseDir, moduleName, destDir):
        self.baseDir = baseDir
        self.moduleName = moduleName
        self.pngSource ='%s\\%s' % (baseDir, moduleName)
        self.destDir = destDir
        
        # 判断哪些动作和方向需要处理
        self.pngActList = ['被击', '等待', '攻击', '跑步', '死亡', '跳', '打坐', '骑乘等待', '骑乘跑步']
        self.pngDirList = ['上', '下', '斜上', '斜下', '右']

    def __createPngDir(self, name):    
        '''创建相应的文件夹'''
        self.newdir = '%s\\%s' % (self.destDir, name)
        if os.path.isdir(self.newdir):
            Logger.instance().loggerCSubPro('%s 已经存在。' % self.newdir)
            return -1   
        os.makedirs(self.newdir)
        Logger.instance().loggerCSubPro('创建目录%s' % self.newdir)

    # 这个是枚举目录，枚举文件不用这个
    def __joinPath(self, desdir):     
        pathList = []
        ls=os.listdir(desdir)
        for filename in ls:
            if filename in self.pngActList or filename in self.pngDirList:
                if not os.path.isdir(desdir + '/' + filename):
                    continue
                '''将路径和文件名拼接'''
                temp = os.path.join('%s\\%s' % (desdir, filename))
                pathList.append(temp)
        return pathList
    
    # 枚举图片文件用这个
    def __joinFiles(self, desdir):
        pathList = []
        os.chdir(desdir)
        ls = glob.glob('*.png')
        ls.sort()
        for filename in ls:
            '''将路径和文件名拼接'''
            temp = os.path.join('%s\\%s' % (desdir, filename))
            pathList.append(temp)
        return pathList

    def cutAllPng(self, name):
        if self.__createPngDir(name) == -1:
            Logger.instance().loggerCSubPro('%s可能已完成图片裁剪' % self.pngSource)
            return
        actList = self.__joinPath(self.pngSource)
        for act in actList:
            self.__cutAct(act)

    def __cutAct(self, actPngDir):
        act = actPngDir.split('\\')[-1]
        
        path = '%s\\%s' % (self.newdir, act)
        os.makedirs(path)
        Logger.instance().loggerCSubPro('82 dir ' + path)
        for direct in os.listdir(actPngDir):
            if not os.path.isdir(actPngDir + '/' + direct):
                continue
            self.__cutDir(act, '%s\\%s' % (actPngDir, direct))
        
    def __cutDir(self, act, dirPngDir):
        direct = dirPngDir.split('\\')[-1]            
        Logger.instance().loggerCSubPro(dirPngDir)
        newActDirectDir = '%s\\%s\\%s' % (self.newdir, act, direct)
        os.makedirs(newActDirectDir)
        Logger.instance().loggerCSubPro('93 dir ' + newActDirectDir)
        
        #for path in self.__joinPath(dirPngDir):
        for path in self.__joinFiles(dirPngDir):
            cutFileFullName = '%s\\%s' % (newActDirectDir, path.split('\\')[-1])
            if Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale == 100:
                cmd = '%s -trim -strip -depth 8 +repage \"%s\" \"%s\"' % (CONVERTCMD, path, cutFileFullName)
            else:
                cmd = '%s -filter Lanczos -resize %s%% -trim -strip -depth 8 +repage \"%s\" \"%s\"' % (CONVERTCMD, str(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale), path, cutFileFullName)
            #os.popen(cmd).read()
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            
            #再无损压缩一下
            if bpngout:
                cmd = "%s %s" % (pngout, cutFileFullName)
                #con = os.popen(cmd).read()
                handle = subprocess.Popen(cmd, shell=True)
                handle.wait()
            Logger.instance().loggerCSubPro('裁剪图片 %s 完成' % path)

class ActNode:
    def __init__(self, act, count, angleNode):
        self.act = act
        self.count = count;
        self.angleNode = angleNode

class AngleNode:
    def __init__(self, angle, pngInfo):
        self.angle = angle
        self.pngInfo = pngInfo
    
'''定义一个可以存放图片偏移量和尺寸的类型'''
class PngInfo:
    def __init__(self, x, y, width, height, path):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.path = path

'''打包裁剪好的png图片到swf'''
class PngPackage:
    def __init__(self, baseDir, moduleName, name, destDir):
        self.baseDir = baseDir
        self.moduleName = moduleName
        self.name = name
        self.destDir = destDir
        self.pngSource = '%s\\%s' % (baseDir, name)
        self.pngActList = ['被击', '等待', '攻击', '跑步', '死亡', '跳', '打坐', '骑乘等待', '骑乘跑步']
        self.pngDirList = ['上', '下', '斜上', '斜下', '右']
        self.pngAct2NumList = {'被击':'8', '等待':'0', '攻击':'7',\
                               '跑步':'2', '死亡':'9', '跳':'3', '打坐':'12', '骑乘等待':'13', '骑乘跑步':'14'}
        self.pngDir2NumList = {'上':'315', '下':'135', \
                               '斜上':'0', '斜下':'90', '右':'45'}
        self.pngDir2XmlDir = {'315':'7', '135':'3', '0':'0',\
                              '90':'2', '45':'1'}
        self.pngDirNum = ['315', '135', '0','90', '45']

    def __getOnePngInfo(self, pngFullName):
        f = pngFullName.replace('_裁剪版', '')
        if Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale != 100:
            cmd = '%s \"%s\" -filter Lanczos -resize %s%% -trim info:-' % (CONVERTCMD, f, str(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale))
        else:
            cmd = '%s \"%s\" -trim info:-' % (CONVERTCMD, f)
        #cmd = '%s \"%s\" -trim info:-' % (CONVERTCMD, f)    
        #out = os.popen(cmd).read()
        handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
        handle.wait()
        out = handle.stdout.read();
        out = out.decode('utf-8')
        outList = out.split()
        
        xyList = outList[3].split('+')
        whList = outList[2].split('x')
        
        # 如果宽度和高度不能整除，就直接舍弃掉
        x = int(int(xyList[1]) - int(xyList[0].split('x')[0])/2)
        y = int(int(xyList[2]) - int(xyList[0].split('x')[1])/2)
        #print 'x: %d, y: %d' % (x, y)
        
        # 如果缩放，还需要修正左上角位置和宽度高度信息
        # bug: 这个地方有数值误差
        #if Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale != 100:
        #    x = int(x * float(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale)/100)
        #    y = int(y * float(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale)/100)
        #    whList[0] = str(int(float(whList[0]) * float(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale)/100))
        #    whList[1] = str(int(float(whList[1]) * float(Config.instance().m_charCfg.modelparamDic[Config.instance().m_charCfg.moduleName].m_scale)/100))

        #print ('x=%s, y=%s width=%s height=%s _x=%d y=%d' %\
        #      (xyList[1], xyList[2], whList[0], whList[1], x, y))
        pi = PngInfo(x, y, whList[0], whList[1], pngFullName)
        return pi
        
    def getPngData(self):
        self.actNodeList = []
        actCount = 0
        sourcePngDir = '%s\\%s' % (self.baseDir, self.moduleName)
        for act in os.listdir(sourcePngDir):
            #检测是否是打包目录
            if act not in self.pngActList:
                continue
            actFullName = '%s\\%s' % (sourcePngDir, act)
            if not os.path.isdir(actFullName):
                continue
            pngDirList = []
            for direct in os.listdir(actFullName):
                if direct not in self.pngDirList:
                    continue
                directFullName = '%s\\%s' % (actFullName, direct)
                if not os.path.isdir(directFullName):
                    continue
                pngInfoList = []
                #files = os.listdir(directFullName)
                os.chdir(directFullName)
                files = glob.glob('*.png')
                files.sort()
                for pngfile in files:
                    fileFullName = '%s\\%s' % (directFullName, pngfile)
                    #print ('test: %s' % fileFullName)
                    pngInfoList.append(self.__getOnePngInfo(fileFullName))
                pngSize = len(pngInfoList)
                if actCount == 0:
                    actCount = pngSize
                elif pngSize > 0 and actCount > pngSize:
                    actCount = pngSize
                    
                angleNode = AngleNode(self.pngDir2NumList[direct], pngInfoList)
                pngDirList.append(angleNode)
                Logger.instance().loggerCSubPro('获取 %s 图片信息完成' % directFullName)
            
            actNode = ActNode(self.pngAct2NumList[act], actCount, pngDirList)
            actCount = 0
            self.actNodeList.append(actNode)
            Logger.instance().loggerCSubPro('获取 %s 图片信息完成' % actFullName)
        Logger.instance().loggerCSubPro('获取全部裁剪图片信息完成。')
        #self.__fillDir()

    def __fillDir(self):
        '''处理补齐方向的操作'''
        for act in self.actNodeList:
            needFillDirList = self.pngDirNum[:]
            Logger.instance().loggerCSubPro(needFillDirList)
            for angle in act.angleNode:
                Logger.instance().loggerCSubPro(angle.angle)
                del needFillDirList[needFillDirList.index(angle.angle)]
                Logger.instance().loggerCSubPro('从待补充列表中删除方向 %s' % angle.angle)

            
            for fillAngle in needFillDirList:
                pngInfoList = []
                fillPngNumber = 0
                while fillPngNumber < act.count:
                    pngInfo = PngInfo(0, 0, '0', '0', '')
                    pngInfoList.append(pngInfo)
                    fillPngNumber += 1
                angleNode = AngleNode(fillAngle, pngInfoList)
                act.angleNode.append(angleNode)
                Logger.instance().loggerCSubPro('补齐 %s 动作的 方向%s完成' %(act.act, fillAngle))
                   
    def createXml(self, xmlDir):
        bbox = stRect()
        '''生成供as3代码读取的xml配置文件开始'''
        Logger.instance().loggerCSubPro('开始创建模型配置文件')
        doc = Document()
        root = doc.createElement('objectDefinition')
        root.setAttribute('name', self.name)
        root.setAttribute('overwrite', '1')
        root.setAttribute('type', '1')
        
        for act in self.actNodeList:
            disPlayModel = doc.createElement('displayModel')
            disPlayModel.setAttribute('act', act.act)
            disPlayModel.setAttribute('xcount', '%s' % act.count)
            disPlayModel.setAttribute('framerate', '%s' % act.count)
            
            for angle in act.angleNode: 
                sprite = doc.createElement('sprite')
                sprite.setAttribute('angle', angle.angle)
                
                # reset
                bbox.reset()
                for png in angle.pngInfo:
                    mapdata = doc.createElement('mapdata')
                    mapdata.setAttribute('xorig', '%d' % png.x)
                    mapdata.setAttribute('yorig', '%d' % png.y)
                    mapdata.setAttribute('width', png.width)
                    mapdata.setAttribute('height', png.height)
                    
                    if hardwareAcc:     # 如果开启硬件加速输出在整张帖图中的位置信息
                        if bbox.m_width + int(png.width) <= maxtexwidth: # 如果可以放在一行上
                            mapdata.setAttribute('xoff', str(bbox.m_width))
                            mapdata.setAttribute('yoff', str(bbox.m_height))
                            bbox.extWidth(int(png.width))
                            bbox.extHeight(int(png.height), False)
                        elif bbox.m_height + int(png.height) <= maxtexheight: # 如果可以换行
                            bbox.m_width = 0
                            if bbox.m_width + int(png.width) <= maxtexwidth: # 如果可以放在一行上
                                bbox.extHeight(int(png.height), True)
                            else:
                                Logger.instance().loggerCSubPro('单张图片太大，超出' + str(maxtexwidth))
                        else:
                            Logger.instance().loggerCSubPro('图片序列太多，超出' + str(maxtexwidth))
                        
                    sprite.appendChild(mapdata)
                disPlayModel.appendChild(sprite)           
            root.appendChild(disPlayModel)
        doc.appendChild(root)
      
        '''生成的xml写入文件'''
        self.xmlFullName = '%s\\%s' % (xmlDir, self.name)
        
        fHandle = open('%s.xml' % self.xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = " ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()
        Logger.instance().loggerCSubPro('建模型配置文件完成')
        
    def __createXmlUsePackageXml(self, xmlDir):
        xmlFullName = '%s\\x%s.xml'\
                              % (xmlDir, self.name) 
        doc = Document()
        root = doc.createElement('lib')
        root.setAttribute('allowDomain', '*')
        byteArray = doc.createElement('bytearray')
        byteArray.setAttribute('file',  '%s\\%s.xml' % (xmlDir, self.name))
        byteArray.setAttribute('class', 'art.cfg.%s' % self.name)
        root.appendChild(byteArray)
        doc.appendChild(root)
        fHandle = open(xmlFullName, 'w')
        fHandle.write(str(doc.toprettyxml(indent = " ", encoding="UTF-8"), encoding='utf-8'))
        fHandle.close()


    # 生成排列，以便生成 atlas
    def buildArr(self, act, dir):
        outfilename = self.destDir + '/' + self.name + '/' + self.name + '_' + self.pngAct2NumList[act] + '_' + self.pngDir2XmlDir[self.pngDir2NumList[dir]]
        filecnt = 0     # 文件数量
        packcnt = 0     # 包的数量
        firname = ''
        path = os.path.join(self.destDir, self.name, act, dir)
        os.chdir(path)
        filelst = glob.glob('*.png')
        filelst.sort()
        tmplist = []
        bbox = stRect()
        for filename in filelst:
            '''将路径和文件名拼接'''
            path = os.path.join(self.destDir, self.name, act, dir, filename)
            
            cmd = '%s -format \"%%Wx%%H\" %s' % (IDENTIFY, path)
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            out = handle.stdout.read();
            out = out.decode('utf-8')
            whList = out.split('x')

            # 真正生成
            if bbox.m_width + int(whList[0]) <= maxtexwidth: # 如果可以放在一行上
                bbox.extWidth(int(whList[0]))
                bbox.extHeight(int(whList[1]), False)
                if filecnt > 1:         # 至少两个以上
                    cmd = MONTAGE + ' ' + outfilename + '_' + str(packcnt) + '.png ' + os.path.join(self.destDir, self.name, act, dir, filename) + ' -tile 2x1 -geometry +0+0 -background \"rgba(0, 0, 0, 0)\" -gravity NorthWest +repage ' + outfilename + '_' + str(packcnt) + '.png'
                    handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
                    handle.wait()
                    if not outfilename + '_' + str(packcnt) + '.png' in tmplist:
                        tmplist.append(outfilename + '_' + str(packcnt) + '.png')
                elif filecnt == 1:
                    cmd = MONTAGE + ' ' + os.path.join(self.destDir, self.name, act, dir, firname) + ' ' + os.path.join(self.destDir, self.name, act, dir, filename) + ' -tile 2x1 -geometry +0+0 -background \"rgba(0, 0, 0, 0)\" -gravity NorthWest +repage ' + outfilename + '_' + str(packcnt) + '.png'
                    handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
                    handle.wait()
                    if not outfilename + '_' + str(packcnt) + '.png' in tmplist:
                        tmplist.append(outfilename + '_' + str(packcnt) + '.png')
                else:
                    firname = filename
            elif bbox.m_height + int(whList[1]) <= maxtexheight: # 如果可以换行
                bbox.m_width = 0
                filecnt = 0
                firname = filename
                if bbox.m_width + int(whList[0]) <= maxtexwidth: # 如果可以放在一行上
                    packcnt += 1
                    bbox.extHeight(int(whList[1]), True)
                else:
                    Logger.instance().loggerCSubPro('单张图片太大，超出' + str(maxtexwidth))
            else:
                Logger.instance().loggerCSubPro('图片序列太多，超出' + str(maxtexwidth))
                
            filecnt += 1
            
        # 把每一行的图片合成一张图片
        tmplststr = ''
        for tmpname in tmplist:
            if len(tmplststr):
                tmplststr += ' '
                tmplststr += tmpname
            else:
                tmplststr += tmpname
        
        if len(tmplist):
            cmd = MONTAGE + ' ' + tmplststr + ' -tile 1x' + str(len(tmplist)) + ' -geometry +0+0 -background \"rgba(0, 0, 0, 0)\" -gravity NorthWest +repage ' + outfilename + '.png'
            handle = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
            handle.wait()
            
        # 删除中间文件
        for tmpname in tmplist:
            os.remove(tmpname)

    # 生成 atlas
    def buildAtlas(self):
        # 目标目录
        actlst = os.listdir(os.path.join(self.destDir, self.name))
        
        for act in actlst:
            if os.path.isdir(os.path.join(self.destDir, self.name, act)):
                dirlst = os.listdir(os.path.join(self.destDir, self.name, act))
                for dir in dirlst:
                    self.buildArr(act, dir)                    

'''入口函数'''       
def modelPack(config):
    '''声明全局变量'''
    baseDir = config.m_charCfg.baseDir  #根目录
    moduleName = config.m_charCfg.moduleName  # 美术给的资源的名称
    name = config.m_charCfg.name
    xmlDir = config.m_charCfg.xmlDir  #as3程序xml
    destDir = config.m_charCfg.destrootdir  # 生成的目标目录
    
    pc = PngCut(baseDir, moduleName, destDir)
    pc.cutAllPng(name)

    package = PngPackage(baseDir, moduleName, name, destDir)
    package.getPngData()
    package.createXml(xmlDir)
    if hardwareAcc:
        package.buildAtlas()        # 生成地图集
    
# 打包接口
def startPack(config):
    global CONVERTCMD
    CONVERTCMD = config.m_commonCfg.CONVERTCMD
    global z7z
    z7z= config.m_commonCfg.z7z
    global jar
    jar = config.m_commonCfg.jar
    global pngout
    pngout = config.m_commonCfg.pngout
    global bpngout
    bpngout = config.m_charCfg.bpngout
    global bcompress
    bcompress = config.m_charCfg.bcompress #是否压缩
    global quality
    quality = config.m_charCfg.quality  #压缩比率
    
    global compress
    #初始化变量
    if bcompress:
        compress = 'true'
    else:
        compress = 'false'
    
    global hardwareAcc
    hardwareAcc = config.m_charCfg.m_hardwareAcc  # 硬件加速
    
    global maxtexwidth
    maxtexwidth = config.m_charCfg.m_maxtexwidth
    
    global maxtexheight
    maxtexheight = config.m_charCfg.m_maxtexheight
    
    global MONTAGE
    MONTAGE = config.m_commonCfg.MONTAGE
    
    global IDENTIFY
    IDENTIFY = config.m_commonCfg.CONVERTIDENT
    
    # 初始化必要目录
    if not os.path.exists(config.m_charCfg.xmlDir):
        os.makedirs(config.m_charCfg.xmlDir)
        Logger.instance().loggerCSubPro('405 dir ' + config.m_charCfg.xmlDir)
    

    for (k,v) in config.m_charCfg.srcn2destn.items():
        if os.path.isdir(config.m_charCfg.srcrootdir + '/' + k):
            config.m_charCfg.moduleName = k
            config.m_charCfg.name = v
            try:
                modelPack(config)
            except:
                # 错误输出
                traceback.print_exc()
                sys.stderr.write('model error: ' + config.m_charCfg.moduleName + '\n')
                sys.stderr.flush()
                # 删除必要的数据
                if os.path.isdir(config.m_charCfg.destrootdir + '/' + config.m_charCfg.name):
                    shutil.rmtree(config.m_charCfg.destrootdir + '/' + config.m_charCfg.name)
                
        else:
            Logger.instance().loggerCSubPro("cannot find dir" + config.m_charCfg.srcrootdir + '/' + k)
    
    Logger.instance().loggerCSubPro('恭喜打包成功！！！！！！')
   
# if __name__ == '__main__':
#     CONVERTCMD = 'F:\\common\\programfile\\ImageMagick-6.8.1-Q8\\convertim'
#     z7z ='F:\\common\\programfile\\7-Zip\\7z.exe'
#     jar = 'F:\\common\\programfile\\swift\\Swift.jar'
#     bpngout = True
#     #bpngout = False
#     pngout = 'F:\\common\\programfile\\pngout\\pngout.exe'
#     bcompress = False
#     compress='false' #是否压缩
#     quality=80  #压缩比率
#     
#     main()

# 模块全局变量
CONVERTCMD = 'F:\\common\\programfile\\ImageMagick-6.8.1-Q8\\convertim'
IDENTIFY = 'F:\\common\\programfile\\ImageMagick-6.8.1-Q8\\identify'
z7z ='F:\\common\\programfile\\7-Zip\\7z.exe'
jar = 'F:\\common\\programfile\\swift\\Swift.jar'
bpngout = True
#bpngout = False
pngout = 'F:\\common\\programfile\\pngout\\pngout.exe'
bcompress = False
compress='false' #是否压缩
quality=80  #压缩比率
hardwareAcc = False     # 是否开启硬件加速,需要添加一些配置信息
maxtexwidth = 2048      # 允许的最大的纹理宽度
maxtexheight = 2048      # 允许的最大的纹理高度
MONTAGE = 'F:\\common\\programfile\\ImageMagick-6.8.1-Q8\\montage'