#! /usr/bin/env python
#coding=utf-8

'''
d = {key : value1 , key2 : value2}
来成
对地指定键值与值。在这里要注意到成对的键值与值之间使用冒号分隔，而每一对键值与值
则使用逗号进行区分，它们全都由一对花括号括起。
'''
# “ab”是地址（Address）簿（Book）的缩写

ab = {
'Swaroop': 'swaroop@swaroopch.com',
'Larry': 'larry@wall.org',
'Matsumoto': 'matz@ruby-lang.org',
'Spammer': 'spammer@hotmail.com'
}

ab['shenhao'] = 'shenhaoisme@163.com'
if 'shenhao' in ab:
	print("if shenhao exist,his mail is %s" % ab['shenhao'])
	
print("total :")
print('\nThere are {} contacts in the address-book\n'.format(len(ab)))

print("del shenhao")
del ab['shenhao']

for name,items in ab.items():
	print('contact {} at {}'.format(name, items))
	

	

