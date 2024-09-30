#include "ComplexNumber.h"


ComplexNumber::ComplexNumber(int real, int imaginary): m_real(real), m_imaginary(imaginary) {}


ComplexNumber::ComplexNumber(const ComplexNumber& number): m_real(number.m_real), m_imaginary(number.m_imaginary) {}


ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) {
    return ComplexNumber(m_real + other.m_real, m_imaginary + other.m_imaginary);
}


ComplexNumber operator+(ComplexNumber& left, int right) {
    return ComplexNumber(left.m_real+right, left.m_imaginary);
}


ComplexNumber operator+(int left, ComplexNumber& right) {
    return ComplexNumber(right.m_real+left, right.m_imaginary);
}


ComplexNumber ComplexNumber::operator-(ComplexNumber& other) {
    return ComplexNumber(m_real - other.m_real, m_imaginary - other.m_imaginary);
}

ComplexNumber operator-(ComplexNumber& left, int right) {
    return ComplexNumber(left.m_real+right, left.m_imaginary);
}


ComplexNumber operator-(int left, ComplexNumber& right) {
    return ComplexNumber(left - right.m_real, -right.m_imaginary);
}


ComplexNumber ComplexNumber::operator*(ComplexNumber& other) {
    return ComplexNumber(m_real*other.m_real - m_imaginary*other.m_imaginary, m_real*other.m_imaginary + other.m_real*m_imaginary);
}

ComplexNumber operator*(ComplexNumber& left, int right) {
    return ComplexNumber(left.m_real * right, left.m_imaginary * right);
}

ComplexNumber operator*(int left, ComplexNumber& right) {
    return ComplexNumber(right.m_real * left, right.m_imaginary * left);
}

bool ComplexNumber::operator>(ComplexNumber& other) {
    return this->abs() > other.abs();
}

bool ComplexNumber::operator<(ComplexNumber& other) {
    return this->abs() < other.abs();
}
 
bool ComplexNumber::operator>=(ComplexNumber& other) {
    return this->abs() >= other.abs();
}
 
bool ComplexNumber::operator==(ComplexNumber& other) {
    return this->abs() == other.abs();
}


int ComplexNumber::abs() {
    return std::sqrt(std::pow(m_real, 2) + std::pow(m_imaginary, 2));
}

std::ostream& operator<<(
    std::ostream &out, const ComplexNumber &number) {
    return out << number.m_real << " + " << number.m_imaginary << "i";
}

