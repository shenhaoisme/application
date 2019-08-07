import urllib.request
import urllib.parse
import json
import random
import hashlib

'''
本例子的主要是把百度翻译开放平台的demo从python2 转化为 python3
本例子强制性规定 英文转中文
http://api.fanyi.baidu.com/api/trans/product/apidoc
'''
#要先去网上注册会收到如下信息
appid = '20190803000323733' #你的appid
secretKey = 'D01BCZMhveQnNZD9EXMc' #你的密钥
#实现实时翻译
content=input("=====请输入您要翻译的内容：=====\n")

myurl = 'http://api.fanyi.baidu.com/api/trans/vip/translate/'
q = content
fromLang = 'en'
toLang = 'zh'
#为了生成签名，必须提供一个随机值
salt = random.randint(32768, 65536)
#签名是必须的，每次翻译都需要一次签名。
#签名的方法：appid+q+salt+密钥 的MD5值
sign = appid+q+str(salt)+secretKey
m1 = hashlib.md5(sign.encode(encoding='UTF-8'))
#m1.update(sign)
sign = m1.hexdigest()
#python2 自己拼接 url ，而python3 是自己组建一个字典，然后通过函数构建 URL
#myurl = myurl+'?appid='+appid+'&q='+urllib.quote(q)+'&from='+fromLang+'&to='+toLang+'&salt='+str(salt)+'&sign='+sign

# q	TEXT	Y	请求翻译query	UTF-8编码
# from	TEXT	Y	翻译源语言	语言列表(可设置为auto)
# to	TEXT	Y	译文语言	语言列表(不可设置为auto)
# appid	TEXT	Y	APP ID	可在管理控制台查看
# salt	TEXT	Y	随机数
# sign	TEXT	Y	签名	appid+q+salt+密钥 的MD5值
data = {
    'q': q,
    'from': fromLang,
    'to': toLang,
    'appid': appid,
    'salt': salt,
    'sign': sign,
}
#把词典改为string style URL
data = urllib.parse.urlencode(data).encode('utf-8')
#method get
response = urllib.request.urlopen(myurl, data)
#get content
html=response.read().decode('utf-8')
#把json转化为字典
target=json.loads(html)
#print(type(target))  #dict
for i in target:
    print(i + ':' + str(target[i]))
#转化为 json 以后：
# from:en
# to:zh
# trans_result:[{'src': 'apple', 'dst': '苹果'}]
# 所以解析的顺序是 字典-列表-字典
print(type(target['trans_result']))
print(target['trans_result'][0]['dst'])