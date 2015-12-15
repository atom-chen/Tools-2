# -*- coding: utf-8 -*-

'''
'''

from Pack.Frame.Config import Config
from Pack.Terrain.TerrainPack import startPackTer

def main():
    Config.instance().initPath(Config.TerPy)
    Config.instance().readInit(Config.instance().configFile)
    Config.instance().readTerNameFile(Config.instance().terNameFile)
    
    startPackTer()

main()

