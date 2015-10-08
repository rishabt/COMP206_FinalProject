#!/usr/bin/python

# Import modules for CGI handling 
import cgi, cgitb 

print "Content-type:text/html\r\n\r\n"

topics = "../data/topics.csv"
members = "../data/members.csv"

# Create instance of FieldStorage 
form = cgi.FieldStorage() 

username = ""
#if "pass" in form:
username += form.getvalue("username")

button = 0

print "<FORM ACTION=\"http://cgi.cs.mcgill.ca/~rtando1/cgi-bin/MyFacebookPage.py\" METHOD=\"POST\">"
print "<DIV><b><i>Your update</i></b>:<BR>"
print "<INPUT NAME=\"data\" SIZE=\"60\" MAXLENGTH=\"80\"><BR>"
print "<input type=\"hidden\" name=\"username\" value=\"" + username + "\">"
print "<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\" NAME=\"status\"></DIV>"
print "</FORM>"

print "<br><br>"
print "<FORM ACTION=\"http://cgi.cs.mcgill.ca/~rtando1/cgi-bin/MyFacebookPage.py\" METHOD=\"POST\">"
print "<DIV><b><i>Who do you want to follow:</i></b><BR>"
print "<INPUT NAME=\"data\" SIZE=\"60\" MAXLENGTH=\"80\"><BR>"
print "<input type=\"hidden\" name=\"username\" value=\"" + username + "\">"
print "<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\" NAME=\"add\"></DIV>"
print "</FORM>"

if "status" in form:
	button = 1
	with open(topics, "a") as myfile:
		myfile.write(username + "\n")
		myfile.write(form.getvalue("data") + "\n")
elif "add" in form:
        button = 2
	data = open(members, "r")
	l = data.readlines()
	data.close()
	for line in l:
		if line.split(" ")[1] == username:
			line = line[:-1]
			line += " " + form.getvalue('data') + "\n"
			#print "<p>" + line + "</p>"
			#print "<p> YAY </p>"
			f = open(members, "w")
			for i in l:
				if i.split(" ")[1] != username:
					f.write(i + "\n")
				else:
					#print "<p>" + line + "</p>"
					f.write(line)


print "<p><b><i> Updates from friends </i></b></p>"
with open(members, "r") as f:
	for l in f.readlines():
		if l.split(" ")[1] == username:
			list_of_friends = l.split(" ")[3:]
			#print "<p>" + str(list_of_friends) + "</p>"
			data = open(topics, "r")
			lines = data.readlines()
			total = 0
			count = 0 
			for i in lines:
				if i in list_of_friends:
					if total <= 10:
						total += 1
						print "<p><b>" + lines[count] + "</b><br>" +lines[count + 1] + "</p>"
				count +=1
			#for i in range(0, lines):
			#	if i in list_of_friends:
					#print "<p>" + i + "<br>" + lines[i+1] + "</p>"
					#i++
			#		print "<p> YAY </p>"


print "<p><b><i>List of registered members</i></b></p>"
with open(members, "r") as f:
	for l in f.readlines():
		print "<p>" + l.split(" ")[1] + "</p>"

print "<p><a href=\"http://cgi.cs.mcgill.ca/~rtando1/index.html\">Logout</a></p>"
