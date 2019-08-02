family={
        'me' : 'Hao shen',
        'father' : 'wenxing shen',
        'mother' : 'wei hu',
        }

list = []
for p, i in family.items():
    list.append(p + ' is ' + i)
#fix each two item to one string using &&
string=' && '.join(list) # if it is family(dictionary), only print key(the map is key : value) 
print('the family has ' + string)

