# -*- coding: utf-8 -*-

'''
@brief start function 
'''

def main():
    import sys
    from FileDirDiff.Frame import Application
    app = Application.Application()
    sys.exit(app.exec_())
    
if __name__ == "__main__":
    main()