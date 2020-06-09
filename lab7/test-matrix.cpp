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


/*! Test the Matrix + and += operators. */
void test_matrix_addition(TestContext &ctx) {
    Matrix result;

    ctx.DESC("Matrix + and += operators on 0x0 matrices");
    {
        Matrix m01, m02;
        result = m01 + m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result += m01 + m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result += result += result;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);
    }
    ctx.result();

    ctx.DESC("Matrix + and += operators on matrices of compatible sizes");
    {
        Matrix ma1{2, 3}, ma2{2, 3};

        ma1.set(0, 0, 5);
        ma1.set(1, 1, -4);
        ma1.set(0, 2, 18);

        ma2.set(0, 0, -8);
        ma2.set(1, 0, 14);
        ma2.set(1, 1, 19);
        ma2.set(1, 2, 7);

        result = ma1 + ma2;

        ctx.CHECK(result.numRows() == 2);
        ctx.CHECK(result.numCols() == 3);
        ctx.CHECK(result.get(0, 0) == -3);
        ctx.CHECK(result.get(0, 1) ==  0);
        ctx.CHECK(result.get(0, 2) == 18);
        ctx.CHECK(result.get(1, 0) == 14);
        ctx.CHECK(result.get(1, 1) == 15);
        ctx.CHECK(result.get(1, 2) ==  7);

        ctx.CHECK(ma1.numRows() == 2);
        ctx.CHECK(ma1.numCols() == 3);
        ctx.CHECK(ma1.get(0, 0) ==  5);
        ctx.CHECK(ma1.get(0, 1) ==  0);
        ctx.CHECK(ma1.get(0, 2) == 18);
        ctx.CHECK(ma1.get(1, 0) ==  0);
        ctx.CHECK(ma1.get(1, 1) == -4);
        ctx.CHECK(ma1.get(1, 2) ==  0);

        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) == -8);
        ctx.CHECK(ma2.get(0, 1) ==  0);
        ctx.CHECK(ma2.get(0, 2) ==  0);
        ctx.CHECK(ma2.get(1, 0) == 14);
        ctx.CHECK(ma2.get(1, 1) == 19);
        ctx.CHECK(ma2.get(1, 2) ==  7);

        ma1 += ma2;

        ctx.CHECK(ma1.numRows() == 2);
        ctx.CHECK(ma1.numCols() == 3);
        ctx.CHECK(ma1.get(0, 0) == -3);
        ctx.CHECK(ma1.get(0, 1) ==  0);
        ctx.CHECK(ma1.get(0, 2) == 18);
        ctx.CHECK(ma1.get(1, 0) == 14);
        ctx.CHECK(ma1.get(1, 1) == 15);
        ctx.CHECK(ma1.get(1, 2) ==  7);
        
        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) == -8);
        ctx.CHECK(ma2.get(0, 1) ==  0);
        ctx.CHECK(ma2.get(0, 2) ==  0);
        ctx.CHECK(ma2.get(1, 0) == 14);
        ctx.CHECK(ma2.get(1, 1) == 19);
        ctx.CHECK(ma2.get(1, 2) ==  7);

    }
    ctx.result();

    ctx.DESC("Chained usage of += operator");
    {
        Matrix mmm{2, 2};
        mmm.set(0, 0, 5);
        mmm.set(0, 1, 7);
        mmm.set(1, 0, 11);
        mmm.set(1, 1, 13);

        // This is weird; each += doubles the matrix
        mmm += mmm += mmm;

        ctx.CHECK(mmm.numRows() == 2);
        ctx.CHECK(mmm.numCols() == 2);
        ctx.CHECK(mmm.get(0, 0) == 20);
        ctx.CHECK(mmm.get(0, 1) == 28);
        ctx.CHECK(mmm.get(1, 0) == 44);
        ctx.CHECK(mmm.get(1, 1) == 52);
    }
    ctx.result();

    ctx.DESC("Matrix + and += operators on matrices of incompatible sizes");
    {
        Matrix m1{3, 2}, m2{2, 3};
        try {
            m1 += m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }

        try {
            result = m1 + m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }
    }
    ctx.result();
}


