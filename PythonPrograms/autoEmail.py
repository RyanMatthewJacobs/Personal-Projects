# Import smtplib for the actual sending function
import smtplib

# Import the email modules we'll need
from email.mime.text import MIMEText

sender = 'rybread42@gmail.com'
receiver = 'rymajaco@ucsc.edu'
filename = 'emailTemplate.txt'
# Open a plain text file for reading.  For this example, assume that
# the text file contains only ASCII characters.

with open(filename, 'rb') as fp:
    # Create a text/plain message
    msg = MIMEText(fp.read())

# me == the sender's email address
# you == the recipient's email address
msg['Subject'] = 'The contents of %s' % textfile
msg['From'] = sender
msg['To'] = receiver

# Send the message via our own SMTP server, but don't include the
# envelope header.
s = smtplib.SMTP('localhost')
s.sendmail(sender, [receiver], msg.as_string())
s.quit()