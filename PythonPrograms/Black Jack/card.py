class Card(object):
	"""docstring for Card"""
	def __init__(self, rank, suit):
		super(Card, self).__init__()
		self.rank = rank
		self.suit = suit

	def cardValue(self):
		print("{0} of {1}".format(self.rank, self.suit))
		