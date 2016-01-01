# Upload data from local esp8266 mains monitor to remote server
# install as cron job with
# sudo crontab -e
# add at the end of the cron file:
# */1 * * * * python /home/pi/readmeter.py


import urllib 
from xml.dom import minidom
import httplib

usock = urllib.urlopen('http://10.0.0.120/xmlfeed') 
xmldoc = minidom.parse(usock)                              
usock.close()                                              
#print xmldoc.toxml() 


name = xmldoc.getElementsByTagName("gasmeter")[0]
gasmeter = name.firstChild.data.strip()

name = xmldoc.getElementsByTagName("electricmeter")[0]
electricmeter = name.firstChild.data.strip()

name = xmldoc.getElementsByTagName("mainscurrent")[0]
mainscurrent = name.firstChild.data.strip()

name = xmldoc.getElementsByTagName("mainscurrentavg")[0]
mainscurrentavg = name.firstChild.data.strip()

name = xmldoc.getElementsByTagName("mainscurrentmax")[0]
mainscurrentmax = name.firstChild.data.strip()

querystring = 'gasmeter='
querystring += gasmeter
querystring += '&'

querystring += 'electricmeter='
querystring += electricmeter
querystring += '&'

querystring += 'mainscurrent='
querystring += mainscurrent
querystring += '&'

querystring += 'mainscurrentavg='
querystring += mainscurrentavg
querystring += '&'

querystring += 'mainscurrentmax='
querystring += mainscurrentmax
# debug values if needed
#print(querystring)

uploadurl = 'http://www.yourserver.com/save.aspx?' + querystring
response = urllib.urlopen(uploadurl)  
print response.read()
response.close()