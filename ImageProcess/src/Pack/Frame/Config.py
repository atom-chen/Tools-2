# -*- coding: utf-8 -*-

'''
通用配置
'''

import os

class ComConfig(object):
    def __init__(self):
        self.CONVERTCMD = 'D:/ProgramFiles/ImageMagick-6.8.0-Q8/convertim.exe'
        self.z7z= 'D:\\ProgramFiles\\7-Zip\\7z.exe'
        self.jar = 'E:\\work\\client-05\\trunk\\tools\\swift-tool\\Swift.jar'
        self.pngout = 'D:\\ProgramFiles\\pngout\\pngout.exe'
        self.CONVERTIDENT = ''
        self.serverid = ''
        self.MONTAGE = 'D:/ProgramFiles/ImageMagick-6.8.6-Q8/montage.exe'
        self.python = "python"  # python 解释命令
        self.swf2xmltool = "swf2xml.exe"    # 将所有 xml 配置文件打包成一个 swf 文件
        self.jsflstartparam = '-AlwaysRunJSFL'  # 启动 jsfl 需要传递给 flash 的参数 
        
    def parseKeyValue(self, lst):
        #公用配置
        if(lst[0] == 'CONVERTCMD'):
            self.CONVERTCMD = lst[1]
        elif(lst[0] == 'z7z'):
            self.z7z = lst[1]
        elif(lst[0] == 'jar'):
            self.jar = lst[1]
        elif(lst[0] == 'pngout'):
            self.pngout = lst[1]
        elif(lst[0] == 'CONVERTIDENT'):
            self.CONVERTIDENT = lst[1]
        elif(lst[0] == 'flashcs'):
            self.flashcs = lst[1]
        elif(lst[0] == 'serverid'):
            self.serverid = lst[1]
        elif lst[0] == 'MONTAGE':
            self.MONTAGE = lst[1]
        elif lst[0] == 'python':
            self.python = lst[1]
        elif lst[0] == 'swf2xmltool':
            self.swf2xmltool = lst[1]
        elif lst[0] == 'jsflstartparam':
            self.jsflstartparam = lst[1]
    
    def resolveCfg(self):
        pass
    
    def saveCFG(self, fHandle):
        fHandle.write('[common]\n')
        fHandle.write('CONVERTCMD=' + self.CONVERTCMD + '\n')
        fHandle.write('CONVERTIDENT=' + self.CONVERTIDENT + '\n')
        fHandle.write('z7z=' + self.z7z + '\n')
        fHandle.write('jar=' + self.jar + '\n')
        fHandle.write('pngout=' + self.pngout + '\n')
        fHandle.write('flashcs=' + self.flashcs + '\n')
        fHandle.write('serverid=' + self.serverid + '\n')
        fHandle.write('MONTAGE=' + self.MONTAGE + '\n')
        fHandle.write('python=' + self.python + '\n')
        fHandle.write('swf2xmltool=' + self.swf2xmltool + '\n')
        fHandle.write('jsflstartparam=' + self.jsflstartparam + '\n')
        
