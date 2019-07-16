import urllib.parse
#encoding=utf8
'''
汉字显示不出来，会被替换
'''
url='https://cn.bing.com/search?q=沈浩&PC=U316&FORM=CHROMN'
print('转换前:  '+url)
ret=urllib.parse.quote(url)
print(ret)

print('重新解码'+urllib.parse.unquote(ret))


#例子2
#假设有这么一个url
# url = http://www.baidu.com/index.hmtl?name=shen&age=24&height=170
# host/path?parma=value&param2=value2 

url='http://www.baidu.com/index.html'
name='shen'
age=25
height=170
data = {
    'name':name,
    'age':age,
    'height':height
}
#把赋值好的字典放到URL中

list = []
for key, value in data.items():
    list.append(key + '=' + str(value))
    
#拼接完成，把列表中元素以 & 连接起来
queryString = '&'.join(list)
ret = url + '?' + queryString
print(ret)
#不是string，不能打印
#print(list)

#urlencode 参数为字典，完成上面的逻辑
queryString = urllib.parse.urlencode(data)
ret = url + '?' + queryString
print(ret)


