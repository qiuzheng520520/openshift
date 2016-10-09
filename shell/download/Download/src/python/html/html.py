#coding=utf-8
import urllib
import re
import os

page = "http://www.jiayuan.com/"
start_no = 100000000
sum_no = 100

def getHtml(url):
	page = urllib.urlopen(url)
	html = page.read()
	fp = open("html.txt","w")
	fp.write(html)
	fp.close()
	return html

def getText(text_file)
	fp = open(text_file,"r")
	try:
		text = fp.read()
	finally:
		fp.close()
#	id = re.search("个人资料",text)
#	print id

def getImg(html):
	reg = r'src="(.+?\.jpg)" pic_ext'
	imgre = re.compile(reg)
	imglist = re.findall(imgre,html)
	os.mkdir("image")
	os.chdir("image")
	x = 0
	for imgurl in imglist:
		urllib.urlretrieve(imgurl,'%s.jpg' % x)
		x+=1

#html =	getHtml("http://tieba.baidu.com/p/3749271755")

#getImg(html)
#getHtml("http://www.baidu.com")

#i = 0
p = start_no
for p in range(start_no,start_no + sum_no):
	getHtml(page + "%s"%p)
	print p
	p += 1
