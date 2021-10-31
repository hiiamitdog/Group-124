# 1. Identification:
Group 124
Poker Game of Five Card Draw
Contributed by Chung Yiu San
And by Lam Wu, Kevin

# 2. Description:
The game we chose to design is a poker game of five card draw. In which, each player would be dealt five cards from a deck of 52. The winner is determined based on the ranks of the five hands. A primary program handles the courses of a game, including but not limited to asking the number of players, initializing the deck, announcing the winner. A secondary program is required to generate a text file, called "rank.txt" which ranks all 2,598,960 distinct combinations of hands, in descending order of ranks to return a corresponding index.

# 3. Features:
# Random - an array of cards denotation is randomized. The n-th card belongs to player ((n modulo m) + 1), where m is the number of player.
# Data Structure - a class of player, which includes the player's name, players' wealth, sorted hands, and an index returned by search in rank.txt, for storing game # status and facilitating hands comparison.
# Dynamic Memory - a vector of the player class, supporting a varying number of player from at least 1 to at most 10.
# File Manipulation - 1) writing of rank.txt, reading content of rank.txt into array to make comparison between hands;
                    2) writing of hallOfFame.txt, to record the final wealth of each player at the end of the game.
# Multiple Codes - a primary (main) and secondary (text file) program, and makefile for compilation.
