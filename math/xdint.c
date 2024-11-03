/* _dint function */

#include "xmath.h"

short _dint(double *px, short xexp) {
    unsigned short *ps = (unsigned short *)px;
    unsigned short frac = ps[D0] & DFRAC || ps[D1] || ps[D2] || ps[D3];
    short xchar = (ps[D0] & DMASK) >> DOFF;
    
    if (xchar == 0 && frac != 0) // zero
        return 0;
    else if (xchar != DMAX) // finite
        ;
    else if (frac != 0)
        return INF;
    else { // NaN
        errno = EDOM;
        return NAN;
    }
    
    xchar = DBIAS + 48 + DOFF + 1 - xchar - xexp;
    if (xchar <= 0) // no frac bits to drop
        return (0);
    else if (48 + DOFF < xchar) { // all frac bits
        ps[D0] = 0;
        ps[D1] = 0;
        ps[D2] = 0;
        ps[D3] = 0;
        
        return FINITE;
    }
    else { // strip out frac bits
        static const size_t sub[] = {D3, D2, D1, D0};
        static const unsigned short mask[] = {
            0x0000, 0x0001, 0x0003, 0x0007,
            0x000f, 0x001f, 0x003f, 0x007f,
            0x00ff, 0x01ff, 0x03ff, 0x07ff,
            0x0fff, 0x1fff, 0x3fff, 0x7fff};

        frac = mask[xchar & 0x0f];
        xchar >>= 4;
        frac &= ps[sub[xchar]];
        ps[sub[xchar]] ^= frac;
        
        switch (xchar) {
            case 3:
                frac |= ps[D1];
                ps[D1] = 0;
                
            case 2:
                frac |= ps[D2];
                ps[D2] = 0;
                
            case 1:
                frac |= ps[D3];
                ps[D3] = 0;
        }
        
        return frac ? FINITE : 0;
    }
}
