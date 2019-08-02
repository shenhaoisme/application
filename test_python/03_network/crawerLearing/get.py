import urllib.request
import urllib.parse

url='https://www.baidu.com/s?'

word = input('what')
data = {
        'ie': 'utf-8',
        'wd': word,
        }
query_string=urllib.parse.urlencode(data)
url += query_string

print(url)

response = urllib.request.urlopen(url)

filename = word + '.html'
with open(filename, 'wb') as fp:
    fp.write(response.read())