'''
特效配置
'''
class EffConfig(object):
    def __init__(self):
        self.dirname = 'E:\\image\\test5\\火雨特效'  # 美术给的资源的原始目录
        self.genxmldir = 'E:\\image\\test5'  # 生成的给AS3代码读取的xml的目录
        self.xmlName = 'e1710'
        self.m_curkey = '技能特效\e112萝莉猛将\e11211'  # 当前键值
        self.genNewPngDir = 'E:\\image\\test5\\cut_png' #打包的目录
        self.effectSwf = 'E:\\image\\test5\\effect_swf'  #放打包好的特效swf文件
        self.effectXmlSwf = 'E:\\image\\test5\\effect_xml_swf'  #放打包好的配置swf文件
        self.MAX_SIZE = 150
        self.bpngout = True
        self.bcompress = False #是否压缩
        self.quality=80  #压缩比率
        self.packType=0 # 0 就是默认的打包类型， 1 就是中心点在中心，， 2 中心点在中心指定大小
        self.packWidth=50
        self.packHeight=50
        self.extName = 'png'  # 打包图像的扩展名字
        self.jsfl=''    # 0 默认打包类型
        self.jsfla=''   # a 中心点在中心，大小最小
        self.jsflb=''   # b 中心点在中心，大小指定
        
        self.srcn2destn = {}    #特效资源原始文件夹到目标文件夹名字映射
        self.modelparamDic = {}    #原始模型配置参数
        self.srcrootdir_bak = ''    # 特效原始根目录可能会改变，因此备份一下
        
        self.effectcfgswfpath = '' # 特效的 swf 文件所在的目录
        self.effectcfgxmlpath = '' # 特效的 xml 文件所在的目录
        
    def parseKeyValue(self, lst):
        if(lst[0] == 'MAX_SIZE'):
            self.MAX_SIZE = int(lst[1])
        elif(lst[0] == 'compress'):
            self.bcompress = lst[1] == 1
        elif(lst[0] == 'quality'):
            self.quality = int(lst[1])
        elif(lst[0] == 'srcrootdir'):
            self.srcrootdir=lst[1]
        elif(lst[0] == 'destrootdir'):
            self.destrootdir=lst[1]
        elif(lst[0] == 'bpngout'):
            self.bpngout = lst[1] == '1'
        elif(lst[0] == 'jsfl'):
            self.jsfl = lst[1]
        elif(lst[0] == 'packType'):
            self.packType = int(lst[1])
        elif(lst[0] == 'packWidth'):
            self.packWidth = int(lst[1])
        elif(lst[0] == 'packHeight'):
            self.packHeight = int(lst[1])
        elif(lst[0] == 'extname'):
            self.extName = lst[1]
        elif(lst[0] == 'jsfl'):
            self.jsfl = int(lst[1])
        #elif(lst[0] == 'effectcfgswfpath'):
        #    self.effectcfgswfpath = lst[1]
        elif(lst[0] == 'effectcfgxmlpath'):
            self.effectcfgxmlpath = lst[1]

    def resolveCfg(self):
        # 根据配置生成其它配置
        self.genxmldir = self.destrootdir
        self.genNewPngDir = self.destrootdir
        self.effectSwf = self.destrootdir + '/' + 'effect_swf'
        self.effectXmlSwf = self.destrootdir + '/' + 'effect_xml_swf'
        self.srcrootdir_bak = self.srcrootdir
        
        # 不同特效打包方法
        dotidx = self.jsfl.find('.')
        self.jsfla = self.jsfl[0:dotidx]
        self.jsfla = self.jsfla + 'a.jsfl'
        
    def saveCFG(self, fHandle):
        fHandle.write('\n')
        fHandle.write('[effect]\n')
        fHandle.write('MAX_SIZE=' + str(self.MAX_SIZE) + '\n')
        if self.bpngout:
            fHandle.write('bpngout=' + '1' + '\n')
        else:
            fHandle.write('bpngout=' + '0' + '\n')
        fHandle.write('srcrootdir=' + self.srcrootdir + '\n')
        fHandle.write('destrootdir=' + self.destrootdir + '\n')
        fHandle.write('packType=' + str(self.packType) + '\n')
        fHandle.write('packWidth=' + str(self.packWidth) + '\n')
        fHandle.write('packHeight=' + str(self.packHeight) + '\n')
        fHandle.write('extname=' + self.extName + '\n')
        fHandle.write('jsfl=' + self.jsfl + '\n')
        #fHandle.write('effectcfgswfpath=' + self.effectcfgswfpath + '\n')
        fHandle.write('effectcfgxmlpath=' + self.effectcfgxmlpath + '\n')

