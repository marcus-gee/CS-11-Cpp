#include "testbase.h"
#include "rational.h"

#include <sstream>

using namespace std;


/*===========================================================================
 * TEST FUNCTIONS
 *
 * These are called by the main() function at the end of this file.
 */


/*! Test the Rational constructors. */
void test_constructors(TestContext &ctx) {
    ctx.DESC("Rational constructors");

    Rational r1;
    Rational r2(5);
    Rational r3(5, 3);

    ctx.CHECK(r1.num() == 0 && r1.denom() == 1);
    ctx.CHECK(r2.num() == 5 && r2.denom() == 1);
    ctx.CHECK(r3.num() == 5 && r3.denom() == 3);
    ctx.result();

    ctx.DESC("Rational constructor handles negative denominator");

    Rational r7(5, -3);
    Rational r8(-5, -3);

    ctx.CHECK(r7.num() == -5 && r7.denom() == 3);
    ctx.CHECK(r8.num() == 5 && r8.denom() == 3);
    ctx.result();

    ctx.DESC("Rational constructor throws on 0 denominator");

    bool pass = true;
    try {
        Rational r7(5, 0);
        pass = false;
    }
    catch (invalid_argument &ia) {
        pass = true;
    }
    catch (...) {
        pass = false;
    }
    ctx.CHECK(pass);
    ctx.result();
}


void test_compound_operators(TestContext &ctx) {
    ctx.DESC("Rational operator +=");

    // 5 += (-3)
    Rational r(5);
    r += Rational(-3);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);

    // 2 += (-2)  This should set r1 = 0.
    r += Rational(-2);
    ctx.CHECK(r.num() == 0 && r.denom() == 1);

    r = Rational(2, 3);
    r += Rational(4, 5);  // 22/15
    ctx.CHECK(r.num() == 22 && r.denom() == 15);

    ctx.result();

    ctx.DESC("Rational operator += self-assignment");
    r = Rational(4, 5);
    r += r;
    ctx.CHECK(r.num() == 8 && r.denom() == 5);
    ctx.result();

    ctx.DESC("Rational operator -=");

    r = 5;
    r -= Rational(3);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);

    r -= Rational(2);
    ctx.CHECK(r.num() == 0 && r.denom() == 1);

    r = Rational(2, 3);
    r -= Rational(1, 5);  // 7/15
    ctx.CHECK(r.num() == 7 && r.denom() == 15);

    ctx.result();

    ctx.DESC("Rational operator -= self-assignment");
    r = Rational(4, 5);
    r -= r;
    ctx.CHECK(r.num() == 0 && r.denom() == 1);
    ctx.result();

    ctx.DESC("Rational operator *=");

    r = Rational(3, 5);

    r *= Rational(2, 7);  // 6/35
    ctx.CHECK(r.num() == 6 && r.denom() == 35);

    r = Rational(4);
    r *= Rational(5, 4);
    ctx.CHECK(r.num() == 5 && r.denom() == 1);

    ctx.result();

    ctx.DESC("Rational operator *= self-assignment");
    r = Rational(4, 5);
    r *= r;
    ctx.CHECK(r.num() == 16 && r.denom() == 25);
    ctx.result();

    ctx.DESC("Rational operator /=");

    r = Rational(3, 5);
    r /= Rational(2);
    ctx.CHECK(r.num() == 3 && r.denom() == 10);
    ctx.result();
    
    ctx.DESC("Rational operator /= self-assignment");
    r = Rational(4, 5);
    r /= r;
    ctx.CHECK(r.num() == 1 && r.denom() == 1);
    ctx.result();
    
    // Make sure division will properly reduce the result.
    ctx.DESC("Rational operator /= reduces fractions");
    r = Rational(4, 5);
    r /= Rational(2, 5);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);
    ctx.result();
    
    ctx.DESC("Rational operator /= throws on divide-by-zero");
    r = Rational(4, 5);
    bool pass = false;
    try {
        r /= Rational();
        pass = false;
    }
    catch (invalid_argument &ia) {
        pass = true;
    }
    catch (...) {
        pass = false;
    }
    ctx.CHECK(pass);
    ctx.result();
}


