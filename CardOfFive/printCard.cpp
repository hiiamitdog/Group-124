#include <iostream>
#include <string>
#include "printCard.h"
using namespace std;
// printCard() function to display players' hand
void printCard(string ins)
{
    for (long i = 0; i < ins.length(); i++)
    {
        switch (ins[i])
        {
            case 'a':
                cout << "♦";
                break;
            case 'b':
                cout << "♣";
                break;
            case 'c':
                cout << "♥";
                break;
            case 'd':
                cout << "♠";
                break;
            default:
                cout << ins[i];
                break;
        }
    }
    cout << endl;
}