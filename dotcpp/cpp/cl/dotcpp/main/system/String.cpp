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

#include <cl/system/api/implement.hpp>
#include <cl/system/api/TString.hpp>
#include <cl/system/api/TChar.hpp>
#include <locale>

namespace cl
{
    const TString TString::Empty = TString("");

    TString::TString(const std::string& value)
        : value_(value)
    { }

    TString::TString(const char* value)
        : value_(value ? value : "")
    { }

    TString::TString(char value)
        : value_(1, value)
    { }

    TString::TString(const TString& value)
        : value_(value.value_)
    { }

    int TString::compareTo(const TObject& value) const //!! Is this the behavior in C#?
    {
        return compareTo(value.ToString());
    }

    int TString::compareTo(const TString& strB) const
    {
        return value_.compare(strB.value_);
    }

    int TString::byteCount() const
    {
        return static_cast<int>(value_.size());
    }

    TString TString::Replace(const TString& oldValue, const TString& newValue) const
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
        return TString(s);
    }

    TString TString::ToLower() const
    {
        return ToLowerInvariant(); //!!! Fix - needs UTF-8 conversion
    }

    TString TString::ToLowerInvariant() const
    {
        std::string result = value_;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return TString(result);
    }

    TString TString::ToUpper() const
    {
        return ToUpperInvariant(); //!!! Fix - needs UTF-8 conversion
    }

    TString TString::ToUpperInvariant() const
    {
        std::string result = value_;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return TString(result);
    }

    TString& TString::operator=(const std::string& rhs)
    {
        value_ = rhs; return *this;
    }

    TString& TString::operator=(const char* rhs)
    {
        if (rhs) value_ = rhs;
        else value_.clear();
        return *this;
    }

    TString& TString::operator=(char rhs)
    {
        value_ = std::string(1, rhs);
        return *this;
    }

    bool TString::operator==(const TString& rhs) const
    {
        return compareTo(rhs) == 0;
    }

    bool TString::operator!=(const TString& rhs) const
    {
        return compareTo(rhs) != 0;
    }

    TChar TString::operator[](int index) const
    {
        //return TChar(value_[index]); //!!!! static_cast<TChar>(value_[index]);
        return TChar();
    }

    int TString::Compare(const TString& strA, const TString& strB)
    {
        return strA.compareTo(strB);
    }

    int TString::Compare(const TString& strA, const TString& strB, bool ignoreCase)
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

    int TString::Compare(TString const& strA, int indexA, const TString& strB, int indexB, int length)
    {
        return strA.value_.compare(indexA, length, strB.value_, indexB, length);
    }

    TString TString::Concat(const TObject& arg0)
    {
        return arg0.ToString();
    }

    TString TString::Concat(const TObject& arg0, const TObject& arg1)
    {
        std::string s;
        s.append(arg0.ToString().value_);
        s.append(arg1.ToString().value_);
        return TString(s);
    }

    TString TString::Concat(const TString& str0, const TString& str1)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        return TString(s);
    }

    TString TString::Concat(const TObject& arg0, const TObject& arg1, const TObject& arg2)
    {
        std::string s;
        s.append(arg0.ToString().value_);
        s.append(arg1.ToString().value_);
        s.append(arg2.ToString().value_);
        return TString(s);
    }

    TString TString::Concat(const TString& str0, const TString& str1, const TString& str2)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        return TString(s);
    }

    TString TString::Concat(const TObject& arg0, const TObject& arg1, const TObject& arg2, const TObject& arg3)
    {
        std::string s;
        s.append(arg0.ToString().value_);
        s.append(arg1.ToString().value_);
        s.append(arg2.ToString().value_);
        s.append(arg3.ToString().value_);
        return TString(s);
    }

    TString TString::Concat(const TString& str0, const TString& str1, const TString& str2, const TString& str3)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        s.append(str3.value_);
        return TString(s);
    }

    TString TString::copy(const TString& str)
    {
        return TString(str);
    }

    bool TString::equals(const TString& strA, const TString& strB)
    {
        return strA.compareTo(strB) == 0;
    }

    bool TString::IsNullOrEmpty(const TString& str)
    {
        return str.value_.empty(); //!! Consider null in implementation
    }

    bool TString::IsNullOrWhiteSpace(const TString& str)
    {
        //!! Consider null in implementation
        const std::string& s = str.value_;
        for (auto it = s.begin(); it != s.end(); ++it)
            if (*it != ' ') return false;
        return true;
    }
}