void test_simple_arithmetic(TestContext &ctx) {
    Rational r;
    bool pass = false;
    
    ctx.DESC("Rational operator +");

    // 5 + (-3)
    r = 5;
    r = r + Rational(-3);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);

    // 2 + (-2)  This should set r1 = 0.
    r = r + Rational(-2);
    ctx.CHECK(r.num() == 0 && r.denom() == 1);

    r = Rational(2, 3);
    r = r + Rational(4, 5);  // 22/15
    ctx.CHECK(r.num() == 22 && r.denom() == 15);

    ctx.result();

    ctx.DESC("Rational operator -");

    r = 5;
    r = r - Rational(3);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);

    r = r - Rational(2);
    ctx.CHECK(r.num() == 0 && r.denom() == 1);

    r = Rational(2, 3);
    r = r - Rational(1, 5);  // 7/15
    ctx.CHECK(r.num() == 7 && r.denom() == 15);

    ctx.result();

    ctx.DESC("Rational operator *");

    r = Rational(3, 5);

    r = r * Rational(2, 7);  // 6/35
    ctx.CHECK(r.num() == 6 && r.denom() == 35);

    r = Rational(4);
    r = r * Rational(5, 4);
    ctx.CHECK(r.num() == 5 && r.denom() == 1);

    ctx.result();

    ctx.DESC("Rational operator /");

    r = Rational(3, 5);
    r = r / Rational(2);
    ctx.CHECK(r.num() == 3 && r.denom() == 10);
    ctx.result();

    // Make sure division will properly reduce the result.
    ctx.DESC("Rational operator / reduces fractions");
    r = Rational(4, 5);
    r = r / Rational(2, 5);
    ctx.CHECK(r.num() == 2 && r.denom() == 1);
    ctx.result();

    ctx.DESC("Rational operator / throws on divide-by-zero");
    r = Rational(4, 5);
    pass = false;
    try {
        r = r / Rational();
        pass = false;
    }
    catch (invalid_argument &ia) {
        pass = true;
    }
    catch (...) {
        pass = false;
    }
    ctx.CHECK(pass);
    ctx.result();
}


void test_reciprocal_reduce(TestContext &ctx) {
    Rational r;
    bool pass;

    ctx.DESC("Reciprocal operation");
    
    r = Rational(2, 5);
    ctx.CHECK(r.num() == 2 && r.denom() == 5);
    r = r.reciprocal();
    ctx.CHECK(r.num() == 5 && r.denom() == 2);
    
    r = Rational(5);
    ctx.CHECK(r.num() == 5 && r.denom() == 1);
    r = r.reciprocal();
    ctx.CHECK(r.num() == 1 && r.denom() == 5);
    
    ctx.result();
    
    ctx.DESC("Reciprocal of 0 should throw");
    r = Rational(0);
    pass = false;
    try {
        r = r.reciprocal();
        pass = false;
    }
    catch (invalid_argument &ia) {
        pass = true;
    }
    catch (...) {
        pass = false;
    }
    ctx.CHECK(pass);
    
    ctx.result();

    ctx.DESC("Reduce operation");

    Rational r4(15, 5);
    ctx.CHECK(r4.num() == 15 && r4.denom() == 5);
    r4.reduce();
    ctx.CHECK(r4.num() == 3 && r4.denom() == 1);

    Rational r5(3, 15);
    ctx.CHECK(r5.num() == 3 && r5.denom() == 15);
    r5.reduce();
    ctx.CHECK(r5.num() == 1 && r5.denom() == 5);

    Rational r6(48, 60);
    ctx.CHECK(r6.num() == 48 && r6.denom() == 60);
    r6.reduce();
    ctx.CHECK(r6.num() == 4 && r6.denom() == 5);

    ctx.result();

    ctx.DESC("Reduce of 0/n becomes 0/1");
    Rational r7(0, 50);
    ctx.CHECK(r7.num() == 0 && r7.denom() == 50);
    r7.reduce();
    ctx.CHECK(r7.num() == 0 && r7.denom() == 1);
    ctx.result();
}

