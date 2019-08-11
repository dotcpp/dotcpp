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
#include <dot/system/object_impl.hpp>

namespace dot
{
    /*
    /// enum_value is an immutable struct representing a date within the calendar,
    /// with no reference to a particular time zone or time of day.
    template <class T>
    class enum_value
    {
        typedef enum_value self;
        typedef T value;

    public: // CONSTRUCTORS

        /// In C\# local date is a struct, and as all structs it has default constructor
        /// that initializes all backing variables to 0. This means that default
        /// constructed value corresponds to 0001-01-01. As Boost date_time library
        /// does not accept the date 0001-01-01, we will instead use the Unix epoch
        /// 1970-01-01 as default constructed value.
        enum_value() { value_ = 0; }

        /// Constructs an instance for the given year, month and day in the ISO calendar.
        enum_value(T value) { value_ = value; }

        /// Copy constructor.
        enum_value(const enum_value& other) { value_ = other.value_; }

        /// Create from object.
        enum_value(object const& rhs) { value_ = (T)(int)rhs; }

    public:

        /// Indicates whether this date is earlier, later or the same as another one.
        int compare_to(const enum_value& other) const;

        /// Compares two enum_value values for equality. This requires that the dates be the same, within the same calendar.
        bool equals(const enum_value& other) const { return value_ == rhs.value_; }

        /// String that represents the current object.
        string to_string() const { return string::empty; }

    public:

        /// Compares two enum_value values for equality. This requires that the dates be the same, within the same calendar.
        bool operator==(const enum_value& other) const { return value_ == rhs.value_; }

        /// Compares two enum_value values for inequality.
        bool operator!=(const enum_value& other) const { return value_ != rhs.value_; }

        self& operator=(T other) { value_ = other; return *this; }
        self& operator=(int rhs) { value_ = rhs; return *this; }
        self& operator=(const self& other) { value_ = other.value_; return *this; }

        operator int() const { return value_; }
        operator T() const { return value_; }

        virtual dot::type_t type() { return typeof(); }
        static dot::type_t typeof()
        {
            static dot::type_t type = []()->dot::type_t
            {
                dot::type_t type = dot::make_type_builder<self>("dot", "enum_value")
                    ->is_enum()
                  //  ->with_constructor(&enum_impl<self<T>>::make_self {})
                    ->with_base<enum_base>()
                    ->build();
                return type;
            }();
            return type;
        }

    private:
        T value_;
    };
    */

    //class object;

    /// Wrapper around double to make it convertible to object (boxing).
    template <class T>
    class enum_impl : public virtual object_impl
    {
        friend object;
        T value_;

    public: // CONSTRUCTORS

        /// Create from value (box).
        enum_impl(T value) : value_(value) {}

        /// Create from object (first step in two-step conversion during unboxing).
        enum_impl(object rhs) : value_(ptr<enum_impl<T>>(rhs)->value_) { }

    public: // METHODS

        /// Returns enum value
        T value() { return value_; };

        /// Returns a value indicating whether this instance is equal to a specified object.
        bool equals(object obj) override { return true; } // TODO - fix

        /// Returns the hash code for this instance.
        virtual size_t hash_code() override { return 0; } // TODO - fix

        /// Converts the numeric value of this instance to its equivalent string representation.
        virtual string to_string() override { return string::empty; } // TODO - fix

    public: // OPERATORS

        /// Convert to enum value
        operator T() const { return value_; }

    public: // REFLECTION

        static type_t typeof() { return nullptr; } // TODO - fix
        virtual type_t type() override { return nullptr; } // TODO - fix
    };
}
