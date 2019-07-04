#! /bin/env/python

class BankAccount:
	def __init__(self, number, name, balance):
		self.number=number
		self.name =name
		self.balance=balance
	def SaveMoney(self, money):
		self.balance += money 
	def WithDraw(self, money):
		self.balance -= money
