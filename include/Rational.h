#pragma once
#include "ffmpeg.h"
#include <memory>

namespace ffmpegcpp{

/// This is a wrapper class internal AVRational 
class Rational{
    public:
        explicit Rational(int numerator=1, int denominator =1);

        Rational(const Rational& other);
        Rational(Rational&& other);
        Rational& operator =(const Rational& other);
        Rational& operator =(Rational&& other);

        int numerator() const;
        int denominator() const;

        double toDouble() const;

        // Comparison Operators
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator!=(const Rational& lhs, const Rational& rhs);
        friend bool operator>(const Rational& lhs, const Rational& rhs);
        friend bool operator>=(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);
        friend bool operator<=(const Rational& lhs, const Rational& rhs);

        /// Arithematic operators
        friend Rational operator+(const Rational& lhs, const Rational& rhs);
        friend Rational operator-(const Rational& lhs, const Rational& rhs);
        friend Rational operator*(const Rational& lhs, const Rational& rhs);
        friend Rational operator/(const Rational& lhs, const Rational& rhs);
    
    private:
        std::unique_ptr<AVRational> data_;
};
}