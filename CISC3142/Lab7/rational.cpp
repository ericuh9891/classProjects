#include "rational_exception.h"

int mygcd(int a, int b){
	return b == 0 ? a : mygcd(b, a % b);
}

Rational::Rational(int num, int denom){
	if(denom == 0)
		throw RationalException("Denominator cannot be zero");
	else{
		int temp = mygcd(num,denom);
		this->num = num/temp;
		this->denom = denom/temp; 
	}
}

int Rational::getNumerator() const{
	return num;
}

int Rational::getDenominator() const{
	return denom;
}

Rational Rational::inv() const{
	return Rational(denom,num);
}

Rational &Rational::operator+=(const Rational &r){
	num = num * r.getDenominator();
	int temp = r.getNumerator() * denom;
	num += temp;
	denom = denom * r.getNumerator();
	temp = mygcd(num,denom);
	num = num/temp;
	denom = denom/temp;
	return *this;
}

Rational &Rational::operator-=(const Rational &r){
	num = num * r.getDenominator();
	int temp = r.getNumerator() * denom;
	num -= temp;
	denom = denom * r.getNumerator();
	temp = mygcd(num,denom);
	num = num/temp;
	denom = denom/temp;
	return *this;
}

Rational &Rational::operator*=(const Rational &r){
	num = num * r.getNumerator();
	denom = denom * r.getDenominator();
	int temp = mygcd(num,denom);
	num = num/temp;
	denom = denom/temp;
	return *this;
}

Rational &Rational::operator/=(const Rational &r){
	Rational inv = r.inv();
	num = num * inv.getNumerator();
	denom = denom * inv.getDenominator(); 
	int temp = mygcd(num,denom);
	num = num / temp;
	denom = denom / temp;
	return *this;
}

Rational Rational::operator-() const{
	return Rational(-num,denom);
}

int Rational::compareTo(const Rational &r) const{
	int callerNumer = this->getNumerator() * r.getDenominator();
	int argNumer = this->getDenominator() * r.getNumerator();
	if(callerNumer < argNumer)
		return -1;
	else if(callerNumer > argNumer)
		return 1;
	else
		return 0;
}

Rational operator+(const Rational &r1, const Rational &r2){
	return Rational(r1.getNumerator() * r2.getDenominator() + r2.getNumerator() * r1.getDenominator(),
		r1.getDenominator() * r2.getNumerator());
}

Rational operator-(const Rational &r1, const Rational &r2){
	return Rational(r1.getNumerator() * r2.getDenominator() - r2.getNumerator() * r1.getDenominator(),
		r1.getDenominator() * r2.getNumerator());
}

Rational operator*(const Rational &r1, const Rational &r2){
	return Rational(r1.getNumerator() * r2.getNumerator(), r1.getDenominator() * r2.getDenominator());
}

Rational operator/(const Rational &r1, const Rational &r2){
	return r1 * r2.inv();
}

bool operator==(const Rational &r1, const Rational &r2){
	if(r1.getNumerator() == r2.getNumerator() && r1.getDenominator() == r2.getDenominator())
		return true;
	else
		return false;
}

void Rational::print(std::ostream &os) const{
	if(num == 0)
		os << 0;
	else if(denom == 1)
		os << num;
	else
		os << num << "/" << denom;
}

std::ostream &operator<<(std::ostream &os, const Rational &r){
	r.print(os);
	return os;
}























