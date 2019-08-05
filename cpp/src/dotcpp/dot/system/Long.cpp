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

#include <dot/precompiled.hpp>
#include <dot/implement.hpp>
#include <dot/system/Long.hpp>
#include <dot/system/string.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    bool long_impl::equals(object obj)
    {
        if (this == &(*obj)) return true;

        if (obj.is<ptr<long_impl>>())
        {
            return value_ == obj.as<ptr<long_impl>>()->value_;
        }

        return false;
    }

    size_t long_impl::hash_code()
    {
        return std::hash<int64_t>()(value_);
    }

    string long_impl::to_string()
    {
        return std::to_string(value_);
    }

    type_t long_impl::typeof()
    {
        return dot::typeof<int64_t>();
    }

    type_t long_impl::type()
    {
        return typeof();
    }

    int64_t long_impl::parse(string s)
    {
        return std::stoll(*s);
    }
}
