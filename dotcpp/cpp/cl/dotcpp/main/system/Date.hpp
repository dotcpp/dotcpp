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
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include "Exception.hpp"

namespace cl
{
    class CL_DOTCPP_MAIN LocalDate
    {
    private:

        std::shared_ptr<LocalDate> impl_; //!! Should it be pointer to self or a separate Impl class?

    public: //  CONSTANTS

        /// <summary>Empty value.</summary>
        static const LocalDate Empty;

    public: //  CONSTRUCTORS

        /// <summary>Create with empty value.</summary>
        LocalDate();

        /// <summary>Create from string in ISO format (YYYY-MM-DD).</summary>
        LocalDate(cl::String value);

        /// <summary>Constructor from int.</summary>
        LocalDate(int year, int month, int day);


        /// <summary>Constructor from variant.</summary>
        template <typename Type>
        LocalDate(Type value)
        {
            *this = value.ToDate();
        }

    public: //  METHODS

        /// <summary>Returns true if the object is empty.</summary>
        virtual bool isNull() const { return impl_->isNull(); }

        /// <summary>Convert atomic type to value.</summary>
        virtual LocalDate& value() const { return *(impl_.get()); }

        /// <summary>Year.</summary>
        virtual int year() const { return impl_->year(); }

        /// <summary>Month.</summary>
        virtual int month() const { return impl_->month(); }

        /// <summary>Day.</summary>
        virtual int day() const { return impl_->day(); }

        /// <summary>Add years (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusYears(int years) const { return impl_->plusYears(years); }

        /// <summary>Add month (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusMonths(int months) const { return impl_->plusMonths(months); }

        /// <summary>Add days (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusDays(int days) const { return impl_->plusDays(days); }

        /// <summary>Days from the specified date. Error message if zero or negative.</summary>
        virtual int daysFrom(LocalDate fromDate) const { return impl_->daysFrom(fromDate); }

        /// <summary>Convert to string.</summary>
        virtual String ToString() const { return impl_->ToString(); }

        /// <summary>Convert to int using Excel format. Empty date is converted to empty int.</summary>
        virtual int toExcelInt() const { return impl_->toExcelInt(); }

        /// <summary>Convert to int using ISO format (YYYYMMDD). Empty date is converted to empty int.</summary>
        virtual int toIsoInt() const { return impl_->toIsoInt(); }

        /// <summary>Convert from int using ISO format (YYYYMMDD). Empty int is converted to empty date.</summary>
        static LocalDate fromIsoInt(int value)
        {
            int year = value / 10000;
            int remainder = value - 10000 * year;
            int month = remainder / 100;
            int day = remainder - 100 * month;

            return LocalDate(year, month, day);
        }

        /// <summary>Hash code.</summary>
        virtual int getHashCode() const { return impl_->getHashCode(); }

        /// <summary>Compare the current instance with another of the same type</summary>
        template<typename Type>
        int compareTo(Type other) const
        {
            if (!other) return isNull() ? 0 : 1;
            else throw std::runtime_error("Attempting to compare LocalDate with a different data type");
        }

        /// <summary>Compare the current instance with another of the same type.
        /// Null is considered to be less than any other value.</summary>
        virtual int compareTo(LocalDate other) const { return impl_->compareTo(other); }

        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        template<typename Type>
        bool equals(Type other) const
        {
            return false; // Method always returns false because Type != TData
        }

        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        virtual bool equals(LocalDate other) const { return compareTo(other) == 0; }

        /// <summary>Equality operator. Returns true if arguments are equal
        /// or both empty and false if only one of the arguments is empty.</summary>
        virtual bool operator ==(LocalDate rhs) const { return equals(rhs); }

        /// <summary>Inequality operator. Returns false if arguments are equal
        /// or both empty and true if only one of the arguments is empty.</summary>
        virtual bool operator !=(LocalDate rhs) const { return !(equals(rhs)); }

        /// <summary>Operator less. Error message if either of the arguments is empty.</summary>
        virtual bool operator <(LocalDate rhs) const { return compareTo(rhs) == -1; }

        /// <summary>Operator more. Error message if either of the arguments is empty.</summary>
        virtual bool operator >(LocalDate rhs) const { return compareTo(rhs) == 1; }

        /// <summary>Parse string in ISO format (YYYY-MM-DD).</summary>
        static LocalDate parse(String s) { return LocalDate(s); }

    private:

        /// <summary>Error message if the date is empty.</summary>
        void checkSet() const { if (isNull()) throw std::runtime_error("TError.Core.NotSet"); }

        /// <summary>Error message if the argument is not a valid date in ISO format (YYYYMMDD).</summary>
        virtual void checkValid() const { impl_->checkValid(); }
    };

    class CL_DOTCPP_MAIN LocalDateEx // TODO Refactor for C++
    {
    public:
        static LocalDate Max(List<LocalDate> src)
        {
            if (src->Count() == 0) throw std::exception("Cannot get max value of a zero size List<Date>.");
            LocalDate result;
            for (LocalDate value : src)
            {
                if (value.isNull()) throw std::exception("Empty date encountered when taking max value of List<Date>.");
                if (result.isNull() || result < value) result = value;
            }
            return result;
        }

        static LocalDate min(List<LocalDate> src)
        {
            if (src->Count() == 0) throw std::exception("Cannot get min value of a zero size List<Date>.");
            LocalDate result;
            for (LocalDate value : src)
            {
                if (value.isNull()) throw std::exception("Empty date encountered when taking min value of List<Date>.");
                if (result.isNull() || result > value) result = value;
            }
            return result;
        }
    };
}
