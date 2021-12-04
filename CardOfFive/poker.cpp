#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include "printCard.h"
#include "printMenu.h"
using namespace std;
// Define string array card as a deck of cards
string card[52] =
{
    "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "aJ", "aQ", "aK", "aA",
    "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "b10", "bJ", "bQ", "bK", "bA",
    "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "cJ", "cQ", "cK", "cA",
    "d2", "d3", "d4", "d5", "d6", "d7", "d8", "d9", "d10", "dJ", "dQ", "dK", "dA"
};
list<string> used; // to record cards that have been drawn to avoid the same card being repeatedly drawn
list<long> numOnly; // to record numbers of cards in each hand
class player // to define class player to record players' information (name, hand and its rank)
{
    public:
        string name;
        string hand;
        long value;
    bool operator > (const player& dummy) const
    {
        return (value > dummy.value);
    }
};
vector<player> flowOfPlayer (10); // to record every player's hand in each round
vector<player> hofPlayer (99); // to record recently 'admitted' hands held by players up to 99 records (players can choose to record his hand or not after each round)
// initIns() function to initialize a new round by dealing cards to n players
void initIns(long n)
{
    used.clear();
    long myRandom;
    srand(time(NULL));
    for (long h = 0; h < n; h++)
    {
        for (long i = 0; i < 5; i++)
        {
            do
            {
                myRandom = rand() % 52;
            } while (find(used.begin(), used.end(), card[myRandom]) != used.end());
            flowOfPlayer[h].hand += card[myRandom];
            flowOfPlayer[h].hand += " ";
            used.push_back(card[myRandom]);
        }
    }
}
// stripFace() function to update list numOnly with the numbers of a hand
void stripFace(string ins)
{
    numOnly.clear();
    string num;
    string w = "";
    list<string> temp;
    for (long i = 0; i < ins.length(); i++)
    {
        if (ins[i] != 'a' && ins[i] != 'b' && ins[i] != 'c' && ins[i] != 'd')
            num += ins[i];
    }
    for (long i = 0; i < num.length(); i++)
    {
        if (num[i] == ' ')
        {
            temp.push_back(w);
            w = "";
        }
        else
        {
            w += num[i];
        }
    }
    list<string>::iterator itr;
    for (itr = temp.begin(); itr != temp.end(); itr++)
    {
        if (*itr == "2") numOnly.push_back(1);
        if (*itr == "3") numOnly.push_back(2);
        if (*itr == "4") numOnly.push_back(3);
        if (*itr == "5") numOnly.push_back(4);
        if (*itr == "6") numOnly.push_back(5);
        if (*itr == "7") numOnly.push_back(6);
        if (*itr == "8") numOnly.push_back(7);
        if (*itr == "9") numOnly.push_back(8);
        if (*itr == "10") numOnly.push_back(9);
        if (*itr == "J") numOnly.push_back(10);
        if (*itr == "Q") numOnly.push_back(11);
        if (*itr == "K") numOnly.push_back(12);
        if (*itr == "A") numOnly.push_back(13);
    }
}
// cHall() function to create a HallOfFame.txt file
void cHall()
{
    fstream hall;
    hall.open("HallOfFame", ios::out);
    if (!hall) cout << "Something went wrong..." << endl;
    else hall.close();
}
// rHall() function to return number of records in HallOfFame.txt file
int rHall()
{
    fstream hall;
    int counter = 0;
    hall.open("HallOfFame", ios::in);
    while (!hall.eof())
    {
        getline(hall, hofPlayer[counter].name);
        getline(hall, hofPlayer[counter].hand);
        counter++;
    }
    hall.close();
    return counter;
}
// aHall() function to ask if winner's hand will be admitted into HallOfFame.txt file
int aHall(int counter)
{
    char response;
    do
    {
        cout << "Admit winner to hall of fame? (Y/N): ";
        cin >> response;
    } while (response != 'y' && response != 'Y' && response != 'n' && response != 'N');
    if (response == 'y' || response == 'Y')
    {
        hofPlayer[counter].name = flowOfPlayer[0].name;
        hofPlayer[counter].hand = flowOfPlayer[0].hand;
        return 1;
    }
    else return 0;
}
// wHall() function to update HallOfFame.txt file with new records
void wHall(int counter)
{
    fstream hall;
    hall.open("HallOfFame", ios::out);
    for (int i = 0; i < counter; i++)
    {
        hall << hofPlayer[i].name << endl;
        hall << hofPlayer[i].hand << endl;
    }
    hall.close();
}
// evaFace() function to return a sum carrying information about the suits in a hand
long evaFace(string ins)
{
    string faceOnly;
    long val;
    for (long i = 0; i < ins.length(); i++)
    {
        if (ins[i] == 'a' || ins[i] == 'b' || ins[i] == 'c' || ins[i] == 'd')
            faceOnly += ins[i];
    }
    for (long i = 0; i < 5; i++)
    {
        switch (faceOnly[i])
        {
            case 'a':
                val += 1;   // val + 1 for a ♦ card
                break;
            case 'b':
                val += 2;   // val + 2 for a ♣ card
                break;
            case 'c':
                val += 3;   // val + 3 for a ♥ card
                break;
            case 'd':
                val += 4;   // val + 4 for a ♠ card
                break;
        }
    }
    return val;
}
// evaNum() function to return a sum of the numbers in a hand
long evaNum(list<long> l)
{
    list<long>::iterator itr;
    long counter = 1;
    long val = 0;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        val += *itr * counter * 10;
    }
    return val;
}
// evaPair() function to check for pairs in a hand
// Note: 1 pair and 2 pairs return different values
long evaPair(list<long> l)
{
    long flag[13];
    long numOfPair = 0;
    long pair;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 2)
        {
            numOfPair++;
            pair += i+1;
        }
    }
    if (numOfPair > 0) return 1000 * pair; // 1 pair: return 1000 points; 2 pairs: return 2000 points
    return 0;
}
// evaThreeOfAKind() function to check for three of a kind in a hand
// Note: Four of a kind are not included
long evaThreeOfAKind(list<long> l)
{
    long flag[13];
    long numOfOcur = 0;
    long twin;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 3)
        {
            numOfOcur++;
            twin = i+1;
        }

    }
    if (numOfOcur == 1) return 100000 * twin;
    else return 0;
}
// evaStraight() function to check for straight in a hand
// Note: Straight flush or royal flush are included
long evaStraight(list<long> l)
{
    long flag[13];
    long spree = 0;
    long lead;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 1) spree++;
        else spree = 0;
        if (spree == 5)
        {
            lead = i+1;
            break;
        }
    }
    if (flag[0] == 1 && flag[1] == 1 && flag[2] == 1 && flag[3] == 1 && flag[12] == 1) // A2345 included
        spree = 5;
    if (spree == 5) return 10000000 * lead;
    else return 0;
}
// evaFlush() function to check for flush in a hand
// Note: Straight flush or royal flush are included
long evaFlush(string ins)
{
    long flagFace[4];
    for (long i = 0; i < 4; i++)
    {
        flagFace[i] = 0;
    } 
    for (long i = 0; i < ins.length(); i++)
    {
        switch (ins[i])
        {
        case 'a':
            flagFace[0]++; 
            break;
        case 'b':
            flagFace[1]++; 
            break;
        case 'c':
            flagFace[2]++; 
            break;
        case 'd':
            flagFace[3]++; 
            break;
        }
    }
    for (long i = 0; i < 4; i++)
    {
        if (flagFace[i] == 5) return 1000000000;
    }
    return 0;
}
// evaFullHouse() function to check for full house in a hand
long evaFullHouse()
{
    if (evaPair(numOnly) > 0 && evaThreeOfAKind(numOnly) > 0)
        return 10000000000;
    else return 0;
}
// evaFourOfAKind() function to check for four of a kind in a hand
long evaFourOfAKind(list<long> l)
{
    long flag[13];
    long numOfOcur = 0;
    long twin;
    for (long i = 0; i < 13; i++)
    {
        flag[i] = 0;
    }
    list<long>::iterator itr;
    for (itr = l.begin(); itr != l.end(); itr++)
    {
        flag[*itr-1]++;
    }
    for (long i = 0; i < 13; i++)
    {
        if (flag[i] == 4)
        {
            numOfOcur++;
            twin = i+1;
        }
    }
    if (numOfOcur == 1) return 1000000000000 * twin;
    return 0;
}
// evaStraightFlush() function to check for straight flush in a hand
long evaStraightFlush(string ins)
{
    if (ins == "a2 a3 a4 a5 a6 " || ins == "a3 a4 a5 a6 a7 " || ins == "a4 a5 a6 a7 a8 " || ins == "a5 a6 a7 a8 a9 " || ins == "a6 a7 a8 a9 a10 " || ins == "a7 a8 a9 a9 a10 " || ins == "a8 a9 a10 aJ aQ " || ins == "a9 a10 aJ aQ aK " || ins == "a10 aJ aQ aK aA " || ins == "a2 a3 a4 a5 aA " || ins == "b2 b3 b4 b5 b6 " || ins == "b3 b4 b5 b6 b7 " || ins == "b4 b5 b6 b7 b8 " || ins == "b5 b6 b7 b8 b9 " || ins == "b6 b7 b8 b9 b10 " || ins == "b7 b8 b9 b9 b10 " || ins == "b8 b9 b10 bJ bQ " || ins == "b9 b10 bJ bQ bK " || ins == "b10 bJ bQ bK bA " || ins == "b2 b3 b4 b5 bA " || ins == "c2 c3 c4 c5 c6 " || ins == "c3 c4 c5 c6 c7 " || ins == "c4 c5 c6 c7 c8 " || ins == "c5 c6 c7 c8 c9 " || ins == "c6 c7 c8 c9 c10 " || ins == "c7 c8 c9 c9 c10 " || ins == "c8 c9 c10 cJ cQ " || ins == "c9 c10 cJ cQ cK " || ins == "c10 cJ cQ cK cA " || ins == "c2 c3 c4 c5 cA " || ins == "d2 d3 d4 d5 d6 " || ins == "d3 d4 d5 d6 d7 " || ins == "d4 d5 d6 d7 d8 " || ins == "d5 d6 d7 d8 d9 " || ins == "d6 d7 d8 d9 d10 " || ins == "d7 d8 d9 d9 d10 " || ins == "d8 d9 d10 dJ dQ " || ins == "d9 d10 dJ dQ dK " || ins == "d10 dJ dQ dK dA " || ins == "d2 d3 d4 d5 dA ")
        return 10000000000000000;
    return 0;
}
// noPlayer() function to get information about number of players and their names at the start of each gameplay
long noPlayer()
{
    long num;
    do
    {
        cout << "Please enter number of player (max. 10): ";
        cin >> num;
    } while (!(num > 0) || !(num <= 10));
    for (long i = 0; i < num; i++)
    {
        cout << "Please enter name of player " << i+1 << ": ";
        cin >> flowOfPlayer[i].name;
    }
    return num;
}
int main()
{
    cHall();
    int option;
    long noOfHofPlayer;
    do
    {
        noOfHofPlayer = rHall();
        printMenu();
        cout << "Enter your command: ";     // 1: Start game;   2: View Hall of Fame;   3: Exit game
        cin >> option;
        // Start game
        if (option == 1)
        {
            // Obtain number of players and their names
            long noOfPlayer = noPlayer();
            // Start a new round by dealing hands of 5 to each player
            system("clear");
            initIns(noOfPlayer);
            // Evaluate hands of each player with scores to facilitate ranking at the next stage
            for (long i = 0; i < noOfPlayer; i++)
            {
                numOnly.clear();
                stripFace(flowOfPlayer[i].hand);
                if (evaFlush(flowOfPlayer[i].hand) > 0)
                    flowOfPlayer[i].value = evaFlush(flowOfPlayer[i].hand) + evaStraight(numOnly) + evaStraightFlush(flowOfPlayer[i].hand);
                else
                    flowOfPlayer[i].value = evaFace(flowOfPlayer[i].hand) + evaNum(numOnly) + evaPair(numOnly) + evaThreeOfAKind(numOnly) + evaStraight(numOnly) + evaFullHouse() + evaFourOfAKind(numOnly);
            }

            // Rank players by their hands (greater hands at the front and smaller hands at the back)
            sort(flowOfPlayer.begin(), flowOfPlayer.end(), greater<player>());

            // Announce the winner and print all the hands
            for (long i = 0; i < noOfPlayer; i++)
            {
                cout << flowOfPlayer[i].name;
                if (i == 0) cout << " WINNER!" << endl;
                else cout << endl;
                printCard(flowOfPlayer[i].hand);
            }
            // Check if players want their hands in the current round to be recorded into Hall of Fame
            int admitted = aHall(noOfHofPlayer);
            if (admitted > 0)
            {
                noOfHofPlayer++;
                wHall(noOfHofPlayer);
            }
            for (int i = 0; i < noOfPlayer; i++)
            {
                flowOfPlayer[i].name = "";
                flowOfPlayer[i].hand = "";
                flowOfPlayer[i].value = 0;
            }
        }
        // View Hall of Fame
        if (option == 2)
        {
            system("clear");

            if (noOfHofPlayer <= 2) // 0 or 1 record prompts 'empty' message
                cout << "Hall of Fame is empty!" << endl;
            else
            {
                cout << "HALL OF FAME" << endl;
                for (int i = 0; i < noOfHofPlayer; i++)
                {
                    if (i % 2 == 1)
                        cout << (i+1)/2 << ". ";
                    cout << hofPlayer[i].name << " ";
                    printCard(hofPlayer[i].hand);
                }
            }
            cout << "Enter YES to continue: ";
            string input;
            cin >> input; 
        }
    } while (option != 3);
    cout << "Goodbye!" << endl;
    cout << "See you again in Card of Five!" << endl;
    return 0;
}