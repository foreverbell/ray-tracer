#!/usr/bin/env python
# encoding: utf-8

from urllib import urlretrieve
from os import mkdir, chdir

resources = [
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/bunny.noff',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/earth_texture.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/landscape_texture.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/front.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/back.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/top.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/bottom.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/left.png',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/right.png',

]

mkdir('resource')
chdir('resource')
mkdir('sunset-skybox')
for url in resources:
    fname = url.split('ray-tracer/')[-1]
    print 'retrieving', url, 'to', fname
    urlretrieve(url, fname)

