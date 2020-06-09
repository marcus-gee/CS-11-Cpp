#include "rational.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

Rational::Rational(int n, int d) {
    if (d < 0) {
        // If d is neg, invert the sign of both n and d so that d is pos
        n *= -1;
        d *= -1;
    }
    else if (d == 0) {
        string error = "invalid: division by 0";
        throw invalid_argument(error);
    }

    // set numerator and denominator
    this->n = n;
    this->d = d;
}

int Rational::gcd(int a, int b) const {
    if ((a == b) || (a == 0)) {
        return b;
    }
    else if (a > b) {
        return gcd(b, a);
    }
    else {
        return gcd((b % a), a);
    }
}

int Rational::num() const {
    return n;
}

int Rational::denom() const {
    return d;
}

Rational Rational::reciprocal() const {
    return Rational{d, n};
}

void Rational::reduce() {
    // calculate gcd with positive values
    int a, b;
    a = n;
    b = d;
    if (n < 0) {
        a *= -1;
    }

    int div = gcd(a, b);
    n /= div;
    d /= div;
}

Rational & Rational::operator*=(const Rational &r) {
    n *= r.n;
    d *= r.d;
    this->reduce();
    return *this;
}

Rational & Rational::operator/=(const Rational &r) {
    *this *= r.reciprocal();
    return *this;
}

Rational & Rational::operator+=(const Rational &r) {
    n = (n * r.d) + (r.n * d);
    d *= r.d;
    this->reduce();
    return *this;
}

Rational & Rational::operator-=(const Rational &r) {
    Rational neg{-1};
    neg *= r;
    *this += neg;
    return *this;
}

Rational &operator*(const Rational &r1, const Rational &r2) {
    return Rational{r1} *= r2;
}

Rational &operator/(const Rational &r1, const Rational &r2) {
    return Rational{r1} /= r2;
}

Rational &operator+(const Rational &r1, const Rational &r2) {
    return Rational{r1} += r2;
}

Rational &operator-(const Rational &r1, const Rational &r2) {
    return Rational{r1} -= r2;
}

ostream &operator<<(ostream &os, const Rational r) {
    os << r.num();

    if (r.denom() != 1) {
        os << "/" << r.denom();
    }
    return os;
}