'''
模型配置
'''
class CharConfig(object):
    def __init__(self):
        # 都实例化一下，防止取数据的时候挂掉
        self.baseDir = 'F:\\common\\pack\\char'
        self.moduleName = '资源'
        self.name = 'c111'
        self.xmlDir = 'F:\\common\\pack\\char\\asxml'
        
        self.xswfDir = 'F:\\common\\pack\\char\\xswf'
        self.swfDir = 'F:\\common\\pack\\char\\swf'
        self.bpngout = True
        self.bcompress = False
        self.quality = 80
        self.m_hardwareAcc = False      # 是否硬件加速
        
        self.srcn2destn = {}    #特效资源原始文件夹到目标文件夹名字映射
        self.modelparamDic = {}    #原始模型配置参数
        
        self.modelcfgswfpath = '' # 模型的 swf 文件所在的目录
        self.modelcfgxmlpath = '' # 模型的 xml 文件所在的目录
    
    def parseKeyValue(self, lst):
        if(lst[0] == 'compress'):
            self.bcompress = lst[1] == '1'
        elif(lst[0] == 'quality'):
            self.quality = int(lst[1])
        elif(lst[0] == 'srcrootdir'):
            self.srcrootdir=lst[1]
        elif(lst[0] == 'destrootdir'):
            self.destrootdir=lst[1]
        elif(lst[0] == 'bpngout'):
            self.bpngout = lst[1] == '1'
        elif(lst[0] == 'moduleName'):
            self.moduleName = lst[1]
        elif(lst[0] == 'name'):
            self.name = lst[1]
        elif lst[0] == 'hardwareAcc':
            self.m_hardwareAcc = lst[1] == '1'
        elif(lst[0] == 'maxtexwidth'):
            self.m_maxtexwidth = int(lst[1])
        elif(lst[0] == 'maxtexheight'):
            self.m_maxtexheight = int(lst[1])
        elif(lst[0] == 'jsfl'):
            self.jsfl = lst[1]
        #elif(lst[0] == 'modelcfgswfpath'):
        #    self.modelcfgswfpath = lst[1]
        elif(lst[0] == 'modelcfgxmlpath'):
            self.modelcfgxmlpath = lst[1]
    
    def resolveCfg(self):
        self.baseDir = self.srcrootdir
        self.xmlDir = self.destrootdir + '/' + 'asxml'
        self.xswfDir = self.destrootdir + '/' + 'xswf'
        self.swfDir = self.destrootdir + '/' + 'swf'
        
    def saveCFG(self, fHandle):
        fHandle.write('\n')
        fHandle.write('[character]\n')
        if self.bpngout:
            fHandle.write('bpngout=' + '1' + '\n')
        else:
            fHandle.write('bpngout=' + '0' + '\n')
        
        fHandle.write('srcrootdir=' + self.srcrootdir + '\n')
        fHandle.write('destrootdir=' + self.destrootdir + '\n')
        if self.m_hardwareAcc:
            fHandle.write('hardwareAcc=' + str(1) + '\n')
        else:
            fHandle.write('hardwareAcc=' + str(0) + '\n')

        fHandle.write('maxtexwidth=' + str(self.m_maxtexwidth) + '\n')
        fHandle.write('maxtexheight=' + str(self.m_maxtexheight) + '\n')
        fHandle.write('jsfl=' + self.jsfl + '\n')
        #fHandle.write('modelcfgswfpath=' + self.modelcfgswfpath + '\n')
        fHandle.write('modelcfgxmlpath=' + self.modelcfgxmlpath + '\n')

