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

#ifndef __cl_system_CppDate_hpp__
#define __cl_system_CppDate_hpp__


#include <cl/system/declare.hpp>
#include <cl/system/CppString.hpp>
#include <cl/system/collections/generic/CppList.hpp>

/*
#include <cl/system/ClObject.hpp>
#include <cl/system/IClvalue.hpp>
#include <cl/system/collections/ClFieldInfo.hpp>
#include <cl/system/collections/ClFieldType.hpp>
*/


namespace cl
{

    class CppDate
    {
    private:

        std::shared_ptr<CppDate> impl_;

    public: //  CONSTANTS

        /// <summary>Empty value.</summary>
        static const CppDate Empty;

    public: //  CONSTRUCTORS

        /// <summary>Create with empty value.</summary>
        CppDate();

        /// <summary>Create from string in ISO format (YYYY-MM-DD).</summary>
        CppDate(cl::CppString value);

        /// <summary>Constructor from int.</summary>
        CppDate(int year, int month, int day);


        /// <summary>Constructor from variant.</summary>
        template <typename Type>
        CppDate(Type value)
        {
            *this = value.ToDate();
        }


    public: //  METHODS

        /// <summary>Returns true if the object is empty.</summary>
        virtual bool isNull() const { return impl_->isNull(); }


        /// <summary>Convert atomic type to value.</summary>
        virtual CppDate& value() const { return *(impl_.get()); }

        /// <summary>Year.</summary>
        virtual int year() const { return impl_->year(); }

        /// <summary>Month.</summary>
        virtual int month() const { return impl_->month(); }

        /// <summary>Day.</summary>
        virtual int day() const { return impl_->day(); }

        /// <summary>Add years (returns result, the object itself remains unchanged).</summary>
        virtual CppDate plusYears(int years) const { return impl_->plusYears(years); }

        /// <summary>Add month (returns result, the object itself remains unchanged).</summary>
        virtual CppDate plusMonths(int months) const { return impl_->plusMonths(months); }

        /// <summary>Add days (returns result, the object itself remains unchanged).</summary>
        virtual CppDate plusDays(int days) const { return impl_->plusDays(days); }

        /// <summary>Days from the specified date. Error message if zero or negative.</summary>
        virtual int daysFrom(CppDate fromDate) const { return impl_->daysFrom(fromDate); }

        /// <summary>Convert to string.</summary>
        virtual CppString toString() const { return impl_->toString(); }

        /// <summary>Convert to int using Excel format. Empty date is converted to empty int.</summary>
        virtual int toExcelInt() const { return impl_->toExcelInt(); }

        /// <summary>Convert to int using ISO format (YYYYMMDD). Empty date is converted to empty int.</summary>
        virtual int toIsoInt() const { return impl_->toIsoInt(); }

        /// <summary>Convert from int using ISO format (YYYYMMDD). Empty int is converted to empty date.</summary>
        static CppDate fromIsoInt(int value)
        {
            int year = value / 10000;
            int remainder = value - 10000 * year;
            int month = remainder / 100;
            int day = remainder - 100 * month;

            return CppDate(year, month, day);
        }

        /// <summary>Hash code.</summary>
        virtual int getHashCode() const { return impl_->getHashCode(); }

        /// <summary>Compare the current instance with another of the same type</summary>
        template<typename Type>
        int compareTo(Type other) const
        {
            if (!other) return isNull() ? 0 : 1;
            else throw cl::CppException("Attempting to compare ClDate with a different data type");
        }

        /// <summary>Compare the current instance with another of the same type.
        /// Null is considered to be less than any other value.</summary>
        virtual int compareTo(CppDate other) const { return impl_->compareTo(other); }

        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        template<typename Type>
        bool equals(Type other) const
        {
            return false; // Method always returns false because Type != CppData
        }

        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        virtual bool equals(CppDate other) const { return compareTo(other) == 0; }

        /// <summary>Equality operator. Returns true if arguments are equal
        /// or both empty and false if only one of the arguments is empty.</summary>
        virtual bool operator ==(CppDate rhs) const { return equals(rhs); }

        /// <summary>Inequality operator. Returns false if arguments are equal
        /// or both empty and true if only one of the arguments is empty.</summary>
        virtual bool operator !=(CppDate rhs) const { return !(equals(rhs)); }

        /// <summary>Operator less. Error message if either of the arguments is empty.</summary>
        virtual bool operator <(CppDate rhs) const { return compareTo(rhs) == -1; }

        /// <summary>Operator more. Error message if either of the arguments is empty.</summary>
        virtual bool operator >(CppDate rhs) const { return compareTo(rhs) == 1; }

        /// <summary>Parse string in ISO format (YYYY-MM-DD).</summary>
        static CppDate parse(CppString s) { return CppDate(s); }

    private:

        /// <summary>Error message if the date is empty.</summary>
        void checkSet() const { if (isNull()) throw new cl::CppException("ClError.Core.NotSet"); }

        /// <summary>Error message if the argument is not a valid date in ISO format (YYYYMMDD).</summary>
        virtual void checkValid() const { impl_->checkValid(); }

    };


    class CppDateEx
    {

    public:
        static CppDate max(CppList<CppDate> src)
        {
            if (src.count() == 0) throw cl::CppException("ClError.Core.ZeroSize");
            CppDate result;
            for each(CppDate value in src)
            {
                if (value.isNull()) throw cl::CppException("ClError.Core.NotSet");
                if (result.isNull() || result < value) result = value;
            }
            return result;
        }

        static CppDate min(CppList<CppDate> src)
        {
            if (src.count() == 0) throw cl::CppException("ClError.Core.ZeroSize");
            CppDate result;
            for each(CppDate value in src)
            {
                if (value.isNull()) throw cl::CppException("ClError.Core.NotSet");
                if (result.isNull() || result > value) result = value;
            }
            return result;
        }
    };
}


#endif  // __cl_system_CppDate_hpp__