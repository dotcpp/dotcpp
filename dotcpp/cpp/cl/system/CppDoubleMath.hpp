/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++ project, an open source implementation of
selected .NET class library APIs in native C++ with optional support
for adjoint algorithmic differentiation (AAD), available from

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

#ifndef __cl_system_CppDoubleMath_hpp__
#define __cl_system_CppDoubleMath_hpp__

#include <cl/system/CppDouble.hpp>
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
    inline cl::CppDouble fabs(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::fabs(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fabs(x.value());
#endif
    }

    inline cl::CppDouble abs(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::abs(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::abs(x.value());
#endif
    }

    inline cl::CppDouble floor(cl::CppDouble x)
{
#ifdef CL_DOUBLE_CPPAD
        return  cl::CppDouble(std::floor(CppAD::Value(x.value())));  //!!! Review
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::floor(x.value());
#endif
    }

    inline cl::CppDouble ceil(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return cl::CppDouble(std::ceil(CppAD::Value(x.value())));  //!!! Review
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::ceil(x.value());
#endif
    }

    inline cl::CppDouble sqrt(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sqrt(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sqrt(x.value());
#endif
    }

    inline cl::CppDouble log(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::log(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::log(x.value());
#endif
    }

    inline cl::CppDouble exp(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::exp(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::exp(x.value());
#endif
    }

    inline cl::CppDouble sin(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sin(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sin(x.value());
#endif
    }

    inline cl::CppDouble cos(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::cos(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::cos(x.value());
#endif
    }

    inline cl::CppDouble tan(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::tan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::tan(x.value());
#endif
    }

    inline cl::CppDouble asin(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::asin(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::asin(x.value());
#endif
    }

    inline cl::CppDouble acos(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::acos(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::acos(x.value());
#endif
    }

    inline cl::CppDouble atan(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::atan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan(x.value());
#endif
    }

    inline cl::CppDouble sinh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::sinh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::sinh(x.value());
#endif
    }

    inline cl::CppDouble cosh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::cosh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::cosh(x.value());
#endif
    }

    inline cl::CppDouble tanh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::tanh(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::tanh(x.value());
#endif
    }

    inline cl::CppDouble pow(cl::CppDouble x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::pow(x.value(), y.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x.value(), y.value());
#endif
    }

    inline cl::CppDouble pow(cl::CppDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return pow(x, cl::CppDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x.value(), y);
#endif
    }

    inline cl::CppDouble pow(double x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return pow(cl::CppDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::pow(x, y.value());
#endif
    }

    inline cl::CppDouble asinh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return log(x + sqrt(cl::CppDouble(1.0) + pow(x, 2.0)));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented");return x;
#else
        return std::asinh(x.value());
#endif
    }

    inline cl::CppDouble acosh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return log(x + sqrt(cl::CppDouble(-1.0) + pow(x, 2.0)));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::acosh(x.value());
#endif
    }

    inline cl::CppDouble atanh(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return 0.5* log((cl::CppDouble(1.0) + x) / (cl::CppDouble(1.0) - x));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atanh(x.value());
#endif
    }

    inline bool isnan(cl::CppDouble x)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::isnan(x.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::isnan(x.value());
#endif
    }


    inline cl::CppDouble min(cl::CppDouble x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::min(x.value(),y.value());
#endif
    }

    inline cl::CppDouble min(cl::CppDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::min(x.value(), y);
#endif
    }

    inline cl::CppDouble min(double x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x < y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented");return x;
#else
        return std::min(x, y.value());
#endif
    }

    inline cl::CppDouble max(cl::CppDouble x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? x : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;

#else
        return std::max(x.value(), y.value());
#endif
    }

    inline cl::CppDouble max(cl::CppDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? x : cl::CppDouble(y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::max(x.value(), y);
#endif
    }

    inline cl::CppDouble max(double x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x > y ? cl::CppDouble(x) : y;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::max(x, y.value());
#endif
    }

    inline cl::CppDouble atan2(cl::CppDouble x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return CppAD::atan2(x.value(), y.value());
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x.value(), y.value());
#endif
    }

    inline cl::CppDouble atan2(cl::CppDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return atan2(x, cl::CppDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x.value(), y);
#endif
    }

    inline cl::CppDouble atan2(double x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return atan2(cl::CppDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::atan2(x, y.value());
#endif
    }

    inline cl::CppDouble fmod(cl::CppDouble x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return x - y * ( x / y > 0 ? floor(x / y) : ceil (x / y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::fmod(x.value(), y.value());
#endif
    }

    inline cl::CppDouble fmod(cl::CppDouble x, double y)
    {
#ifdef CL_DOUBLE_CPPAD
        return fmod(x, cl::CppDouble(y));
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;

#else
        return std::fmod(x.value(), y);
#endif
    }

    inline cl::CppDouble fmod(double x, cl::CppDouble y)
    {
#ifdef CL_DOUBLE_CPPAD
        return fmod(cl::CppDouble(x), y);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;

#else
        return std::fmod(x, y.value());
#endif
    }

    inline cl::CppDouble modf(cl::CppDouble x, cl::CppDouble* iptr)
    {
#ifdef CL_DOUBLE_CPPAD
        double fractpart;
        double intpart;
        fractpart = std::modf(CppAD::Value(x.value()), &intpart);     //!!! Review
        (*iptr) = cl::CppDouble(intpart);
        return cl::CppDouble( fractpart);
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        double fractpart;
        double intpart;
        fractpart = std::modf(x.value(), &intpart);
        (*iptr) = intpart;
        return cl::CppDouble( fractpart);
#endif
    }

    template<class T1, class T2>
    inline cl::CppDouble inner_product(T1 first1, T1 last1, T2 first2, cl::CppDouble value)
    {
#ifdef CL_DOUBLE_CPPAD
        while (first1 != last1)
        {
            value = value + (*first1)*(*first2);
            ++first1; ++first2;
        }
        return cl::CppDouble(value);

#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return cl::CppDouble(std::inner_product(first1, last1, first2, value.value()));
#endif
    }
    template<class T1, class T2>
    inline double inner_product(T1 first1, T1 last1, T2 first2, double value)
    {
#ifdef CL_DOUBLE_CPPAD
        while (first1 != last1)
        {

            value = value + CppAD::Value(((*first1)*(*first2)).value());    //!!! Review

            ++first1; ++first2;
        }
        return value;
#elif CL_DOUBLE_ADOLC
        cl::throw_("Not implemented"); return x;
#else
        return std::inner_product(first1, last1, first2, value);
#endif
    }

    // Math functions for std::complex<Real>
    inline cl::CppDouble real(std::complex<cl::CppDouble> x) {
        return x.real();
    }

    inline cl::CppDouble imag(std::complex<cl::CppDouble> x) {
        return x.imag();
    }

    inline std::complex<cl::CppDouble> operator-(const std::complex<cl::CppDouble>& lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(lhs.real() - rhs.real(), lhs.imag() - rhs.imag());
    }

    inline std::complex<cl::CppDouble> operator*(const std::complex<cl::CppDouble>& lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(lhs.real()*rhs.real() - lhs.imag()*rhs.imag(), lhs.real()*rhs.imag() + lhs.imag()*rhs.real());
    }

    inline std::complex<cl::CppDouble> operator/(const std::complex<cl::CppDouble>& lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>((lhs.real()*rhs.real() + lhs.imag()*rhs.imag()) * std::pow((std::pow(rhs.real(), 2) + std::pow(rhs.imag(), 2)), -1.0),
            (lhs.imag()*rhs.real() - lhs.real()*rhs.imag()) * std::pow((std::pow(rhs.real(), 2) + std::pow(rhs.imag(), 2)), -1.0));
    }

    inline std::complex<cl::CppDouble> operator+(const std::complex<cl::CppDouble>& lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
    }

    // Arithmetics for std::complex<Real>
    inline std::complex<cl::CppDouble> operator+(const std::complex<cl::CppDouble>& lhs, cl::CppDouble rhs){
        return complex<cl::CppDouble>(lhs.real() + rhs, lhs.imag());
    }

    inline std::complex<cl::CppDouble> operator-(const std::complex<cl::CppDouble>& lhs, cl::CppDouble rhs){
        return complex<cl::CppDouble>(lhs.real() - rhs, lhs.imag());
    }

    inline std::complex<cl::CppDouble> operator*(const std::complex<cl::CppDouble>& lhs, cl::CppDouble rhs){
        return complex<cl::CppDouble>(lhs.real() *rhs, lhs.imag()*rhs);
    }

    inline std::complex<cl::CppDouble> operator/(const std::complex<cl::CppDouble>& lhs, cl::CppDouble rhs){
        return complex<cl::CppDouble>(lhs.real() / rhs, lhs.imag() / rhs);
    }

    inline std::complex<cl::CppDouble> operator+(cl::CppDouble lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(lhs + rhs.real(), rhs.imag());
    }

    inline std::complex<cl::CppDouble> operator-(cl::CppDouble lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(lhs - rhs.real(), -rhs.imag());
    }

    inline std::complex<cl::CppDouble> operator*(cl::CppDouble lhs, const std::complex<cl::CppDouble>& rhs){
        return complex<cl::CppDouble>(rhs.real() *lhs, rhs.imag()*lhs);
    }

    inline std::complex<cl::CppDouble> operator/(cl::CppDouble lhs, const std::complex<cl::CppDouble>& rhs){
        return cl::CppDouble(std::pow((std::pow(rhs.real(), 2) + std::pow(rhs.imag(), 2)), -1.0)*lhs)* complex<cl::CppDouble>(rhs.real() - rhs.imag());
    }

    // Arithmetics for std::complex<Real>
    inline std::complex<cl::CppDouble> operator+(const std::complex<cl::CppDouble>& lhs, double rhs) { return lhs + cl::CppDouble(rhs); }

    inline std::complex<cl::CppDouble> operator-(const std::complex<cl::CppDouble>& lhs, double rhs) { return lhs - cl::CppDouble(rhs); }

    inline std::complex<cl::CppDouble> operator*(const std::complex<cl::CppDouble>& lhs, double rhs) { return lhs * cl::CppDouble(rhs); }

    inline std::complex<cl::CppDouble> operator/(const std::complex<cl::CppDouble>& lhs, double rhs) { return lhs / cl::CppDouble(rhs); }

    inline std::complex<cl::CppDouble> operator+(double lhs, const std::complex<cl::CppDouble>& rhs) { return cl::CppDouble(lhs) + rhs; }

    inline std::complex<cl::CppDouble> operator-(double lhs, const std::complex<cl::CppDouble>& rhs) { return cl::CppDouble(lhs) - rhs; }

    inline std::complex<cl::CppDouble> operator*(double lhs, const std::complex<cl::CppDouble>& rhs) { return cl::CppDouble(lhs) * rhs; }

    inline std::complex<cl::CppDouble> operator/(double lhs, const std::complex<cl::CppDouble>& rhs) { return cl::CppDouble(lhs) / rhs; }

    //!! Providing implementation causes compilation error due to NaN not being defined for Real, to be resolved
    // { return std::complex<cl::Double>(cl::Double(lhs),0.0) / rhs; }

    inline std::complex<cl::CppDouble> sqrt(std::complex<cl::CppDouble> x) {
        //!!! Review
        return cl::CppDouble(std::pow(2.0, -0.5))*std::complex<cl::CppDouble>(std::sqrt(x.real() + std::sqrt(std::pow(x.real(), 2) + std::pow(x.imag(), 2))),
            (x.imag()>0.0 ? 1.0 : -1.0)*std::sqrt(std::sqrt(std::pow(x.real(), 2) + std::pow(x.imag(), 2)) - x.real()));
    }

    inline std::complex<cl::CppDouble> log(std::complex<cl::CppDouble> x) {
        //!!! Review
        return std::complex<cl::CppDouble>(cl::CppDouble(0.5)*std::log(std::pow(x.real(), 2) + std::pow(x.imag(), 2)),
            std::atan(x.imag() / x.real()));
        //return cl::Double(0.5)* std::complex<cl::Double>(std::pow(x.real(), 2.0) + std::pow(x.imag(), 2.0));
    }

    inline std::complex<cl::CppDouble> exp(std::complex<cl::CppDouble> x) {
        //!!! Review
        return cl::CppDouble(std::exp(x.real()))*std::complex<cl::CppDouble>(std::cos(x.imag()), std::sin(x.imag()));
    }


}

#endif  // __cl_system_CppDoubleMath_hpp__