#!/usr/bin/env python3  
#coding: utf-8  
import smtplib  
from email.mime.multipart import MIMEMultipart  
from email.mime.text import MIMEText  
from email.mime.image import MIMEImage  
  
sender = 'lantianyu520520@163.com'  
receiver = 'lantianyu520520@qq.com'  
subject = 'python email test'  
smtpserver = 'smtp.163.com'  
username = 'lantianyu520520@163.com'  
password = 'xiaotangshong'  
    
msgRoot = MIMEMultipart('related')  
msgRoot['Subject'] = 'test'  
	  
msgText = MIMEText('<html><p>test by python,time:2015-5-8</p></html>','html','utf-8')  
msgRoot.attach(msgText)  
#构造附件  
#att = MIMEText(open('/var/lib/openshift/543dd9894382ec666100002d/app-deployments/test/src/python/html/image/1.jpg', 'rb').read(), 'base64', 'utf-8')  
att = MIMEText(open('/var/lib/openshift/543dd9894382ec666100002d/app-deployments/test/src/python/html/log.txt', 'rb').read(), 'base64', 'utf-8')  
att["Content-Type"] = 'application/octet-stream'  
att["Content-Disposition"] = 'attachment;filename="log.txt"'  
msgRoot.attach(att)  
	            
smtp = smtplib.SMTP()  
smtp.connect('smtp.163.com')  
smtp.login(username, password)  
smtp.sendmail(sender, receiver, msgRoot.as_string())  
smtp.quit()  
