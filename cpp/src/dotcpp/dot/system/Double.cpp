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

#include <dot/implement.hpp>
#include <dot/system/Double.hpp>
#include <dot/system/string.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    bool DoubleImpl::Equals(object obj)
    {
        if (this == &(*obj)) return true;

        if (obj.is<ptr<DoubleImpl>>())
        {
            return value_ == obj.as<ptr<DoubleImpl>>()->value_;
        }

        return false;
    }

    size_t DoubleImpl::hash_code()
    {
        return std::hash<double>()(value_);
    }

    string DoubleImpl::to_string()
    {
        return std::to_string(value_);
    }

    type_t DoubleImpl::typeof()
    {
        return dot::typeof<double>();
    }

    type_t DoubleImpl::type()
    {
        return typeof();
    }

    double Double::Parse(string s)
    {
        return std::stod(*s);
    }
}
