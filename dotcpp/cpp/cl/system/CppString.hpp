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

#ifndef __cl_system_CppString_hpp__
#define __cl_system_CppString_hpp__

#include <cl/system/declare.hpp>
#include <cl/system/CppObject.hpp>
#include <cl/system/CppPtr.hpp>

namespace cl
{
    template <class T> class ICppEnumerable;
    template <class T> class CppArray;
    enum class CppCompareOptions;
    enum class CppStringSplitOptions;
    enum class CppStringComparison;
    class CppChar;
    class CppCultureInfo;
    class CppObject;
    class ICppFormatProvider;

    /// <summary>Immutable string type with unicode support.</summary>
    class CL_SYSTEM CppString
    {
        std::string value_;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static const CppString Empty;

    public: // CONSTRUCTORS

        /// <summary>Create from a single Unicode character.</summary>
        CppString(const CppChar& value);

        /// <summary>Create from std::string.</summary>
        CppString(const std::string& value);

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        CppString(const char* value);

        /// <summary>Create from a single 8-bit character.</summary>
        CppString(char value);

        /// <summary>Create a copy of CppString.</summary>
        CppString(const CppString& value);

    public: // METHODS

        /// <summary>Compares this instance with a specified Object and indicates whether
        /// this instance precedes, follows, or appears in the same position in the sort
        /// order as the specified Object.</summary>
        int compareTo(const CppObject& value) const;

        /// <summary>Compares this instance with a specified String object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified String.</summary>
        int compareTo(const CppString& strB) const;

        /// <summary>Convert to std::string.</summary>
        std::string value() const;

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.\\
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int length() const;

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
        CppString& operator=(const std::string& rhs);

        /// <summary>Assignment of const char*, null pointer is converted to to empty value.</summary>
        CppString& operator=(const char* rhs);

        /// <summary>Assignment of 8-bit character.</summary>
        CppString& operator=(char rhs);

        /// <summary>Equality operator.</summary>
        bool operator==(const CppString& rhs) const;

        /// <summary>Inequality operator.</summary>
        bool operator!=(const CppString& rhs) const; 

        /// <summary>Gets the Char object at a specified position in the current String object.</summary>
        CppChar operator[](int index) const;
        
    public: // STATIC

        /// <summary>Compares two specified String objects and returns an integer that
        /// indicates their relative position in the sort order.</summary>
        static int compare(const CppString& strA, const CppString& strB);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int compare(const CppString& strA, const CppString& strB, bool ignoreCase);

        /// <summary>Compares two specified String objects using the specified rules, and
        /// returns an integer that indicates their relative position in the sort order.</summary>
        static int compare(const CppString& strA, const CppString& strB, const CppStringComparison& comparisonType);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int compare(const CppString& strA, const CppString& strB, bool ignoreCase, const CppCultureInfo& culture);

        /// <summary>Compares two specified String objects using the specified comparison
        /// options and culture-specific information to influence the comparison, and
        /// returns an integer that indicates the relationship of the two strings to
        /// each other in the sort order.</summary>
        static int compare(const CppString& strA, const CppString& strB, const CppCultureInfo& culture, CppCompareOptions options);

        /// <summary>Compares substrings of two specified String objects and returns an
        /// integer that indicates their relative position in the sort order.</summary>
        static int compare(const CppString& strA, int indexA, const CppString& strB, int indexB, int length);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case, and returns an integer that indicates their relative position
        /// in the sort order.</summary>
        static int compare(const CppString& strA, int indexA, const CppString& strB, int indexB, int length, bool ignoreCase);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// rules, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int compare(const CppString& strA, int indexA, const CppString& strB, int indexB, int length, const CppStringComparison& comparisonType);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int compare(const CppString& strA, int indexA, const CppString& strB, int indexB, int length, bool ignoreCase, const CppCultureInfo& culture);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// comparison options and culture-specific information to influence the comparison,
        /// and returns an integer that indicates the relationship of the two substrings
        /// to each other in the sort order.</summary>
        static int compare(const CppString& strA, int indexA, const CppString& strB, int indexB, int length, const CppCultureInfo& culture, const CppCompareOptions& options);

        /// <summary>Compares two specified String objects by evaluating the numeric values
        /// of the corresponding Char objects in each string.</summary>
        static int compareOrdinal(const CppString& strA, const CppString& strB);

        /// <summary>Compares substrings of two specified String objects by evaluating
        /// the numeric values of the corresponding Char objects in each substring.</summary>
        static int compareOrdinal(const CppString& strA, int indexA, const CppString& strB, int indexB, int length);

