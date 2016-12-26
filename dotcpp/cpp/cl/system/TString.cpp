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

#include <cl/system/implement.hpp>
#include <cl/system/CppString.hpp>
#include <cl/system/CppChar.hpp>
#include <locale>

namespace cl
{
    CppString::CppString(const std::string& value)
        : value_(value)
    { }

    CppString::CppString(const char* value)
        : value_(value ? value : "")
    { }

    CppString::CppString(char value)
        : value_(1, value)
    { }

    CppString::CppString(const CppString& value)
        : value_(value.value_)
    { }

    int CppString::compareTo(const CppObject& value) const
    {
        return compareTo(value.toString());
    }

    int CppString::compareTo(const CppString& strB) const
    {
        return value_.compare(strB.value_);
    }

    std::string CppString::value() const
    {
        return value_;
    }

    int CppString::length() const
    {
        return static_cast<int>(value_.size());
    }

    CppString CppString::replace(const CppString& oldValue, const CppString& newValue) const
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
        return CppString(s);
    }

    CppString& CppString::operator=(const std::string& rhs)
    {
        value_ = rhs; return *this;
    }

    CppString& CppString::operator=(const char* rhs)
    {
        if (rhs) value_ = rhs;
        else value_.clear();
        return *this;
    }

    CppString& CppString::operator=(char rhs)
    {
        value_ = std::string(1, rhs);
        return *this;
    }

    bool CppString::operator==(const CppString& rhs) const
    {
        return compareTo(rhs) == 0;
    }

    bool CppString::operator!=(const CppString& rhs) const
    {
        return compareTo(rhs) != 0;
    }

    CppChar CppString::operator[](int index) const
    {
        //return CppChar(value_[index]); //!!!! static_cast<CppChar>(value_[index]);
        return CppChar();
    }
    
    int CppString::compare(const CppString& strA, const CppString& strB)
    {
        return strA.compareTo(strB);
    }

    static int compare(const CppString& strA, const CppString& strB, bool ignoreCase)
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

    int CppString::compare(CppString const& strA, int indexA, const CppString& strB, int indexB, int length)
    {
        return strA.value_.compare(indexA, length, strB.value_, indexB, length);
    }

    CppString CppString::concat(const CppObject& arg0)
    {
        return arg0.toString();
    }

    CppString CppString::concat(const CppObject& arg0, const CppObject& arg1)
    {
        std::string s;
        s.append(arg0.toString().value_);
        s.append(arg1.toString().value_);
        return CppString(s);
    }

    CppString CppString::concat(const CppString& str0, const CppString& str1)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        return CppString(s);
    }

    CppString CppString::concat(const CppObject& arg0, const CppObject& arg1, const CppObject& arg2)
    {
        std::string s;
        s.append(arg0.toString().value_);
        s.append(arg1.toString().value_);
        s.append(arg2.toString().value_);
        return CppString(s);
    }

    CppString CppString::concat(const CppString& str0, const CppString& str1, const CppString& str2)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        return CppString(s);
    }

    CppString CppString::concat(const CppObject& arg0, const CppObject& arg1, const CppObject& arg2, const CppObject& arg3)
    {
        std::string s;
        s.append(arg0.toString().value_);
        s.append(arg1.toString().value_);
        s.append(arg2.toString().value_);
        s.append(arg3.toString().value_);
        return CppString(s);
    }

    CppString CppString::concat(const CppString& str0, const CppString& str1, const CppString& str2, const CppString& str3)
    {
        std::string s;
        s.append(str0.value_);
        s.append(str1.value_);
        s.append(str2.value_);
        s.append(str3.value_);
        return CppString(s);
    }

    CppString CppString::copy(const CppString& str)
    {
        return CppString(str);
    }

    bool CppString::equals(const CppString& strA, const CppString& strB)
    {
        return strA.compareTo(strB) == 0;
    }

    bool CppString::isEmpty(const CppString& str)
    {
        return str.value_.empty();
    }

    bool CppString::isEmptyOrWhiteSpace(const CppString& str)
    {
        const std::string& s = str.value_;
        for (auto it = s.begin(); it != s.end(); ++it)
            if (*it != ' ') return false;
        return true;
    }
}

