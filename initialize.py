#!/usr/bin/env python
# encoding: utf-8

from urllib import urlretrieve
from os import mkdir, chdir

resources = [
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/bunny.noff',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/earth_texture.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/landscape_texture.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/front.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/back.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/top.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/bottom.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/left.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/sunset-skybox/right.bmp'
]

mkdir('resource')
chdir('resource')
mkdir('sunset-skybox')
for url in resources :
    fname = url.split('ray-tracer/')[-1]
    print 'retrieving', url, 'to', fname
    urlretrieve(url, fname)

