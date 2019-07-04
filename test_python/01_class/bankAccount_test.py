#! /bin/env/python 

from bankAccount import BankAccount

Tom = BankAccount("1234","Tom", 100)
Jerry = BankAccount("2345", "Jerry", 200)
def _compare():
    if Tom.balance > Jerry.balance:
        print("Tom is more rich than Jerry")
    else:
        print("Tom is more poor than Jerry")

_compare()

print("now I give Tom $200,and Tom save it ")

Tom.SaveMoney(200)
_compare()
#print(Tom.balance)
print("Tom withdraw $150 by himself")
Tom.WithDraw(150)
_compare()
