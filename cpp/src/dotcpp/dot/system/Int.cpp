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
#include <dot/system/Int.hpp>
#include <dot/system/string.hpp>
#include <dot/system/Type.hpp>

namespace dot
{
    bool IntImpl::Equals(object obj)
    {
        if (this == &(*obj)) return true;

        if (obj.is<ptr<IntImpl>>())
        {
            return value_ == obj.as<ptr<IntImpl>>()->value_;
        }

        return false;
    }

    size_t IntImpl::GetHashCode()
    {
        return std::hash<int>()(value_);
    }

    string IntImpl::to_string()
    {
        return std::to_string(value_);
    }

    Type IntImpl::typeof()
    {
        return dot::typeof<int>();
    }

    Type IntImpl::GetType()
    {
        return typeof();
    }

    int Int::Parse(string s)
    {
        return std::stoi(*s);
    }
}