#include "testbase.h"
#include "matrix.h"

#include <sstream>
#include <stdexcept>

using namespace std;


/*===========================================================================
 * TEST FUNCTIONS
 *
 * These are called by the main() function at the end of this file.
 */


/*! Test the default Matrix constructor. */
void test_matrix_default_ctor(TestContext &ctx) {
    ctx.DESC("Matrix default constructor");

    Matrix m;

    ctx.CHECK(m.numRows() == 0);
    ctx.CHECK(m.numCols() == 0);

    bool pass = true;

    // Accessing any element should throw an exception.
    try {
        (void) m.get(0, 0);
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    // Accessing a negative index should throw an exception.
    try {
        (void) m.get(-1, -1);
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    ctx.result();
}


/*! Test the two-argument Matrix constructor. */
void test_matrix_2arg_ctor(TestContext &ctx) {
    ctx.DESC("Matrix 2-argument constructor");

    // Choose a relatively large size so that there's some chance we will see
    // garbage values if the matrix contents are not properly zeroed out.
    Matrix m{50, 80};

    ctx.CHECK(m.numRows() == 50);
    ctx.CHECK(m.numCols() == 80);

    // Check that all elements are initially 0.
    for (int r = 0; r < m.numRows(); r++) {
        for (int c = 0; c < m.numCols(); c++) {
            ctx.CHECK(m.get(r, c) == 0);
        }
    }

    bool pass = true;

    // Accessing an element past the # of rows should throw an exception.
    try {
        (void) m.get(50, 0);
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    // Accessing an element past the # of columns should also throw.
    try {
        (void) m.get(0, 80);
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    // Accessing a negative index should throw an exception.
    try {
        (void) m.get(-1, -1);
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    ctx.result();
}


/*! Test the two-argument Matrix constructor with bad values. */
void test_matrix_2arg_ctor_bad_values(TestContext &ctx) {
    ctx.DESC("Matrix 2-argument constructor w/bad values");

    bool pass = true;
    try {
        Matrix m{-20, 80};
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    try {
        Matrix m{20, -80};
        pass = false;  // ERROR:  No exception
    }
    catch (invalid_argument &) {
        pass = true;
    }
    catch (...) {
        pass = false;  // ERROR:  Wrong exception type
    }
    ctx.CHECK(pass);

    ctx.result();
}


/*! Test the Matrix get/set element functions. */
void test_matrix_get_set(TestContext &ctx) {
    ctx.DESC("Matrix get/set member functions");

    Matrix m{80, 50};

    // Set all the values in the first pass, so that if things overwrite,
    // we will be more likely to catch them in the second pass.
    for (int r = 0; r < m.numRows(); r++) {
        for (int c = 0; c < m.numCols(); c++) {
            ctx.CHECK(m.get(r, c) == 0);
            m.set(r, c, r * m.numCols() + c);
        }
    }

    // Check that values are what we expect.
    for (int r = 0; r < m.numRows(); r++) {
        for (int c = 0; c < m.numCols(); c++) {
            ctx.CHECK(m.get(r, c) == r * m.numCols() + c);
        }
    }

    ctx.result();
}


/*! Test the Matrix copy-constructor. */
void test_matrix_copy_ctor(TestContext &ctx) {
    ctx.DESC("Matrix copy-constructor");

    // Initialize a matrix.
    Matrix m1{2, 3};
    m1.set(0, 0, 15);
    m1.set(1, 2, -6);
    m1.set(0, 2, 38);

    // Make a copy.
    Matrix m2{m1};
    ctx.CHECK(m2.numRows() == 2);
    ctx.CHECK(m2.numCols() == 3);
    ctx.CHECK(m2.get(0, 0) == 15);
    ctx.CHECK(m2.get(1, 2) == -6);
    ctx.CHECK(m2.get(0, 2) == 38);

    // Mutate the original; the copy should be unchanged.
    m1.set(1, 1, -29);
    ctx.CHECK(m2.get(1, 1) == 0);

    // Mutate the copy; the original should be unchanged.
    m2.set(0, 0, 384);
    ctx.CHECK(m1.get(0, 0) == 15);

    ctx.result();
}


/*! Test the Matrix copy-assignment operator. */
void test_matrix_copy_assign(TestContext &ctx) {
    ctx.DESC("Matrix copy-assignment");

    // Initialize a matrix.
    Matrix m1{2, 3};
    m1.set(0, 0, 15);
    m1.set(1, 2, -6);
    m1.set(0, 2, 38);

    // Make a copy.
    Matrix m2;

    ctx.CHECK(m2.numRows() == 0 && m2.numCols() == 0);

    m2 = m1;
    ctx.CHECK(m2.numRows() == 2);
    ctx.CHECK(m2.numCols() == 3);
    ctx.CHECK(m2.get(0, 0) == 15);
    ctx.CHECK(m2.get(1, 2) == -6);
    ctx.CHECK(m2.get(0, 2) == 38);

    // Mutate the original; the copy should be unchanged.
    m1.set(1, 1, -29);
    ctx.CHECK(m2.get(1, 1) == 0);

    // Mutate the copy; the original should be unchanged.
    m2.set(0, 0, 384);
    ctx.CHECK(m1.get(0, 0) == 15);

    // Set the first matrix to a new empty matrix.
    m1 = Matrix{};

    ctx.CHECK(m1.numRows() == 0);
    ctx.CHECK(m1.numCols() == 0);

    ctx.CHECK(m2.numRows() == 2);
    ctx.CHECK(m2.numCols() == 3);
    ctx.CHECK(m2.get(0, 0) == 384);
    ctx.CHECK(m2.get(1, 2) == -6);
    ctx.CHECK(m2.get(0, 2) == 38);

    ctx.result();

    ctx.DESC("Matrix copy-assignment of self");

    Matrix m3{40, 50};

    for (int r = 0; r < m3.numRows(); r++) {
        for (int c = 0; c < m3.numCols(); c++) {
            m3.set(r, c, r * m3.numCols() + c);
        }
    }

    ((m3 = m3 = m3) = (m3 = m3 = m3));

    for (int r = 0; r < m3.numRows(); r++) {
        for (int c = 0; c < m3.numCols(); c++) {
            ctx.CHECK(m3.get(r, c) == r * m3.numCols() + c);
        }
    }

    ctx.result();
}


/*! Test the Matrix == and != operators. */
void test_matrix_equals(TestContext &ctx) {
    ctx.DESC("Matrix == and != operators on 0x0 matrices");

    Matrix m01, m02;

    ctx.CHECK(m01 == m01);
    ctx.CHECK(m01 == m02);
    ctx.CHECK(m02 == m01);

    ctx.CHECK(!(m01 != m01));
    ctx.CHECK(!(m01 != m02));
    ctx.CHECK(!(m02 != m01));

    ctx.result();

    ctx.DESC("Matrix == and != operators on matrices of varying sizes");

    Matrix m1{3, 2}, m2{2, 3};  // Contents are currently identical

    ctx.CHECK(m1 != m2);
    ctx.CHECK(!(m1 == m2));

    ctx.CHECK(m01 != m1);
    ctx.CHECK(!(m01 == m1));

    ctx.result();

    ctx.DESC("Matrix == and != operators on identical matrices");

    Matrix m3{3, 2};

    ctx.CHECK(m1 == m3);
    ctx.CHECK(!(m1 != m3));

    m1.set(0, 0, 15);
    m1.set(2, 1, 35);
    m3.set(2, 1, 35);

    ctx.CHECK(m1 != m3);
    ctx.CHECK(!(m1 == m3));

    m3.set(0, 0, 15);

    ctx.CHECK(m1 == m3);
    ctx.CHECK(!(m1 != m3));

    ctx.result();
}


/*! This program is a simple test-suite for the Matrix class. */
int main() {

    cout << "Testing the Matrix class." << endl << endl;

    TestContext ctx(cout);

    test_matrix_default_ctor(ctx);
    test_matrix_2arg_ctor(ctx);
    test_matrix_2arg_ctor_bad_values(ctx);

    test_matrix_get_set(ctx);

    test_matrix_copy_ctor(ctx);
    test_matrix_copy_assign(ctx);

    test_matrix_equals(ctx);

    // Return 0 if everything passed, nonzero if something failed.
    return !ctx.ok();
}
