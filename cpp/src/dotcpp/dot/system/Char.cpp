/*
Copyright (C) 2003-present CompatibL

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
#include <dot/system/String.hpp>
#include <dot/system/Type.hpp>

namespace dot
{
    bool CharImpl::Equals(Object obj)
    {
        if (this == &(*obj)) return true;

        if (obj.is<Ptr<CharImpl>>())
        {
            return value_ == obj.as<Ptr<CharImpl>>()->value_;
        }

        return false;
    }

    size_t CharImpl::GetHashCode()
    {
        return std::hash<char>()(value_);
    }

    String CharImpl::ToString()
    {
        return std::to_string(value_);
    }

    Type CharImpl::typeof()
    {
        return dot::typeof<char>();
    }

    Type CharImpl::GetType()
    {
        return typeof();
    }
}