#! /usr/bin/env python
#encode='utf-8'
letter = ['a','b','c','d','e','f','g']

print("total letters has %d letters"%len(letter))

print("insert '1' at defore c")

index = letter.index('c')
letter.insert(index, '1')
#if I want insert after 'c',just "index +1 "
letter.remove('1')
for item in letter:
	print("%c"%item)
	
#拥有一种切片（Slicing）运算符	
print('item 1 - 3 ', letter[1:3])
print('item 3 - end ', letter[3:])
	
	
