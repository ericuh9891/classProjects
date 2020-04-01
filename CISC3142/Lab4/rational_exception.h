#ifndef RATIONAL_EXCEPTION
#define RATIONAL_EXCEPTION

#include <string>

using namespace std;

class RationalException {
public:
    RationalException(string what) : what(what) {}
    string getWhat() {return what;}
private:
    string what;
};

#endif
