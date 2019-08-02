#encoding=utf8
#python3.x

import urllib.request
import requests
import types

'''
获取上海的天气
'''
def weather(targte = None, place = None):
    target = targte
    place = place
    if target is not None:
        ret=urllib.request.urlopen(target)
        with open('weather.html','w') as fp:
            fp.write(ret.read().decode())
    
    response=requests.get(target)
    response.encoding='utf-8'
    #print(response.status_code)
    #print(response.content)
    ret=response.json()['weatherinfo']['city']
    
    ret = response.json()['weatherinfo']['city'],response.json()['weatherinfo']['WD'], response.json()['weatherinfo']['temp']
    print(type(ret)) #tuple

    if place  in ret :
        windDirection = ret[1]
        temperature  = ret[2]   
    else :
        print('no this place')
        return -1
    print(place + '->'+ windDirection + '->' + temperature)



shanghai = 'http://www.weather.com.cn/weather/101020100.shtml'
beijing = 'http://www.weather.com.cn/data/sk/101010100.html'
weather(shanghai, '上海')