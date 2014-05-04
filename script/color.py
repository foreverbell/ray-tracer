#!/usr/bin/python

import urllib2
import urllib
import re
import sys

url = 'http://www.w3schools.com/html/html_colornames.asp'

def format(name, value) :
	color = int(value, 16)
	blue = color % 256
	color /= 256
	green = color % 256
	color /= 256
	red = color % 256
	color /= 256
	
	return 'colorRGB color_' + name.lower() + ' = colorRGB(' + str(red / 255.0) + ', ' + str(green / 255.0) + ', ' + str(blue / 255.0) + ');'
	
html = urllib2.urlopen(url).read()
reg = re.compile('<td><a target="_blank" href="/tags/ref_color_tryit.asp\?color=.*?">(.*?)</a>&nbsp;</td>\s*<td><a target="_blank" href="/tags/ref_color_tryit.asp\?hex=.*?">\#(.*?)</a></td>')

print '=== Declaration ==='

for color in reg.findall(html) :
	print format(color[0], color[1])
	

print ' '

print '=== Prototype ==='
for color in reg.findall(html) :
	print 'extern colorRGB color_' + color[0].lower() + ';'
