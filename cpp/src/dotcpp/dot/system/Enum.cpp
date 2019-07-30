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
#include <dot/system/Enum.hpp>
#include <dot/system/type.hpp>
#include <dot/system/reflection/Activator.hpp>

namespace dot
{
    string Enum::to_string()
    {
        auto valuesMap = GetEnumMap();

        for (auto& x : valuesMap)
        {
            if (x.second == value_)
                return x.first;
        }

        // returns int value_ converted to string
        return std::to_string(value_);
    }

    size_t Enum::GetHashCode()
    {
        return std::hash<int>()(value_);
    }

    bool Enum::Equals(object obj)
    {
        if (obj->type()->Equals(type()))
        {
            Enum* en = dynamic_cast<Enum*>(obj.operator->());
            return en->value_ == value_;
        }
        return false;
    }

    object Enum::Parse(type_t enumType, string value)
    {
        object enum_obj = Activator::CreateInstance(enumType);
        Enum* en = dynamic_cast<Enum*>(enum_obj.operator->());
        auto valuesMap = en->GetEnumMap();

        int intValue = 0;
        if(!valuesMap->TryGetValue(value, intValue))
        {
            throw new_Exception("value is outside the range of the underlying type of enumType.");
        }

        en->value_ = intValue;
        return enum_obj;
    }
}
