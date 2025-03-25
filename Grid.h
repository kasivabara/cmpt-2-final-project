
using namespace std;

class GridRow
{
    private:
        int numC;
        bool* row;

    public:
        GridRow();
        GridRow(int);
        ~GridRow();
        int getLength();
        bool &operator[](const int);
        const bool &operator[](const int) const;

        GridRow& operator=(const GridRow &);
        GridRow& operator=(GridRow &&);
};

class Grid
{
    private:
        int numRows, numCols;
        bool isWrap = false;
        GridRow* plane;

    public:
        // Getter of column and row of grid
        const int& getRows() const;
        const int& getCols() const;

        //Getter and setter of isWrap;
        const bool& get_isWrap() const;
        void set_isWrap(bool);

        //default constructor
        Grid();

        // constructor with 2 int parameters
        Grid(int, int);

        // copy constructor
        Grid(const Grid&);

        // move constructor
        Grid(Grid &&);

        //constructor with 1 string parameter
        // TO DO
        Grid(const string&);

        // copy assignment operator
        Grid& operator=(const Grid&);

        // move assignment operator
        Grid& operator=(Grid &&);

        // destructor
        ~Grid();

        // offset operator[]
        GridRow& operator[](int);
        const GridRow& operator[](int) const;

        // prefix
        // TO DO
        Grid& operator++();

        // operator<<
        friend ostream& operator<<(ostream&, const Grid&);

        // operator>>
        friend istream& operator>>(istream&, const Grid&);
        
};