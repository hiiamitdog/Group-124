# 1. Identification:
Group 124.
Card of Five.
Contributed by Chung Yiu San;
And by Lam Wu, Kevin.

# 2. Description:
The game we chose to design is card of five. In which, each player would be dealt five cards from a deck of 52. The winner is determined based on the ranks of the five hands. A primary program handles the courses of a game, including but not limited to asking the number of players, initializing the deck and announcing the winner. Two secondary programs are included. The first one is printMenu.cpp, which displays the main menu of the game, while the second one is printCard.cpp, which facilitates the printing of each player's hand. A text file called "HallOfFame" is as well included, which takes record of all the hands obtained by each player at the end of every round.

# 3. Features:
# 3.1 Random
Cards are randomly dealt to each player.
srand(time(NULL)) with header file <time.h> and <stdlib.h> are adopted to generate a random seed and deal random hands to players.
# 3.2 Data Structure
A class of player, which includes the player's name, hands, and value returned by evaluation algorithm.
Players' names, hands and their values can be accessed by player.name, player.hand and player.value.
# 3.3 Dynamic Memory
A vector of the player class (i.e. vector<player>), supporting a varying number of player from at least 1 to at most 10.
vector<player> is also adopted to facilitate record-taking into HallOfFame file.
# 3.4 File Manipulation
Reading and writing of HallOfFame, to record the name and hand of each player at the end of each round.
# 3.5 Multiple Codes
1 primary (CardOfFive.cpp) and 2 secondary (printMenu.cpp and printCard.cpp) programs, and makefile for compilation.
printMenu.cpp is seperated out so that it can be reused for generating main menus for other games or applications in the future.
printCard.cpp is as well seperated out so that it can be reused for printing players' hands in other Poker games.

# 4. The Card of Five Game:
A card of five game is played by drawing five cards and comparing ranks against other players. Different types of rank are listed across # 4.1 - # 4.3 in descending order of their .
# 4.1 Hands
The ranks of hand is descending order is:
1) Straight Flush
2) 4 of a Kind
3) Full House
4) Flush
5) Straight
6) 3 of a Kind
7) Two Pair
8) One Pair
9) High Card
# 4.2 Cards
1) The highest card is Ace or A
2) and lowest card is Deuce or 2
# 4.3 Suits
The rank of suits in descending order is:
1) Spade ♠
2) Heart ♥
3) Club ♣
4) Diamond ♦

# 5 Libraries
1) stdlib.h for screen-clearing by the system
2) time.h to randomize seed with srand(time(NULL))
3) fstream for file manipulation (i.e. input/output)
4) algorithm to make use of find() and search() functions for sorting and searching within list<string>

# 6 Quick Start
1) Generate an executable game by entering "make p" in the terminal.

2) Execute the game by entering "./p" in the terminal.

1) A main menu will be displayed upon execution. In the main menu, there are 3 options to choose from: <br />
        1. Start a new round (by entering "1") <br />
        2. View hall of fame (by entering "2") [Hall of fame records all the hands in previous gameplays] <br />
        3. Exit game (by entering "3") <br />

2) By entering "1": <br />
        A. Enter the number of players in this round, then enter the name of each player one by one. <br />
        B. 5 cards will be randomly dealt to each player. <br />
        C. Hands of each player will be shown, in descending order of each hand's ranking. The player with the greatest ranking will be announced winner. <br />
        D. Enter 'Y' or 'y' record all the hands in this round into Hall of fame, so that they can be reviewed anytime through hall of fame in the main menu; enter 'N' or 'n' otherwise. <br />
        E. Main menu will be displayed. <br />

3) By entering "2": <br />
        A. You can view all the 'admitted' hands in previous rounds, up to 99 recent records. <br />
        B. Each hand will be displayed in lines of < player > < player's hand >. <br />

4) By entering "3": <br />
        A. The game will be closed. <br />

5) Good day and enjoy the game! :)
