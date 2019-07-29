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

#pragma once

#include <dot/declare.hpp>
#include <fmt/core.h>
#include <dot/detail/const_string_base.hpp>
#include <dot/system/ptr.hpp>
#include <dot/system/Char.hpp>

namespace dot
{
    class string_impl; class string;
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;
    template <class T> class Nullable;
    enum class string_split_options;
    class Char;
    class Comparer;
    class stringComparer;

    /// <summary>
    /// Immutable string type similar to string.
    ///
    /// The string is encoded internally as UTF-8 instead of UTF-16 used by C# string.
    /// </summary>
    class DOT_CLASS string_impl : public virtual object_impl, public detail::const_string_base
    {
        typedef string_impl self;
        typedef detail::const_string_base base;
        friend string make_string(const std::string& rhs);
        friend string make_string(const char* rhs);

    public: // PROPERTIES

        /// <summary>Gets the number of characters in the current string object.</summary>
        DOT_GET(int, Length, { return this->GetLength(); })

    public: // CONSTRUCTORS

        /// <summary>Creates an empty string.</summary>
        string_impl() {}

        /// <summary>Create from a single Unicode character.</summary>
        string_impl(const Char& value);

        /// <summary>
        /// Initializes from std::string or string literal.
        ///
        /// This constructor is private. Use make_string(str) function instead.
        /// </summary>
        string_impl(const std::string& value) : base(value) {}

        /// <summary>Create from const char*, null pointer is converted to to empty value.</summary>
        string_impl(const char* value) : base(value) {}

        /// <summary>Create from a single 8-bit character.</summary>
        string_impl(char value) : base(std::to_string(value)) {}

    public: // METHODS

        /// <summary>Returns the number of 8-bit characters, not the number of Unicode characters.
        /// This number may be different from the number of Unicode characters because each
        /// Unicode character might be represented by more than one 8-bit character.</summary>
        int byteCount() const;

    public: // METHODS

        /// <summary>Determines whether this instance and a specified object,
        /// which must also be a string object, have the same value.</summary>
        virtual bool Equals(object obj) override;

        /// <summary>Returns the hash code for this string.</summary>
        virtual size_t GetHashCode() override;

        /// <summary>Returns this instance of string; no actual conversion is performed.</summary>
        virtual string to_string() override;

        /// <summary>Determines whether the end of this
        /// string matches the specified string.</summary>
        bool EndsWith(const string& value);

        /// <summary>Determines whether the beginning of this
        /// string matches the specified string.</summary>
        bool StartsWith(const string& value);

        /// <summary>Retrieves a substring which starts at the specified
        /// character position and has the specified length.</summary>
        string Substring(int startIndex, int length);

        /// <summary>Gets the number of characters in the current string.
        /// Note that for Unicode this is not the same as the number of bytes.</summary>
        int GetLength();

        /// <summary>Compares this instance with a specified string object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified string.</summary>
        int compareTo(const string& strB) const;

        /// <summary>Reports the zero-based index of the first occurrence in this instance of any
        /// character in a specified array of Unicode characters.</summary>
        int IndexOfAny(Array1D<char> anyOf);

        /// <summary>Returns a new string in which all the characters in the current instance, beginning
        /// at a specified position and continuing through the last position, have been deleted.</summary>
        string Remove(int startIndex);

        /// <summary>Returns a new string in which a specified number of characters in the current
        /// instance beginning at a specified position have been deleted.</summary>
        string Remove(int startIndex, int count);

        /// <summary>Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.</summary>
        string Replace(const string& oldValue, const string& newValue) const;

        /// <summary>Returns a new string in which all occurrences of a specified character
        /// in this instance are replaced with another specified character.</summary>
        string Replace(const char oldChar, const char newChar) const;

        /// <summary>Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.</summary>
        Array1D<string> Split(char separator) const;

        /// <summary>Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.
        /// A parameter specifies whether to return empty array elements.</summary>
        Array1D<string> Split(const Array1D<string>& separator, const string_split_options& options) const;

        ///<summary>Indicates whether the argument occurs within this string.</summary>
        bool Contains(string const& s) const;

        ///<summary>Returns a copy of this string converted to lowercase.</summary>
        string ToLower() const;

        ///<summary>Returns a copy of this string object converted to lowercase using the casing rules of the invariant culture.</summary>
        string ToLowerInvariant() const;

