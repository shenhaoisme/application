import os
import requests
import urllib
from bs4 import BeautifulSoup

def get_url():
    page_url = 'https://m.mzitu.com/188091/1'
    page_url1 = 'http://pic19.nipic.com/20120309/3145425_091538022000_2.jpg'
    responese = urllib.request.urlopen(page_url)
    with open('./qing.jpg', 'wb') as fp:
        fp.write(responese.read())


    #requests.get(page)
def request_get():
    #just test without jpg's path, call method get
    page_url = 'https://m.mzitu.com/188091/1'
    responese = requests.get(page_url)
    print(responese.status_code)

if __name__ == '__main__' :
    #test 1
    #get_url()
    #test 2
    request_get()
