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

#pragma once

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    /// <summary>Empty string.</summary>
    String String::Empty = new_String("");

    /// <summary>Determines whether the end of this
    /// string matches the specified string.</summary>
    bool StringImpl::EndsWith(const std::string& value)
    {
        int p = length() - value.length();
        if (p >= 0 && substr(p, value.length())
            == value)
            return true;
        return false;
    }

    /// <summary>Determines whether the beginning of this
    /// string matches the specified string.</summary>
    bool StringImpl::StartsWith(const String& value)
    {
        int p = length() - value->length();
        if (p >= 0 && substr(0, value->length()) == *value)
            return true;
        return false;
    }

    /// <summary>Retrieves a substring which starts at the specified
    /// character position and has the specified length.</summary>
    String StringImpl::SubString(int startIndex, int length)
    {
        return new_String(this->substr(startIndex, length));
    }

    /// <summary>Gets the number of characters in the current string.
    /// Note that for Unicode this is not the same as the number of bytes.</summary>
    int StringImpl::getLength()
    {
        return length(); //!!! This has to be corrected for Unicode
    }

    ///<summary>Indicates whether the argument occurs within this string.</summary>
    bool StringImpl::Contains(String const& s) const
    {
        throw std::exception("Not implemented");
       // TODO - fix return this->find(s) != std::string::npos;
    }

    /// <summary>Case sensitive comparison to Object.</summary>
    bool String::operator==(const Object& rhs) const
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
            String rhsStr = rhs.as<String>();
            if (rhsStr != nullptr) return operator==(rhsStr);
            else return false;
        }
    }

    bool String::operator<(const Ptr<StringImpl>& rhs) const
    {
        return this->operator*() < *rhs;
    }

}
