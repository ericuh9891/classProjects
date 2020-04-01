#include <string>
#include <iostream>
#include "rational.h"
#include <stdlib.h>
#include "rational_exception.h"

using namespace std;

int Rational::gcd(int num1, int num2){
	num1 = abs(num1);
	num2 = abs(num2);
	if(num2 == 0)
		return num1;
	else
		return gcd(num2, num1%num2);
}

Rational::Rational(int numer, int denom){
	if(denom == 0)
		throw RationalException("Denominator cannot be zero");
	else{
		int gcd = Rational::gcd(numer,denom);	
		this->num = numer/gcd;
		this->denom = denom/gcd;
	}
}
int Rational::getNumerator()const{
	return num;
}
int Rational::getDenominator()const{
	return denom;
}
Rational Rational::neg()const{
	return Rational(this->getNumerator() * -1,this->getDenominator());
}
Rational Rational::inv()const{
	return Rational(this->getDenominator(), this->getNumerator());
}
Rational Rational::add(const Rational &r)const{
	return Rational(this->num * r.getDenominator() + r.getNumerator() * this->denom, this->denom * r.getDenominator());
}
Rational Rational::sub(const Rational &r)const{
	return Rational(this->num * r.getDenominator() - r.getNumerator() * this->denom, this->denom * r.getDenominator());
}
Rational Rational::mul(const Rational &r)const{
	return Rational(this->num * r.getNumerator(), this->denom * r.getDenominator());
}
Rational Rational::div(const Rational &r) const{
	return this->mul(r.inv());
}
Rational& Rational::addInPlace(const Rational &r){
	return *this = this->add(r);
}
Rational& Rational::subInPlace(const Rational &r){
	return *this = this->sub(r);
}
Rational& Rational::mulInPlace(const Rational &r){
	return *this = this->mul(r);
}
Rational& Rational::divInPlace(const Rational &r){
	return *this = this->div(r);
}
bool Rational::equals(const Rational &r)const{
	if(this->num == r.getNumerator() && this->denom == r.getDenominator())
		return true;
	else
		return false;
}
int Rational::compareTo(const Rational &r)const{
	int tempCallerNumer = this->getNumerator() * r.getDenominator();
	int tempArgNumer = this->getDenominator() * r.getNumerator();
	if(tempCallerNumer < tempArgNumer)
		return -1;
	else if (tempCallerNumer > tempArgNumer)
		return 1;
	else 
		return 0;
}
void Rational::print(ostream &os)const{
	if(num == 0)
		os << 0;
	else if (denom == 1)
		os << num;
	else
		os << this->getNumerator() << "/" << this->getDenominator();
}
