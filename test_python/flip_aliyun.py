#! /usr/bin/env/python

import ffmpeg
'''
ffmpeg \
.file_input('../../doc/vedio/gotowork.mp4') \
.hflip() \
.file_output('output.mp4') \
.run()
'''

vin=ffmpeg.file_input('/home/sh/share/doc/vedio/gotowork.mp4')
flipped=ffmpeg.hflip(vin)
out=ffmpeg.file_output(flipped,0)
ffmpeg.run(out)
