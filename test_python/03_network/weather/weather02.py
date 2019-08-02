#encoding=utf8
#python3.x

import urllib.request
import requests
import json
from urllib.parse import quote
import string

from xml.dom import minidom

def get_support_city(province = None):
	pass
	url = 'http://www.webxml.com.cn/WebServices/WeatherWebService.asmx/getSupportCity?byProvinceName=' + province 
	url = quote(url, safe = string.printable)
	ret = urllib.request.urlopen(url)
	txt = ret.read().decode('utf8')
	string_str=''
	key_value=''
	key_value_list=[]
	word_flag=0
	print(txt)
	for i in txt:
		string_str += i
		if string_str.replace(' ','').replace('\n','').replace('\r','')=='<string>':
			word_flag =1
		if i == '>':
			string_str=''
		if word_flag==1:
			key_value += i
		else:
			key_value=''
		if i == '<' and word_flag == 1:	
			key_value_list.append(key_value.replace('<','').replace('(','').replace(')','').replace('>',''))
			key_value=''
			word_flag=0
	print(key_value_list)
	support_city={}
	for i in key_value_list:
		print(i)
		word=i.split(' ')
		support_city[word[0]] = word[1]

	return support_city

def get_weather(name):
	page = urllib.request.urlopen("http://www.webxml.com.cn/WebServices/WeatherWebService.asmx/getWeatherbyCityName?theCityName="+name)
	lines = page.readlines()
	page.close()
	doc = ''
	for line in lines:
		doc = doc + line.decode('utf8')

	from xml.dom.minidom import parseString
	dom = parseString(doc)
	strings = dom.getElementsByTagName('string')
	print('今日天气情况', strings[10].childNodes[0].data)

if __name__ == '__main__' :
	province=input('请输入要查询的省份--')
	province=quote(province, safe = string.printable)
	support_city = get_support_city(province)
	print(support_city)
	name=input('请在上述的城市中选取一个')
	name=support_city[name]
	get_weather(name)