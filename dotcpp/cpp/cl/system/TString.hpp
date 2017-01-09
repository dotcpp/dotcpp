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

#ifndef cl_system_TString_hpp
#define cl_system_TString_hpp

#include <cl/system/declare.hpp>
#include <cl/system/TObject.hpp>
#include <cl/system/TPtr.hpp>
#include <xhash>

namespace cl
{
    class TString; using tstring = TString;

    template <class T> class ITEnumerable;
    template <class T> class TArray;
    enum class TCompareOptions;
    enum class TStringSplitOptions;
    enum class TStringComparison;
    class TChar;
    class TCultureInfo;
    class TObject;
    class ITFormatProvider;

    /// <summary>Immutable string type with Unicode support.</summary>
    class CL_SYSTEM TString
    {
        friend class TStringBuilder;

        std::string value_;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static const TString Empty;

    public: // CONSTRUCTORS

        /// <summary>Create from a single Unicode character.</summary>
        TString() : value_()
        {}

        /// <summary>Create from a single Unicode character.</summary>
        TString(const TChar& value);

        /// <summary>Create from std::string.</summary>
        TString(const std::string& value);

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        TString(const char* value);

        /// <summary>Create from a single 8-bit character.</summary>
        TString(char value);

        /// <summary>Create a copy of TString.</summary>
        TString(const TString& value);

    public:

        ///<summary>Convert to std::string.</summary>
        std::string value() const { return value_; }

        ///<summary>Hash code.</summary>
        int getHashCode() const
        {
            return std::hash<std::string>()(value_);
        }

        bool EndsWith(TString const& value)
        {
            int p = value_.length() - value.value_.length();
            if (p >= 0 && value_.substr(p, value.value_.length())
                == value.value_)
                return true;
            return false;
        }

        bool StartsWith(TString const& value)
        {
            int p = value_.length() - value.value_.length();
            if (p >= 0 && value_.substr(0, value.value_.length()) == value.value_)
                return true;
            return false;
        }

        TString Substring(int startIndex, int length)
        {
            return value_.substr(startIndex, length);
        }

        int Length()
        {
            return value_.length();
        }

    public: // METHODS

        /// <summary>Compares this instance with a specified Object and indicates whether
        /// this instance precedes, follows, or appears in the same position in the sort
        /// order as the specified Object.</summary>
        int compareTo(const TObject& value) const;

        /// <summary>Compares this instance with a specified String object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified String.</summary>
        int compareTo(const TString& strB) const;

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.\\
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int length() const;

        /// <summary>Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.</summary>
        TString replace(const TString& oldValue, const TString& newValue) const;

        /// <summary>Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.</summary>
        TArray<TString> split(char separator) const;

        /// <summary>Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.\\
        /// A parameter specifies whether to return empty array elements.</summary>
        TArray<TString> split(const TArray<TString>& separator, const TStringSplitOptions& options) const;

        ///<summary> </summary>
        inline bool contains(cl::TString const& s) const
        {
            return value_.find(s.value_) != std::string::npos;
        }

    public: // OPERATORS

        /// <summary>Assignment of std::string.</summary>
        TString& operator=(const std::string& rhs);

        /// <summary>Assignment of const char*, null pointer is converted to to empty value.</summary>
        TString& operator=(const char* rhs);

        /// <summary>Assignment of 8-bit character.</summary>
        TString& operator=(char rhs);

        /// <summary>Equality operator.</summary>
        bool operator==(const TString& rhs) const;

        /// <summary>Inequality operator.</summary>
        bool operator!=(const TString& rhs) const;

        /// <summary>Gets the Char object at a specified position in the current String object.</summary>
        TChar operator[](int index) const;

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend TString operator+(const TString& lhs, const TString& rhs);

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend bool operator<(const TString& lhs, const TString& rhs);

    public: // STATIC

        /// <summary>Compares two specified String objects and returns an integer that
        /// indicates their relative position in the sort order.</summary>
        static int compare(const TString& strA, const TString& strB);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int compare(const TString& strA, const TString& strB, bool ignoreCase);

        /// <summary>Compares two specified String objects using the specified rules, and
        /// returns an integer that indicates their relative position in the sort order.</summary>
        static int compare(const TString& strA, const TString& strB, const TStringComparison& comparisonType);

        /// <summary>Compares two specified String objects, ignoring or honoring their
        /// case, and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int compare(const TString& strA, const TString& strB, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares two specified String objects using the specified comparison
        /// options and culture-specific information to influence the comparison, and
        /// returns an integer that indicates the relationship of the two strings to
        /// each other in the sort order.</summary>
        static int compare(const TString& strA, const TString& strB, const TCultureInfo& culture, TCompareOptions options);

        /// <summary>Compares substrings of two specified String objects and returns an
        /// integer that indicates their relative position in the sort order.</summary>
        static int compare(const TString& strA, int indexA, const TString& strB, int indexB, int length);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case, and returns an integer that indicates their relative position
        /// in the sort order.</summary>
        static int compare(const TString& strA, int indexA, const TString& strB, int indexB, int length, bool ignoreCase);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// rules, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int compare(const TString& strA, int indexA, const TString& strB, int indexB, int length, const TStringComparison& comparisonType);

        /// <summary>Compares substrings of two specified String objects, ignoring or honoring
        /// their case and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int compare(const TString& strA, int indexA, const TString& strB, int indexB, int length, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares substrings of two specified String objects using the specified
        /// comparison options and culture-specific information to influence the comparison,
        /// and returns an integer that indicates the relationship of the two substrings
        /// to each other in the sort order.</summary>
        static int compare(const TString& strA, int indexA, const TString& strB, int indexB, int length, const TCultureInfo& culture, const TCompareOptions& options);

