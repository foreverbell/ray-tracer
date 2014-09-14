#!/usr/bin/env python
# encoding: utf-8

from urllib import urlretrieve

resources = [
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/bunny.noff',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/earth_texture.bmp',
    'https://raw.githubusercontent.com/foreverbell/miscellaneous/master/resource/ray-tracer/landscape_texture.bmp'
]

for url in resources :
    fname = 'resource/' + url.split('/')[-1]
    print 'retrieving', url
    urlretrieve(url, fname)

