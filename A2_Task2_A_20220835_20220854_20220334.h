//
// Created by nofa on 11/5/2023.
//

#ifndef BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H
#define BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H
//file:
//purpose: Task 2 bigreal numbers
//Author: Safa Tawfik, nafisa Abdulrahman, mariam matar
//section: s1, s2
//ID: 20220835, 20220854, 20220334
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
    BigReal(string real) {
        if (regex_match(real,regex("[+-]?\\d*.?\\d+"))){// before we do any operations on the number that
            // the user entered, we should check first whether
            // it was a valid number or not, and to check we will use
            // this function regex to check if  the input number
            // has one sign (+ or -) or more .. and check also if it
            // had one dot or more, this step is essential to determine
            // the validation of the number


            sign = (real[0] == '-') ? +'-' : '+';
            integer = real.substr(1, real.find('.') - 1);// if and only if the number is valid, we will start to store its sign,
            // integer part of it and the fraction part, and this will help us
            // later when we do operations of add and subtraction and even when
            // printing the final result itself
            fraction = real.substr(real.find('.') + 1);
        }
        else{// otherwise we will give the number the value 0.0
            sign = '+';
            integer = "0";
            fraction = ".0";
        }
    }
    bool operator > (const BigReal& newReal);
    bool operator < (const BigReal& newReal);
    bool operator == (const BigReal& newReal);
    BigReal operator - (const BigReal& newReal);
    BigReal operator + (const BigReal& newReal);


    friend ostream& operator<<(ostream& os, const BigReal& obj);
};


ostream& operator<<(ostream& os, const BigReal& obj) {
    os << obj.sign << obj.integer << "." << obj.fraction;
    return os;
}



bool BigReal:: operator > (const BigReal& newReal) {

    //check if the frist number  if + and second numder is -  then return true 

    if (sign == '+' && newReal.sign == '-') {
        return true;
    }
    //check if the frist number  if - and second numder is +  then return false 
    else if (sign == '-' && newReal.sign == '+') {
        return false;
    }
  
    //cheke if the 2 numbers are differnt in size in integer part I will add zero frome the left of the smallest number to make the 2 number in same size

    string temp1 = integer;
    string temp2 = newReal.integer;
    while (temp1.length() < temp2.length()) {
        temp1 = '0' + temp1;
    }
    while (temp2.length() < temp1.length()) {
        temp2 = '0' + temp2;
    }
   
        if ((temp1 > temp2) && sign=='+') {
            return true;

        }

        else if (temp1 < temp2 && sign == '-') {
            return  true;
        }



    //check cheke if the 2 numbers are differnt in size in fraction part I will add zero frome the right of the smallest number to make the 2 number in same size 




    string frcTemp1 = fraction;
    string frcTemp2 = newReal.fraction;
    while (frcTemp1.length() < frcTemp2.length()) {
        frcTemp1 += '0';
    }
    while (frcTemp2.length() < frcTemp1.length()) {
        frcTemp2 += '0';
    }
    //compre the fraction part to find the bigger number
    if (frcTemp1 > frcTemp2 && sign == '+' && newReal.sign == '+') {

        return true;
    }
    else if (frcTemp1 < frcTemp2 && sign == '-' && newReal.sign == '-' && temp1 == temp2) {
        return  true;
    }

    else  {
        return false;
    }



  
}


bool BigReal:: operator < (const BigReal& newReal) {
    //check if the frist number  if + and second numder is -  then return false 
    if (sign == '+' && newReal.sign == '-') {
        return false;
    }
    //check if the frist number  if - and second numder is +  then return true 
    else if (sign == '-' && newReal.sign == '+') {
        return true;
    }

    if (fraction == "0" && newReal.fraction == "0")
        return false;

   
    //cheke if the 2 numbers are differnt in size in integer part I will add zero frome the left of the smallest number to make the 2 number in same size
   
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
    }
    
   else if (temp1 > temp2&&sign=='+') {
        return  false;
    }
    else if (temp1 >temp2 && sign == '-') {
        return  true;
    }
  
    //cheke if the 2 numbers are differnt in size in fraction part I will add zero frome the right of the smallest number to make the 2 number in same size

    string frcTemp1 = fraction;
    string frcTemp2 = newReal.fraction;
    while (frcTemp1.length() < frcTemp2.length()) {
        frcTemp1 += '0';
    }
    while (frcTemp2.length() < frcTemp1.length()) {
        frcTemp2 += '0';
    }

    if (frcTemp1 < frcTemp2&& sign=='+'&& newReal.sign=='+'&&temp1==temp2) {
        return true;
    }
    else if(frcTemp1 > frcTemp2 && sign == '-' && newReal.sign == '-' && temp1 == temp2) {
      return  true;
    }
    else {
        return false;
    }
 
}
bool BigReal:: operator == (const BigReal& newReal) {
    //check if the sign and two number is equal

    if (sign == newReal.sign && integer == newReal.integer&& fraction==newReal.fraction)
    {
        return true;

    }
    else
    {
        return false;
    }

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


#endif //BIGREAL_A2_TASK2_A_20220835_20220854_20220334_H
