#!/usr/bin/env python
# coding=utf-8
import os
import sys

exe = '/Applications/Marmalade.app/Contents/s3e/bin/s3e'
if os.name == 'nt':
    exe += '.bat'

cmd = list(sys.argv)
cmd[0] = exe

cmd.append('-via:"/Users/lucasgeiken/Desktop/squareinfinity/RadioApp/UCCSRadio/build_uccsradio_scons_x86/UCCSRadio_release.via"')
os.execvp(cmd[0], cmd)
