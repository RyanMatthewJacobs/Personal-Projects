"""
This program reads in the sender's email credentials and sends an email to a number of recipients.
The body of the email is contained in emailTemplate.txt. The list of contacts to send the email
to is contained in contacts.txt.
"""

# used to login into the sender's email and send the emails
import smtplib
import ssl
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

# used for the body of the email
from string import Template 
import datetime

def get_address_info(filename):
	"""
	Return two strings with the address and password
	"""

	with open(filename, mode='r', encoding='utf-8') as address_file:
		for line in address_file:
			info = line.split()
			address = info[0]
			password = info[1]
		return address, password

def get_contacts(filename):
	"""
	Return two lists names, emails containing names and email addresses
	read from a file specified by filename.
	"""
	
	names = []
	emails = []
	with open(filename, mode='r', encoding='utf-8') as contacts_file:
		for a_contact in contacts_file:
			contact = a_contact.split()
			if(len(contact) != 2):
				continue
			names.append(contact[0])
			emails.append(contact[1])
		return names, emails

def read_template(filename):

	"""
	Returns a Template object comprising the contents of the 
	file specified by filename.
	"""
	
	with open(filename, 'r', encoding='utf-8') as template_file:
		template_file_content = template_file.read()

		return Template(template_file_content)

def main():
	MY_ADDRESS, PASSWORD = get_address_info('mailAddress.txt') # get login info
	names, emails = get_contacts('contacts.txt')               # read contacts
	message_template = read_template('emailTemplate.txt')      # get the email template

	# set up the SMTP server
	s = smtplib.SMTP(host='smtp.gmail.com', port=25)
	s.connect(host='smtp.gmail.com', port=25)
	s.ehlo()
	s.starttls()
	s.ehlo()
	s.login(MY_ADDRESS, PASSWORD)
	print("Logged in")

	# For each contact, send the email:
	for name, email in zip(names, emails):
		msg = MIMEMultipart()       # create a message

		# set name of person
		message = message_template.safe_substitute(PERSON_NAME=name.title())
		message = Template(message)

		# set the next work day
		dayOfWeek = datetime.date.today().weekday()
		if(dayOfWeek >= 4):
			message = message.substitute(DATE='Monday')
		else:
			tomorrow = datetime.date.today()
			tomorrow = tomorrow.replace(day = datetime.date.today().day + 1)
			message = message.substitute(DATE=tomorrow.strftime("%A"))

		# Prints out the message body for our sake
		print(message)

		# setup the parameters of the message
		msg['From'] = MY_ADDRESS
		msg['To'] = email
		msg['Subject'] = "Hello World"
		
		# add in the message body
		msg.attach(MIMEText(message, 'plain'))
		
		# send the message via the server set up earlier.
		s.send_message(msg)
		del msg
		
	# Terminate the SMTP session and close the connection
	s.quit()
	
if __name__ == '__main__':
	main()