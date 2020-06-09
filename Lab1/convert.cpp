#include "units.h"
#include <string>
#include <iostream>

using namespace std;

/* main function prompts user to enter a value with units and new units to
 * convert to. If conversion can be done, the converted value is output, if not,
 * an error message is printed.
 */
int main() {
    double val;
    string units, to_units;

    cout << "Enter value with units: ";
    cin >> val >> units;
    UValue input{val, units};

    cout << "Convert to units: ";
    cin >> to_units;

    UValue converted = convert_to(input, to_units);
    if (converted.get_units() != to_units) {
        cout << "Couldn't convert to " << to_units << "!\n";
    } else {
        cout << "Converted to: "
             << converted.get_value() << " " << converted.get_units() << "\n";
    }
    return 0;
}