/*! Test the Matrix - and -= operators. */
void test_matrix_subtraction(TestContext &ctx) {
    Matrix result;

    ctx.DESC("Matrix - and -= operators on 0x0 matrices");
    {
        Matrix m01, m02;
        result = m01 - m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result -= m01 - m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result -= result -= result;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);
    }
    ctx.result();

    ctx.DESC("Matrix - and -= operators on matrices of compatible sizes");
    {
        Matrix ma1{2, 3}, ma2{2, 3};

        ma1.set(0, 0, 5);
        ma1.set(1, 1, -4);
        ma1.set(0, 2, 18);

        ma2.set(0, 0, -8);
        ma2.set(1, 0, 14);
        ma2.set(1, 1, 19);
        ma2.set(1, 2, 7);

        result = ma1 - ma2;

        ctx.CHECK(result.numRows() == 2);
        ctx.CHECK(result.numCols() == 3);
        ctx.CHECK(result.get(0, 0) ==  13);
        ctx.CHECK(result.get(0, 1) ==   0);
        ctx.CHECK(result.get(0, 2) ==  18);
        ctx.CHECK(result.get(1, 0) == -14);
        ctx.CHECK(result.get(1, 1) == -23);
        ctx.CHECK(result.get(1, 2) ==  -7);

        ctx.CHECK(ma1.numRows() == 2);
        ctx.CHECK(ma1.numCols() == 3);
        ctx.CHECK(ma1.get(0, 0) ==  5);
        ctx.CHECK(ma1.get(0, 1) ==  0);
        ctx.CHECK(ma1.get(0, 2) == 18);
        ctx.CHECK(ma1.get(1, 0) ==  0);
        ctx.CHECK(ma1.get(1, 1) == -4);
        ctx.CHECK(ma1.get(1, 2) ==  0);

        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) == -8);
        ctx.CHECK(ma2.get(0, 1) ==  0);
        ctx.CHECK(ma2.get(0, 2) ==  0);
        ctx.CHECK(ma2.get(1, 0) == 14);
        ctx.CHECK(ma2.get(1, 1) == 19);
        ctx.CHECK(ma2.get(1, 2) ==  7);

        ma1 -= ma2;

        ctx.CHECK(ma1.numRows() == 2);
        ctx.CHECK(ma1.numCols() == 3);
        ctx.CHECK(ma1.get(0, 0) ==  13);
        ctx.CHECK(ma1.get(0, 1) ==   0);
        ctx.CHECK(ma1.get(0, 2) ==  18);
        ctx.CHECK(ma1.get(1, 0) == -14);
        ctx.CHECK(ma1.get(1, 1) == -23);
        ctx.CHECK(ma1.get(1, 2) ==  -7);
        
        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) == -8);
        ctx.CHECK(ma2.get(0, 1) ==  0);
        ctx.CHECK(ma2.get(0, 2) ==  0);
        ctx.CHECK(ma2.get(1, 0) == 14);
        ctx.CHECK(ma2.get(1, 1) == 19);
        ctx.CHECK(ma2.get(1, 2) ==  7);

    }
    ctx.result();

    ctx.DESC("Chained usage of -= operator");
    {
        Matrix mmm{2, 2};
        mmm.set(0, 0, 5);
        mmm.set(0, 1, 7);
        mmm.set(1, 0, 11);
        mmm.set(1, 1, 13);

        // Way less exciting than += += ...
        mmm -= mmm -= mmm;

        ctx.CHECK(mmm.numRows() == 2);
        ctx.CHECK(mmm.numCols() == 2);
        ctx.CHECK(mmm.get(0, 0) == 0);
        ctx.CHECK(mmm.get(0, 1) == 0);
        ctx.CHECK(mmm.get(1, 0) == 0);
        ctx.CHECK(mmm.get(1, 1) == 0);
    }
    ctx.result();

    ctx.DESC("Matrix - and -= operators on matrices of incompatible sizes");
    {
        Matrix m1{3, 2}, m2{2, 3};
        try {
            m1 -= m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }

        try {
            result = m1 - m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }
    }
    ctx.result();
}


