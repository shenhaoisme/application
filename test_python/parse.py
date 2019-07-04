#! /usr/bin/python3
import argparse
	
if __name__ == "__main__":
	parser = argparse.ArgumentParser(description = '输入h|help 会显示该条信息')
	
	parser.add_argument('--test','-t', type=int, default=0, help='类型是int，默认为0，用法是来加参数来设置一个值')
	parser.add_argument('--choices', choices = [ 'A' ,'B', 'C'])
	args = parser.parse_args()
	
	if args.test > 0:
		print(args.test)
	else:
		print(args.test)
		
	print('your choice is %s'%(args.choices))
	