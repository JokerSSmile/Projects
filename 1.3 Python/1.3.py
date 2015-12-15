# coding: utf-8
import re
import urllib
import urllib2
import urlparse
import os


def find_url_with_text(url, text_to_find):
    if not (url in used_urls) and text_to_find:
        used_urls.append(url)
        data = urllib2.urlopen(url).read()

        handler_urls = re.findall('href="(.*?)"', data)

        convert_data_urls = [urlparse.urljoin(url, url_temp) for url_temp in handler_urls]

        if text_to_find in data:
            print 'FIND!!!'
            download(url)

        for url_list in convert_data_urls:
            name_file = url_list.rsplit('/', 1)[-1]
            if '.htm' in name_file or '.html' in name_file:
                find_url_with_text(url_list, text_to_find)


def download(url):
    used_urls.append(url)

    content_download = urllib2.urlopen(url).read()

    data_urls = re.findall('src="(.*?)"', content_download)
    data_urls = data_urls + re.findall('href="(.*?)"', content_download)

    convert_data_urls = [urlparse.urljoin(url, urlI) for urlI in data_urls]
    name_directory = re.findall('<title>(.*?)</title>', content_download)
    name_directory = name_directory[0]
    os.mkdir(name_directory)
    os.chdir(name_directory)

    length = len(data_urls)
    for url_id in range(length):
        url = data_urls[url_id]
        filename = url.rsplit('/', 1)[-1]
        exp = (filename.rsplit('/', 1)[-1]).rsplit('.')[-1]
        try:
            if ('.' in filename) and (exp in list_of_extensions):
                print filename
                filename = 'file' + str(url_id) +  '.' + exp
                urllib.urlretrieve(convert_data_urls[url_id], filename)
                content_download = content_download.replace(url, name_directory + '/' + filename)
        except:
            print 'INCORRECT URL:'

    print content_download
    current_path = os.getcwd()
    buff_path = current_path.split('\\')[:-1]

    buff_path[0] += '\\'
    for element in buff_path[1:]:
        buff_path[0] += element + '\\'

    os.chdir(buff_path[0])

    print content_download
    file = open(name_directory + '.html', 'w')
    file.write(content_download)
    file.close()


given_url = "https://www.python.org/"
text_to_find = 'Software'
used_urls = []
list_of_extensions = ['gif', 'bmp', 'jpg', 'jpeg', 'png', 'js', 'css', 'html', 'ico']

find_url_with_text(given_url, text_to_find)
print "DONE"
