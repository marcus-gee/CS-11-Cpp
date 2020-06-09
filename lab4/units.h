#include <string>
#include <vector>
#include <set>
using namespace std;

/** a unit-value class */
class UValue {
    /** represents the numerical value of the data */
    double value;
    /** represents the units the data is in */
    string units;

public:
    /** constructor */
    UValue(double value, const string units);

    /** accessors */
    /**
     * gets the value of the UValue instance
     * @param instance of UValue
     * @return the double representing the value
     */
    double get_value() const;

    /**
     * gets the units of the UValue instance
     * @param instance of UValue
     * @return the string representing the units
     */
    string get_units() const;
};

/**
 * class contains all possible conversions between a pair of units as
 * given by conversion rules
 */
class UnitConverter {
    struct Conversion {
        /** unit to be converted from */
        string from_units;
        /** ratio between unit conversion */
        double multiplier;
        /** unit to be convert to */
        string to_units;
    };
    /** list of all pairs of conversions */
    vector<Conversion> items;

public:
    /** methods */
    /**
     * add a pair of conversions to the vector list
     * @param two strings representing the units to be converted to and from,
     *         and a double representing the conversion ratio.
     * @return void
     */
    void add_conversion(string from_units, double multiplier, string to_units);

    /**
     * convert funtion to convert to 'to_units'
     * @param UValue instance, a string of the units to convert that instance
     *         to, and set of stings of units that cannot be used in the
     *         conversion (starts empty & accumulates in the function)
     * @return the new instance of the converted UValue
     */
    UValue convert_to(const UValue input, const string to_units,set<string> seen);

    /**
     * convert funtion to convert to 'to_units'
     * @param UValue instance, a string of the units to convert that instance
     *         to
     * @return the new instance of the converted UValue
     */
    UValue convert_to(const UValue input, const string to_units);
};
