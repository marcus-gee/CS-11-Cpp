#include "units.h"
#include <string>
#include <iostream>

using namespace std;

/** initialize the converter w/ all conversions coded inside */
UnitConverter init_converter() {
    UnitConverter converter;

    converter.add_conversion("mi", 5280, "ft");
    converter.add_conversion("mi", 1.6, "km");
    converter.add_conversion("ft", 12, "in");

    converter.add_conversion("in", 2.54, "cm");

    converter.add_conversion("lb", 0.45, "kg");
    converter.add_conversion("stone", 14, "lb");
    converter.add_conversion("lb", 16, "oz");

    converter.add_conversion("kg", 1000, "g");

    converter.add_conversion("gal", 3.79, "L");
    converter.add_conversion("bushel", 9.3, "gal");
    converter.add_conversion("ft^3", 7.5, "gal");
    converter.add_conversion("L", 1000, "ml");

    return converter;
}

/** main program will init all conversions and use that data to make
 * conversions as prompted by user. Will throw error if user
 * tries to make an invalid conversion (i.e. cannot convert between units, or
 * conversion was not mentioned in 'rules' file)
 */
int main() {
    UnitConverter u = init_converter();


    double val;
    string from_units, to_units;

    cout << "Enter value with units: ";
    cin >> val >> from_units;
    UValue input{val, from_units};

    cout << "Convert to units: ";
    cin >> to_units;

    try {
        UValue output = u.convert_to(input, to_units);
        cout << "Converted to: "
             << output.get_value() << " " << output.get_units() << "\n";
    }
    catch (invalid_argument e) {
        cout << "Couldn't convert to " << to_units << "!\n";
        cout << e.what() << "\n";
    }
    return 0;
}
