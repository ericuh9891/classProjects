#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include "rational.h"
#include "rational_exception.h"

using namespace std;

#define ALLOW_ZERO_ZERO false

void getError(const Rational &r, int num, int den);
void compOpError(Rational opd1,  Rational opd2,  int result, int correctResult);
void equalsError(const Rational &opd1,  const Rational &opd2,  bool result, bool correctResult);
void binopError(const string &theOperation, const Rational &opd1, const Rational &opd2, const Rational &result, const Rational &myResult);
void unopError(const string &theOperation, const Rational &opd1, const Rational &result, const Rational &myResult);
void normalizationCheck(const Rational &r, int num, int denom);
void insertionCheck(const Rational &r);
void exceptionError();
void noExceptionError(string optr, const Rational &r, int num, int denom);

void doOneTest(int num1, int den1, int num2, int den2);
string str(const Rational &r);
int gcd(int a, int b);

int main() {

    cerr << "Initial tests...";

    //---------- Testing getNumerator/getDenominator on simple fractions -- no normalization needed

    Rational r(1, 2);
    if (r.getNumerator() != 1 || r.getDenominator() != 2)
        getError(r, 1, 2);

    normalizationCheck(r, 1, 2);      // Check for normalization of rationals

    insertionCheck(r);          // Check << operator

    r = Rational(2, 4);
    normalizationCheck(r, 2, 4);      // Check for normalization of rationals

    insertionCheck(r);          // Check << operator

    // Check 1-arg constructor

    r = Rational(3);
    if (r.getNumerator() != 3 || r.getDenominator() != 1)
        getError(r, 3, 1);

	// Check compareTo method

	Rational 
		r1(1, 3),
		r2(1, 2);
	int val = r1.compareTo(r2);
	if (val != -1) compOpError(r1, r2, val, -1);
	val = r2.compareTo(r1);
	if (val != 1) compOpError(r1, r2, val, 1);
	r2 = Rational(1,3);
	val = r1.compareTo(r2);
	if (val != 0) compOpError(r1, r2, val, 0);

	// Check equals method
	
	r1 = Rational(1, 3);
	r2 = Rational(1, 2);
	bool b = r1.equals(r2);
	if (b) equalsError(r1, r2, b, false);
	b = r2.equals(r1);
	if (b) equalsError(r1, r2, b, false);
	r2 = Rational(1,3);
	b = r1.equals(r2);
	if (!b) equalsError(r1, r2, b, true);

    // Check that 0 denominator throws exception
    try {
        r = Rational(5, 0);
        noExceptionError("Rational(int, int)", r, 5, 0);
    } catch(RationalException re) {
    }

    try {
        r = Rational(0, 3);
    } catch(RationalException re) {
        exceptionError();
    }

    cerr << "done!" << endl;

    cerr << "Testing on some simple rationals...";

    for (int num1 = 0; num1 < 4; num1++)
        for (int den1 = 0; den1 < 4; den1++)
            for (int num2 = 0; num2 < 4; num2++)
                for (int den2 = 0; den2 < 4; den2++)
                    doOneTest(num1, den1, num2, den2);

    cerr << "done!" << endl;

    cerr << "Testing on 10,000 random rationals...";

    srand(time(NULL));

    for (int i = 0; i < 10000; i++) {
        int
            num1 = rand() % 10000,
            denom1 = rand() % 10000,
            num2 = rand() % 10000,
            denom2 = rand() % 10000;

        doOneTest(num1, denom1, num2, denom2);
    }

   cerr << "done!" << endl;

   cerr << "**** Success ****" << endl;

   return 0;
}

void doOneTest(int num1, int denom1, int num2, int denom2) {
    bool expectingException = false;

    try {

       if (!ALLOW_ZERO_ZERO) {
           if (num1 == 0 && denom1 == 0 ||
                num2 == 0 && denom2 == 0) {
                //cerr << "Ignoring Rational(0, 0)" << endl;
                return;
           }
       }

       expectingException = denom1 == 0;

       Rational opd1(num1, denom1);

       if (expectingException) noExceptionError("Rational(int, int)", opd1, num1, denom1);

       normalizationCheck(opd1, num1, denom1);

       insertionCheck(opd1);

       expectingException = denom2 == 0;

       Rational opd2(num2, denom2);

       if (expectingException) noExceptionError("Rational(int, int)", opd2, num2, denom2);


       normalizationCheck(opd2, num2, denom2);
       insertionCheck(opd2);

        Rational result = opd1.neg();
	   Rational myResult = Rational(-opd1.getNumerator(), opd1.getDenominator());
        if (!result.equals(myResult)) unopError("neg", opd1, result, myResult);

        result = opd2.neg();
	   myResult = Rational(-opd2.getNumerator(), opd2.getDenominator());
        if (!result.equals(myResult)) unopError("neg", opd2, result, myResult);

        result = opd1.add(opd2);
        myResult = Rational(opd1.getNumerator() * opd2.getDenominator() + opd2.getNumerator() * opd1.getDenominator(),
                                opd1.getDenominator() * opd2.getDenominator());
        if (!result.equals(myResult)) binopError("add", opd1, opd2, result, myResult);

        result = opd1.sub(opd2);
        myResult = Rational(opd1.getNumerator() * opd2.getDenominator() - opd2.getNumerator() * opd1.getDenominator(),
                        opd1.getDenominator() * opd2.getDenominator());
        if (!result.equals(myResult)) binopError("sub", opd1, opd2, result, myResult);

        result = opd1.mul(opd2);
        myResult = Rational(opd1.getNumerator() * opd2.getNumerator(), opd1.getDenominator() * opd2.getDenominator());
        if (!result.equals(myResult)) binopError("mul", opd1, opd2, result, myResult);

        expectingException = opd2.getNumerator() == 0;

        result = opd1.div(opd2);
        myResult = Rational(opd1.getNumerator() * opd2.getDenominator(),
                    opd1.getDenominator() * opd2.getNumerator());
        if (!result.equals(myResult)) binopError("div", opd1, opd2, result, myResult);

        if (expectingException)
            noExceptionError("div", opd2, opd2.getNumerator(), opd2.getDenominator());

        if (opd1.getNumerator() == 0) expectingException = true;

        result = opd1.inv();
	   myResult = Rational(opd1.getDenominator(), opd1.getNumerator());
        if (!result.equals(myResult)) unopError("inv", opd1, result, myResult);

        if (expectingException)
            noExceptionError("inv", opd2, opd2.getNumerator(), opd2.getDenominator());

        expectingException = opd2.getNumerator() == 0;

        result = opd2.inv();
	   myResult = Rational(opd2.getDenominator(), opd2.getNumerator());
        if (!result.equals(myResult)) unopError("inv", opd2, result, myResult);

        if (expectingException)
            noExceptionError("inv", opd2, opd2.getNumerator(), opd2.getDenominator());

        expectingException = false;


    } catch (RationalException re) {
      if (!expectingException) exceptionError();
    }
}


