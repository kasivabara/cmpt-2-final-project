#include <iostream>
#include <algorithm>
#include <fstream>
#include "Grid.h"
using namespace std;

GridRow::GridRow(){};

GridRow::GridRow(int n): numC(n)
{
    row = new bool[numC];
};

GridRow::~GridRow()
{
    delete[] row;
};

int GridRow::getLength()
{
    return numC;
}

bool& GridRow::operator[](const int index)
{
    
    if (index < 0 || index >= numC) 
    {
        throw std::out_of_range("Column out of range");
    }
    
    return row[index];
}

const bool& GridRow::operator[](const int index) const
{
    
    if (index < 0 || index >= numC) 
    {
        throw std::out_of_range("Column out of range");
    }
    
    return row[index];
};

GridRow& GridRow::operator=(GridRow && gr)
{
    std::swap(numC, gr.numC);
    std::swap(row, gr.row);
    return (*this);
};

GridRow& GridRow::operator=(const GridRow & gr)
{
    numC = gr.numC;
    row = new bool[numC];
    for (int i=0; i!=numC; i++)
    {
        (*this)[i] = gr[i];
    }
    return (*this);
};

//--------------------------------------------------------------


/*
This is my own function to calculate what the cell should be in
next generation. 
Initial -> initial state of the sell in currect generation.
arr -> a boolean array that contains all of the closest cells that determine
    the next state of initial cell.
SIZE -> size of the array 
*/
bool calculateState(bool initial, bool* arr, const int SIZE)
{
    int c = 0;
    for (int i=0; i!=SIZE; i++) ++c;
    if (c <= 1) {return false;}
    if (c == 2) {return initial;}
    if (c == 3) {return true;}
    if (c >= 4) {return false;}
}

const int& Grid::getRows() const
{
    return numRows;
};

const int& Grid::getCols() const
{
    return numCols;
};

const bool& Grid::get_isWrap() const
{
    return isWrap;
};

void Grid::set_isWrap(bool state)
{
    isWrap = state;
};

Grid::Grid(): numRows(0), numCols(0), isWrap(false){};

Grid::Grid(int r, int c): numRows(r), numCols(c), isWrap(false)
{
    plane = new GridRow[numRows];
    GridRow temp(numCols);
    for (int i=0; i!=numRows; i++)
    {
        plane[i] = temp;
    }  
}

Grid::Grid(const Grid &g): numRows(g.numRows), numCols(g.numCols), isWrap(g.isWrap)
{
    plane = new GridRow[numRows];
    for (int row=0; row!=numRows; row++)
    {
        for (int col=0; col != numCols; col++)
        {
            plane[row][col] = g[row][col];
        }
    }
};

Grid::Grid(Grid && g): numRows(g.numRows), numCols(g.numCols), isWrap(g.isWrap)
{
    plane = g.plane;
    g.plane = nullptr;
}

// TO DO
Grid::Grid(const string& str)
{
    string temp;
    fstream dataFile;

    dataFile.open("info.txt", ios::in);
    dataFile >> numRows;
    dataFile >> numCols;
    plane = new GridRow[numRows];

    int row = 0;
    while (dataFile >> temp)
    {
        for (int col=0; col != numCols; col++)
        {
            if (temp.at(col) == 'x')
                {(*this)[row][col] = true;}

            else
                {(*this)[row][col] = false;}
        }
    }
}

Grid& Grid::operator=(const Grid &g)
{
    numRows = g.numRows;
    numCols = g.numCols;
    isWrap = g.isWrap;
    plane = g.plane;
    return (*this);
};

Grid& Grid::operator=(Grid && g)
{
    std::swap(numRows, g.numRows);
    std::swap(numCols, g.numCols);
    std::swap(isWrap, g.isWrap);
    std::swap(plane, g.plane);
    return (*this);
};

Grid::~Grid()
{
    delete[] plane;
}

GridRow& Grid::operator[](int r)
{
    if (r < 0 || r >= numCols) 
    {
        throw std::out_of_range ("Row out of range");
    }
    return plane[r];
}

const GridRow& Grid::operator[](int r) const
{
    if (r < 0 || r >= numCols) 
    {
        throw std::out_of_range ("Row out of range");
    }
    return plane[r];
}

// TO DO
Grid& Grid::operator++()
{
    int size = 0;
    bool* array;
    Grid nextGeneration(numRows, numCols);

    if (isWrap == false)
    {
        nextGeneration.set_isWrap(false);
        for (int row=0; row!=numRows; row++)
        {
            for (int col=0; col!=numCols; col++)
            {
                delete[] array;
                size = 0;


                if ((row == 0) && (col == 0))
                {
                    size = 3;
                    array = new bool[size];
                    array[0] = (*this)[row][col+1];
                    array[1] = (*this)[row+1][col];
                    array[2] = (*this)[row+1][col+1];
                    nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                }

                if ((row == 0) && (col == numCols-1))
                {
                    size = 3;
                    array = new bool[size];
                    array[0] = (*this)[row][numCols-2];
                    array[1] = (*this)[row+1][numCols-1];
                    array[2] = (*this)[row+1][numCols-2];
                    nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                }

            }
        }
    }

    else 
    {

    }
    return *this;
}

ostream& operator<<(ostream& out, const Grid& g)
{
    out << "\n\n\n\n\n\n";
    for (int row=0; row != g.numRows; row++)
    {
        for (int col=0; col != g.numCols; col++)
        {
            if (g[row][col] == true)
                {
                    out << 'x';
                }
            else
                {
                    out << '-';
                }
        }
    }
    out << std::endl;
    return out;
};

istream& operator>>(istream& in, Grid& g)
{
    fstream fileTemp;
    string temp;
    cout << "Enter file's name: ";
    in >> temp;
    fileTemp.open(temp, ios::in);
    while (fileTemp.fail())
    {
        cout << "There is an error with opening the file.\nEnter the name again: ";
        temp.clear();
        in >> temp;
        fileTemp.open(temp, ios::in);
    }
    fileTemp.close();
    g = Grid(temp);
    return in;
};

//hui