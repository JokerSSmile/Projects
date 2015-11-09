# Patrushev Oleg PS-21


import requests
import urllib
import urlparse
from lxml import html



given_url = 'http://lenta.ru/'
response = requests.get(given_url)
page = html.fromstring(response.text)
urllib.urlretrieve(given_url, filename='index.html')
file = open('index.html', 'r')
text = file.read()
file.close()
i = 1;

page.make_links_absolute(given_url)
image_urls = page.xpath('//img/@src')
css_urls = page.xpath('//link/@href')
js_urls = page.xpath('//script/@src')
urls = image_urls + css_urls + js_urls
urls = [urlparse.urljoin(response.url, url) for url in urls]
for url in urls:
    try:
        name = (url.rsplit('/', 1)[-1]).rsplit('.')[-1]
        name = '.' + name
        urllib.urlretrieve(url.encode('raw-unicode-escape'), 'downloaded_files/file' + str(i) + str(name))
        text = text.replace(url.encode('raw-unicode-escape'), 'downloaded_files/file' + str(i) + str(name))
        i += 1;
    except IOError:
        print 'Invalid URL'
file = open('index.html', 'w')
file.write(text)
file.close()
print 'Done'
