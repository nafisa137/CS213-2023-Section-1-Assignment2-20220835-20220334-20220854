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
    BigReal operator - (const BigReal& newReal);
    friend ostream& operator<<(ostream& os, const BigReal& obj);
};
ostream& operator<<(ostream& os, const BigReal& obj) {
    os << obj.sign << obj.integer << "." << obj.fraction;
    return os;
}
BigReal BigReal::operator - (const BigReal& newReal) {
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

    long double x2 = stold(x);
    long double y2 = stold(y);

    if (x2 == y2) {
        result.sign = '+';
        result.integer = "0";
        result.fraction = "0";
        return result;
    } else if (x2 < y2) {
        result.sign = (SignX == '+') ? '-' : '+';
        swap(x, y);
    } else {
        result.sign = SignX;
    }

    auto x1 = x.rbegin();
    auto y1 = y.rbegin();

    while (x1 != x.rend()) {
        int digit1 = *x1 - '0';
        int digit2 = *y1 - '0';

        int diff = digit1 - digit2 - carry;
        if (diff < 0) {
            carry = 1;
            diff += 10;
        } else {
            carry = 0;
        }

        result.integer = char(diff + '0') + result.integer;

        ++x1;
        ++y1;
    }

    // Remove leading zeros from the result
    while (result.integer.length() > 1 && result.integer[0] == '0') {
        result.integer.erase(0, 1);
    }

    return result;
}

int main() {
    BigReal a("8562.51");
    BigReal b("54515.55");

    BigReal result = a - b;

    cout << "Result: " << result << endl;
    return 0;
}