        ///<summary>Returns a copy of this string converted to uppercase.</summary>
        string ToUpper() const;

        ///<summary>Returns a copy of this string object converted to uppercase using the casing rules of the invariant culture.</summary>
        string ToUpperInvariant() const;

    public: // OPERATORS

        /// <summary>Gets the Char object at a specified position in the current string object.</summary>
        Char operator[](int index) const;

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend string operator+(const string& lhs, const string& rhs);

        /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
        friend bool operator<(const string& lhs, const string& rhs);

    public: // REFLECTION

        virtual Type GetType();
        static Type typeof();

    public: // STATIC

        /* TODO

        /// <summary>Compares two specified string objects and returns an integer that
        /// indicates their relative position in the sort order.</summary>
        static int Compare(const string& strA, const string& strB);

        /// <summary>Compares two specified string objects, ignoring or honoring their
        /// case, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const string& strA, const string& strB, bool ignoreCase);

        /// <summary>Compares two specified string objects using the specified rules, and
        /// returns an integer that indicates their relative position in the sort order.</summary>
        static int Compare(const string& strA, const string& strB, const stringComparison& comparisonType);

        /// <summary>Compares two specified string objects, ignoring or honoring their
        /// case, and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const string& strA, const string& strB, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares two specified string objects using the specified comparison
        /// options and culture-specific information to influence the comparison, and
        /// returns an integer that indicates the relationship of the two strings to
        /// each other in the sort order.</summary>
        static int Compare(const string& strA, const string& strB, const TCultureInfo& culture, TCompareOptions options);

        /// <summary>Compares substrings of two specified string objects and returns an
        /// integer that indicates their relative position in the sort order.</summary>
        static int Compare(const string& strA, int indexA, const string& strB, int indexB, int length);

        /// <summary>Compares substrings of two specified string objects, ignoring or honoring
        /// their case, and returns an integer that indicates their relative position
        /// in the sort order.</summary>
        static int Compare(const string& strA, int indexA, const string& strB, int indexB, int length, bool ignoreCase);

        /// <summary>Compares substrings of two specified string objects using the specified
        /// rules, and returns an integer that indicates their relative position in the
        /// sort order.</summary>
        static int Compare(const string& strA, int indexA, const string& strB, int indexB, int length, const stringComparison& comparisonType);

        /// <summary>Compares substrings of two specified string objects, ignoring or honoring
        /// their case and using culture-specific information to influence the comparison,
        /// and returns an integer that indicates their relative position in the sort
        /// order.</summary>
        static int Compare(const string& strA, int indexA, const string& strB, int indexB, int length, bool ignoreCase, const TCultureInfo& culture);

        /// <summary>Compares substrings of two specified string objects using the specified
        /// comparison options and culture-specific information to influence the comparison,
        /// and returns an integer that indicates the relationship of the two substrings
        /// to each other in the sort order.</summary>
        static int Compare(const string& strA, int indexA, const string& strB, int indexB, int length, const TCultureInfo& culture, const TCompareOptions& options);

        /// <summary>Compares two specified string objects by evaluating the numeric values
        /// of the corresponding Char objects in each string.</summary>
        static int CompareOrdinal(const string& strA, const string& strB);

        /// <summary>Compares substrings of two specified string objects by evaluating
        /// the numeric values of the corresponding Char objects in each substring.</summary>
        static int CompareOrdinal(const string& strA, int indexA, const string& strB, int indexB, int length);

        /// <summary>Concatenates the elements of a specified string array.</summary>
        static string Concat(const IEnumerable<string>& values);

        /// <summary>Concatenates the members of an IEnumerable<T> implementation.</summary>
        template <class T>
        static string Concat(const IEnumerable<T>& values);

        /// <summary>Creates the string representation of a specified object.</summary>
        static string Concat(const object& arg0);

        /// <summary>Concatenates the string representations of the elements in a specified object array.</summary>
        static string Concat(const Array1D<object>& args);

        /// <summary>Concatenates the elements of a specified string array.</summary>
        static string Concat(const Array1D<string>& values);

        /// <summary>Concatenates the string representations of two specified objects.</summary>
        static string Concat(const object& arg0, const object& arg1);

        /// <summary>Concatenates two specified instances of string.</summary>
        static string Concat(const string& str0, const string& str1);

        /// <summary>Concatenates the string representations of three specified objects.</summary>
        static string Concat(const object& arg0, const object& arg1, const object& arg2);

        /// <summary>Concatenates three specified instances of string.</summary>
        static string Concat(const string& str0, const string& str1, const string& str2);

        /// <summary>Concatenates the string representations of four specified objects and any
        /// objects specified in an optional variable length parameter list.</summary>
        static string Concat(const object& arg0, const object& arg1, const object& arg2, const object& arg3);

        /// <summary>Concatenates four specified instances of string.</summary>
        static string Concat(const string& str0, const string& str1, const string& str2, const string& str3);

        /// <summary>Creates a new instance of string with the same value as a specified string.</summary>
        static string copy(const string& str);

        /// <summary>Determines whether two specified string objects have the same value.</summary>
        static bool equals(const string& strA, const string& strB);

        /// <summary>Determines whether two specified string objects have the same value.
        /// A parameter specifies the culture, case, and sort rules used in the comparison.</summary>
        static bool equals(const string& strA, const string& strB, const stringComparison& comparisonType);

        /// <summary>Replaces one or more format items in a specified string with the string representation
        /// of a specified object.</summary>
        static string Format(const string& format, const object& arg0);

        /// <summary>Replaces the format item (e.g. {0}, {1}, etc.) in a specified string
        /// with the string representation of a corresponding object in a specified array.</summary>
        static string Format(const string& format, const Array1D<object>& args);

        /// <summary>Replaces the format item in a specified string with the string representation
        /// of a corresponding object in a specified array. A specified parameter supplies
        /// culture-specific formatting information.</summary>
        static string Format(const ITFormatProvider& provider, const string& format, const Array1D<object>& args);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of two specified objects.</summary>
        static string Format(const string& format, const object& arg0, const object& arg1);

        /// <summary>Replaces the format items in a specified string with the string representation
        /// of three specified objects.</summary>
        static string Format(const string& format, const object& arg0, const object& arg1, const object& arg2);

        /// <summary>Indicates whether the specified string is null or empty.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrEmpty(const string& str);

        /// <summary>Indicates whether a specified string is null,
        /// empty, or consists only of white-space characters.
        /// Note that null string and empty string are not the same.</summary>
        static bool IsNullOrWhiteSpace(const string& str);

        /// <summary>Concatenates the members of a constructed IEnumerable<T>
        /// collection of type string, using the specified separator between each
        /// member.</summary>
        static string Join(const string& separator, const IEnumerable<string>& values);

        /// <summary>Concatenates the members of a collection, using the specified separator between
        /// each member.</summary>
        template<class T>
        static string Join(const string& separator, const IEnumerable<T>& values);

        /// <summary>Concatenates the elements of an object array, using the specified separator
        /// between each element.</summary>
        static string Join(const string& separator, const Array1D<object>& values);

        /// <summary>Concatenates all the elements of a string array, using the specified separator
        /// between each element.</summary>
        static string Join(const string& separator, const Array1D<string>& value);

        /// <summary>Concatenates the specified elements of a string array, using the specified
        /// separator between each element.</summary>
        static string Join(const string& separator, const Array1D<string>& value, int startIndex, int count);

        */
    };

