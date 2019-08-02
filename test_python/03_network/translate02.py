import urllib.request
import urllib.parse
'''
in request headers. 
    should not contains gzip info, because brower can unzip message.
    content lenght can be set. 
'''
request_URL = 'https://fanyi.baidu.com/v2transapi'

request_headers = {
	'Accept': '*/*',
	'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
	'Origin': 'https://fanyi.baidu.com',
	'Referer': 'https://fanyi.baidu.com/',
	'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36',
	'X-Requested-With': 'XMLHttpRequest',
	'cookie': 'BAIDUID=87FFBBD37218732EADF547CB27300E2C:FG=1; BIDUPSID=87FFBBD37218732EADF547CB27300E2C; PSTM=1537499414; REALTIME_TRANS_SWITCH=1; FANYI_WORD_SWITCH=1; HISTORY_SWITCH=1; SOUND_SPD_SWITCH=1; SOUND_PREFER_SWITCH=1; BDUSS=1VPamQtdmV0bFRsWkdoUktEUmFRcEJPR1ZuY0NadG5IZHZCbWtKaUo1dzQzejVjQVFBQUFBJCQAAAAAAAAAAAEAAADs4BI2w6TIy8nkyta1xMrAvecAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADhSF1w4UhdcV; MCITY=-%3A; pgv_pvi=6094193664; BDRCVFR[feWj1Vr5u3D]=I67x6TjHwwYf0; delPer=0; BDRCVFR[suEBtok9FlY]=mbxnW11j9Dfmh7GuZR8mvqV; H_PS_PSSID=1450_21088_29523_29518_28519_29099_28830_29220; PSINO=3; BDORZ=B490B5EBF6F3CD402E515D22BCDA1598; locale=zh; Hm_lvt_64ecd82404c51e03dc91cb9e8c025574=1562295231,1563437375; pgv_si=s9540036608; yjs_js_security_passport=3114cc903865f745b1afe7f6100e7e09e4eb0431_1563519375_js; from_lang_often=%5B%7B%22value%22%3A%22fra%22%2C%22text%22%3A%22%u6CD5%u8BED%22%7D%2C%7B%22value%22%3A%22zh%22%2C%22text%22%3A%22%u4E2D%u6587%22%7D%2C%7B%22value%22%3A%22en%22%2C%22text%22%3A%22%u82F1%u8BED%22%7D%5D; to_lang_often=%5B%7B%22value%22%3A%22en%22%2C%22text%22%3A%22%u82F1%u8BED%22%7D%2C%7B%22value%22%3A%22zh%22%2C%22text%22%3A%22%u4E2D%u6587%22%7D%5D; Hm_lpvt_64ecd82404c51e03dc91cb9e8c025574=1563519405'
}

from_data = {	
	'from': 'en',
	'to': 'zh',
	'query': 'baby',
	'transtype': 'realtime',
	'simple_means_flag': '3',
	'sign': '814534.560887',
	'token': 'c8379e7424a735f6d9e36cc342294134'

}
#get response
ob = urllib.request.Request(request_URL, headers = request_headers)
#urlencode ==> can make dectionary to one string(URL format)
#but encode ??
from_data = urllib.parse.urlencode(from_data).encode()

response = urllib.request.urlopen(ob, data = from_data)

print(response.read().decode())
