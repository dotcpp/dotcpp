/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp (.C++), an open source implementation of
selected .NET class library APIs in native C++ with optional support
for algorithmic differentiation (AD), available from

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

#ifndef __cl_system_CppString_hpp__
#define __cl_system_CppString_hpp__

#include <cl/system/declare.hpp>

namespace cl
{
    class Char;
    class CppObject;
    template <class T> class CppArray;

    /// <summary>Immutable string type with unicode support.</summary>
    class CL_SYSTEM CppString
    {
        std::string value_;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static const CppString Empty;

    public: // CONSTRUCTORS
        
        /// <summary>Create from a single Unicode character.</summary>
        CppString(const Char& value);

        /// <summary>Create from std::string.</summary>
        CppString(const std::string& value) : value_(value) {}

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        CppString(const char* value) : value_(rhs ? value : "") {}

        /// <summary>Create from a single 8-bit character.</summary>
        CppString(char value) : value_(1, value) {}

    public: // METHODS

        /// <summary>Convert to std::string.</summary>
        std::string value() const { return value_; }

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.\\
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int length() const { return static_cast<int>(value_.size()); }

        /// <summary>Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.</summary>
        CppString replace(const CppString& oldValue, const CppString& newValue) const;

        /// <summary>Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.</summary>
        CppArray<CppString> split(char separator) const;

        /// <summary>Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.\\
        /// A parameter specifies whether to return empty array elements.</summary>
        CppArray<CppString> split(const CppArray<CppString>& separator, const CppStringSplitOptions& options) const;

    public: // OPERATORS

        /// <summary>Assignment of std::string.</summary>
        CppString& operator=(const std::string& rhs) { value_ = rhs; return *this; }

        /// <summary>Assignment of const char*, null pointer is converted to to empty value.</summary>
        CppString& operator=(const char* rhs) { if(rhs) value_ = rhs; else value_.clear(); return *this; }

        /// <summary>Assignment of 8-bit character.</summary>
        CppString& operator=(char rhs) { value_ = std::string(1,rhs); return *this; }

        /// <summary>Equality operator.</summary>
        bool operator==(const CppString& rhs) const { return value_ == rhs.value_; }

        /// <summary>Inequality operator.</summary>
        bool operator!=(const CppString& rhs) const { return value_ != rhs.value_; }

    public: // STATIC

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static CppString concat(const CppArray<CppString>& values);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static CppString format(const CppString& format, const CppArray<CppObject>& args);
    };
}

#endif  // __cl_system_CppString_hpp__
