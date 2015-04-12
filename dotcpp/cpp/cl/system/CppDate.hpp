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
#include <cl/system/IClValue.hpp>
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
        //static const CppDate Empty;

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
        virtual bool IsNull() const { return impl_->IsNull(); }


        /// <summary>Convert atomic type to value.</summary>
        virtual CppDate& Value() const { return *(impl_.get()); }   

        /// <summary>Year.</summary>
        virtual int& Year() { return impl_->Year(); }

        /// <summary>Month.</summary>
        virtual int& Month() { return impl_->Month(); }
        
        /// <summary>Day.</summary>
        virtual int& Day() { return impl_->Day(); }

        /// <summary>Add years (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusYears(int years) { return impl_->PlusYears(years); }

        /// <summary>Add month (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusMonths(int months) { return impl_->PlusMonths(months); }

        /// <summary>Add days (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusDays(int days) { return impl_->PlusDays(days); }

        /// <summary>Days from the specified date. Error message if zero or negative.</summary>
        virtual int DaysFrom(CppDate fromDate) { return impl_->DaysFrom(fromDate); }

        /// <summary>Convert to string.</summary>
        virtual CppString ToString() { return impl_->ToString(); }

        /// <summary>Convert to int using Excel format. Empty date is converted to empty int.</summary>
        virtual int ToExcelInt() const { return impl_->ToExcelInt(); }

        /// <summary>Convert to int using ISO format (YYYYMMDD). Empty date is converted to empty int.</summary>
        virtual int ToIsoInt() const { return impl_->ToIsoInt(); }

        /// <summary>Convert from int using ISO format (YYYYMMDD). Empty int is converted to empty date.</summary>
        static CppDate FromIsoInt();

        /// <summary>Hash code.</summary>
        virtual int GetHashCode() { return impl_->GetHashCode(); }

        /// <summary>Compare the current instance with another of the same type</summary>
        template<typename Type>
        int CompareTo(Type other) 
        { 
            if (!other) return IsNull() ? 0 : 1;
            else throw cl::CppException("Attempting to compare ClDate with a different data type");
        }

        /// <summary>Compare the current instance with another of the same type.
        /// Null is considered to be less than any other value.</summary>
        virtual int CompareTo(CppDate other) { return impl_->CompareTo(other); }

        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        template<typename Type>
        bool Equals(Type other)
        {
            return false; // Method always returns false because Type != CppData
        }
        
        /// <summary>Checks equality using tolerance-based comparison without causing an exception even if the object is not set.
        /// Two empty objects are considered equal.</summary>
        virtual bool Equals(CppDate other) { return impl_->Equals(other); }

        /// <summary>Equality operator. Returns true if arguments are equal
        /// or both empty and false if only one of the arguments is empty.</summary>
        virtual bool operator ==(CppDate rhs) { return this->Value() == rhs.Value(); }
        
        /// <summary>Inequality operator. Returns false if arguments are equal
        /// or both empty and true if only one of the arguments is empty.</summary>
        virtual bool operator !=(CppDate rhs) { return !(this->Value() == rhs.Value()); }

        /// <summary>Operator less. Error message if either of the arguments is empty.</summary>
        virtual bool operator <(CppDate rhs) { return this->Value() < rhs.Value(); }

        /// <summary>Operator more. Error message if either of the arguments is empty.</summary>
        virtual bool operator >(CppDate rhs) { return this->Value() > rhs.Value(); }

        /// <summary>Parse string in ISO format (YYYY-MM-DD).</summary>
        static CppDate Parse(CppString s) { return CppDate(s); }
        
        private:
        
        /// <summary>Error message if the date is empty.</summary>
        void CheckSet() { if (IsNull()) throw new cl::CppException("ClError.Core.NotSet"); }

        /// <summary>Error message if the argument is not a valid date in ISO format (YYYYMMDD).</summary>
        virtual void CheckValid() { impl_->CheckValid(); }
    
    };


    class CppDateEx
    {
        
    public:
        static CppDate Max(CppList<CppDate> src)
        {
            if (src.getCount() == 0) throw cl::CppException("ClError.Core.ZeroSize");
            CppDate result;
            for each(CppDate value in src)
            {
                if (value.IsNull()) throw cl::CppException("ClError.Core.NotSet");
                if (result.IsNull() || result < value) result = value;
            }
            return result;
        }

        static CppDate Min(CppList<CppDate> src)
        {
            if (src.getCount() == 0) throw cl::CppException("ClError.Core.ZeroSize");
            CppDate result;
            for each(CppDate value in src)
            {
                if (value.IsNull()) throw cl::CppException("ClError.Core.NotSet");
                if (result.IsNull() || result > value) result = value;
            }
            return result;
        }
    };
}


#endif  // __cl_system_CppDate_hpp__