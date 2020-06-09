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
    int length = r * c;
    this->elems = new int[length];
    for (int i = 0; i < length; i++) {
        this->elems[i] = 0;
    }
    // numerator value
    this->rows = r;
    // denominator value
    this->cols = c;
}


Matrix::Matrix(const Matrix &m) {
    int length = m.numRows() * m.numCols();
    this->elems  = new int[length];
    for (int i = 0; i < length; i++) {
        this->elems[i] = m.elems[i];
    }
    // numerator value
    this->rows =m.numRows();
    // denominator value
    this->cols = m.numCols();
}


Matrix & Matrix::operator=(const Matrix &m) {
    if (this == &m) {
        return *this;
    }

    delete[] this->elems;
    int length = m.numRows() * m.numCols();
    this->elems  = new int[length];
    for (int i = 0; i < length; i++) {
        this->elems[i] = m.elems[i];
    }
    // numerator value
    this->rows =m.numRows();
    //denominator value
    this->cols = m.numCols();
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
    return elems[index];
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

    int length = this->numRows() * this->numCols();
    for (int i = 0; i < length; i++) {
        if (this->elems[i] != m.elems[i]) {
            return false;
        }
    }
    return true;
}


 bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}
