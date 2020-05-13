#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
public:
	Rational(int num=0, int denom=1);

	Rational &operator +=(const Rational &r);
	Rational &operator -=(const Rational &r);
	Rational &operator *=(const Rational &r);
	Rational &operator /=(const Rational &r);

	Rational operator -() const;
	Rational inv() const;

	int compareTo(const Rational &r) const;

	int getNumerator() const;
	int getDenominator() const;

	void print(std::ostream &os) const;
private:
	int num, denom;
};

Rational operator +(const Rational &r1, const Rational &r2);
Rational operator -(const Rational &r1, const Rational &r2);
Rational operator *(const Rational &r1, const Rational &r2);
Rational operator /(const Rational &r1, const Rational &r2);
bool operator ==(const Rational &r1, const Rational &r2);

std::ostream &operator <<(std::ostream &os, const Rational &r);


#endif

#include "rational.cpp"
