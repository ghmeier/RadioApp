#
# (C) 2001-2012 Marmalade. All Rights Reserved.
#
# This document is protected by copyright, and contains information
# proprietary to Marmalade.
#
# This file consists of source code released by Marmalade under
# the terms of the accompanying End User License Agreement (EULA).
# Please do not use this program/source code before you have read the
# EULA and have agreed to be bound by its terms.
#
import deploy_config

config = deploy_config.config
cmdline = deploy_config.cmdline
mkb = deploy_config.mkb
mkf = deploy_config.mkf

assets = deploy_config.assets

class HubConfig(deploy_config.DefaultConfig):
    android_icon_group = {}
    android_install_location = 1
    android_pkgname = r"com.Garret.USSCRadio"
    assets = assets["Default"]
    config = [r"C:/Users/Garret/Documents/GitHub/USSCRadio/resources/common.icf", r"C:/Users/Garret/Documents/GitHub/USSCRadio/resources/app.icf"]
    name = r"USSCRadio"
    caption = r"USSCRadio"
    provider = r"Garret"
    copyright = r"(C) Garret"
    version = [0, 0, 1]
    pass

default = HubConfig()
