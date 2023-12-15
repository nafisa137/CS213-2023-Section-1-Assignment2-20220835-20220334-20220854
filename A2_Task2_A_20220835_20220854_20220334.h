// Created by nofa on 11/5/2023.

#ifndef BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H
#define BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H

// File: bigreal.h
// Purpose: Task 2 bigreal numbers
// Author: Safa Tawfik, Nafisa Abdulrahman, Mariam Matar
// Section: S1, S2
// ID: 20220835, 20220854, 20220334

#include <iostream>
#include <deque>
#include <regex>

using namespace std;

class BigReal {
private:
    char sign;
    string integer, fraction;

public:
    BigReal() : sign('+'), integer("0"), fraction("0") {}
    BigReal(string real);

    bool operator>(const BigReal& newReal);
    bool operator<(const BigReal& newReal);
    bool operator==(const BigReal& newReal);
    BigReal operator-(const BigReal& newReal) const;
    BigReal operator+(const BigReal& newReal) const;

    friend ostream& operator<<(ostream& os, const BigReal& obj);
};

ostream& operator<<(ostream& os, const BigReal& obj) {
    os << obj.sign << obj.integer << "." << obj.fraction;
    return os;
}

BigReal::BigReal(string real) {
    if (regex_match(real, regex("[+-]?\\d*.?\\d+"))) {
        sign = (real[0] == '-') ? '-' : '+';
        integer = real.substr(1, real.find('.') - 1);
        fraction = real.substr(real.find('.') + 1);
    } else {
        sign = '+';
        integer = "0";
        fraction = ".0";
    }
}

bool BigReal::operator>(const BigReal& newReal) {
    if (sign == '+' && newReal.sign == '-') {
        return true;
    } else if (sign == '-' && newReal.sign == '+') {
        return false;
    }

    string temp1 = integer;
    string temp2 = newReal.integer;
    while (temp1.length() < temp2.length()) {
        temp1 = '0' + temp1;
    }
    while (temp2.length() < temp1.length()) {
        temp2 = '0' + temp2;
    }

    if ((temp1 > temp2) && sign == '+') {
        return true;
    } else if (temp1 < temp2 && sign == '-') {
        return true;
    }

    string frcTemp1 = fraction;
    string frcTemp2 = newReal.fraction;
    while (frcTemp1.length() < frcTemp2.length()) {
        frcTemp1 += '0';
    }
    while (frcTemp2.length() < frcTemp1.length()) {
        frcTemp2 += '0';
    }

    if (frcTemp1 > frcTemp2 && sign == '+') {
        return true;
    } else if (frcTemp1 < frcTemp2 && sign == '-' && temp1 == temp2) {
        return true;
    }

    return false;
}

bool BigReal::operator<(const BigReal& newReal) {
    if (sign == '+' && newReal.sign == '-') {
        return false;
    } else if (sign == '-' && newReal.sign == '+') {
        return true;
    }

    if (fraction == "0" && newReal.fraction == "0") {
        return false;
    }

    string temp1 = integer;
    string temp2 = newReal.integer;
    while (temp1.length() < temp2.length()) {
        temp1 = '0' + temp1;
    }
    while (temp2.length() < temp1.length()) {
        temp2 = '0' + temp2;
    }

    if (temp1 < temp2 && sign == '+') {
        return true;
    } else if (temp1 > temp2 && sign == '+') {
        return false;
    } else if (temp1 > temp2 && sign == '-') {
        return true;
    }

    string frcTemp1 = fraction;
    string frcTemp2 = newReal.fraction;
    while (frcTemp1.length() < frcTemp2.length()) {
        frcTemp1 += '0';
    }
    while (frcTemp2.length() < frcTemp1.length()) {
        frcTemp2 += '0';
    }

    if (frcTemp1 < frcTemp2 && sign == '+' && newReal.sign == '+' && temp1 == temp2) {
        return true;
    } else if (frcTemp1 > frcTemp2 && sign == '-' && newReal.sign == '-' && temp1 == temp2) {
        return true;
    }

    return false;
}

