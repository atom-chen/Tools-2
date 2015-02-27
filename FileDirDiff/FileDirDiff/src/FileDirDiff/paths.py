# -*- coding: utf-8 -*-
'''
Created on 2013-4-23

@author: Administrator
'''

import os

FROZEN = False

from autoupdate import fake

PACKAGE_DIR = os.path.dirname(os.path.abspath(fake.__file__))

if PACKAGE_DIR.endswith(os.path.join("library.zip", "autoupdate")):
    FROZEN = True
    PACKAGE_DIR = os.path.dirname(PACKAGE_DIR)

UI_DIR = os.path.join(PACKAGE_DIR, "ui")

if not FROZEN:
    assert(os.path.exists(PACKAGE_DIR))
    assert(os.path.exists(UI_DIR))