'''
地形配置
'''
class TerConfig(object):
    def __init__(self):
        self.m_cropWidth = 128
        self.m_cropHeight = 128
        self.srcn2destn = {}    #特效资源原始文件夹到目标文件夹名字映射
        self.jsfl = ''
        self.m_bfight = False;    # 是不是战斗地图
        #self.m_addLeftGrid = 0    # 左边增加的格子
        #self.m_addRightGrid = 0   # 右边增加的格子
        #self.m_fightGridSize = 0   # 战斗格子大小
        self.m_bJustXml = False     # 仅仅导出 xml 配置文件，资源不再打包
        
        #self.m_thumbnailsWidth = 32  # 缩略图宽度
        #self.m_thumbnailsHeight = 32  # 缩略图高度
        self.m_thumbnailsscale = 20 # 图像缩放比例
        self.m_thumbnailsquality = 80 # 缩略图 imagemagic 压缩质量
        self.m_thumbnailsjsfl = '' # 缩略图打包的工具
        self.m_thumbnailsFolderName = 'tthumbnails'  # 缩略图图片所在的目录
        
        # 地形区域大小
        self.m_cropWidth = 128
        self.m_cropHeight = 128
        #地形格子大小
        self.m_gridWidth = 32
        self.m_gridHeight = 32
        # 每一个包中 floor 的个数
        self.m_floorperpack = 4
    
    def parseKeyValue(self, lst):
        if(lst[0] == 'srcrootdir'):
            self.srcrootdir=lst[1]
        elif(lst[0] == 'destrootdir'):
            self.destrootdir=lst[1]
        elif(lst[0] == 'cropwidth'):
            self.m_cropWidth=int(lst[1])
        elif(lst[0] == 'cropheight'):
            self.m_cropHeight=int(lst[1])
        elif(lst[0] == 'gridwidth'):
            self.m_gridWidth=int(lst[1])
        elif(lst[0] == 'gridheight'):
            self.m_gridHeight=int(lst[1])
        elif(lst[0] == 'jsfl'):
            self.jsfl = lst[1]
        elif(lst[0] == 'bfight'):
            self.m_bfight = lst[1] == '1'
        elif(lst[0] == 'floorperpack'):
            self.m_floorperpack = int(lst[1])
        #elif(lst[0] == 'addleftgrid'):
        #    self.m_addLeftGrid = int(lst[1])
        #elif(lst[0] == 'addrightgrid'):
        #    self.m_addRightGrid = int(lst[1])
        #elif(lst[0] == 'fightgridwidth'):
        #    self.m_fightGridSize = int(lst[1])
        elif(lst[0] == 'bjustxml'):
            self.m_bJustXml = lst[1] == '1'
        #elif(lst[0] == 'thumbnailswidth'):
        #    self.m_thumbnailsWidth = int(lst[1])
        #elif(lst[0] == 'thumbnailsheight'):
        #    self.m_thumbnailsHeight = int(lst[1])
        elif(lst[0] == 'thumbnailsscale'):
            self.m_thumbnailsscale = int(lst[1])
        elif(lst[0] == 'thumbnailsquality'):
            self.m_thumbnailsquality = int(lst[1])
        elif(lst[0] == 'thumbnailsjsfl'):
            self.m_thumbnailsjsfl = lst[1]
    
    def resolveCfg(self):
        self.XmlSwfFolderName = 'aterxmlswf'
    
    def saveCFG(self, fHandle):
        fHandle.write('\n')
        fHandle.write('[terrain]\n')
        fHandle.write('srcrootdir=' + self.srcrootdir + '\n')
        fHandle.write('destrootdir=' + self.destrootdir + '\n')
        fHandle.write('cropwidth=' + str(self.m_cropWidth) + '\n')
        fHandle.write('cropheight=' + str(self.m_cropHeight) + '\n')
        fHandle.write('gridwidth=' + str(self.m_gridWidth) + '\n')
        fHandle.write('gridheight=' + str(self.m_gridHeight) + '\n')
        if self.m_bfight:
            fHandle.write('bfight=1\n')
        else:
            fHandle.write('bfight=0\n')
        fHandle.write('floorperpack=' + str(self.m_floorperpack) + '\n')
        if self.m_bJustXml:
            fHandle.write('bjustxml=1\n')
        else:
            fHandle.write('bjustxml=0\n')
        #fHandle.write('addleftgrid=' + str(self.m_addLeftGrid) + '\n')
        #fHandle.write('addrightgrid=' + str(self.m_addRightGrid) + '\n')
        #fHandle.write('fightgridwidth=' + str(self.m_fightGridSize) + '\n')
        #fHandle.write('thumbnailswidth=' + str(self.m_thumbnailsWidth) + '\n')
        #fHandle.write('thumbnailsheight=' + str(self.m_thumbnailsHeight) + '\n')
        fHandle.write('thumbnailsscale=' + str(self.m_thumbnailsscale) + '\n')
        fHandle.write('thumbnailsquality=' + str(self.m_thumbnailsquality) + '\n')
        fHandle.write('thumbnailsjsfl=' + self.m_thumbnailsjsfl + '\n')
        fHandle.write('jsfl=' + self.jsfl)
    
'''
'''
class TerItemConfig(object):
    def __init__(self):
        self.m_srcImageName = ''        #原始文件名字
        self.m_tplFileName = ''         #地形材质文件名字
        self.m_terFileName = ''         #地形文件名字
        self.m_fog = False              # 是否显示 fog
        self.m_nobgpic = False             # 是否加载显示地图的图片资源，有些地图是不需要加载地图图片资源的，因为这个地图是永远看不见的，但是却能进入

