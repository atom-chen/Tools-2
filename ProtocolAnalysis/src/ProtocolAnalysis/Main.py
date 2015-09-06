# -*- coding: utf-8 -*-

'''
@brief start function 
'''

def main():
    import sys
    from ProtocolAnalysis.FrameWork import AppFrame
    app = AppFrame.AppFrame()
    sys.exit(app.exec_())
    
if __name__ == "__main__":
    main()


