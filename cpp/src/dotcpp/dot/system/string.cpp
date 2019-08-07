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
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <dot/implement.hpp>
#include <dot/system/string.hpp>
#include <dot/system/object.hpp>
#include <dot/system/nullable.hpp>
#include <dot/system/type.hpp>

namespace dot
{
    /// Empty string.
    string string::Empty = make_string("");

    dot::type_t string_impl::typeof()
    {
        static dot::type_t type = []()->dot::type_t
        {
            dot::type_t type = dot::make_type_builder<string_impl>("System", "string")
                ->build();
            return type;
        }();
        return type;
    }

    dot::type_t string_impl::type()
    {
        return typeof();
    }


    bool string_impl::equals(object obj)
    {
        if (this == &(*obj)) return true;

        if (obj.is<string>())
        {
            return *this == *obj.as<string>();
        }

        return false;
    }

    size_t string_impl::hash_code()
    {
        return std::hash<std::string>()(*this);
    }

    string string_impl::to_string()
    {
        return this;
    }

    /// Determines whether the end of this
    /// string matches the specified string.
    bool string_impl::ends_with(const string& value)
    {
        int p = length() - value->length();
        if (p >= 0 && substr(p, value->length()) == *value)
            return true;
        return false;
    }

    /// Determines whether the beginning of this
    /// string matches the specified string.
    bool string_impl::starts_with(const string& value)
    {
        int p = length() - value->length();
        if (p >= 0 && substr(0, value->length()) == *value)
            return true;
        return false;
    }

    /// Retrieves a substring which starts at the specified
    /// character position and has the specified length.
    string string_impl::substring(int startIndex, int length)
    {
        return make_string(this->substr(startIndex, length));
    }

    int string_impl::index_of_any(list<char> anyOf)
    {
        size_t pos = find_first_of(anyOf->data(), 0, anyOf->size());
        if (pos != std::string::npos)
            return pos;
        return -1;
    }

    string string_impl::remove(int startIndex)
    {
        return make_string(*this)->erase(startIndex);
    }

    string string_impl::remove(int startIndex, int count)
    {
        return make_string(*this)->erase(startIndex, count);
    }

    string string_impl::replace(const char oldChar, const char newChar) const
    {
        string new_str = *this;
        std::replace(new_str->begin(), new_str->end(), oldChar, newChar);
        return new_str;
    }

    bool string::is_null_or_empty(string value)
    {
        if (value == nullptr || value->empty())
            return true;
        return false;
    }

    /// Case sensitive comparison to object.
    bool string::operator==(const object& rhs) const
    {
        // If rhs is null, return false. Otherwise, check if
        // the other object is a string. If yes, compare by value.
        // If no, return false.
        if (rhs == nullptr)
        {
            return false;
        }
        else
        {
            string rhsStr = rhs.as<string>();
            if (rhsStr != nullptr) return operator==(rhsStr);
            else return false;
        }
    }

    /// Non-template implementation of string.Format.
    std::string string::format_impl(fmt::string_view format_str, fmt::format_args args)
    {
        return fmt::vformat(format_str, args);
    }
}
