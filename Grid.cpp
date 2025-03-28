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
        throw std::out_of_range ("Row out of range");
    }
    return row[index];
}

const bool& GridRow::operator[](const int index) const
{
    if (index < 0 || index >= numC) 
    {
        throw std::out_of_range ("Row out of range");
    }
    return row[index];
};

GridRow& GridRow::operator=(GridRow && gr)
{
    std::swap(numC, gr.numC);
    std::swap(row, gr.row);
    return (*this);
};

GridRow& GridRow::operator=(const GridRow &gr)
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
    int liveCount = 0;
    for (int i = 0; i != SIZE; i++)
    {
        if (arr[i]) liveCount++;
    }

    if (liveCount <= 1) { return false; }
    if (liveCount == 2) { return initial; }
    if (liveCount == 3) { return true; }
    return false;
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

const string& Grid::get_name() const
{
    return name;
}

void Grid::set_name(const string& str)
{
    name = str;
}

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
    name = g.name;
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
    name = g.name;
    plane = g.plane;
    g.plane = nullptr;
}

// TO DO
Grid::Grid(const string& str)
{
    string temp;
    fstream dataFile;

    dataFile.open(str, ios::in);
    dataFile >> numRows;
    dataFile >> numCols;
    plane = new GridRow[numRows];

    int row = 0;
    GridRow tempRow(numCols);

    while (dataFile >> temp)
    {
        if ((temp.size() == 0) || (temp.find('#') != -1)){break;}
        
        for (int col=0; col != numCols; col++)
        {
            if (temp.at(col) == 'X')
                {tempRow[col] = true;}

            else
                {tempRow[col] = false;}
            
        }
        plane[row] = tempRow;
        row++;
    }
    name = str;
}

Grid& Grid::operator=(const Grid &g)
{
    numRows = g.numRows;
    numCols = g.numCols;
    isWrap = g.isWrap;
    name = g.name;
    for (int row=0; row!=numRows; row++)
    {
        for (int col=0; col!=numCols; col++)
        {
            plane[row][col] = g.plane[row][col];
        }
    }
    return (*this);
};

Grid& Grid::operator=(Grid && g)
{
    numRows = g.numRows;
    numCols = g.numCols;
    isWrap = g.isWrap;
    plane = g.plane;
    g.plane = nullptr;
    name = g.name;
    return (*this);
};

Grid::~Grid()
{
    delete[] plane;
}

GridRow& Grid::operator[](int r)
{
    if (r < 0 || r >= numRows) 
    {
        throw std::out_of_range ("Row out of range");
    }
    return plane[r];
}

const GridRow& Grid::operator[](int r) const
{
    if (r < 0 || r >= numRows) 
    {
        throw std::out_of_range ("Row out of range");
    }
    return plane[r];
}

//garbage code territory
Grid& Grid::operator++()
{
    int size;
    bool* array = new bool[numCols];
    Grid nextGeneration(numRows, numCols);

    if (isWrap == false)
    {
        nextGeneration.set_isWrap(false);
        for (int row=0; row!=numRows; row++)
        {
            for (int col=0; col!=numCols; col++)
            {
                size = 0;

                if ((row == 0) && (col == 0))
                    {
                        size = 3;
                        array[0] = (*this)[row][col+1];
                        array[1] = (*this)[row+1][col];
                        array[2] = (*this)[row+1][col+1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                if ((row == 0) && (col == numCols-1))
                    {
                        size = 3;
                        array[0] = (*this)[row][col-1];
                        array[1] = (*this)[row+1][col];
                        array[2] = (*this)[row+1][col-1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }
                
                if ((row == numRows-1) && (col == 0))
                    {
                        size = 3;
                        array[0] = (*this)[row][col+1];
                        array[1] = (*this)[row-1][col];
                        array[2] = (*this)[row-1][col+1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                if ((row == numRows-1) && (col == numCols-1))
                    {
                        size = 3;
                        array[0] = (*this)[row][col-1];
                        array[1] = (*this)[row-1][col];
                        array[2] = (*this)[row-1][col-1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                if (row == 0)
                    {
                        size = 5;
                        array[0] = (*this)[row][col-1];
                        array[1] = (*this)[row][col+1];
                        array[2] = (*this)[row+1][col-1];
                        array[3] = (*this)[row+1][col];
                        array[4] = (*this)[row+1][col+1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                if (row == numRows-1)
                    {
                        size = 5;
                        array[0] = (*this)[row][col-1];
                        array[1] = (*this)[row][col+1];
                        array[2] = (*this)[row-1][col-1];
                        array[3] = (*this)[row-1][col];
                        array[4] = (*this)[row-1][col+1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                if (col == 0)
                    {
                        size = 5;
                        array[0] = (*this)[row-1][col];
                        array[1] = (*this)[row+1][col];
                        array[2] = (*this)[row-1][col+1];
                        array[3] = (*this)[row][col+1];
                        array[4] = (*this)[row+1][col+1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }
                
                if (col == numCols-1)
                    {
                        size = 5;
                        array[0] = (*this)[row-1][col];
                        array[1] = (*this)[row+1][col];
                        array[2] = (*this)[row-1][col-1];
                        array[3] = (*this)[row][col-1];
                        array[4] = (*this)[row+1][col-1];
                        nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                        continue;
                    }

                
                //else
                    size = 8;
                    array[0] = (*this)[row-1][col-1];
                    array[1] = (*this)[row-1][col];
                    array[2] = (*this)[row-1][col+1];
                    array[3] = (*this)[row][col-1];
                    array[4] = (*this)[row][col+1];
                    array[5] = (*this)[row+1][col-1];
                    array[6] = (*this)[row+1][col];
                    array[7] = (*this)[row+1][col+1];
                    nextGeneration[row][col] = calculateState((*this)[row][col], array, size);
                    continue;

            }
        }
    }

    else 
    {
        //pass
        nextGeneration = *this;
    }


    (*this) = nextGeneration;

    delete[] array;
    return *this;
}

ostream& operator<<(ostream& out, const Grid& g)
{
    out << "\n";
    for (int row=0; row != g.numRows; row++)
    {
        out << "\n";
        for (int col=0; col != g.numCols; col++)
        {
            if (g[row][col] == true)
                {
                    out << static_cast<char>(178);
                }
            else
                {
                    out << "  ";
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
    cout << "Grid input file name? ";
    in >> temp;
    fileTemp.open(temp, ios::in);
    while (fileTemp.fail())
    {
        cout << "There is an error with opening the file.\nEnter the name again: ";
        in >> temp;
        fileTemp.open(temp, ios::in);
    }
    fileTemp.close();
    g = Grid(temp);
    g.set_name(temp);
    return in;
};