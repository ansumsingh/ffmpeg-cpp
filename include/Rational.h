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

        // Comparator operators
        friend bool operator==(const Rational& input1, const Rational& input2);
        friend bool operator!=(const Rational& input1, const Rational& input2);
    
    private:
        std::unique_ptr<AVRational> data_;
};
}