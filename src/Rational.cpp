#include "Rational.h"
#include "ffmpeg.h"

ffmpegcpp::Rational::Rational(int numerator, int denominator): data_{std::make_unique<AVRational>()}
{
    data_->num = numerator;
    data_->den = denominator;
};

ffmpegcpp::Rational::Rational(const Rational& other): data_{std::make_unique<AVRational>()}
{    
    data_->num = other.data_->num;
    data_->den = other.data_->den;
}

ffmpegcpp::Rational::Rational(Rational&& other): data_{std::move(other.data_)}{}

ffmpegcpp::Rational& ffmpegcpp::Rational::operator=(const Rational& other)
{
    data_->num = other.data_->num;
    data_->den = other.data_->den;
    return *this;
}

ffmpegcpp::Rational& ffmpegcpp::Rational::operator=(Rational&& other)
{
    if(data_ != other.data_)
        {
            data_.reset();
            data_ = std::move(other.data_);
        }
    return *this;
}

int ffmpegcpp::Rational::numerator() const 
{
    return data_->num;
}

int ffmpegcpp::Rational::denominator() const 
{
    return data_->den;
}

double ffmpegcpp::Rational::toDouble() const
{
    return av_q2d(*data_);
}

/// Returns true if lhs == rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator==(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return av_cmp_q(*lhs.data_, *rhs.data_) == 0;
}

/// Returns true if lhs != rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator!=(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return !(lhs == rhs);
}

/// Return true if lhs > rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator>(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return av_cmp_q(*lhs.data_, *rhs.data_) > 0;
}

/// Return true if lhs <= rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator<=(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return !(lhs > rhs);
}

/// Return true if lhs < rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator<(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return av_cmp_q(*lhs.data_, *rhs.data_) < 0;
}

/// Return true if lhs >= rhs. Behaviour is undefined if one of the input is 0/0.
bool ffmpegcpp::operator>=(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    return !(lhs < rhs);
}

/// Returns lhs + rhs.
ffmpegcpp::Rational ffmpegcpp::operator+(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    auto rational = av_add_q(*lhs.data_, *rhs.data_);
    return Rational{rational.num, rational.den};
}

/// Returns lhs - rhs.
ffmpegcpp::Rational ffmpegcpp::operator-(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    auto rational = av_sub_q(*lhs.data_, *rhs.data_);
    return Rational{rational.num, rational.den};
}

/// Returns lhs x rhs.
ffmpegcpp::Rational ffmpegcpp::operator*(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    auto rational = av_mul_q(*lhs.data_, *rhs.data_);
    return Rational{rational.num, rational.den};
}

/// Returns lhs / rhs.
ffmpegcpp::Rational ffmpegcpp::operator/(const ffmpegcpp::Rational& lhs, const ffmpegcpp::Rational& rhs)
{
    auto rational = av_div_q(*lhs.data_, *rhs.data_);
    return Rational{rational.num, rational.den};
}

