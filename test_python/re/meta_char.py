import re
#encoding='utf-8'
str=('hello world')

# '.' ==> onechar
ret = re.findall("he..o", str)

# '^'
#必须以该字符开头
ret = re.findall('^he..o', str)
# '$'
#必须以该字符结尾
ret = re.findall('w..ld$',str)

# '+' ==> [1,+oo]
#循环字符b，至于有一个
str1 = ('abckkkkkkkabggggg')
ret = re.findall('ab+', str1)
# '*' ==> [0,+oo]
# ab*将匹配‘a’、‘ab’或‘a’ 后面跟随任意数目的‘b’
ret = re.findall('ab*',str1)

# '?' ==> [0, 1]
#ab?将匹配‘a’或者‘ab’。
ret = re.findall('ab?', str1)
# '{}'
# 表示精确匹配前面的正则表达式的m个拷贝；较少的匹配将导致整个表达式不能匹配。
#['abckkkk']

ret = re.findall('abck{1,4}',str1)


#'[]' 字符集
# -> or
ret = re.findall('h[a,b,c,e]l',str)
#eg2
str2='qaweer1234*'
#[]可以把特殊字符变普通 *,except \ ^ -
ret = re.findall('[a-z][0-9][*]', str2)
#eg3 [^t] 取反

# '\'
# \ 去除特殊功能
# \d => [0-9] ; \D [^0-9]
ret = re.findall('\d{5}', 'ssssd112334xxx1234')
# \s 匹配任何空白字符  --》 [\t\n\r\f\v] ; \S 非空的字符
ret = re.findall('\s{4}', 'sss s d       3 4x xx1234')
# \w 匹配任何字母数字字符-> [a-zA-Z0-0] \W
ret = re.findall('\w123','11dadxcqqqzxxxx123')#x123
ret = re.findall('\W123','11dadxcqqqzxxxx 123')#' 123'

#\b 匹配特殊字符的便捷 
#区分 LIST的I
#ret = re.findall(r'I\b','I am LIST')

#'()'
#把几个字母作为一个整体
ret = re.findall('(as)+','assaassa')

#'|'



print(ret)
