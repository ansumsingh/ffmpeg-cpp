#pragma once
#include "ffmpeg.h"
#include <memory>

namespace ffmpegcpp{

/// This is a wrapper class internal AVRational 
class Rational{
    public:
        explicit Rational(int numerator=1, int denominator =1);

        Rational(const AVRational& other);
        Rational(const Rational& other);
        Rational(Rational&& other);
        Rational& operator =(const Rational& other);
        Rational& operator =(Rational&& other);
        Rational& operator =(const AVRational& other);

        int numerator() const;
        int denominator() const;

        double toDouble() const;

        /// Arithematic operators
        Rational& operator+=(const Rational& rhs);
        Rational& operator-=(const Rational& rhs);
        Rational& operator*=(const Rational& rhs);
        Rational& operator/=(const Rational& rhs);

        friend Rational operator+(const Rational& lhs, const Rational& rhs);
        friend Rational operator-(const Rational& lhs, const Rational& rhs);
        friend Rational operator*(const Rational& lhs, const Rational& rhs);
        friend Rational operator/(const Rational& lhs, const Rational& rhs);

        // Comparison Operators
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator!=(const Rational& lhs, const Rational& rhs);
        friend bool operator>(const Rational& lhs, const Rational& rhs);
        friend bool operator>=(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
        friend bool operator<=(const Rational& lhs, const Rational& rhs);

    
    private:
        std::unique_ptr<AVRational> data_;
};
}