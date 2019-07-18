import urllib.request

quest_url = 'https://fanyi.baidu.com/sug'

my_headers = {
   'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36'
}


from_data = {
    'kw':'baby'
}

from_data = urllib.parse.urlencode(from_data).encode()
request = urllib.request.Request(quest_url, headers = my_headers, )

response = urllib.request.urlopen(request, data=from_data)

print('OK')


