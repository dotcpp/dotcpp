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
    const string Bool::false_string = "False";

    const string Bool::true_string = "True";

    bool BoolImpl::Equals(object obj)
    {
        if (this == &(*obj)) return true;
        if (obj.is<ptr<BoolImpl>>())
        {
            return value_ == obj.as<ptr<BoolImpl>>()->value_;
        }

        return false;
    }

    size_t BoolImpl::GetHashCode()
    {
        return std::hash<bool>()(value_);
    }

    string BoolImpl::to_string()
    {
        return value_ ? Bool::true_string : Bool::false_string;
    }

    type_t BoolImpl::typeof()
    {
        return dot::typeof<bool>();
    }

    type_t BoolImpl::type()
    {
        return typeof();
    }

    bool Bool::Parse(string s)
    {
        if (s == Bool::false_string) return false;
        if (s == Bool::true_string) return true;

        throw new_Exception("value is not equivalent to true_string or false_string.");
    }
}
