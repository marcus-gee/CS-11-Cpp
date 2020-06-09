#include "units.h"
#include <string>

using namespace std;

// standard two argument constructor - sets value and units
UValue::UValue(double value, string units) {
    // numerical value of the data
    this->value = value;
    // string representation of the units of the data
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


// convert from current UValue units to new to_units
UValue convert_to(UValue input, string to_units) {
    double converted_val;
    string curr_units = input.get_units();
    double curr_val   = input.get_value();

    if ((curr_units == "lb") && (to_units == "kg")) {
        // 1 lb = 0.45 kg
        converted_val = 0.45 * curr_val;
    } else if ((curr_units == "gal") && (to_units == "L")) {
        // 1 gal = 3.79 L
        converted_val = 3.79 * curr_val;
    } else if ((curr_units == "mi") && (to_units == "km")) {
        // 1 mi = 1.6 km
        converted_val = 1.6 * curr_val;
    } else {
        // if conversion cannot be done just return the input
        return input;
    }

    // return UValue representation of new conversion
    return UValue{converted_val, to_units};
}
