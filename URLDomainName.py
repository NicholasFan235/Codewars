

prefParts = {'https:', 'http:', 'www', ''}

def domain_name(url):
    url = url.replace('.', '/')
    url = url.split('/')
    for part in url:
        if part not in prefParts:
            return part


domain_name("http://google.com")
domain_name("http://google.co.jp")
domain_name("www.xakep.ru")
domain_name("https://youtube.com")
