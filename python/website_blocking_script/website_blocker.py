# python scriopt that modify's hosts file to act as a sudo firewall during
#hours that was between the mentioned times. 8 a- 4 p

import time
from datetime import datetime as dt   # import time module for firewall during the times

hosts_temp="hosts"
hosts_path=r"C:\Windows\System32\drivers\etc\hosts"
redirect="127.0.0.1"
website_list=["www.facebook.com","facebook.com","youtube.com","wwww.youtube.com"]

while True: # check current time vs time slive 8am - 4pm
    if   dt(dt.now().year,dt.now().month,dt.now().day,8)  < dt.now() <  dt(dt.now().year,dt.now().month,dt.now().day,16):
        print("working hours")
        with open(hosts_path,"r+") as file: # open & read hosts file save as content
            content=file.read()
            for website in website_list:   # loop and see if web_site list in hosts file and in working hours pass
                if website in content:
                    pass                   # pass = nothing happens
                else:
                    file.write(redirect+ " " + website + "\n")    #write in black list website_list
    else:
        with open(hosts_path, "r+") as file:
            content = file.readlines()
            file.seek()
            for line in content:
                if not any(website in line for website in website_list):
                    file.write(line)
            file.truncate() # remove everthing after cursor
        print("Fun Hours ...")

    time.sleep(5)   # sleep exectuion so script isn't being runned every mili second
