# Patrushev Oleg PS-21


import requests
import urllib
import urlparse
from lxml import html



given_url = 'http://luboeporno.com//'
response = requests.get(given_url)
page = html.fromstring(response.text)
urllib.urlretrieve(given_url, filename='index.html')
file = open('index.html', 'r')
text = file.read()
file.close()
page.make_links_absolute(given_url)
image_urls = page.xpath('//img/@src')
css_urls = page.xpath('//link/@href')
js_urls = page.xpath('//script/@src')
urls = image_urls + css_urls + js_urls
urls = [urlparse.urljoin(response.url, url) for url in urls]
for url in urls:
    try:
        name = url.rsplit('/', 1)[-1]
        urllib.urlretrieve(url.encode('raw-unicode-escape'), 'downloaded_files/%s' % name)
        text = text.replace(url, 'downloaded_files/%s' % name)
    except IOError:
        print 'Invalid URL'
file = open('index.html', 'w')
file.write(text)
file.close()

