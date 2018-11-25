import random

def is_not_int(input):
	try:
		input = int(input)
	except ValueError:
		print("That is not an int")
		return True
	else:
		return False

play_again = 0
dice = 0

while play_again == 0:
	dice = int(random.random() * 6)
	print("You rolled a ", dice)
	play_again = input("Press 0 to roll again: ")
	
	while is_not_int(play_again):
		play_again = input("Press 0 to roll again: ")