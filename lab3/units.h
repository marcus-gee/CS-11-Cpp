#include <string>
#include <vector>
#include <set>
using namespace std;

// a unit-value class
class UValue {
    // represents the numerical value of the data
    double value;
    // represents the units the data is in
    string units;

public:
    // constructor
    UValue(double value, string units);

    // accessors
    double get_value() const;
    string get_units() const;
};

/* class contains all possible conversions between a pair of units as
 * given by conversion rules
 */
class UnitConverter {
    /* this struct will hold a pair of units that can be use to converted units
     * and the conversion ratio
     */
    struct Conversion {
        // unit to be converted from
        string from_units;
        // ratio between unit conversion
        double multiplier;
        // unit to be convert to
        string to_units;
    };
    // list of all pairs of conversions
    vector<Conversion> items;

public:
    // methods
    void add_conversion(string from_units, double multiplier, string to_units);
    UValue convert_to(const UValue input, const string to_units,set<string> seen);
    UValue convert_to(const UValue input, const string to_units);

};
