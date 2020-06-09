#include "matrix.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

Matrix::Matrix(int r, int c) {
    if (r < 0 || c < 0) {
        string error = "invalid number of rows or columns. must be >= 0.";
        throw invalid_argument(error);
    }

    // number of rows
    this->rows = r;
    // number of columns
    this->cols = c;

    int length = this->rows * this->cols;
    this->elems = new int[length];
    // initialized to all 0's
    for (int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j < this->numCols() ; j++) {
            this->set(i, j,  0);
        }
    }
}

Matrix::Matrix(const Matrix &m) {
    // number of rows
    this->rows = m.numRows();
    // number of columns
    this->cols = m.numCols();

    int length = this->numRows() * this->numCols();
    this->elems = new int[length];
    for (int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j < this->numCols(); j++) {
            this->set(i, j, m.get(i, j));
        }
    }
}

Matrix & Matrix::operator=(const Matrix &m) {
    if (this == &m) {
        return *this;
    }

    // number of rows
    this->rows = m.numRows();
    // number of columns
    this->cols = m.numCols();

    delete[] this->elems;
    this->elems = new int[this->rows * this->cols];

    for (int i = 0; i < this->rows * this->cols; i++) {
        this->elems[i] = m.elems[i];
    }

    return *this;
}

 Matrix::Matrix(Matrix &&m) {
     // number of rows
     this->rows = m.numRows();
     // number of columns
     this->cols = m.numCols();
     // move elements and free mem
     this->elems = m.elems;

     m.elems = nullptr;
}

Matrix & Matrix::operator=(Matrix &&m) {
    // self assignment case
    if (this == &m) {
        return *this;
    }

    // number of rows
    this->rows = m.numRows();
    // number of columns
    this->cols = m.numCols();

    // move elements and free mem
    delete[] this->elems;
    this->elems = m.elems;

    m.elems = nullptr;
    return *this;
}

Matrix::~Matrix() {
    delete[] this->elems;
}

int Matrix::get(int r, int c) const {
    // check that input index is valid
    if (r >= this->numRows() || r < 0 || c >= this->numCols() || c < 0) {
        string e_message = "invalid index";
        throw invalid_argument(e_message);
    }
    int index = (r * this->numCols()) + c;
    return this->elems[index];
}

void Matrix::set(int r, int c, int value) {
    // check that input index is valid
    if (r >= this->numRows() || r < 0 || c >= this->numCols() || c < 0) {
        string e_message = "invalid index";
        throw invalid_argument(e_message);
    }
    int index = (r * this->numCols()) + c;
    this->elems[index] = value;
}

bool Matrix::operator==(const Matrix &m) const {
    // check that input index is valid
    if (this->numRows() != m.numRows() || this->numCols() != m.numCols()) {
        return false;
    }


    for (int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j < this->numCols(); j++) {
            if (this->get(i, j) != m.get(i, j)) {
                return false;
            }
        }
    }

    return true;
}


 bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}


Matrix & Matrix::operator+=(const Matrix &m) {
    // check that input index is valid
    if (this->numRows() != m.numRows() || this->numCols() != m.numCols()) {
        string e_message = "size of matrices are not compatible";
        throw invalid_argument(e_message);
    }

    for (int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j < this->numCols(); j++) {
            this->set(i, j, (this->get(i, j) + m.get(i, j)));
        }
    }
    return *this;
}


Matrix & Matrix::operator-=(const Matrix &m) {
    // check that input index is valid
    if (this->numRows() != m.numRows() || this->numCols() != m.numCols()) {
        string e_message = "size of matrices are not compatible";
        throw invalid_argument(e_message);
    }

    for (int i = 0; i < this->numRows(); i++) {
        for (int j = 0; j < this->numCols(); j++) {
            this->set(i, j, (this->get(i, j) - m.get(i, j)));
        }
    }
    return *this;
}


Matrix & Matrix::operator*=(const Matrix &m) {
    int r, c, product_sum;

    if (this->numCols() != m.numRows()) {
        string e_message = "size of matrices are not compatible";
        throw invalid_argument(e_message);
    }

    // create new Matrix with proper dimensions
    r = this->numRows();
    c = m.numCols();
    Matrix temp{r, c};

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            product_sum = 0;
            for (int k = 0; k < this->numCols(); k++) {
                product_sum += (this->get(i, k) * m.get(k, j));
            }
            temp.set(i, j, product_sum);
        }
    }

    *this = temp;
    return *this;
}


Matrix operator+(const Matrix &m1, const Matrix &m2) {
    return Matrix{m1} += m2;
}


Matrix operator-(const Matrix &m1, const Matrix &m2) {
    return Matrix{m1} -= m2;
}


Matrix operator*(const Matrix &m1, const Matrix &m2) {
    return Matrix{m1} *= m2;
}