/*
void test_comparison(TestContext &ctx) {
    ctx.DESC("Rational == operator");
    ctx.CHECK(Rational{4, 5} == Rational{4, 5});
    ctx.CHECK(Rational{-10, 2} == Rational{-5});
    ctx.CHECK(!(Rational{9, 3} == Rational{9}));
    ctx.result();

    ctx.DESC("Rational != operator");
    ctx.CHECK(Rational{4, 5} != Rational{-4, 5});
    ctx.CHECK(Rational{4, 5} != Rational{4, 3});
    ctx.CHECK(!(Rational{9, 3} != Rational{3}));
    ctx.result();

    ctx.DESC("Rational > operator");
    ctx.CHECK(Rational{5} > Rational{4});
    ctx.CHECK(Rational{10, 2} > Rational{20, 5});
    ctx.CHECK(!(Rational{4} > Rational{5}));
    ctx.result();

    ctx.DESC("Rational < operator");
    ctx.CHECK(Rational{4} < Rational{5});
    ctx.CHECK(Rational{20, 5} < Rational{10, 2});
    ctx.CHECK(!(Rational{5} < Rational{4}));
    ctx.result();

    ctx.DESC("Rational >= operator");
    ctx.CHECK(Rational{5} >= Rational{4});
    ctx.CHECK(Rational{10, 2} >= Rational{20, 5});
    ctx.CHECK(!(Rational{4} >= Rational{5}));
    ctx.CHECK(Rational{4, 5} >= Rational{4, 5});
    ctx.CHECK(Rational{-10, 2} >= Rational{-5});
    ctx.CHECK(!(Rational{9, 3} >= Rational{9}));
    ctx.result();

    ctx.DESC("Rational <= operator");
    ctx.CHECK(Rational{4} <= Rational{5});
    ctx.CHECK(Rational{20, 5} <= Rational{10, 2});
    ctx.CHECK(!(Rational{5} <= Rational{4}));
    ctx.CHECK(Rational{4, 5} <= Rational{4, 5});
    ctx.CHECK(Rational{-10, 2} <= Rational{-5});
    ctx.CHECK(!(Rational{9, 3} <= Rational{9}));
    ctx.result();

}
*/

void test_casting(TestContext &ctx) {
    Rational r;

    ctx.DESC("Implicit casting from int to Rational");
    
    r = 62;
    ctx.CHECK(r.num() == 62 && r.denom() == 1);
    
    ctx.result(); 
}


void test_stream_output(TestContext &ctx) {
    Rational r;
    stringstream sstream;
    
    ctx.DESC("Stream-output of a whole number");
    r = Rational(31);
    sstream.str("");
    sstream << r;
    ctx.CHECK(sstream.str() == "31");
    ctx.result();
    
    ctx.DESC("Stream-output of zero");
    r = Rational();
    sstream.str("");
    sstream << r;
    ctx.CHECK(sstream.str() == "0");
    ctx.result();

    ctx.DESC("Stream-output of a fraction");
    r = Rational(22, 7);
    sstream.str("");
    sstream << r;
    ctx.CHECK(sstream.str() == "22/7");
    ctx.result();
}


/*! This program is a simple test-suite for the Rational class. */
int main() {
  
    cout << "Testing the Rational class." << endl << endl;

    TestContext ctx(cout);

    test_constructors(ctx);
    test_reciprocal_reduce(ctx);
    test_compound_operators(ctx);
    test_simple_arithmetic(ctx);
    // test_comparison(ctx);
    test_casting(ctx);
    test_stream_output(ctx);
    
    // Return 0 if everything passed, nonzero if something failed.
    return !ctx.ok();
}

