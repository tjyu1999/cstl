/* floor function: round down value */

#include "xmath.h"

double floor(double x) {
    double y = x;
    
    return (_dint(&y, 0) < 0 && x < 0.0 ? y - 1.0 : y);
}