    /// <summary>
    /// Pointer to string_impl that has additional constructors compared to ptr(string)
    /// </summary>
    class DOT_CLASS string : public ptr<string_impl>
    {
        typedef ptr<string_impl> base;

    public: // CONSTANTS

        /// <summary>Empty string.</summary>
        static string Empty;

    public: // CONSTRUCTORS

        /// <summary>Create null string.</summary>
        string() : base() {}

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        /// </summary>
        string(string_impl* p) : base(p) {}

        /// <summary>
        /// Create from std::string.
        /// </summary>
        string(const std::string& rhs) : base(new string_impl(rhs)) {}

        /// <summary>
        /// Create from string literal.
        /// </summary>
        string(const char* rhs) : base(new string_impl(rhs)) {}

        /// <summary>
        /// Copy constructor.
        /// </summary>
        string(const string& rhs) : base(rhs) {}

        /// <summary>
        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed int.
        /// Null object becomes empty NullableInt.
        /// </summary>
        explicit string(const ptr<object_impl>& rhs) : base(rhs) {}

    public: // STATIC

        /// <summary>
        /// Replaces format entries in the specified string with the string
        /// representation of objects in the argument array.
        /// </summary>
        template <typename ...Args>
        static string Format(const string& format, const Args& ...args);

        /// <summary>Indicates whether the specified string is null or an string.Empty string.</summary>
        static bool IsNullOrEmpty(string value);

