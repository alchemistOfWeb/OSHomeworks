#pragma once
#include <cmath>
#include <iostream>


class ComplexNumber {
public:
    ComplexNumber(int real=0, int imaginary=0);

    ComplexNumber(const ComplexNumber& number);

    ComplexNumber operator+(const ComplexNumber& other);

    friend ComplexNumber operator+(ComplexNumber& left, int right);

    friend ComplexNumber operator+(int left, ComplexNumber& right);

    ComplexNumber operator-(ComplexNumber& other);

    friend ComplexNumber operator-(ComplexNumber& left, int right);

    friend ComplexNumber operator-(int left, ComplexNumber& right);

    // multiply
    ComplexNumber operator*(ComplexNumber& other);

    friend ComplexNumber operator*(ComplexNumber& left, int right);

    friend ComplexNumber operator*(int left, ComplexNumber& right);
    
    bool operator>(ComplexNumber& other);

    bool operator<(ComplexNumber& other); 
 
    bool operator>=(ComplexNumber& other);
 
    bool operator==(ComplexNumber& other);

    int abs();
    
    friend std::ostream& operator<<(
        std::ostream &out, const ComplexNumber &number);

private:
    int m_imaginary;
    int m_real;
};

