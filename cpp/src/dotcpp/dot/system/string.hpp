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
    template <class T> class list_impl; template <class T> using list = ptr<list_impl<T>>;
    template <class T> class nullable;
    enum class string_split_options;
    class Char;

    /// Immutable string type.
    ///
    /// The string is encoded internally as UTF-8.
    class DOT_CLASS string_impl : public virtual object_impl, public detail::const_string_base
    {
        typedef string_impl self;
        typedef detail::const_string_base base;
        friend string make_string(const std::string& rhs);
        friend string make_string(const char* rhs);

    public: // CONSTRUCTORS

        /// Creates an empty string.
        string_impl() {}

        /// Create from a single Unicode character.
        string_impl(const Char& value);

        /// Initializes from std::string or string literal.
        ///
        /// This constructor is private. Use make_string(str) function instead.
        string_impl(const std::string& value) : base(value) {}

        /// Create from const char*, null pointer is converted to to empty value.
        string_impl(const char* value) : base(value) {}

        /// Create from a single 8-bit character.
        string_impl(char value) : base(std::to_string(value)) {}

    public: // METHODS

        /// Determines whether this instance and a specified object,
        /// which must also be a string object, have the same value.
        bool equals(object obj) override;

        /// Returns the hash code for this string.
        virtual size_t hash_code() override;

        /// Returns this instance of string; no actual conversion is performed.
        virtual string to_string() override;

        /// Determines whether the end of this
        /// string matches the specified string.
        bool ends_with(const string& value);

        /// Determines whether the beginning of this
        /// string matches the specified string.
        bool starts_with(const string& value);

        /// Retrieves a substring which starts at the specified
        /// character position and has the specified length.
        string substring(int startIndex, int length);

        /// Compares this instance with a specified string object and indicates
        /// whether this instance precedes, follows, or appears in the same position
        /// in the sort order as the specified string.
        int compare_to(const string& strB) const; // TODO - implement

        /// Reports the zero-based index of the first occurrence in this instance of any
        /// character in a specified array of Unicode characters.
        int index_of_any(list<char> anyOf);

        /// Returns a new string in which all the characters in the current instance, beginning
        /// at a specified position and continuing through the last position, have been deleted.
        string remove(int startIndex);

        /// Returns a new string in which a specified number of characters in the current
        /// instance beginning at a specified position have been deleted.
        string remove(int startIndex, int count);

        /// Returns a new string in which all occurrences of a specified string
        /// in the current instance are replaced with another specified string.
        string replace(const string& oldValue, const string& newValue) const; // TODO - implement

        /// Returns a new string in which all occurrences of a specified character
        /// in this instance are replaced with another specified character.
        string replace(const char oldChar, const char newChar) const;

        /// Returns a string array that contains the substrings of the current string
        /// that are delimited by any of the specified 8-bit characters.
        list<string> split(char separator) const;  // TODO - implement

        /// Returns a string array that contains the substrings in
        /// this string that are delimited by any of the specified strings.
        /// A parameter specifies whether to return empty array elements.
        list<string> split(const list<string>& separator, const string_split_options& options) const; // TODO - implement

        /// Indicates whether the argument occurs within this string.
        bool contains(string const& s) const; // TODO - implement

        /// Returns a copy of this string converted to lowercase.
        string to_lower() const; // TODO - implement

        /// Returns a copy of this string converted to uppercase.
        string to_upper() const; // TODO - implement

    public: // OPERATORS

        /// Gets the Char object at a specified position in the current string object.
        Char operator[](int index) const;

        /// Returns a string containing characters from lhs followed by the characters from rhs.
        friend string operator+(const string& lhs, const string& rhs);

        /// Returns a string containing characters from lhs followed by the characters from rhs.
        friend bool operator<(const string& lhs, const string& rhs);

    public: // REFLECTION

        virtual type_t type();
        static type_t typeof();
    };

    /// Pointer to string_impl that has additional constructors compared to ptr(string)
    class DOT_CLASS string : public ptr<string_impl>
    {
        typedef ptr<string_impl> base;

    public: // CONSTANTS

        /// Empty string.
        static string empty;

    public: // CONSTRUCTORS

        /// Create null string.
        string() : base() {}

        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        string(string_impl* p) : base(p) {}

        /// Create from std::string.
        string(const std::string& rhs) : base(new string_impl(rhs)) {}

        /// Create from string literal.
        string(const char* rhs) : base(new string_impl(rhs)) {}

        /// Copy constructor.
        string(const string& rhs) : base(rhs) {}

        /// Supports cast (explicit constructor) from object.
        ///
        /// Error if object does is not a boxed int.
        /// Null object becomes empty nullableInt.
        explicit string(const ptr<object_impl>& rhs) : base(rhs) {}

    public: // STATIC

        /// Replaces format entries in the specified string with the string
        /// representation of objects in the argument array.
        template <typename ...Args>
        static string format(const string& format_string, const Args& ...args);

        /// Indicates whether the specified string is null or an string.Empty string.
        static bool is_null_or_empty(string value);

    public: // OPERATORS

        /// Case sensitive comparison to std::string.
        bool operator==(const std::string& rhs) const { string_impl& impl = base::operator*(); return impl == rhs; }

        /// Case sensitive comparison to std::string.
        bool operator!=(const std::string& rhs) const { return !operator==(rhs); }

        /// Case sensitive comparison to string literal.
        bool operator==(const char* rhs) const { if (rhs == nullptr) return base::operator==(nullptr); string_impl& impl = base::operator*(); return impl == rhs; }

        /// Case sensitive comparison to string literal.
        bool operator!=(const char* rhs) const { return !operator==(rhs); }

        /// Case sensitive comparison to string literal.
        bool operator==(const ptr<string_impl>& rhs) const { return *this == *rhs; }

        /// Case sensitive comparison to string literal.
        bool operator!=(const ptr<string_impl>& rhs) const { return !operator==(rhs); }

        /// Case sensitive comparison to object.
        bool operator==(const object& rhs) const;

        /// Case sensitive comparison to object.
        bool operator!=(const object& rhs) const { return !operator==(rhs); }

    private: // STATIC

        /// Non-template implementation of string.Format.
        static std::string format_impl(fmt::string_view format_str, fmt::format_args args);
    };

    /// Create from std::string or string literal using new
    inline string make_string(const std::string& rhs) { return new string_impl(rhs); }

    /// Create from std::string or string literal using new
    inline string make_string(const char* rhs) { return new string_impl(rhs); }

    /// Returns a string containing characters from lhs followed by the characters from rhs.
    inline string operator+(const string& lhs, const string& rhs) { return make_string(*lhs + *rhs); }

    /// Returns a string containing characters from lhs followed by the characters from rhs.
    inline bool operator<(const string& lhs, const string& rhs) { return *lhs < *rhs; }

    /// Helper class for fmt::format arguments conversion
    template <class T>
    struct format_forward {
        static inline auto convert(const T& t) { return t; }
    };

    /// Helper class for fmt::format arguments conversion
    template<>
    struct format_forward<string> {
        static inline const std::string& convert(const string& s) { return *s; }
    };

    /// Helper class for fmt::format arguments conversion
    template<class T>
    struct format_forward<ptr<T>> {
        static inline std::string convert(const ptr<T>& o) { return *o->to_string(); }
    };

    /// Helper class for fmt::format arguments conversion
    template<class T>
    struct format_forward<nullable<T>> {
        static inline T convert(const nullable<T>& o) { return o.value_or_default(); }
    };

    template<typename ...Args>
    string string::format(const string& format_string, const Args& ...args)
    {
        return format_impl(*format_string, fmt::make_format_args(format_forward<Args>::convert(args)...));
    }
}

namespace std
{
    /// Implements hash struct used by STL unordered_map for string.
    template <>
    struct hash<dot::string> : public hash<dot::ptr<dot::string_impl>>
    {};

    /// Implements equal_to struct used by STL unordered_map for string.
    template <>
    struct equal_to<dot::string> : public equal_to<dot::ptr<dot::string_impl>>
    {};
}
