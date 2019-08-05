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
#include <dot/system/Bool.hpp>
#include <dot/system/string.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    const string bool_impl::false_string = "False";

    const string bool_impl::true_string = "True";

    bool bool_impl::equals(object obj)
    {
        if (this == &(*obj)) return true;
        if (obj.is<ptr<bool_impl>>())
        {
            return value_ == obj.as<ptr<bool_impl>>()->value_;
        }

        return false;
    }

    size_t bool_impl::hash_code()
    {
        return std::hash<bool>()(value_);
    }

    string bool_impl::to_string()
    {
        return value_ ? bool_impl::true_string : bool_impl::false_string;
    }

    type_t bool_impl::typeof()
    {
        return dot::typeof<bool>();
    }

    type_t bool_impl::type()
    {
        return typeof();
    }

    bool bool_impl::parse(string s)
    {
        if (s == bool_impl::false_string) return false;
        if (s == bool_impl::true_string) return true;

        throw exception("value is not equivalent to true_string or false_string.");
    }
}
