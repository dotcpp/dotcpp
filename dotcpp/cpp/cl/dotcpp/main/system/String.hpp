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

#pragma once

#include <cl/dotcpp/main/declare.hpp>
#include <string>

namespace cl
{
    enum class StringSplitOptions;
    class Char;
    class Comparer;
    template <typename T> class Array;
    class StringComparer;

    /// <summary>Immutable string type with Unicode support.</summary>
    class String : public std::string
    {
        typedef std::string base;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static constexpr const char* Empty = "";

    public: // CONSTRUCTORS

        /// <summary>Creates an empty string.</summary>
        String() {}

        /// <summary>Create from a single Unicode character.</summary>
        String(const Char& value);

        /// <summary>Create from std::string.</summary>
        String(const std::string& value) : base(value) {}

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        String(const char* value) : base(value) {}

        /// <summary>Create from a single 8-bit character.</summary>
        String(char value) : base(std::to_string(value)) {}

    public: // METHODS

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.\\
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int byteCount() const;

    public: // METHODS

        /// <summary>Determines whether the end of this
        /// string matches the specified string.</summary>
        bool EndsWith(const std::string& value)
        {
            int p = length() - value.length();
            if (p >= 0 && substr(p, value.length())
                == value)
                return true;
            return false;
        }

        /// <summary>Determines whether the beginning of this
        /// string matches the specified string.</summary>
        bool StartsWith(String const& value)
        {
            int p = length() - value.length();
            if (p >= 0 && substr(0, value.length()) == value)
                return true;
            return false;
        }

        /// <summary>Retrieves a substring which starts at the specified
        /// character position and has the specified length.</summary>
        String Substring(int startIndex, int length)
        {
            return substr(startIndex, length);
        }

        /// <summary>Gets the number of characters in the current string.
        /// Note that for Unicode this is not the same as the number of bytes.</summary>
        int getLength()
        {
            return length(); //!!! This has to be corrected for Unicode
        }

        /// <summary>Compares this instance with a specified String object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified String.</summary>
        int compareTo(const String& strB) const;

        /// <summary>Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.</summary>
        String Replace(const String& oldValue, const String& newValue) const;

        /// <summary>Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.</summary>
        Array<String> Split(char separator) const;

        /// <summary>Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.\\
        /// A parameter specifies whether to return empty array elements.</summary>
        Array<String> Split(const Array<String>& separator, const StringSplitOptions& options) const;

        ///<summary>Indicates whether the argument occurs within this string.</summary>
        inline bool Contains(cl::String const& s) const
        {
            return find(s) != std::string::npos;
        }

        ///<summary>Returns a copy of this string converted to lowercase.</summary>
        String ToLower() const;

        ///<summary>Returns a copy of this System.String object converted to lowercase using the casing rules of the invariant culture.</summary>
        String ToLowerInvariant() const;

        ///<summary>Returns a copy of this string converted to uppercase.</summary>
        String ToUpper() const;

        ///<summary>Returns a copy of this System.String object converted to uppercase using the casing rules of the invariant culture.</summary>
        String ToUpperInvariant() const;

    public: // OPERATORS

        /// <summary>Assignment of std::string.</summary>
        String& operator=(const std::string& rhs);

        /// <summary>Assignment of const char*, null pointer is converted to to empty value.</summary>
        String& operator=(const char* rhs)
        {
            if (rhs)
            {
                base::operator=(rhs);
            }
            else
            {
                base::operator=(Empty);
            }
            return *this;
        }

        /// <summary>Assignment of 8-bit character.</summary>
        String& operator=(char rhs);

        /// <summary>Gets the Char object at a specified position in the current String object.</summary>
        Char operator[](int index) const;

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend String operator+(const String& lhs, const String& rhs);

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend bool operator<(const String& lhs, const String& rhs);

    public: // STATIC

