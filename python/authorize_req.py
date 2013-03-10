import requests

r = requests.get('https://accounts.google.com', auth=('A.Panyakin8@gmail.com', 'iniesta8'))

print r.text
