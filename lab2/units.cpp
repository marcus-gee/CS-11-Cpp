#include "units.h"
#include <string>
#include <stdexcept>

using namespace std;

// standard two argument constructor - sets value and units
UValue::UValue(double value, string units) {
    this->value = value;
    this->units = units;
}

// returns value of a UValue
double UValue::get_value() {
    return value;
}

// returns the units of a UValue
string UValue::get_units() {
    return units;
}

// adds a conversion to the list of conversions if it is not currently there
// throws invalid_argument error if conversion already exists
void UnitConverter::add_conversion
(   string from_units,
    double multiplier,
    string to_units
)
{
    // Verify that the conversion doesn't already appear in the object!
    for (Conversion c : items) {
        // If this case occurs, method should throw invalid_argument exception.
        if ((c.from_units == from_units) && (c.to_units == to_units)) {
            string e_message_f = "Already have a conversion from " + from_units;
            string e_message_t = " to " + to_units;
            throw invalid_argument(e_message_f + e_message_t);
        }
    }

    // if exception not thrown, we can proceed to add conversion
    items.push_back({from_units, multiplier, to_units});
    items.push_back({to_units, (1 / multiplier), from_units});
}

// convert from current UValue units to new to_units
UValue UnitConverter::convert_to(UValue input, string to_units) {
    string from_units = input.get_units();
    double from_val   = input.get_value();

    for (Conversion c : items) {
        // If conversion is found, convert and return
        if ((c.from_units == from_units) && (c.to_units == to_units)) {
            return UValue{(from_val * c.multiplier), to_units};
        }
    }

    string e_message_f = "Don't know how to convert from " + from_units;
    string e_message_t = " to " + to_units;
    throw invalid_argument(e_message_f + e_message_t);
}