        /* TODO

        /// <summary>Compares two specified String objects and returns an integer that
        /// indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, const String& strB);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const String& strA, const String& strB, bool ignoreCase);

        /// <summary>Compares two specified String objects using the specified rules, and
        /// returns an integer that indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, const String& strB, const StringComparison& comparisonType);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const String& strA, const String& strB, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares two specified String objects using the specified comparison
        /// options and culture-specific information to influence the comparison, and
        /// returns an integer that indicates the relationship of the two strings to
        /// each other in the sort order.</summary>
        static int Compare(const String& strA, const String& strB, const TCultureInfo& culture, TCompareOptions options);

        /// <summary>Compares substrings of two specified String objects and returns an
        /// integer that indicates their relative position in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case, and returns an integer that indicates their relative position
        /// in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, bool ignoreCase);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// rules, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, const StringComparison& comparisonType);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// comparison options and culture-specific information to influence the comparison,
        /// and returns an integer that indicates the relationship of the two substrings
        /// to each other in the sort order.</summary>
        static int Compare(const String& strA, int indexA, const String& strB, int indexB, int length, const TCultureInfo& culture, const TCompareOptions& options);

        /// <summary>Compares two specified String objects by evaluating the numeric values
        /// of the corresponding Char objects in each string.</summary>
        static int CompareOrdinal(const String& strA, const String& strB);

        /// <summary>Compares substrings of two specified String objects by evaluating
        /// the numeric values of the corresponding Char objects in each substring.</summary>
        static int CompareOrdinal(const String& strA, int indexA, const String& strB, int indexB, int length);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static String Concat(const IEnumerable<String>& values);

        /// <summary>Concatenates the members of an IEnumerable<T> implementation.</summary>
        template <class T>
        static String Concat(const IEnumerable<T>& values);

        /// <summary>Creates the string representation of a specified object.</summary>
        static String Concat(const Object& arg0);

        /// <summary>Concatenates the string representations of the elements in a specified Object array.</summary>
        static String Concat(const Array<Object>& args);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static String Concat(const Array<String>& values);

        /// <summary>Concatenates the string representations of two specified objects.</summary>
        static String Concat(const Object& arg0, const Object& arg1);

        /// <summary>Concatenates two specified instances of String.</summary>
        static String Concat(const String& str0, const String& str1);

        /// <summary>Concatenates the string representations of three specified objects.</summary>
        static String Concat(const Object& arg0, const Object& arg1, const Object& arg2);

        /// <summary>Concatenates three specified instances of String.</summary>
        static String Concat(const String& str0, const String& str1, const String& str2);

        /// <summary>Concatenates the string representations of four specified objects and any
        /// objects specified in an optional variable length parameter list.</summary>
        static String Concat(const Object& arg0, const Object& arg1, const Object& arg2, const Object& arg3);

        /// <summary>Concatenates four specified instances of System.String.</summary>
        static String Concat(const String& str0, const String& str1, const String& str2, const String& str3);

        /// <summary>Creates a new instance of System.String with the same value as a specified String.</summary>
        static String copy(const String& str);

        /// <summary>Determines whether two specified System.String objects have the same value.</summary>
        static bool equals(const String& strA, const String& strB);

        /// <summary>Determines whether two specified System.String objects have the same value.
        /// A parameter specifies the culture, case, and sort rules used in the comparison.</summary>
        static bool equals(const String& strA, const String& strB, const StringComparison& comparisonType);

        /// <summary>Replaces one or more format items in a specified string with the string representation
        /// of a specified object.</summary>
        static String Format(const String& format, const Object& arg0);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static String Format(const String& format, const Array<Object>& args);

        /// <summary>Replaces the format item in a specified string with the string representation
        /// of a corresponding object in a specified array. A specified parameter supplies
        /// culture-specific formatting information.</summary>
        static String Format(const ITFormatProvider& provider, const String& format, const Array<Object>& args);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of two specified objects.</summary>
        static String Format(const String& format, const Object& arg0, const Object& arg1);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of three specified objects.</summary>
        static String Format(const String& format, const Object& arg0, const Object& arg1, const Object& arg2);

        /// <summary>Indicates whether the specified string is null or empty.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrEmpty(const String& str);

        /// <summary>Indicates whether a specified string is null,
        /// empty, or consists only of white-space characters.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrWhiteSpace(const String& str);

        /// <summary>Concatenates the members of a constructed IEnumerable<T>
        /// collection of type String, using the specified separator between each
        /// member.</summary>
        static String Join(const String& separator, const IEnumerable<String>& values);

        /// <summary>Concatenates the members of a collection, using the specified separator between
        /// each member.</summary>
        template<class T>
        static String Join(const String& separator, const IEnumerable<T>& values);

        /// <summary>Concatenates the elements of an object array, using the specified separator
        /// between each element.</summary>
        static String Join(const String& separator, const Array<Object>& values);

        /// <summary>Concatenates all the elements of a string array, using the specified separator
        /// between each element.</summary>
        static String Join(const String& separator, const Array<String>& value);

        /// <summary>Concatenates the specified elements of a string array, using the specified
        /// separator between each element.</summary>
        static String Join(const String& separator, const Array<String>& value, int startIndex, int count);

        */
    };

    /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
    inline String operator+(const String& lhs, const String& rhs) { return String(lhs + rhs); }
}
