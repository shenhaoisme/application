#encoding ='utf-8'

class except_raise(Exception):
	"""docstring for except_raise"""
	def _init__(self, length, least):
			#super(Exception, self).__init__()
			Exception.__init__(self)
			self.len = length
			self.least = least

try:
	text = input("please input something, len more than 3 bytes \n")
	if len(text) < 3:
		raise except_raise(len(text), 3)
except EOFError:
	print('Why did you do an EOF on me?')
except except_raise as er:
	print(('input is {0} less than len is asked for {1}').format(er.length, er.least))