    public: // OPERATORS

        /// <summary>Case sensitive comparison to std::string.</summary>
        bool operator==(const std::string& rhs) const { string_impl& impl = base::operator*(); return impl == rhs; }

        /// <summary>Case sensitive comparison to std::string.</summary>
        bool operator!=(const std::string& rhs) const { return !operator==(rhs); }

        /// <summary>Case sensitive comparison to string literal.</summary>
        bool operator==(const char* rhs) const { if (rhs == nullptr) return base::operator==(nullptr); string_impl& impl = base::operator*(); return impl == rhs; }

        /// <summary>Case sensitive comparison to string literal.</summary>
        bool operator!=(const char* rhs) const { return !operator==(rhs); }

        /// <summary>Case sensitive comparison to string literal.</summary>
        bool operator==(const ptr<string_impl>& rhs) const { return *this == *rhs; }

        /// <summary>Case sensitive comparison to string literal.</summary>
        bool operator!=(const ptr<string_impl>& rhs) const { return !operator==(rhs); }

        /// <summary>Case sensitive comparison to object.</summary>
        bool operator==(const object& rhs) const;

        /// <summary>Case sensitive comparison to object.</summary>
        bool operator!=(const object& rhs) const { return !operator==(rhs); }

    private: // STATIC

        /// <summary>Non-template implementation of string.Format.</summary>
        static std::string format_impl(fmt::string_view format_str, fmt::format_args args);
    };

    /// <summary>
    /// Create from std::string or string literal using new
    /// </summary>
    inline string make_string(const std::string& rhs) { return new string_impl(rhs); }

    /// <summary>
    /// Create from std::string or string literal using new
    /// </summary>
    inline string make_string(const char* rhs) { return new string_impl(rhs); }

    /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
    inline string operator+(const string& lhs, const string& rhs) { return make_string(*lhs + *rhs); }

    /// <summary>Returns a string containing characters from lhs followed by the characters from rhs.</summary>
    inline bool operator<(const string& lhs, const string& rhs) { return *lhs < *rhs; }

    /// <summary>Helper class for fmt::format arguments conversion</summary>
    template <class T>
    struct format_forward {

        static inline auto convert_impl(const T& t, std::true_type)
        {
	        return format_forward<typename T::value_type>::convert(t.operator typename T::value_type()); 
        }
        static inline const T& convert_impl(const T& t, std::false_type) { return t; }

        static inline auto convert(const T& t) { return convert_impl(t, typename std::is_base_of<detail::decl_get, T>::type() ); }
    };

    /// <summary>Helper class for fmt::format arguments conversion</summary>
    template<class T>
    struct format_forward<detail::auto_get<T>> {
        static inline std::string convert(const T& o) { return format_forward<T>::convert(o); }
    };

    /// <summary>Helper class for fmt::format arguments conversion</summary>
    template<>
    struct format_forward<string> {
        static inline const std::string& convert(const string& s) { return *s; }
    };

    /// <summary>Helper class for fmt::format arguments conversion</summary>
    template<class T>
    struct format_forward<ptr<T>> {
        static inline std::string convert(const ptr<T>& o) { return *o->to_string(); }
    };

    /// <summary>Helper class for fmt::format arguments conversion</summary>
    template<class T>
    struct format_forward<Nullable<T>> {
        static inline T convert(const Nullable<T>& o) { return o.GetValueOrDefault(); }
    };

    template<typename ...Args>
    string string::Format(const string& format, const Args& ...args)
    {
        return format_impl(*format, fmt::make_format_args(format_forward<Args>::convert(args)...));
    }
}

namespace std
{
    /// <summary>Implements hash struct used by STL unordered_map for string.</summary>
    template <>
    struct hash<dot::string> : public hash<dot::ptr<dot::string_impl>>
    {};

    /// <summary>Implements equal_to struct used by STL unordered_map for string.</summary>
    template <>
    struct equal_to<dot::string> : public equal_to<dot::ptr<dot::string_impl>>
    {};
}
