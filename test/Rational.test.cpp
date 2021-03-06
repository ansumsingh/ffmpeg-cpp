#include "common.hpp"
#include "Rational.h"

#include <cmath>
#include <limits>
#include <catch2/catch.hpp>

namespace{
    auto commonRational = [] () -> ffmpegcpp::Rational {
        return ffmpegcpp::Rational{ffmpegcpp::unittests::commonNumerator, ffmpegcpp::unittests::commonDenominator};
    };
}
namespace ffmpegcpp::unittests{

    TEST_CASE("Rational()")
    {
        SECTION("Rational(int, int)")
        {
            using namespace ffmpegcpp;
            auto [numerator, denominator, rational] = GENERATE(
                std::tuple{1, 1, Rational{}},
                std::tuple{-1, 1, Rational{-1, 1}},
                std::tuple{2, 1, Rational{2, 1}},
                std::tuple{-2, 1, Rational{-2, 1}},
                std::tuple{1, 2, Rational{1, 2}},
                std::tuple{-1, 2, Rational{-1, 2}},
                std::tuple{2, 2, Rational{2, 2}},
                std::tuple{-2, 2, Rational{-2, 2}}
            );

            REQUIRE(rational.numerator() == numerator);
            REQUIRE(rational.denominator() == denominator);
        }

        SECTION("Rational(const Rational&)")
        {
            using namespace ffmpegcpp;
            auto rational = GENERATE( Rational{2,1}, Rational{2,3} );
            auto rationalCopy = rational;

            REQUIRE(rational.numerator() == rationalCopy.numerator());
            REQUIRE(rational.denominator() == rationalCopy.denominator());
        }

        SECTION("Rational(Rational&&)")
        {
            using namespace ffmpegcpp;
            auto rationalMoveCopy = commonRational();

            REQUIRE(rationalMoveCopy.numerator() == commonNumerator);
            REQUIRE(rationalMoveCopy.denominator() == commonDenominator);
        }
    }

    TEST_CASE("Rational::operator=()")
    {
        SECTION("operator=(const Rational&)")
        {
            using namespace ffmpegcpp;
            auto rational =  GENERATE( Rational{2,1}, Rational{2,3} );
            auto rationalCopy = Rational{commonNumerator, commonDenominator};

            REQUIRE(rationalCopy.numerator() == commonNumerator);
            REQUIRE(rationalCopy.denominator() == commonDenominator);

            rationalCopy = rational;
            
            REQUIRE(rational.numerator() == rationalCopy.numerator());
            REQUIRE(rational.denominator() == rationalCopy.denominator());
        }

        SECTION("operator=(Rational&&)")
        {
            using namespace ffmpegcpp;
            auto rationalCopy = Rational{commonNumerator, commonDenominator};

            REQUIRE(rationalCopy.numerator() == commonNumerator);
            REQUIRE(rationalCopy.denominator() == commonDenominator);

            rationalCopy = [] () { 
                return Rational{2, 3};
                }();

            REQUIRE(rationalCopy.numerator() == 2);
            REQUIRE(rationalCopy.denominator() == 3);
        }
    }

    TEST_CASE("toDouble()")
    {
        using namespace ffmpegcpp;
        auto [expected, rational] = GENERATE(
            std::pair{1.0, Rational{}},
            std::pair{0.0, Rational{0, 1}},
            std::pair{0.0, Rational{0, 2}},
            std::pair{0.0, Rational{0, 4}},
            std::pair{0.5, Rational{1, 2}},
            std::pair{0.5, Rational{2, 4}},
            std::pair{0.5, Rational{3, 6}},
            std::pair{std::numeric_limits<double>::infinity(), Rational{1, 0}},
            std::pair{-std::numeric_limits<double>::infinity(), Rational{-1, 0}}
        );

        REQUIRE(rational.toDouble() == expected);

        SECTION("toDouble() => NaN")
        {
            auto rational = Rational(0,0);

            REQUIRE(std::isnan(rational.toDouble()));
        }
    }

    TEST_CASE("operator==(..., ...) && operator!=(..., ...)")
    {
        using namespace ffmpegcpp;
        SECTION("RationalA == RationalB")
        {
            auto [rationalA, rationalB] = GENERATE(
                std::pair{Rational{}, Rational{2, 2}},
                std::pair{Rational{0, 1}, Rational{0, 3}},
                std::pair{Rational{1, 2}, Rational{2, 4}},
                std::pair{Rational{2, 4}, Rational{3, 6}}
                );
            
            REQUIRE(rationalA == rationalB);
            REQUIRE_FALSE(rationalA != rationalB);
        }

        SECTION("RationalA != RationalB)")
        {
            auto [rationalA, rationalB] = GENERATE(
                std::pair{Rational{}, Rational{1, 2}},
                std::pair{Rational{0, 1}, Rational{1, 1}},
                std::pair{Rational{1, 2}, Rational{2, 5}},
                std::pair{Rational{2, 4}, Rational{3, 7}}
                );
            
            REQUIRE_FALSE(rationalA == rationalB);
            REQUIRE(rationalA != rationalB);
        }
    }
    
