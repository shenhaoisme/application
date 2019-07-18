#encoding=utf8
#python3.x

import urllib.request
import requests

'''
获取上海的天气


'''
def weather():
    target='http://www.weather.com.cn/data/sk/101020100.html'
    ret=urllib.request.urlopen(target)
    with open('weather.html','w') as fp:
        fp.write(ret.read().decode())
    
    response=requests.get(target)
    response.encoding='utf-8'
    print(response.status_code)
    print(response.content)
    ret=response.json()['weatherinfo']['city']
    
    print(response.json()['weatherinfo']['city'],response.json()['weatherinfo']['WD'], response.json()['weatherinfo']['temp'])
    


weather()