/* ceil function: round up value */

#include "xmath.h"

double ceil(double x) {
    double y = x;

    return (_dint(&y, 0) < 0 && 0.0 < x ? y + 1.0 : y);
}
