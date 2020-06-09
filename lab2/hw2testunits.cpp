#include "testbase.h"
#include "units.h"

#include <cstdlib>
#include <iostream>


using namespace std;


/*===========================================================================
 * TEST FUNCTIONS
 *
 * These are called by the main() function at the end of this file.
 */


/*!
 * Perform some basic tests using the UnitConverter
 */
void test_converter(TestContext &ctx) {
    ctx.DESC("UnitConverter operations");

    UnitConverter u;

    u.add_conversion("km", 1000, "m");  // 1km = 1000m

    UValue v = u.convert_to(UValue{5, "km"}, "m");
    ctx.CHECK(v.get_value() == 5000);
    ctx.CHECK(v.get_units() == "m");

    v = u.convert_to(UValue{10000, "m"}, "km");
    ctx.CHECK(v.get_value() == 10);
    ctx.CHECK(v.get_units() == "km");

    ctx.result();

    ctx.DESC("UnitConverter allows multiple conversions for a type");

    u.add_conversion("m", 39.4, "in");  // 1m = 39.4in

    v = u.convert_to(UValue{5, "m"}, "in");
    ctx.CHECK(v.get_value() == 5 * 39.4);
    ctx.CHECK(v.get_units() == "in");

    v = u.convert_to(UValue{394, "in"}, "m");
    ctx.CHECK(v.get_value() == 394 / 39.4);
    ctx.CHECK(v.get_units() == "m");

    ctx.result();

    ctx.DESC("UnitConverter doesn't allow a conversion more than once");

    try {
        u.add_conversion("m", 39.4, "in");  // Already recorded
        ctx.CHECK(false);  // If no exception, it's a failure
    }
    catch (invalid_argument) {
        ctx.CHECK(true);  // Success!
    }
    catch (...) {
        ctx.CHECK(false);  // Failure:  wrong exception
    }

    try {
        u.add_conversion("in", 1.0 / 39.4, "m");  // Already recorded
        ctx.CHECK(false);  // If no exception, it's a failure
    }
    catch (invalid_argument) {
        ctx.CHECK(true);  // Success!
    }
    catch (...) {
        ctx.CHECK(false);  // Failure:  wrong exception
    }

    ctx.result();

    ctx.DESC("UnitConverter throws on unrecognized conversion");

    try {
        v = u.convert_to(UValue{15, "furlong"}, "km");
        ctx.CHECK(false);  // If no exception, it's a failure
    }
    catch (invalid_argument) {
        ctx.CHECK(true);  // Success!
    }
    catch (...) {
        ctx.CHECK(false);  // Failure:  wrong exception
    }

    ctx.result();
}


/*! This program is a simple test-suite for the units code. */
int main() {
  
    cout << "Lab 2:  Testing the UnitConverter\n\n";

    TestContext ctx(cout);

    test_converter(ctx);

    // Return 0 if everything passed, nonzero if something failed.
    return !ctx.ok();
}