bool BigReal::operator==(const BigReal& newReal) {
    return (sign == newReal.sign && integer == newReal.integer && fraction == newReal.fraction);
}

BigReal BigReal::operator+(const BigReal &other) const {
    BigReal result;

    if (sign == other.sign) {
        // Both numbers have the same sign
        result.sign = sign;

        // Align decimal places
        int maxDecimalPlace = std::max(fraction.length(), other.fraction.length());
        std::string paddedIntegerPart = integer;
        std::string otherPaddedIntegerPart = other.integer;

        while (paddedIntegerPart.length() < maxDecimalPlace) {
            paddedIntegerPart = '0' + paddedIntegerPart;
        }

        while (otherPaddedIntegerPart.length() < maxDecimalPlace) {
            otherPaddedIntegerPart = '0' + otherPaddedIntegerPart;
        }

        // Add integer parts
        long long intSum = std::stoll(paddedIntegerPart) + std::stoll(otherPaddedIntegerPart);
        result.integer = std::to_string(intSum);

        // Add fraction parts
        std::string paddedFractionPart = fraction;
        std::string otherPaddedFractionPart = other.fraction;

        while (paddedFractionPart.length() < maxDecimalPlace) {
            paddedFractionPart += '0';
        }

        while (otherPaddedFractionPart.length() < maxDecimalPlace) {
            otherPaddedFractionPart += '0';
        }

        long long fracSum = std::stoll(paddedFractionPart) + std::stoll(otherPaddedFractionPart);

        // Adjust result based on carry in fraction part
        if (fracSum >= 10LL * maxDecimalPlace) {
            result.integer = std::to_string(intSum + 1);
            fracSum -= 10LL * maxDecimalPlace;
        }

        result.fraction = std::to_string(fracSum);
    } else {
        // Numbers have different signs
        // Implement subtraction by changing the sign of the second number and then adding
        BigReal temp = other;
        temp.sign = (temp.sign == '+') ? '-' : '+';
        result = *this + temp;
    }

    return result;
}

// Subtraction operator
BigReal BigReal::operator-(const BigReal& other) const {
    BigReal result;

    if (sign == other.sign) {
        // Both numbers have the same sign
        result.sign = sign;

        // Align decimal places
        int maxDecimalPlace = max(fraction.length(), other.fraction.length());
        string paddedIntegerPart = integer;
        string otherPaddedIntegerPart = other.integer;

        while (paddedIntegerPart.length() < maxDecimalPlace) {
            paddedIntegerPart = '0' + paddedIntegerPart;
        }

        while (otherPaddedIntegerPart.length() < maxDecimalPlace) {
            otherPaddedIntegerPart = '0' + otherPaddedIntegerPart;
        }

        // Subtract integer parts
        long long intDiff = stoll(paddedIntegerPart) - stoll(otherPaddedIntegerPart);
        result.integer = to_string(intDiff);

        // Subtract fraction parts
        string paddedFractionPart = fraction;
        string otherPaddedFractionPart = other.fraction;

        while (paddedFractionPart.length() < maxDecimalPlace) {
            paddedFractionPart += '0';
        }

        while (otherPaddedFractionPart.length() < maxDecimalPlace) {
            otherPaddedFractionPart += '0';
        }

        long long fracDiff = stoll(paddedFractionPart) - stoll(otherPaddedFractionPart);

        // Adjust result based on borrow in fraction part
        if (fracDiff < 0) {
            result.integer = to_string(intDiff - 1);
            fracDiff += 10LL * maxDecimalPlace;
        }

        result.fraction = to_string(fracDiff);
    } else {
        // Numbers have different signs
        // Implement addition by changing the sign of the second number and then adding
        BigReal temp = other;
        temp.sign = (temp.sign == '+') ? '-' : '+';
        result = *this + temp;
    }

    return result;
}
#endif //BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H