/*! Test the Matrix * and *= operators. */
void test_matrix_multiplication(TestContext &ctx) {
    Matrix result;

    ctx.DESC("Matrix * and *= operators on 0x0 matrices");
    {
        Matrix m01, m02;
        result = m01 * m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result *= m01 * m02;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);

        result *= result *= result;
        ctx.CHECK(result.numRows() == 0);
        ctx.CHECK(result.numCols() == 0);
        ctx.CHECK(result == m01);
        ctx.CHECK(result == m02);
    }
    ctx.result();

    ctx.DESC("Matrix * and *= operators on matrices of compatible sizes");
    {
        Matrix ma1{4, 2}, ma2{2, 3};

        ma1.set(0, 0,  5);
        ma1.set(0, 1,  9);
        ma1.set(1, 0,  0);
        ma1.set(1, 1,  2);
        ma1.set(2, 0, -7);
        ma1.set(2, 1,  1);
        ma1.set(3, 0, -8);
        ma1.set(3, 1,  0);

        ma2.set(0, 0,  0);
        ma2.set(0, 1,  4);
        ma2.set(0, 2, -3);
        ma2.set(1, 0,  7);
        ma2.set(1, 1,  0);
        ma2.set(1, 2,  5);

        result = ma1 * ma2;

        ctx.CHECK(result.numRows() ==   4);
        ctx.CHECK(result.numCols() ==   3);
        ctx.CHECK(result.get(0, 0) ==  63);
        ctx.CHECK(result.get(0, 1) ==  20);
        ctx.CHECK(result.get(0, 2) ==  30);
        ctx.CHECK(result.get(1, 0) ==  14);
        ctx.CHECK(result.get(1, 1) ==   0);
        ctx.CHECK(result.get(1, 2) ==  10);
        ctx.CHECK(result.get(2, 0) ==   7);
        ctx.CHECK(result.get(2, 1) == -28);
        ctx.CHECK(result.get(2, 2) ==  26);
        ctx.CHECK(result.get(3, 0) ==   0);
        ctx.CHECK(result.get(3, 1) == -32);
        ctx.CHECK(result.get(3, 2) ==  24);

        ctx.CHECK(ma1.numRows() == 4);
        ctx.CHECK(ma1.numCols() == 2);
        ctx.CHECK(ma1.get(0, 0) ==  5);
        ctx.CHECK(ma1.get(0, 1) ==  9);
        ctx.CHECK(ma1.get(1, 0) ==  0);
        ctx.CHECK(ma1.get(1, 1) ==  2);
        ctx.CHECK(ma1.get(2, 0) == -7);
        ctx.CHECK(ma1.get(2, 1) ==  1);
        ctx.CHECK(ma1.get(3, 0) == -8);
        ctx.CHECK(ma1.get(3, 1) ==  0);
        
        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) ==  0);
        ctx.CHECK(ma2.get(0, 1) ==  4);
        ctx.CHECK(ma2.get(0, 2) == -3);
        ctx.CHECK(ma2.get(1, 0) ==  7);
        ctx.CHECK(ma2.get(1, 1) ==  0);
        ctx.CHECK(ma2.get(1, 2) ==  5);

        ma1 *= ma2;

        ctx.CHECK(ma1.numRows() ==   4);
        ctx.CHECK(ma1.numCols() ==   3);
        ctx.CHECK(ma1.get(0, 0) ==  63);
        ctx.CHECK(ma1.get(0, 1) ==  20);
        ctx.CHECK(ma1.get(0, 2) ==  30);
        ctx.CHECK(ma1.get(1, 0) ==  14);
        ctx.CHECK(ma1.get(1, 1) ==   0);
        ctx.CHECK(ma1.get(1, 2) ==  10);
        ctx.CHECK(ma1.get(2, 0) ==   7);
        ctx.CHECK(ma1.get(2, 1) == -28);
        ctx.CHECK(ma1.get(2, 2) ==  26);
        ctx.CHECK(ma1.get(3, 0) ==   0);
        ctx.CHECK(ma1.get(3, 1) == -32);
        ctx.CHECK(ma1.get(3, 2) ==  24);

        ctx.CHECK(ma2.numRows() == 2);
        ctx.CHECK(ma2.numCols() == 3);
        ctx.CHECK(ma2.get(0, 0) ==  0);
        ctx.CHECK(ma2.get(0, 1) ==  4);
        ctx.CHECK(ma2.get(0, 2) == -3);
        ctx.CHECK(ma2.get(1, 0) ==  7);
        ctx.CHECK(ma2.get(1, 1) ==  0);
        ctx.CHECK(ma2.get(1, 2) ==  5);
    }
    ctx.result();

    ctx.DESC("Chained usage of *= operator");
    {
        Matrix mmm{2, 2};
        mmm.set(0, 0, 5);
        mmm.set(0, 1, 7);
        mmm.set(1, 0, 11);
        mmm.set(1, 1, 13);

        mmm *= mmm *= mmm;

        ctx.CHECK(mmm.numRows() == 2);
        ctx.CHECK(mmm.numCols() == 2);
        ctx.CHECK(mmm.get(0, 0) == 35352);
        ctx.CHECK(mmm.get(0, 1) == 43848);
        ctx.CHECK(mmm.get(1, 0) == 68904);
        ctx.CHECK(mmm.get(1, 1) == 85464);
    }
    ctx.result();

    ctx.DESC("Matrix * and *= operators on matrices of incompatible sizes");
    {
        Matrix m1{3, 2}, m2{3, 2};
        try {
            m1 *= m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }

        try {
            result = m1 * m2;
            ctx.CHECK(false); // Error:  No exception
        }
        catch (invalid_argument &) {
            ctx.CHECK(true);  // Expected exception
        }
        catch (...) {
            ctx.CHECK(false);  // Error:  Wrong kind of exception
        }
    }
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

    // Unfortunately, cannot test move operators since they are about
    // performance and not correctness.  However, they will likely be used
    // in the matrix-arithmetic tests.

    test_matrix_addition(ctx);
    test_matrix_subtraction(ctx);
    test_matrix_multiplication(ctx);

    // Return 0 if everything passed, nonzero if something failed.
    return !ctx.ok();
}

