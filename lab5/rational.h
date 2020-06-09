#include <string>
using namespace std;

/** a rational number class  */
class Rational {
    private:
        /** int values for the numerator and denominator */
        int n, d;
        /**
         * private function to find gcd of two nums. used in reduce
         * @param ints to find the gcd between
         * @return the gcd of the inputs
         */
        int gcd(int a, int b) const;

    public:
        /**
         * Rational constructor
         * @param ints representing numerator and denominator
         * @return instance of Rational with given n/d.
         */
        Rational(int n = 0, int d = 1);

        /**
         * accessor - returns numerator
         * @param void
         * @return numerator of Rational object
         */
        int num() const;

        /**
         * accessor - returns denominator
         * @param void
         * @return denominator of Rational object
         */
        int denom() const;

         // methods
         /**
          * return reciprocal of rational fract (i.e. n/d -> d/n)
          * @param void
          * @return instance Rational object representing the reciprocal
          */
         Rational reciprocal() const;

         /**
          * reduces the rational number such that the greatest common divisor
          * of the numerator and denominator is 1
          * @param void
          * @return void
          */
         void reduce();

         /**
          * compound assignment multiplication for the Rational class
          * @param Rational object
          * @return Rational object
          */
         Rational &operator*=(const Rational &r);

         /**
          * compound assignment division for the Rational class
          * @param Rational object
          * @return Rational object
          */
         Rational &operator/=(const Rational &r);

         /**
          * compound assignment addition for the Rational class
          * @param Rational object
          * @return Rational object
          */
         Rational &operator+=(const Rational &r);

         /**
          * compound assignment subtraction for the Rational class
          * @param Rational object
          * @return Rational object
          */
         Rational &operator-=(const Rational &r);
};

/**
 * simple arithmetic multiplication for the Rational class
 * @param two Rational objects
 * @return Rational object
 */
Rational &operator*(const Rational &r1, const Rational &r2);

/**
 * simple arithmetic division for the Rational class
 * @param two Rational objects
 * @return Rational object
 */
Rational &operator/(const Rational &r1, const Rational &r2);

/**
 * simple arithmetic addition for the Rational class
 * @param two Rational objects
 * @return Rational object
 */
Rational &operator+(const Rational &r1, const Rational &r2);

/**
 * simple arithmetic subtraction for the Rational class
 * @param two Rational objects
 * @return Rational object
 */
Rational &operator-(const Rational &r1, const Rational &r2);

/**
 * stream output of rational value
 * @param ostream and Rational object
 * @return ostream
 */
ostream &operator<<(ostream &os, const Rational r);
