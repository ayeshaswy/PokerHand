# PokerHand
PROBLEM:

Program to analyse poker hand and identify combination. Poker hands are ranked by the following partial order from lowest to highest. 
● High Card: Hands which do not fit any higher category are ranked by the value of their highest card. If the highest cards have the same value, the hands are ranked by the next highest, and so on.
● Pair: 2 of the 5 cards in the hand have the same value. Hands which both contain a pair are ranked by the value of the cards forming the pair. If these values are the same, the hands are ranked by the values of the cards not forming the pair, in
decreasing order.
● Two Pairs: The hand contains 2 different pairs. Hands which both contain 2 pairs are ranked by the value of their highest pair. Hands with the same highest pair are ranked by the value of their other pair. If these values are the same the hands are
ranked by the value of the remaning card.
● Three of a Kind: Three of the cards in the hand have the same value. Hands which both contain three of a kind are ranked by the value of the 3 cards.
● Straight: Hand contains 5 cards with consecutive values. Hands which both contain a straight are ranked by their highest card.
● Flush: Hand contains 5 cards of the same suit. Hands which are both flushes are ranked using the rules for High Card.
● Full House: 3 cards of the same value, with the remaining 2 cards forming a pair. Ranked by the value of the 3 cards.
● Four of a kind: 4 cards with the same value. Ranked by the value of the 4 cards.
● Straight flush: 5 cards of the same suit with consecutive values. Ranked by the highest card in the hand.

Sample input:
Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C AH
Black: 2H 3D 5S KS KD White: 2C 3H 4S 8C AH
Black: 2H 4S 4C 2D 4H White: 2S 8S AS QS 3S
Black: 2H 3D 5S 9C KD White: 2C 3H 4S 8C KH
Black: 2H 3D 5S 9C KD White: 2D 3H 5C 9S KH

Sample output:
White wins. - with high card: Ace
Black wins. - with pair
White wins. - with flush
Black wins. - with high card: 9
Tie.


SOLUTION:

The solution works in 4 steps:
1. Input
2. Store Player Info
3. Evaluate Player's hand (identify poker combination)
4. Decide winner and Print.


Input:

Input is handled by 'InputHandler' Class. The input can be provided in 2 ways.
* From console
* From input text file
The 'InputHandler' class accepts input, processes and validates the input.
It then passes the input to 'Hand' class.


Store Player Info:

The 'Hand class receives the processed input and saves it for further use. It then 
passes the hand information of each player one by one to 'HandEvaluator' class
for hand analysis. The output of 'HandEvaluator' analysis is also saved in the 
'Hand' class.


Evaluate Player's hand:

A player's hand is evaluated by 'HandEvaluator' class. It gets the needed input 
from the 'Hand' class and identfies the combination of highest value possible 
with the hand. The resulting information is saved back in 'Hand' Class.


Decide winner and print:

Using the analysis of 'HandEvaluator' class, the 'Judge' class decides the winner
or decides if its a tie. Judge class also prints out the result as expected.



USAGE:

A Makefile is provided with the solution which can be used to generate executable.
The executable generated using the Makefile will have the name "poker".

When you run the executable it asks th prefered mode of input.
1 for intreractive (console)
2 for file

Please provide the absolute path of the input file.

Output will be printed on the console.

once the output is printed, the application falls back to input mode.
Continue to use as many times as needed and press 0 to exit.


I have provided the input file I used for testing. It contains all possible input 
combinations that I could think of. I have also provided result captured while testing
with the input file.




ASSUMPTIONS:

One of the examples of input/ouput provided with the problem statement shows that
'flush' wins over 'full house' which is not correct. The solution implemented considers
'full house' higher than 'flush'