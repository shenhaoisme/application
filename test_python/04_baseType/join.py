
#encoding=utf-8

'''
1、join()函数

语法：  'sep'.join(seq)

参数说明
sep：分隔符。可以为空
seq：要连接的元素序列、字符串、元组、字典
上面的语法即：以sep作为分隔符，将seq所有的元素合并成一个新的字符串

返回值：返回一个以分隔符sep连接各个元素后生成的字符串

'''

seq1 = ['hello','good','boy','doiido']
#把每个元素以空格分来，并且返回 一个 string
ret = ' '.join(seq1)

print(ret)