import os
import re

import requests
import urllib
from bs4 import BeautifulSoup
HEADERS = {
            'X-Requested-With': 'XMLHttpRequest',
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 '
                                  '(KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36',
                                      'Referer': 'http://www.mzitu.com'
                                      }


def get_url():
    page_url = 'https://m.mzitu.com/188091/2'
    page_url1 = 'http://pic19.nipic.com/20120309/3145425_091538022000_2.jpg'
    responese = urllib.request.urlopen(page_url)
    with open('./qing.jpg', 'wb') as fp:
        fp.write(responese.read())
HEADERS = {
            'X-Requested-With': 'XMLHttpRequest',
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 '
                                  '(KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36',
                                      'Referer': 'http://www.mzitu.com'
                                      }
    #requests.get(page)
def request_get():
    '''
    get 188091 shenmengyao 50 picture
    '''

    page_urls = ['http://www.mzitu.com/188091/{cnt}'.format(cnt=cnt)
            for cnt in range(2,10)]
    print("2 -50 pictures")
    
    img_urls=[]
    for page_url in page_urls:
        print(page_url)
        responese = requests.get(page_url, headers=HEADERS, timeout=10)
        print(responese.status_code)
		
		
        bs = BeautifulSoup(responese.text,'html.parser').find('ul', id="pins")
        result = re.findall(r"(?<=href=)\S+", str(bs))

        img_url = [url.replace('"', "") for url in result]
        img_urls.extend(img_url)
        return set(img_urls)
if __name__ == '__main__' :
    #test 1
    # get_url()
    #test 2
    request_get()
	
	
	
	
