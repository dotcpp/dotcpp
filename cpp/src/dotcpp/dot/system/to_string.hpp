/*
Copyright (C) 2015-present The DotCpp Authors.

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

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

#pragma once

#include <dot/declare.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    /// Helper class to provide provides to_string(value) syntax for atomic
    /// and external classes where we cannot define member function to_string().
    ///
    /// The implementation is provided by creating a specialization of this
    /// helper class with template parameter T for which to_string is beign
    /// defined:
    ///
    /// 
    /// 
    /// This class is necessary because C++ permits partial specialization of
    /// classes, but not functions. Partial specialization is necessary when
    /// defining to_string for a type that is itself a template, for example
    /// nullable.
    template <class T>
    class to_string_impl
    {
    public:
        static string to_string(const T& value)
        {
            throw exception("To implement to_string(const T& value), provide template specialization for to_string_impl<T>.")
        }
    };

    /// Per C++ convention for extension methods, provides to_string(value)
    /// syntax for atomic and external classes where we cannot define member
    /// function to_string().
    template <class T>
    string to_string(const T& value)
    {
        return to_string_impl<T>::to_string(value);
    }
}