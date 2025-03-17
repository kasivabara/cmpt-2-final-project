#include <iostream>
#include <fstream>
#include "Grid.h"
using namespace std;


void simulate(Grid& g)
{
    int frames;
    cout << "How many frames? ";
    cin >> frames;
    while(!cin.good())
    {
        cout << "How many frames? ";
        cin >> frames;
    }
    
    for (int frame=0; frame != frames; frame++)
    {
        system("cls");
        ++g;
    }
}

void forward(Grid& g)
{
    ++g;
}

int getChoice()
{
    string temp;
    while (true)
    {
        temp.clear();
        cout << "s)imulate, f)orward, q)uit? ";
        getline(cin, temp);
        if (temp.at(0) == 's'){return 's';}
        if (temp.at(0) == 'f'){return 'f';}
        if (temp.at(0) == 'q'){return 'q';}
    }
}

int main()
{
    char choice = 'x';
    fstream test;
    string temp;
    Grid mainGrid;
    cout << "Grid input file name? ";
    cin >> temp;
    test.open(temp, ios::in);
    while(test.fail())
    {
        cout << "The file does not exist, enter again.\n";
        cout << "Grid input file name? ";
        cin >> temp;
        test.open(temp, ios::in);
    }


    cout << std::endl;
    int tempRows, tempCols;
    test >> tempRows; test >> tempCols;
    cout << "row: " << tempRows << ", col: " << tempCols;
    while (test >> temp)
    {
        cout << temp << "\n";
    }

    cout << "Should the simulation wrap around the grid (y/n)? ";
    cin >> temp;
    if (temp.at(0) == 'n') {mainGrid.set_isWrap(false);}
    else {mainGrid.set_isWrap(true);}

    
    while (choice != 'q')
    {
        if (choice == 's')
        {
            simulate(mainGrid);
            continue;
        }

        if (choice == 'f')
        {
            forward(mainGrid);
            continue;
        }
        choice = getChoice();
    }

    return 0;
}