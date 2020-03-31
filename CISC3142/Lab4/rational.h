#include <string>
#include <iostream>

#ifndef RATIONAL_H
#define RATIONAL_H

using namespace std;

class Rational{
	public:
		Rational() : num{0}, denom{0}{};
		Rational(int numer) : num{numer}, denom{1}{};
		Rational(int numer, int denom);
		Rational(const Rational &r){
		    this->num = r.getNumerator();
		    this->denom = r.getDenominator();
		}
		int getNumerator()const;
		int getDenominator()const;
		Rational neg()const;
		Rational inv()const;
		Rational add(const Rational &r)const;
		Rational sub(const Rational &r)const;
		Rational mul(const Rational &r)const;
		Rational div(const Rational &r)const;
		Rational &addInPlace(const Rational &r);
		Rational &subInPlace(const Rational &r);
		Rational &mulInPlace(const Rational &r);
		Rational &divInPlace(const Rational &r);
		bool equals(const Rational &r)const;
		int compareTo(const Rational &r)const;
		void print(ostream &os) const;
	private:
		int num;
		int denom;
};

inline ostream &operator <<(ostream &os, const Rational &r) {r.print(os);}

#endif
class RationalException{
	public:
		RationalException(string what) : what(what){}
		string getWhat(){return what;}
	private:
		string what;
};