'''
'''
class EffItemConfig(object):
    def __init__(self):
        self.m_srcName = ''        # 原始文件名字
        self.m_destName = ''       # 转换后的文件名字
        self.m_scale = 100         # 缩放百分比，只支持等比缩放

'''
'''
class CharItemConfig(object):
    def __init__(self):
        self.m_srcName = ''        # 原始文件名字
        self.m_destName = ''       # 转换后的文件名字
        self.m_scale = 100         # 缩放百分比，只支持等比缩放

'''
'''
class Config(object):
    #single
    pInstance = None
    # 启动类型
    MainExe = 0
    MainPy = 1
    EffPy = 2
    CharPy = 3
    TerPy = 4
    
    @classmethod
    def instance(cls):
        if cls.pInstance is None:
            cls.pInstance = cls()
            
        return cls.pInstance
        
    def __init__(self):
        #assert(Config.instance is None)
        #Config.instance = self
        '''入口函数'''       
        '''配置初始化'''
        self.m_commonCfg = ComConfig()
        self.m_effCfg = EffConfig()
        self.m_charCfg = CharConfig()
        self.m_terCfg = TerConfig()
        self.m_curCfg = None            #当前正在解析的配置文件
        
        #self.readInit()
        self.initPath(Config.MainExe)
        
    # init vary path
    def initPath(self, starttype):
        self.startType = starttype
        if starttype == Config.MainExe:
            self.effExePath = 'effpack.exe'
            self.charExePath = 'charpack.exe'
            self.terExePath = 'terpack.exe'
            self.configFile = 'config.txt'
            self.effNameFile = 'effname.txt'
            self.charNameFile = 'charname.txt'
            self.terNameFile = 'tername.txt'
        elif starttype == Config.MainPy:
            self.effExePath = './eff/maineff.py'
            self.charExePath = './char/mainchar.py'
            self.terExePath = './terrain/mainter.py'
            self.configFile = 'config.txt'
            self.effNameFile = 'effname.txt'
            self.charNameFile = 'charname.txt'
            self.terNameFile = 'tername.txt'
        elif starttype == Config.EffPy:
            self.configFile = '../config.txt'
            self.effNameFile = '../effname.txt'
        elif starttype == Config.CharPy:
            self.configFile = '../config.txt'
            self.charNameFile = '../charname.txt'
        elif starttype == Config.TerPy:
            self.configFile = '../config.txt'
            self.terNameFile = '../tername.txt'

    #读取初始化数据
    def readInit(self, filename):
        #filename = "effconfig.txt";
        #cont = open(filename, 'r', ).read().decode('gbk')
        fHandle = open(filename, 'r', encoding = 'utf8')
        cont = fHandle.read()
        #strlist = list
        strlist = cont.split('\n')
        idx = 0
        #key2value = {}
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            if strlist[idx] == '[common]':
                if self.m_curCfg != None:
                    self.m_curCfg.resolveCfg()
                self.m_curCfg = self.m_commonCfg
                idx += 1
                continue
            elif strlist[idx] == '[effect]':
                if self.m_curCfg != None:
                    self.m_curCfg.resolveCfg()
                self.m_curCfg = self.m_effCfg
                idx += 1
                continue
            elif strlist[idx] == '[character]':
                if self.m_curCfg != None:
                    self.m_curCfg.resolveCfg()
                self.m_curCfg = self.m_charCfg
                idx += 1
                continue
            elif strlist[idx] == '[terrain]':
                if self.m_curCfg != None:
                    self.m_curCfg.resolveCfg()
                self.m_curCfg = self.m_terCfg
                idx += 1
                continue
            elif strlist[idx] == '':
                idx += 1
                continue

            substrList = strlist[idx].split('=')
            #key2value[substrList[0]] = substrList[1]
            
            self.m_curCfg.parseKeyValue(substrList)
            
            idx += 1

        #最后一个调用解析
        self.m_curCfg.resolveCfg()
        fHandle.close()
        
        # 一次额配置文件的变量赋值
        self.m_effCfg.effectcfgswfpath = os.path.join(self.m_commonCfg.serverid, 'xml\\effect')
        self.m_charCfg.modelcfgswfpath = os.path.join(self.m_commonCfg.serverid, 'xml\\being')
        

    '''
    读取模型或特效配置文件
    '''
    def readEffNameFile(self, filename):
        fHandle = open(filename, 'r', encoding='utf-8')
        cont = fHandle.read()
        strlist = cont.split('\n')
        idx = 0
        whsplit = []        # 问号分裂的字符串
        whidx = 0           # 当前问号的索引
        whlength = 0        # 问号分裂的长度
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            if str(strlist[idx]):       # 如果这一行有内容
                if strlist[idx][0] != '#':      # 如果这一行开头是 # 就是注释
                    whsplit = strlist[idx].split('?')
                    whlength = len(whsplit)
                    whidx = 0
                    while(whidx < whlength):
                        substrList = whsplit[whidx].split('=')
                        if whidx == 0:      # 第一个区域是通用配置
                            item = CharItemConfig()
                            item.m_srcName = substrList[0];
                            item.m_destName = substrList[1];
                            keystr = substrList[0]
                        elif substrList[0] == 'scale':    # 缩放参数
                            item.m_scale = int(substrList[1])
                           
                        whidx += 1
                         
                    self.m_effCfg.modelparamDic[keystr] = item
                    self.m_effCfg.srcn2destn[keystr] = item.m_destName

            idx += 1
            
        fHandle.close()
    
    '''
    读取模型或特效配置文件
    '''
    def readCharNameFile(self, filename):
        fHandle = open(filename, 'r', encoding='utf-8')
        cont = fHandle.read()
        strlist = cont.split('\n')
        idx = 0
        whsplit = []        # 问号分裂的字符串
        whidx = 0           # 当前问号的索引
        whlength = 0        # 问号分裂的长度
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            if str(strlist[idx]):       # 如果这一行有内容
                if strlist[idx][0] != '#':      # 如果这一行开头是 # 就是注释
                    whsplit = strlist[idx].split('?')
                    whlength = len(whsplit)
                    whidx = 0
                    while(whidx < whlength):
                        substrList = whsplit[whidx].split('=')
                        if whidx == 0:      # 第一个区域是通用配置
                            item = CharItemConfig()
                            item.m_srcName = substrList[0];
                            item.m_destName = substrList[1];
                            keystr = substrList[0]
                        elif substrList[0] == 'scale':    # 缩放参数
                            item.m_scale = int(substrList[1])
                           
                        whidx += 1
                         
                    self.m_charCfg.modelparamDic[keystr] = item
                    self.m_charCfg.srcn2destn[keystr] = item.m_destName

            idx += 1
            
        fHandle.close()
        
    '''
    读取地形配置文件
    '''
    def readTerNameFile(self, filename):
        fHandle = open(filename, 'r', encoding='utf-8')
        cont = fHandle.read()
        strlist = cont.split('\n')
        idx = 0
        whsplit = []        # 问号分裂的字符串
        whidx = 0           # 当前问号的索引
        whlength = 0        # 问号分裂的长度
        substrList = []
        listlen = len(strlist)
        while(idx < listlen):
            if str(strlist[idx]):       # 如果这一行有内容
                if strlist[idx][0] != '#':      # 如果这一行开头是 # 就是注释
                    whsplit = strlist[idx].split('?')
                    whlength = len(whsplit)
                    whidx = 0
                    while(whidx < whlength):
                        substrList = whsplit[whidx].split('=')
                        if whidx == 0:      # 第一个区域是通用配置
                            item = TerItemConfig()
                            item.m_srcImageName = substrList[0]
                            item.m_tplFileName = substrList[1]
                            item.m_terFileName = substrList[2]
                            keystr = substrList[0]
                        elif substrList[0] == 'fog':    # 后面是参数
                            item.m_fog = (substrList[1] == '1')
                        elif substrList[0] == 'nobgpic':
                            item.m_nobgpic = (substrList[1] == '1')
                            
                        whidx += 1
                    
                    self.m_terCfg.srcn2destn[keystr] = item
            idx += 1
            
        fHandle.close()

    # 保存数据
    def saveCFG(self):
        filename = 'config.txt'
        fHandle = open(filename, 'w', encoding='utf-8')
        
        self.m_commonCfg.saveCFG(fHandle)
        self.m_effCfg.saveCFG(fHandle)
        self.m_charCfg.saveCFG(fHandle)
        self.m_terCfg.saveCFG(fHandle)
        
        fHandle.close()
