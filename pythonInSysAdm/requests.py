import requests, sys

def requests_demo_get():
        cookies = {'a': 123}
        headers = dict({'User-Agent': 'Hello_O'})
        r = requests.get('http://google.com/search?q=hello', cookies = cookies, headers = headers, allow_redirects = True)
        print '[Request] uri: ' + r.request.path_url
        print '[Request] url: ' + r.request.full_url
        print '[Request] headers: \n' + str(r.request.headers)
        print '[Response] ok flag: ' + str(r.ok)
        print '[Response] status code: ' + str(r.status_code)
        print '[Response] redirects followed: ' + str(len(r.history))
        print '[Response] final url: ' + r.url
        print '[Response] encoding: ' + r.encoding
        print '[Response] cookies set: \n' + str(r.cookies)
        print '[Response] headers: \n' + str(r.headers)
        print '[Response] header example: ' + r.headers['date']
        print '[Response] content (first 512 bytes): \n' + r.text[0:511]

def requests_demo_post():
        cookies = {'a': 123}
        headers = dict({'User-Agent': 'Hello_O'}), 
        r = requests.post('http://google.com/search?q=hello', cookies = cookies, headers = headers, allow_redirects = True)
        print '[Request] uri: ' + r.request.path_url
        print '[Request] url: ' + r.request.full_url
        print '[Request] headers: \n' + str(r.request.headers)
        print '[Response] ok flag: ' + str(r.ok)
        print '[Response] status code: ' + str(r.status_code)
        print '[Response] redirects followed: ' + str(len(r.history))
        print '[Response] final url: ' + r.url
        print '[Response] encoding: ' + r.encoding
        print '[Response] cookies set: \n' + str(r.cookies)
        print '[Response] headers: \n' + str(r.headers)
        print '[Response] header example: ' + r.headers['date']
        print '[Response] content (first 512 bytes): \n' + r.text[0:511]

def requests_demo_auth(login = sys.argv[1], password = sys.argv[2]):
        r = requests.get('http://10.0.0.1', auth = (login, password))
        print r.text

#requests_demo_get()
requests_demo_auth()
