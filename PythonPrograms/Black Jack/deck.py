import random
from card import Card

class Deck(object):
	"""docstring for Deck"""
	def __init__(self):
		super (Deck, self).__init__()
		self.deckList = []
		self.suit = ['spades', 'hearts', 'diamonds', 'clubs']
		self.rank = ['ace', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'jack', 'queen', 'king']
		for s in self.suit:
			for r in self.rank:
				self.deckList.append(Card(r, s))

	def shuffle(self):
		tempDeck = [None] * 52
		while len(self.deckList) > 0:
			randomIndex = int(random.random() * 52)
			if tempDeck[randomIndex] == None:
				tempDeck[randomIndex] = self.deckList.pop()
		self.deckList = tempDeck
		print("\nshuffled deck\n")

	def dealCard(self):
		return self.deckList.pop()

	def printDeck(self):
		for card in self.deckList:
			card.cardValue()
