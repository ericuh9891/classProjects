#ifndef GCD_H
#define GCD_H

inline int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}

#endif
