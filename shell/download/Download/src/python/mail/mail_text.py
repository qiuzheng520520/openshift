#!/usr/bin/env python3
#coding: utf-8
import smtplib
from email.mime.text import MIMEText
from email.header import Header

sender = "lantianyu520520@163.com"
receiver = "lantianyu520520@qq.com"
subject = 'python email test'
smtpserver = 'smtp.163.com'
username = 'lantianyu520520@163.com'
password = 'xiaotangshong'

#msg = MIMEText('你好','text','utf-8')	#中文需参数‘utf-8'，单字节字符不需要
msg = MIMEText('<html><h1>你好</h1></html>','html','utf-8')	#中文需参数‘utf-8'，单字节字符不需要
msg['Subject'] = Header(subject, 'utf-8')

smtp = smtplib.SMTP("smtp.163.com",25)
#smtp.connect("smtp.163.com")
smtp.login(username, password)
smtp.sendmail(sender, receiver, msg.as_string())
smtp.quit()
