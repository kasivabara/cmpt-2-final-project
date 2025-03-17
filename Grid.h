/*
Your program should begin by prompting the user for a file name 
and using that file's contents to set the initial state of your Grid object. 
Then, it should ask if the simulation should wrap around the Grid (read Wrap 
Version section for the details of wrapping). Then the user can type f to go 
forward the bacteria growth by one generation; or s to begin an 
animation-style simulation that go forward the simulation by multiple 
generations, the animation will go forward every 100 milliseconds; or q to 
quit. Your menu should be case-insensitive and will only get the first 
character; for example, an uppercase or lowercase S, F, or Q should work; 
and a word like "for", "qui" or "Simulate" should work as well
*/

// You do not need to write any code to handle a mis-formatted file.
// You may also assume that the input file name typed by the user does not contain any spaces.

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