#include <string>
using namespace std;

// a unit-value class
class UValue {
    double value;
    string units;

    public:
        // constructor
        UValue(double value, string units);

        // accessors
        double get_value();
        string get_units();
};

// convert from current UValue units to new to_units
UValue convert_to(UValue input, string to_units);