        /// <summary>Concatenates the elements of a specified CppString array.</summary>
        static CppString concat(const ICppEnumerable<CppString>& values);

        /// <summary>Concatenates the members of an ICppEnumerable<T> implementation.</summary>
        template <class T>
        static CppString concat(const ICppEnumerable<T>& values);

        /// <summary>Creates the string representation of a specified object.</summary>
        static CppString concat(const CppObject& arg0);

        /// <summary>Concatenates the string representations of the elements in a specified Object array.</summary>
        static CppString concat(const CppArray<CppObject>& args);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static CppString concat(const CppArray<CppString>& values);

        /// <summary>Concatenates the string representations of two specified objects.</summary>
        static CppString concat(const CppObject& arg0, const CppObject& arg1);

        /// <summary>Concatenates two specified instances of String.</summary>
        static CppString concat(const CppString& str0, const CppString& str1);

        /// <summary>Concatenates the string representations of three specified objects.</summary>
        static CppString concat(const CppObject& arg0, const CppObject& arg1, const CppObject& arg2);

        /// <summary>Concatenates three specified instances of String.</summary>
        static CppString concat(const CppString& str0, const CppString& str1, const CppString& str2);

        /// <summary>Concatenates the string representations of four specified objects and any
        /// objects specified in an optional variable length parameter list.</summary>
        static CppString concat(const CppObject& arg0, const CppObject& arg1, const CppObject& arg2, const CppObject& arg3);

        /// <summary>Concatenates four specified instances of System.String.</summary>
        static CppString concat(const CppString& str0, const CppString& str1, const CppString& str2, const CppString& str3);

        /// <summary>Creates a new instance of System.String with the same value as a specified String.</summary>
        static CppString copy(const CppString& str);

        /// <summary>Determines whether two specified System.String objects have the same value.</summary>
        static bool equals(const CppString& strA, const CppString& strB);

        /// <summary>Determines whether two specified System.String objects have the same value.
        /// A parameter specifies the culture, case, and sort rules used in the comparison.</summary>
        static bool equals(const CppString& strA, const CppString& strB, const CppStringComparison& comparisonType);

        /// <summary>Replaces one or more format items in a specified string with the string representation
        /// of a specified object.</summary>
        static CppString format(const CppString& format, const CppObject& arg0);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static CppString format(const CppString& format, const CppArray<CppObject>& args);

        /// <summary>Replaces the format item in a specified string with the string representation
        /// of a corresponding object in a specified array. A specified parameter supplies
        /// culture-specific formatting information.</summary>
        static CppString format(const ICppFormatProvider& provider, const CppString& format, const CppArray<CppObject>& args);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of two specified objects.</summary>
        static CppString format(const CppString& format, const CppObject& arg0, const CppObject& arg1);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of three specified objects.</summary>
        static CppString format(const CppString& format, const CppObject& arg0, const CppObject& arg1, const CppObject& arg2);

        /// <summary>Indicates whether the specified string is an empty string.</summary>
        static bool isEmpty(const CppString& str);

        /// <summary>Indicates whether a specified string is empty or consists only of
        /// white-space characters.</summary>
        static bool isEmptyOrWhiteSpace(const CppString& str);

        /// <summary>Concatenates the members of a constructed ICppEnumerable<T>
        /// collection of type String, using the specified separator between each
        /// member.</summary>
        static CppString join(const CppString& separator, const ICppEnumerable<CppString>& values);

        /// <summary>Concatenates the members of a collection, using the specified separator between
        /// each member.</summary>
        template<class T>
        static CppString join(const CppString& separator, const ICppEnumerable<T>& values);

        /// <summary>Concatenates the elements of an object array, using the specified separator
        /// between each element.</summary>
        static CppString join(const CppString& separator, const CppArray<CppObject>& values);

        /// <summary>Concatenates all the elements of a string array, using the specified separator
        /// between each element.</summary>
        static CppString join(const CppString& separator, const CppArray<CppString>& value);

        /// <summary>Concatenates the specified elements of a string array, using the specified
        /// separator between each element.</summary>
        static CppString join(const CppString& separator, const CppArray<CppString>& value, int startIndex, int count);

        /// <summary>static create methods to create instance which can't call from other scope </summary>
        static CppPtr<CppString> create()   {  return CppPtr<CppString>(new CppString("")); }
    };
}

#endif  // __cl_system_CppString_hpp__
