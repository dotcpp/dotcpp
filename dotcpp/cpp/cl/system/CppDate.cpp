#include <cl\system\CppDate.hpp>

#include <time.h>
namespace cl
{


    

    class CppDateImpl : public CppDate
    {
    private:
        tm * value_;

        /// <summary>Normalize parameter and set value_</summary>
        void normalize(tm notNormedTM)
        {
            time_t normed = mktime(&notNormedTM);
            value_ = localtime(&normed);
        }

    public:

        /// <summary>Create with empty value.</summary>
        CppDateImpl() 
        {
            value_ = new tm();
            *value_ = {0};
        }

        /// <summary>Create from string in ISO format (YYYY-MM-DD).</summary>
        CppDateImpl(cl::CppString value)
        {

            std::istringstream strstream(value.value());
            char delimiter;
            int year;
            int month;
            int day;
            if (strstream >> year >> delimiter >> month >> delimiter >> day)
            {
                tm notNormedTM = {0};
                notNormedTM.tm_year = year - 1900; // Years since 1900 
                notNormedTM.tm_mon = month - 1; //Months sinsce January (0-based)
                notNormedTM.tm_mday = day; // 1-based
                notNormedTM.tm_isdst = -1;
                
                //normalize:
                normalize(notNormedTM);
                
            }
            else throw cl::CppException("date is invalid");
        }

        /// <summary>Constructor from int.</summary>
        CppDateImpl(int year, int month, int day)
        {
            tm notNormedTM = { 0 };
            notNormedTM.tm_year = year - 1900; // Years since 1900 
            notNormedTM.tm_mon = month - 1; //Months sinsce January (0-based)
            notNormedTM.tm_mday = day; // 1-based
            notNormedTM.tm_isdst = -1;

            //normalize:
            normalize(notNormedTM);
        }

        /// <summary>Returns true if the object is empty.</summary>
        virtual bool IsNull() const 
        { 
            tm empty = { 0 };
            return mktime(value_) == mktime(&empty); 
        }

        /// <summary>Convert atomic type to value.</summary>
        virtual CppDate& Value() { return *this; }
    
        /// <summary>Year.</summary>
        virtual int& Year() { return value_->tm_year; }

        /// <summary>Month.</summary>
        virtual int& Month() { return value_->tm_mon; }

        /// <summary>Day.</summary>
        virtual int& Day() { return value_->tm_mday; }

        /// <summary>Add years (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusYears(int years) 
        { 
            tm notNormedTM = *value_;
            notNormedTM.tm_year += years;
            normalize(notNormedTM);
            return CppDate();
        }

        /// <summary>Add month (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusMonths(int months)
        {
            tm notNormedTM = *value_;
            notNormedTM.tm_mon += months;
            normalize(notNormedTM);
            return CppDate();
        }

        /// <summary>Add days (returns result, the object itself remains unchanged).</summary>
        virtual CppDate PlusDays(int days) 
        {
            tm notNormedTM = *value_;
            notNormedTM.tm_mday += days;
            normalize(notNormedTM);
            return CppDate();
        }
    
        /// <summary>Days from the specified date. Error message if zero or negative.</summary>
        virtual int DaysFrom(CppDate fromDate)
        {
            time_t this_time = mktime(value_);
            tm from_date = { 0 };
            from_date.tm_year = fromDate.Year();
            from_date.tm_mon = fromDate.Month();
            from_date.tm_mday = fromDate.Day();
            time_t from_time = mktime(&from_date);

            int secondsInDay = 60 * 60 * 24;
            if (this_time - from_time > 0) return (this_time - from_time) / secondsInDay;
                else throw cl::CppException("CppDate.DaysFrom() function should not be used when the argument date is after or equal this date");
                return 0;
        }

    };


    CppDate::CppDate() : impl_(new CppDateImpl()) {}

    CppDate::CppDate(cl::CppString value) : impl_(new CppDateImpl(value)) {}

    CppDate::CppDate(int year, int month, int day) : impl_(new CppDateImpl(year, month, day)) {}


}