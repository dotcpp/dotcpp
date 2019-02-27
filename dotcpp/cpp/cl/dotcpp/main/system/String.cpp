/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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
#include <cl/dotcpp/main/system/Char.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <locale>

namespace cl
{
    const String String::Empty = String("");

    String::String(const std::string& value)
        : value_(value)
    { }

    String::String(const char* value)
        : value_(value ? value : "")
    { }

    String::String(char value)
        : value_(1, value)
    { }

    String::String(const String& value)
        : value_(value.value_)
    { }

    int String::compareTo(const Object& value) const //!! Is this the behavior in C#?
    {
        return compareTo(value.ToString());
    }

    int String::compareTo(const String& strB) const
    {
        return value_.compare(strB.value_);
    }

    int String::byteCount() const
    {
        return static_cast<int>(value_.size());
    }

    String String::Replace(const String& oldValue, const String& newValue) const
    {
        std::string s = value_;
        std::size_t pos = 0,
            count = oldValue.value_.length(),
            ncount = newValue.value_.length();
        while ((pos = s.find(oldValue.value_, pos)) != std::string::npos)
        {
            s.replace(pos, count, newValue.value_);
            pos += ncount;
        }
        return String(s);
    }

    String String::ToLower() const
    {
        return ToLowerInvariant(); //!!! Fix - needs UTF-8 conversion
    }

    String String::ToLowerInvariant() const
    {
        std::string result = value_;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return String(result);
    }

    String String::ToUpper() const
    {
        return ToUpperInvariant(); //!!! Fix - needs UTF-8 conversion
    }

    String String::ToUpperInvariant() const
    {
        std::string result = value_;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return String(result);
    }

    String& String::operator=(const std::string& rhs)
    {
        value_ = rhs; return *this;
    }

    String& String::operator=(const char* rhs)
    {
        if (rhs) value_ = rhs;
        else value_.clear();
        return *this;
    }

    String& String::operator=(char rhs)
    {
        value_ = std::string(1, rhs);
        return *this;
    }

    bool String::operator==(const String& rhs) const
    {
        return compareTo(rhs) == 0;
    }

    bool String::operator!=(const String& rhs) const
    {
        return compareTo(rhs) != 0;
    }

    Char String::operator[](int index) const
    {
        //return Char(value_[index]); //!!!! static_cast<Char>(value_[index]);
        return Char();
    }

    int String::Compare(const String& strA, const String& strB)
    {
        return strA.compareTo(strB);
    }

    int String::Compare(const String& strA, const String& strB, bool ignoreCase)
    {
        if (!ignoreCase)
            return strA.compareTo(strB);

        auto itA = strA.value_.cbegin(),
            itB = strB.value_.cbegin(),
            endA = strA.value_.cend(),
            endB = strA.value_.cend();
        for (; (itA != endA) && (itB != endB); ++itA, ++itB)
        {
            std::locale loc;
            char a = std::tolower(*itA, loc);
            char b = std::tolower(*itB, loc);
            if (a < b)
                return -1;
            else if (a > b)
                return 1;
        }
        if (itA != endA)
            return 1;
        else if (itB != endB)
            return -1;
        else
            return 0;
    }

    int String::Compare(String const& strA, int indexA, const String& strB, int indexB, int length)
    {
        return strA.value_.compare(indexA, length, strB.value_, indexB, length);
    }

    String String::Concat(const Object& arg0)
    {
        return arg0.ToString();
    }

    String String::Concat(const Object& arg0, const Object& arg1)
    {
        std::string s;
        s.append(arg0.ToString());
        s.append(arg1.ToString());
        return String(s);
    }

    String String::Concat(const String& str0, const String& str1)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        return String(s);
    }

    String String::Concat(const Object& arg0, const Object& arg1, const Object& arg2)
    {
        std::string s;
        s.append(arg0.ToString());
        s.append(arg1.ToString());
        s.append(arg2.ToString());
        return String(s);
    }

    String String::Concat(const String& str0, const String& str1, const String& str2)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        return String(s);
    }

    String String::Concat(const Object& arg0, const Object& arg1, const Object& arg2, const Object& arg3)
    {
        std::string s;
        s.append(arg0.ToString());
        s.append(arg1.ToString());
        s.append(arg2.ToString());
        s.append(arg3.ToString());
        return String(s);
    }

    String String::Concat(const String& str0, const String& str1, const String& str2, const String& str3)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        s.append(str3.value_);
        return String(s);
    }

    String String::copy(const String& str)
    {
        return String(str);
    }

    bool String::equals(const String& strA, const String& strB)
    {
        return strA.compareTo(strB) == 0;
    }

    bool String::IsNullOrEmpty(const String& str)
    {
        return str.value_.empty(); //!! Consider null in implementation
    }

    bool String::IsNullOrWhiteSpace(const String& str)
    {
        //!! Consider null in implementation
        const std::string& s = str.value_;
        for (auto it = s.begin(); it != s.end(); ++it)
            if (*it != ' ') return false;
        return true;
    }
}

