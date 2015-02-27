# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
@brief start function 
'''

def main():
    import sys
    from autoupdate.frame import application
    app = application.Application()
    sys.exit(app.exec_())
    
if __name__ == "__main__":
    main()