void insertionCheck(const Rational &r) {
    ostringstream oss;
    oss << r;
    if (oss.str() != str(r)) {
        cerr << endl <<"****** Error !!!!! *****" << endl;
        cerr << "operator << produces incorrect result of '" << oss.str() << "' for the rational " << str(r) << endl;
        exit(1);
    }
}

string str(const Rational &r) {
    ostringstream oss;
    if (r.getDenominator() != 1)
	    oss << r.getNumerator() << "/" << r.getDenominator();
    else 
	    oss << r.getNumerator();
    return oss.str();
}

void normalizationCheck(const Rational &r, int num, int denom) {
    if (gcd(r.getNumerator(), r.getDenominator()) != 1) {
        cerr << endl <<"****** Error !!!!! *****" << endl;
        cerr << str(r) << " is not in normalized (simplest) form" << endl;
        exit(1);
    }
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void getError(const Rational &r, int num, int den) {
    cerr << endl <<"****** Error !!!!! *****" << endl;
    cerr << "Error in constructor or 'get' functions" << endl;
    cerr << "\t'getNumerator' returns: " << r.getNumerator() << endl;
    cerr << "\t'getDenominator' returns: " << r.getNumerator() << endl;
    cerr << "\tThe numerator used to construct the Rational is " << num << endl;
    cerr << "\tThe denominator used to construct the Rational is " << den << endl;
    exit(1);
}

void compOpError(Rational opd1,  Rational opd2,  int result, int correctResult) {
	cout << "\n****** Error !!!!! *****" << endl;
	cout << "Incorrect result for Rational.compareTo" << endl;
	cout << "\topd1: " << opd1 << endl;
	cout << "\topd2: " << opd2 << endl;
	cout << "\tyour result: " << result << endl;
	cout << "\tcorrect result: " << correctResult << endl;
	exit(1);
}

void equalsError(const Rational &opd1,  const Rational &opd2,  bool result, bool correctResult) {
	cout << "\n****** Error !!!!! *****" << endl;
	cout << "Incorrect result for Rational.equals" << endl;
	cout << "\topd1: " << opd1 << endl;
	cout << "\topd2: " << opd2 << endl;
	cout << "\tyour result: " << result << endl;
	cout << "\tcorrect result: " << correctResult << endl;
	exit(1);
}

void binopError(const string &theOperation, const Rational &opd1, const Rational &opd2, const Rational &result, const Rational &myResult) {
    cerr << endl <<"****** Error !!!!! *****" << endl;
    cerr << "Incorrect result for Rational::operator " << theOperation << endl;
    cerr << "\topd1          : " << str(opd1) << endl;
    cerr << "\topd2          : " << str(opd2) << endl;
    cerr << "\tyour result   : " << str(result) << endl;
    cerr << "\tcorrect result: " << str(myResult) << endl;
    exit(1);
}

void unopError(const string &theOperation, const Rational &opd, const Rational &result, const Rational &myResult) {
    cerr << endl <<"****** Error !!!!! *****" << endl;
    cerr << "Incorrect result for Rational::" << theOperation << endl;
    cerr << "\topd           : " << opd << endl;
    cerr << "\tyour result   : " << result << endl;
    cerr << "\tcorrect result: " << myResult << endl;
    exit(1);
}

void exceptionError() {
    cerr << endl <<"****** Error !!!!! *****" << endl;
    cerr << "You are throwing an exception when none should be thrown" << endl;
    exit(1);
}

void noExceptionError(string optr, const Rational &r, int num, int denom) {
    cerr << endl <<"****** Error !!!!! *****" << endl;
    cerr << "You are not throwing an exception when one should be thrown" << endl;
    cerr << "\tThe operation being performed was " << optr << endl;
    cerr << "\tThe offending Rational is " << str(r) << endl;
    cerr << "\tThe numerator used to construct the Rational is " << num << endl;
    cerr << "\tThe denominator used to construct the Rational is " << denom << endl;
    exit(1);
}
