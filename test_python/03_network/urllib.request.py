#encoding=utf8
#python3.x
'''
'''
import urllib.request 
'''
url为百度时没有问题，当为一张图片时， 错误如下;
decode
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xff 
删掉 decode
open的时侯得以 byte去打开；write才可以直接写

总结：
decode 与 write的冲突。http传输的时候都是以字节的方式传。
jpg 没有办法decoder为string； html格式需要code
与decode。当需要支持中文的时候，open(..., encoding='utf8')
'''

def get_image():
    
    target='http://www.xiaohuar.com/d/file/20190709/small6f25d7b6b627e42a4cd355df522b32d71562683530.jpg'
    response=urllib.request.urlopen(target)
    with open('girl.jpg','wb') as f:
        f.write(response.read())
    target1='http://www.baidu.com'
    html=urllib.request.urlopen(target1).read().decode()
    with open('baidu.html','w') as f:
        f.write(html)
def second_downJPG():
    target='http://www.xiaohuar.com/d/file/20190709/small6f25d7b6b627e42a4cd355df522b32d71562683530.jpg'
    urllib.request.urlretrieve(target,'girl_cp.jpg')
get_image()
second_downJPG()
