#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
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
        ++g;
        system("cls");
        cout << g;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
    }
}

void forward(Grid& g)
{
    ++g;
}

char getChoice()
{
    string temp;
    while (true)
    {
        cout << "s)imulate, f)orward, q)uit? ";
        cin >> temp;
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

    cin >> mainGrid;
    test.open(mainGrid.get_name(), ios::in);

    int tempRows = 0, tempCols = 0;
    test >> tempRows; test >> tempCols;
    cout << "row: " << tempRows << ", col: " << tempCols << endl;
    while (test >> temp)
    {
        if (temp.find('#') != -1){break;}
        cout << temp << "\n";
    }

    cout << "Should the simulation wrap around the grid (y/n)? ";
    cin >> choice;
    if (choice == 'n') {mainGrid.set_isWrap(false);}
    else {mainGrid.set_isWrap(true);}

    choice = 'x';
    while (choice != 'q')
    {
        choice = getChoice();  // Get user input FIRST

        if (choice == 's')
        {
            simulate(mainGrid);
        }
        else if (choice == 'f')
        {
            forward(mainGrid);
        }

        // Print the grid after processing the choice
        system("cls");  // Optional: clear screen for better visibility
        cout << mainGrid;
    }

    return 0;
}