#include "units.h"
#include <string>
#include <stdexcept>
#include <set>


using namespace std;

// standard two argument constructor - sets value and units
UValue::UValue(double value, string units) {
    this->value = value;
    this->units = units;
}

// returns value of a UValue
double UValue::get_value() const {
    return value;
}

// returns the units of a UValue
string UValue::get_units() const {
    return units;
}

// adds a conversion to the list of conversions if it is not currently there
// throws invalid_argument error if conversion already exists
void UnitConverter::add_conversion(string from_units, double multiplier, string to_units)
{
    // Verify that the conversion doesn't already appear in the object!
    for (Conversion c : items) {
        // If this case occurs, method should throw invalid_argument exception.
        if ((c.from_units == from_units) && (c.to_units == to_units)) {
            string e_message = "Already have a conversion from " + from_units \
                               + " to " + to_units;
            throw invalid_argument(e_message);
        }
    }

    // if exception not thrown, we can proceed to add conversion
    items.push_back({from_units, multiplier, to_units});
    items.push_back({to_units, (1 / multiplier), from_units});
}

// convert from current UValue units to new to_units
UValue UnitConverter::convert_to
(   const UValue input, const string to_units, set<string> seen   )
{
    string from_units = input.get_units();
    double from_val   = input.get_value();

    // add units to seen
    seen.insert(from_units);

    for (Conversion c : items) {
        // If conversion is found, convert and return
        if ((c.from_units == from_units) && (c.to_units == to_units)) {
            return UValue{(from_val * c.multiplier), to_units};
        }
        else if ((c.from_units == from_units) && (seen.count(c.to_units) == 0)){
            UValue v{(from_val * c.multiplier), c.to_units};
            try {
                return convert_to(v, to_units, seen);
            }
            catch (invalid_argument e) {
            }
        }
    }

    string e_message = "Don't know how to convert from " + from_units + " to " \
                        + to_units;
    throw invalid_argument(e_message);
}

// two argument function, which calls the three argument one
UValue UnitConverter::convert_to(const UValue input, const string to_units) {
    return convert_to(input, to_units, set<string>{});
}
