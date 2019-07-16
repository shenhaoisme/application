import requests
import re

#获取网页地址
#http://www.xiaohuar.com/list-1-3.html
#变化的只有 1-0 ~ 1-4，一共 5 页 
#另外图片上的url多有大概三种，所以用正则表达式去过滤时，获取出两个字典
#
#因为没哟反爬，这个例子连header 信息都没有做

url='http://www.xiaohuar.com/list-1-%s.html'

for i in range(2):
    temp=url % i
    print(temp)
    #获取网页源码
    response=requests.get(temp)
    html=response.text
    #从源码文本中匹配我们需要的url
    img_urls=re.findall(r'/d/file/\d+/\w+\.jpg',html)
    img_urls_1=re.findall(r'api/xiaohua/upload/min_img/\d+/\w+\.jpg',html)

    for img_url in img_urls:
        img_response=requests.get('http://www.xiaohuar.com%s'%img_url)
        print(img_url)
        #图片的二进制信息
        img_data=img_response.content
        girl=img_url.split('/')[-1]
        with open('./image/%s'%girl,'wb') as f:
            f.write(img_data)
    for img_url in img_urls_1:
        img_response=requests.get('https://www.dxsabc.com/%s'%img_url)
        print(img_url)
        #图片的二进制信息
        img_data=img_response.content
        girl=img_url.split('/')[-1]
        with open('./image/%s'%girl,'wb') as f:
            f.write(img_data)