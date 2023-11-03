#include <iostream>
#include <string>

using namespace std;

class BigReal {
private:
    char sign;
    string integer, fraction;

public:
    BigReal() : sign('+'), integer("0"), fraction("0") {}
    BigReal(string real) {
        sign = (real[0] == '-') ? '-' : '+';
        integer = real.substr(1, real.find('.') - 1);
        fraction = real.substr(real.find('.') + 1);
    }

    bool operator > (const BigReal& newReal);
    bool operator < (const BigReal& newReal);
    bool operator == (const BigReal& newReal);
    BigReal operator + (const BigReal& newReal);

    friend ostream& operator<<(ostream& os, const BigReal& obj);
    friend istream& operator>>(istream& is, BigReal& obj);
};

ostream& operator<<(ostream& os, const BigReal& obj) {
    os << obj.sign << obj.integer << "." << obj.fraction;
    return os;
}

BigReal BigReal::operator + (const BigReal& newReal) {
    BigReal result;
    char SignX = sign, SignY = newReal.sign;
    int carry = 0;
    string x = integer;
    string y = newReal.integer;

    while (x.length() < y.length()) {
        x = '0' + x;
    }
    while (y.length() < x.length()) {
        y = '0' + y;
    }

    if (SignX == SignY) {
        result.sign = SignY;
    } else {
        result.sign = SignX;
    }

    auto x1 = x.rbegin();
    auto y1 = y.rbegin();

    while (x1 != x.rend()) {
        int digit1 = *x1 - '0';
        int digit2 = *y1 - '0';

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        result.integer = char((sum % 10) + '0') + result.integer;

        ++x1;
        ++y1;
    }

    if (carry > 0) {
        result.integer = char(carry + '0') + result.integer;
    }

    return result;
}

int main() {
    BigReal a ( "02615610.58");
    BigReal b( "-054510.58");

    BigReal result = a + b;

    cout << "Result: " << result << endl;
    return 0;
}
