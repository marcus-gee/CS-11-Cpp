#include "units.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

UnitConverter init_converter(const string filename) {
    UnitConverter converter;

    ifstream ifs{filename};

    // make sure file was opened successfully
    if (!ifs) {
        throw invalid_argument("Couldn't open " + filename + "\n");
    }

    // read data until EOF
    while (ifs) {
        double multiplier;
        string from_units, to_units;

        ifs >> from_units >> multiplier >> to_units;
        converter.add_conversion(from_units, multiplier, to_units);
    }

    return converter;
}

int main() {
    double val;
    string from_units, to_units;

    // try-catch improper file
    try {
        UnitConverter u = init_converter("rules.txt");

        cout << "Enter value with units: ";
        cin >> val >> from_units;
        UValue input{val, from_units};

        cout << "Convert to units: ";
        cin >> to_units;

        // try-catch invalid conversions
        try {
            UValue output = u.convert_to(input, to_units);
            cout << "Converted to: "
                 << output.get_value() << " " << output.get_units() << "\n";
        }
        catch (invalid_argument e) {
            cout << e.what() << "\n";
            // return 1;
        }
    }

    catch (invalid_argument e) {
        cout << "File could not be opened!\n";
        // return 1;
    }

    return 0;
}
