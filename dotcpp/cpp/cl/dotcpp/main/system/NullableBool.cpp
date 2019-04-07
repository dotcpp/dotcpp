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

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/NullableBool.hpp>

namespace cl
{
    /// <summary>A string representing the current type.</summary>
    String BoolImpl::ToString() { return std::to_string(value_); }

    /// <summary>Returns string representation of the object.</summary>
    std::string NullableBool::AsString() const
    {
        switch(value_)
        {
            case 1: return "Y";
            case 0: return "N";
            case Bool::Empty: return "";
            default: throw std::runtime_error("Unknown internal value in NullableBool.");
        }
    }
}
