#include <string>
using namespace std;

/** a 2D integer matrix class  */
class Matrix {
    private:
        /** int values for the number of rows of the matrix */
        int rows;
        /** int values for the number of columns of the matrix */
        int cols;
        /** 1d array representing the 2d matrix */
        int *elems;

    public:
        // constructor
        /**
         * Matrix initialization
         * @param int value representing number of rows
         * @param int value representing number of columns
         * @return instance of Matrix
         * @exception illegal_argument thrown if inputs are less than zero
         */
        Matrix(int rows = 0, int cols = 0);

        /**
         * Matrix copy-constructor
         * @param instance of Matrix
         * @return instance of Matrix that is a copy of the input
         */
        Matrix(const Matrix &m);

        /**
         * Matrix copy-assignment operator
         * @param instance of Matrix
         * @return instance of Matrix that is equal to the input
         */
        Matrix &operator=(const Matrix &m);

        /**
         * Matrix destructor
         * @param void
         * @return void
         */
        ~Matrix();

        // accessors
        /**
         * returns number of rows
         * @param void
         * @return number of rows
         */
        int numRows() const {
            return this->rows;
        }

        /**
         * returns number of columns
         * @param void
         * @return number of rows
         */
        int numCols() const {
            return this->cols;
        }

        // methods
        /**
         * Returns the value stored at the specified row and column.
         * @param int value representing the row
         * @param int value representing the column
         * @return the value stored in the input index of the Matrix
         * @exception throws an invalid_argument exception
         * if the row or column index is out of bounds.
         */
        int get(int r, int c) const;

        /**
         * Sets the value stored at the specified row and column.
         * @param int value representing the row
         * @param int value representing the column
         * @return void
         * @exception throws an invalid_argument exception
         * if the row or column index is out of bounds.
         */
        void set(int r, int c, int value);

        /**
         * should return true iff the specified matrix is "equal to" this
         * matrix; i.e. the total number of rows and columns are identical,
         * and all of the values are also identical
         * @param instance of Matrix
         * @return bool
         */
        bool operator==(const Matrix &m) const;

        /**
         * should do the opposite of operator==()
         * @param instance of Matrix
         * @return bool
         */
        bool operator!=(const Matrix &m) const;
};
