#pragma once


template<typname T>
class ComplexNumber {
public:
    ComplexNumber<T>(T real, T imaginary);

    ComplexNumber<T>(ComplexNumber<T>& number);

    ComplexNumber<T> operator+(ComplexNumber<T>& other);

    template<typename T>
    friend ComplexNumber<T> operator+(ComplexNumber<T>& left, T right);

    template<typename T>
    friend ComplexNumber<T> operator+(T left, ComplexNumber<T>& right);

    ComplexNumber<T> operator-(ComplexNumber<T>& other);

    template<typename T>
    friend ComplexNumber<T> operator-(ComplexNumber<T>& left, T right);

    template<typename T>
    friend ComplexNumber<T> operator-(T left, ComplexNumber<T>& right);

    // multiply
    ComplexNumber<T> operator*(ComplexNumber<T>& other);

    template<typename T>
    friend ComplexNumber<T> operator*(ComplexNumber<T>& left, T right);

    template<typename T>
    friend ComplexNumber<T> operator*(T left, ComplexNumber<T>& right);

private:
    T m_imaginary;
    T m_real;
}


template<typename T>
ComplexNumber<T>::ComplexNumber<T>(T real=0, T imaginary=0): m_real(real), m_imaginary(imaginary) {}

template<typename T>
ComplexNumber<T>::ComplexNumber<T>(ComplexNumber<T>& number): m_real(number.m_real), m_imaginary(number.m_imaginary) {}

template<typename T>
ComplexNumber<T> ComplexNumber<T>::operator+(ComplexNumber<T>& other) {
    return ComplexNumber<T>(m_real + other.m_real, m_imaginary + other.m_imaginary);
}

template<typename T>
ComplexNumber<T> ComplexNumber<T>::operator-(ComplexNumber<T>& other) {
    return ComplexNumber<T>(m_real - other.m_real, m_imaginary - other.m_imaginary);
}

ComplexNumber<T> ComplexNumber<T>::operator*(ComplexNumber<T>& other) {
    return ComplexNumber<T>(m_real*other.m_real - m_imaginary*other.m_imaginary, m_real*other.m_imaginary + other.m_real*m_imaginary);
}

template<typename T>
friend ComplexNumber<T> operator*(ComplexNumber<T>& left, T right) {
    return ComplexNumber<T>(left.m_real * right, left.m_imaginary * right);

template<typename T>
friend ComplexNumber<T> operator*(T left, ComplexNumber<T>& right) {
    return ComplexNumber<T>(right.m_real * left, right.m_imaginary * left);
}


