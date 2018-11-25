from deck import Deck
import random

def is_not_int(input):
	try:
		input = int(input)
	except ValueError:
		return True
	else:
		return False

def handTotal(hand):

	handTotal = 0
	userInput = "l"
	for card in hand:
		if is_not_int(card.rank):
			if card.rank == "ace":
				userInput = input("Press 1 to give the ace a value of 1 and 2 to give the ace a value of 11: ")
				if is_not_int(userInput):
					while is_not_int(userInput):
						userInput = input("Press 1 to give the ace a value of 1 and 2 to give the ace a value of 11: ")
				userInput = int(userInput)
				if userInput < 1 or userInput > 2:
					userInput = "l"
				if userInput == 1:
					handTotal = handTotal + 1
				else:
					handTotal = handTotal + 11
			else:
				handTotal = handTotal + 10
		else:
			handTotal = handTotal + card.rank

	return handTotal

def handTotalAI(hand):

	handTotal = 0
	userInput = "l"
	for card in hand:
		if is_not_int(card.rank):
			if card.rank == "ace":
				userInput = int(random.random()) + 1

				if userInput < 1 or userInput > 2:
					userInput = "l"

				if userInput == 1:
					handTotal = handTotal + 1
				else:
					handTotal = handTotal + 11
			else:
				handTotal = handTotal + 10
		else:
			handTotal = handTotal + card.rank

	return handTotal


def printHand(hand):
	for card in hand:
		card.cardValue()

playAgain = 0

while playAgain == 0: # Play again loop
	
	# Initialize everything for blackjack
	playerHand = []
	dealerHand = []
	deck = Deck()
	deck.shuffle()
	print("-----------------------------------------------------------------------------------------------")
	playerHand.append(deck.dealCard())
	playerHand.append(deck.dealCard())
	dealerHand.append(deck.dealCard())
	dealerHand.append(deck.dealCard())
	playerInput = "l";
	dealerChoice = -1
	playerHandTotal = -1
	dealerHandTotal = -1
	playerHold = False

	# Gameplay loop
	while  playerHandTotal < 21 and dealerHandTotal < 21:
		print("You have: ")
		printHand(playerHand)
		print()
		print("The dealer's top card is: ")
		dealerHand[0].cardValue()
		print("-----------------------------------------------------------------------------------------------")
		
		playerInput = input("Press 0 to hold and 1 to hit: ")
		while is_not_int(playerInput):
			playerInput = input("Press 0 to hold and 1 to hit: ")
		playerInput = int(playerInput)

		if playerInput == 1:
			playerHand.append(deck.dealCard())
			print("The dealer gives you the", playerHand[len(playerHand) - 1].rank, "of", playerHand[len(playerHand) - 1].suit)
		else:
			playerHold = True
			break

		dealerChoice = int(random.random())

		if dealerChoice == 0:
			print("The dealer holds")
		else:
			print("The dealer takes a card")
			dealerHand.append(deck.dealCard)

		playerHandTotal = handTotal(playerHand)
		dealerHandTotal = handTotalAI(dealerHand)
		print("")

	if playerHold == True:
		dealerChoice = int(random.random())

		if dealerChoice == 0:
			print("The dealer holds")
		else:
			print("The dealer takes a card")
			dealerHand.append(deck.dealCard)
		print()

		playerHandTotal = handTotal(playerHand)
		dealerHandTotal = handTotalAI(dealerHand)
		print("")

	print("You have: ")
	printHand(playerHand)
	print()
	print("The house had: ")
	printHand(dealerHand)
	print()
	
	if playerHandTotal == 21 and dealerHandTotal == 21:
		print("Tie")
	elif playerHandTotal == 21:
		print("You win")
	elif dealerHandTotal == 21:
		print("The house wins")
	elif playerHandTotal > 21:
		print("You bust. The house wins")
	elif dealerHandTotal > 21:
		print("The house busts. You win")
	elif playerHandTotal > dealerHandTotal:
		print("You win")
	elif playerHandTotal < dealerHandTotal:
		print("The house wins")

	playAgain = input("Press 0 to play again: ")
	if not is_not_int(playAgain):
		playAgain = int(playAgain)