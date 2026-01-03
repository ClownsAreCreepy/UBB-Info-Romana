# Let us consider that we have a sum M of money and coins of 1, 5, 25 units (an unlimited number of coins).
# The problem is to establish a modality to pay the sum M using a minimum number of coins.
def selectMostPromissing(c):
    """
      select the largest coin from the remaining
      c - candidate coins
      return a coin
    """
    return max(c)


def acceptable(b):
    """
   verify if a candidate solution is valid
   basically verify if we are not over the sum M
    """
    sum = _computeSum(b)
    return sum <= SUM


def solution(b):
    """
   verify if a candidate solution is an actual solution
   basically verify if the coins conduct to the sum M
   b – candidate solution
    """
    sum = _computeSum(b)
    return sum == SUM


def _computeSum(b):
    """
   compute the payed amount with the current candidate
    return int, the payment
   b – candidate solution
    """
    sum = 0
    for coin in b:
        nrCoins = (SUM - sum) / coin
        # if this is in a candidate solution we need to use at least 1 coin
        if nrCoins == 0: nrCoins = 1
        sum += nrCoins * coin
    return sum


def printSol(b):
    """
      Print the solution: NrCoinns1 * Coin1 +  NrCoinns2 *
   Coin2 +...
    """
    solStr = ""
    sum = 0
    for coin in b:
        nrCoins = (SUM - sum) / coin
        solStr += str(nrCoins) + "*" + str(coin)
        sum += nrCoins * coin
        if SUM - sum > 0: solStr += " + "
    print (solStr)