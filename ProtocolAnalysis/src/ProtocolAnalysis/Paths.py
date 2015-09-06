# -*- coding: utf-8 -*-

import os

FROZEN = False

from ProtocolAnalysis import Fake

PACKAGE_DIR = os.path.dirname(os.path.abspath(Fake.__file__))

if PACKAGE_DIR.endswith(os.path.join("library.zip", "ProtocolAnalysis")):
    FROZEN = True
    PACKAGE_DIR = os.path.dirname(PACKAGE_DIR)

UI_DIR = os.path.join(PACKAGE_DIR, "UI")

if not FROZEN:
    assert(os.path.exists(PACKAGE_DIR))
    assert(os.path.exists(UI_DIR))