        /// <summary>Compares two specified String objects by evaluating the numeric values
        /// of the corresponding Char objects in each string.</summary>
        static int compareOrdinal(const TString& strA, const TString& strB);

        /// <summary>Compares substrings of two specified String objects by evaluating
        /// the numeric values of the corresponding Char objects in each substring.</summary>
        static int compareOrdinal(const TString& strA, int indexA, const TString& strB, int indexB, int length);

        /// <summary>Concatenates the elements of a specified TString array.</summary>
        static TString concat(const ITEnumerable<TString>& values);

        /// <summary>Concatenates the members of an ITEnumerable<T> implementation.</summary>
        template <class T>
        static TString concat(const ITEnumerable<T>& values);

        /// <summary>Creates the string representation of a specified object.</summary>
        static TString concat(const TObject& arg0);

        /// <summary>Concatenates the string representations of the elements in a specified Object array.</summary>
        static TString concat(const TArray<TObject>& args);

        /// <summary>Concatenates the elements of a specified String array.</summary>
        static TString concat(const TArray<TString>& values);

        /// <summary>Concatenates the string representations of two specified objects.</summary>
        static TString concat(const TObject& arg0, const TObject& arg1);

        /// <summary>Concatenates two specified instances of String.</summary>
        static TString concat(const TString& str0, const TString& str1);

        /// <summary>Concatenates the string representations of three specified objects.</summary>
        static TString concat(const TObject& arg0, const TObject& arg1, const TObject& arg2);

        /// <summary>Concatenates three specified instances of String.</summary>
        static TString concat(const TString& str0, const TString& str1, const TString& str2);

        /// <summary>Concatenates the string representations of four specified objects and any
        /// objects specified in an optional variable length parameter list.</summary>
        static TString concat(const TObject& arg0, const TObject& arg1, const TObject& arg2, const TObject& arg3);

        /// <summary>Concatenates four specified instances of System.String.</summary>
        static TString concat(const TString& str0, const TString& str1, const TString& str2, const TString& str3);

        /// <summary>Creates a new instance of System.String with the same value as a specified String.</summary>
        static TString copy(const TString& str);

        /// <summary>Determines whether two specified System.String objects have the same value.</summary>
        static bool equals(const TString& strA, const TString& strB);

        /// <summary>Determines whether two specified System.String objects have the same value.
        /// A parameter specifies the culture, case, and sort rules used in the comparison.</summary>
        static bool equals(const TString& strA, const TString& strB, const TStringComparison& comparisonType);

        /// <summary>Replaces one or more format items in a specified string with the string representation
        /// of a specified object.</summary>
        static TString format(const TString& format, const TObject& arg0);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static TString format(const TString& format, const TArray<TObject>& args);

        /// <summary>Replaces the format item in a specified string with the string representation
        /// of a corresponding object in a specified array. A specified parameter supplies
        /// culture-specific formatting information.</summary>
        static TString format(const ITFormatProvider& provider, const TString& format, const TArray<TObject>& args);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of two specified objects.</summary>
        static TString format(const TString& format, const TObject& arg0, const TObject& arg1);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of three specified objects.</summary>
        static TString format(const TString& format, const TObject& arg0, const TObject& arg1, const TObject& arg2);

        /// <summary>Indicates whether the specified string is an empty string.</summary>
        static bool isEmpty(const TString& str);

        /// <summary>Indicates whether a specified string is empty or consists only of
        /// white-space characters.</summary>
        static bool isEmptyOrWhiteSpace(const TString& str);

        /// <summary>Concatenates the members of a constructed ITEnumerable<T>
        /// collection of type String, using the specified separator between each
        /// member.</summary>
        static TString join(const TString& separator, const ITEnumerable<TString>& values);

        /// <summary>Concatenates the members of a collection, using the specified separator between
        /// each member.</summary>
        template<class T>
        static TString join(const TString& separator, const ITEnumerable<T>& values);

        /// <summary>Concatenates the elements of an object array, using the specified separator
        /// between each element.</summary>
        static TString join(const TString& separator, const TArray<TObject>& values);

        /// <summary>Concatenates all the elements of a string array, using the specified separator
        /// between each element.</summary>
        static TString join(const TString& separator, const TArray<TString>& value);

        /// <summary>Concatenates the specified elements of a string array, using the specified
        /// separator between each element.</summary>
        static TString join(const TString& separator, const TArray<TString>& value, int startIndex, int count);

        /// <summary>static create methods to create instance which can't call from other scope </summary>
        static TString create()   {  return TString(""); }
    };

    //!!!!!! typedef TString string;

    /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
    inline TString operator+(const TString& lhs, const TString& rhs) { return lhs.value_ + rhs.value_; }

    inline bool operator<(const TString& lhs, const TString& rhs) { return lhs.value_ < rhs.value_; }

    inline size_t hash_value(const cl::TString& _Keyval) //!!!! Why do we need this?
    {
        return stdext::hash_value(_Keyval.value());
    }

}

namespace std
{
    template<>
    struct hash<cl::TString> : public unary_function<cl::TString, size_t>
    {
        size_t operator()(const cl::TString value) //!!!! Why do we need this?
        {
            return value.getHashCode();
        }
    };
}

#endif // cl_system_TString_hpp
