#include <string>
#include <vector>
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

/** class contains all possible conversions between a pair of units as
 * given by conversion rules
 */
class UnitConverter {
    struct Conversion {
        /** unit to be converted from */
        string from_units;
        //*** ratio between unit conversion */
        double multiplier;
        /** unit to be convert to */
        string to_units;
    };
    /** list of all pairs of conversions */
    vector<Conversion> items;

public:
    // methods
    void add_conversion(string from_units, double multiplier, string to_units);
    UValue convert_to(UValue input, string to_units);
};
