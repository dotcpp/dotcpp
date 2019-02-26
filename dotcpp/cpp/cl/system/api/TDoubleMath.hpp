/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef cl_system_api_TDoubleMath_hpp
#define cl_system_api_TDoubleMath_hpp

#include <cl/system/TDouble.hpp>
#include <complex>

//!!! Math in AD mode, in progress
namespace cl
{
    inline void throw_(char const* what)
    {
        throw std::exception(what);
    }
}

namespace std
{
    inline cl::TDouble fabs(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::fabs(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fabs(x.value());
#endif
    }

    inline cl::TDouble abs(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::abs(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::abs(x.value());
#endif
    }

    inline cl::TDouble floor(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return  cl::TDouble(std::floor(CppAD::Value(x.value())));  //!!! Review
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::floor(x.value());
#endif
    }

    inline cl::TDouble ceil(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return cl::TDouble(std::ceil(CppAD::Value(x.value())));  //!!! Review
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::ceil(x.value());
#endif
    }

    inline cl::TDouble sqrt(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sqrt(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sqrt(x.value());
#endif
    }

    inline cl::TDouble log(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::log(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::log(x.value());
#endif
    }

    inline cl::TDouble exp(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::exp(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::exp(x.value());
#endif
    }

    inline cl::TDouble sin(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sin(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sin(x.value());
#endif
    }

    inline cl::TDouble cos(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::cos(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::cos(x.value());
#endif
    }

    inline cl::TDouble tan(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::tan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::tan(x.value());
#endif
    }

    inline cl::TDouble asin(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::asin(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::asin(x.value());
#endif
    }

    inline cl::TDouble acos(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::acos(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::acos(x.value());
#endif
    }

    inline cl::TDouble atan(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::atan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan(x.value());
#endif
    }

    inline cl::TDouble sinh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sinh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sinh(x.value());
#endif
    }

    inline cl::TDouble cosh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::cosh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::cosh(x.value());
#endif
    }

    inline cl::TDouble tanh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::tanh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::tanh(x.value());
#endif
    }

    inline cl::TDouble pow(cl::TDouble x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::pow(x.value(), y.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x.value(), y.value());
#endif
    }

    inline cl::TDouble pow(cl::TDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return pow(x, cl::TDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x.value(), y);
#endif
    }

    inline cl::TDouble pow(double x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return pow(cl::TDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x, y.value());
#endif
    }

    inline cl::TDouble asinh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return log(x + sqrt(cl::TDouble(1.0) + pow(x, 2.0)));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented");return x;
#else
        return std::asinh(x.value());
#endif
    }

    inline cl::TDouble acosh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return log(x + sqrt(cl::TDouble(-1.0) + pow(x, 2.0)));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::acosh(x.value());
#endif
    }

    inline cl::TDouble atanh(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return 0.5* log((cl::TDouble(1.0) + x) / (cl::TDouble(1.0) - x));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atanh(x.value());
#endif
    }

    inline bool isnan(cl::TDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::isnan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::isnan(x.value());
#endif
    }


    inline cl::TDouble min(cl::TDouble x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::min(x.value(),y.value());
#endif
    }

    inline cl::TDouble min(cl::TDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::min(x.value(), y);
#endif
    }

    inline cl::TDouble min(double x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented");return x;
#else
        return std::min(x, y.value());
#endif
    }

    inline cl::TDouble max(cl::TDouble x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::max(x.value(), y.value());
#endif
    }

    inline cl::TDouble max(cl::TDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? x : cl::TDouble(y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::max(x.value(), y);
#endif
    }

    inline cl::TDouble max(double x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? cl::TDouble(x) : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::max(x, y.value());
#endif
    }

    inline cl::TDouble atan2(cl::TDouble x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::atan2(x.value(), y.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x.value(), y.value());
#endif
    }

    inline cl::TDouble atan2(cl::TDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return atan2(x, cl::TDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x.value(), y);
#endif
    }

    inline cl::TDouble atan2(double x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return atan2(cl::TDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x, y.value());
#endif
    }

    inline cl::TDouble fmod(cl::TDouble x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x - y * ( x / y > 0 ? floor(x / y) : ceil (x / y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fmod(x.value(), y.value());
#endif
    }

    inline cl::TDouble fmod(cl::TDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return fmod(x, cl::TDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fmod(x.value(), y);
#endif
    }

    inline cl::TDouble fmod(double x, cl::TDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return fmod(cl::TDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fmod(x, y.value());
#endif
    }

    inline cl::TDouble modf(cl::TDouble x, cl::TDouble* iptr)
    {
#ifdef CL_DOUBLE_CPPAD
        double fractpart;
        double intpart;
        fractpart = std::modf(CppAD::Value(x.value()), &intpart);     //!!! Review
        (*iptr) = cl::TDouble(intpart);
        return cl::TDouble( fractpart);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        double fractpart;
        double intpart;
        fractpart = std::modf(x.value(), &intpart);
        (*iptr) = intpart;
        return cl::TDouble( fractpart);
#endif
    }

//!! Do we need this define if TDouble is always a class?
#if defined(CL_DOUBLE_NOAD) || defined(CL_DOUBLE_CPPAD) || defined(CL_DOUBLE_ADOLC)
    template<class T1, class T2>
    inline cl::TDouble inner_product(T1 first1, T1 last1, T2 first2, double value)
    {
        cl::TDouble prod(value);
        while (first1 != last1)
        {
            prod += (*first1) * (*first2);
            ++first1; ++first2;
        }
        return prod;
    }
#endif

    // Arithmetics for std::complex<cl::TDouble> and cl::TDouble

    inline std::complex<cl::TDouble> operator+(const std::complex<cl::TDouble>& lhs, cl::TDouble rhs){
        return complex<cl::TDouble>(lhs.real() + rhs, lhs.imag());
    }

    inline std::complex<cl::TDouble> operator-(const std::complex<cl::TDouble>& lhs, cl::TDouble rhs){
        return complex<cl::TDouble>(lhs.real() - rhs, lhs.imag());
    }

    inline std::complex<cl::TDouble> operator*(const std::complex<cl::TDouble>& lhs, cl::TDouble rhs){
        return complex<cl::TDouble>(lhs.real() *rhs, lhs.imag()*rhs);
    }

    inline std::complex<cl::TDouble> operator/(const std::complex<cl::TDouble>& lhs, cl::TDouble rhs){
        return complex<cl::TDouble>(lhs.real() / rhs, lhs.imag() / rhs);
    }

    inline std::complex<cl::TDouble> operator+(cl::TDouble lhs, const std::complex<cl::TDouble>& rhs){
        return complex<cl::TDouble>(lhs + rhs.real(), rhs.imag());
    }

    inline std::complex<cl::TDouble> operator-(cl::TDouble lhs, const std::complex<cl::TDouble>& rhs){
        return complex<cl::TDouble>(lhs - rhs.real(), -rhs.imag());
    }

    inline std::complex<cl::TDouble> operator*(cl::TDouble lhs, const std::complex<cl::TDouble>& rhs){
        return complex<cl::TDouble>(rhs.real() *lhs, rhs.imag()*lhs);
    }

    inline std::complex<cl::TDouble> operator/(cl::TDouble lhs, const std::complex<cl::TDouble>& rhs){
        return std::complex<cl::TDouble>(lhs) / rhs;
    }

    // Arithmetics for std::complex<cl::TDouble> and double

    inline std::complex<cl::TDouble> operator+(const std::complex<cl::TDouble>& lhs, double rhs) { return lhs + cl::TDouble(rhs); }

    inline std::complex<cl::TDouble> operator-(const std::complex<cl::TDouble>& lhs, double rhs) { return lhs - cl::TDouble(rhs); }

    inline std::complex<cl::TDouble> operator*(const std::complex<cl::TDouble>& lhs, double rhs) { return lhs * cl::TDouble(rhs); }

    inline std::complex<cl::TDouble> operator/(const std::complex<cl::TDouble>& lhs, double rhs) { return lhs / cl::TDouble(rhs); }

    inline std::complex<cl::TDouble> operator+(double lhs, const std::complex<cl::TDouble>& rhs) { return cl::TDouble(lhs) + rhs; }

    inline std::complex<cl::TDouble> operator-(double lhs, const std::complex<cl::TDouble>& rhs) { return cl::TDouble(lhs) - rhs; }

    inline std::complex<cl::TDouble> operator*(double lhs, const std::complex<cl::TDouble>& rhs) { return cl::TDouble(lhs) * rhs; }

    inline std::complex<cl::TDouble> operator/(double lhs, const std::complex<cl::TDouble>& rhs) { return cl::TDouble(lhs) / rhs; }

    //!! Providing implementation causes compilation error due to NaN not being defined for Real, to be resolved
}

#endif // cl_system_api_TDoubleMath_hpp