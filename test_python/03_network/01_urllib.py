#! /usr/bin/env python3
#encode='utf-8'

'''
1 必须用python3去执行
2 百度图片里的不行，看都是 www.mzitu.com找的


'''
import urllib.request
import os
os.makedirs('./image', exist_ok = True)

from urllib.request import urlretrieve


IMAGE_URL = "http://image.nationalgeographic.com.cn/2017/1122/20171122113404332.jpg"


'''
例子1 从server获取的内容是responese，这个内容支持好几种读取的方式。然后，以 bytes 为单位
创建了一个文件，把收到的bytes原封不动的copy过去
'''
responese = urllib.request.urlopen(IMAGE_URL)
with open('./image/fish.jpg', 'wb') as fp:
	fp.write(responese.read())

'''另一个更好用的函数'''	
urlretrieve(IMAGE_URL, './image/fish01.ipg')


'''做好这个page不会用'''
url = r'http://www.lagou.com/zhaopin/Python/?labelWords=label'
headers = {
    'User-Agent': r'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) '
                  r'Chrome/45.0.2454.85 Safari/537.36 115Browser/6.0.3',
    'Referer': r'http://www.lagou.com/zhaopin/Python/?labelWords=label',
    'Connection': 'keep-alive'
}
req = request.Request(url, headers=headers)
page = request.urlopen(req).read()
page = page.decode('utf-8')