    TEST_CASE("operator<(..., ...), operator>(..., ...), operator>=(..., ...)")
    {
        using namespace ffmpegcpp;
        SECTION("A < B")
        {
            auto [rationalA, rationalB] = GENERATE(
                std::pair{Rational{}, Rational{2, 1}},
                std::pair{Rational{0, 1}, Rational{1, 3}},
                std::pair{Rational{1, 2}, Rational{3, 4}},
                std::pair{Rational{2, 4}, Rational{3, 5}}
                );
            
            REQUIRE(rationalA < rationalB);
            REQUIRE(rationalB > rationalA);
            REQUIRE_FALSE(rationalA > rationalB);
            REQUIRE_FALSE(rationalA >= rationalB);
        }

        SECTION("A <= B")
        {
            auto [rationalA, rationalB] = GENERATE(
                std::pair{Rational{}, Rational{2, 1}},
                std::pair{Rational{0, 1}, Rational{1, 3}},
                std::pair{Rational{1, 2}, Rational{3, 4}},
                std::pair{Rational{2, 4}, Rational{1, 2}}
                );
            
            REQUIRE(rationalA <= rationalB);
            REQUIRE(rationalB >= rationalA);
            REQUIRE_FALSE(rationalA > rationalB);
        }
    }

    TEST_CASE("operator+(lhs, rhs)&& operator+=(..)")
    {
        auto [expected, lhs, rhs] = GENERATE(
                std::tuple{Rational{3, 1}, Rational{}, Rational{2, 1}},
                std::tuple{Rational{1, 3}, Rational{0, 1}, Rational{1, 3}},
                std::tuple{Rational{5, 4}, Rational{1, 2}, Rational{3, 4}},
                std::tuple{Rational{1, 1}, Rational{2, 4}, Rational{1, 2}},
                std::tuple{Rational{0, 1}, Rational{2, 4}, Rational{-1, 2}}
                );
        auto result = lhs + rhs;

        REQUIRE(result.numerator() == expected.numerator());
        REQUIRE(result.denominator() == expected.denominator());

        lhs += rhs;

        REQUIRE(lhs.numerator() == expected.numerator());
        REQUIRE(lhs.denominator() == expected.denominator());
    }

    TEST_CASE("operator-(lhs, rhs) && operator-=(...)")
    {
        auto [expected, lhs, rhs] = GENERATE(
                std::tuple{Rational{-1, 1}, Rational{}, Rational{2, 1}},
                std::tuple{Rational{-1, 3}, Rational{0, 1}, Rational{1, 3}},
                std::tuple{Rational{-1, 4}, Rational{1, 2}, Rational{3, 4}},
                std::tuple{Rational{0, 1}, Rational{2, 4}, Rational{1, 2}},
                std::tuple{Rational{1, 1}, Rational{2, 4}, Rational{-1, 2}}
                );
        auto result = lhs - rhs;

        REQUIRE(result.numerator() == expected.numerator());
        REQUIRE(result.denominator() == expected.denominator());

        lhs -= rhs;

        REQUIRE(lhs.numerator() == expected.numerator());
        REQUIRE(lhs.denominator() == expected.denominator());
    }

    TEST_CASE("operator*(lhs, rhs)")
    {
        auto [expected, lhs, rhs] = GENERATE(
                std::tuple{Rational{2, 1}, Rational{}, Rational{2, 1}},
                std::tuple{Rational{0, 1}, Rational{0, 1}, Rational{1, 3}},
                std::tuple{Rational{3, 8}, Rational{1, 2}, Rational{3, 4}},
                std::tuple{Rational{1, 4}, Rational{2, 4}, Rational{1, 2}},
                std::tuple{Rational{-1, 4}, Rational{2, 4}, Rational{-1, 2}}
                );
        auto result = lhs * rhs;

        REQUIRE(result.numerator() == expected.numerator());
        REQUIRE(result.denominator() == expected.denominator());

        lhs *= rhs;

        REQUIRE(lhs.numerator() == expected.numerator());
        REQUIRE(lhs.denominator() == expected.denominator());
    }

    TEST_CASE("operator/(lhs, rhs)")
    {
        auto [expected, lhs, rhs] = GENERATE(
                std::tuple{Rational{1, 2}, Rational{}, Rational{2, 1}},
                std::tuple{Rational{0, 1}, Rational{0, 1}, Rational{1, 3}},
                std::tuple{Rational{2, 3}, Rational{1, 2}, Rational{3, 4}},
                std::tuple{Rational{1, 1}, Rational{2, 4}, Rational{1, 2}},
                std::tuple{Rational{-1, 1}, Rational{2, 4}, Rational{-1, 2}}
                );
        auto result = lhs / rhs;

        REQUIRE(result.numerator() == expected.numerator());
        REQUIRE(result.denominator() == expected.denominator());

        lhs /= rhs;

        REQUIRE(lhs.numerator() == expected.numerator());
        REQUIRE(lhs.denominator() == expected.denominator());
    }
}