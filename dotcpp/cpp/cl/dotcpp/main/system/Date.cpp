#include <math.h>
#include <time.h>

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/Date.hpp>

namespace cl
{
    class LocalDateImpl : public LocalDate
    {
    private:
        struct tm * value_;

        /// <summary>Normalize parameter and set value_</summary>
        tm normalize(tm notNormedTM) const
        {
            time_t normed = mktime(&notNormedTM);
            tm normedTM = { 0 };
            gmtime_s(&normedTM, &normed);
            return normedTM;
        }

    public:

        /// <summary>Create with empty value.</summary>
        LocalDateImpl()
        {
            value_ = new tm();
            *value_ = { 0 };
        }

        /// <summary>Create from string in ISO format (YYYY-MM-DD).</summary>
        LocalDateImpl(cl::String value)
        {

            std::istringstream strstream(value.value());
            char delimiter;
            int year;
            int month;
            int day;
            if (strstream >> year >> delimiter >> month >> delimiter >> day)
            {
                tm notNormedTM = { 0 };
                notNormedTM.tm_year = year - 1900; // Years since 1900
                notNormedTM.tm_mon = month - 1; //Months sinsce January (0-based)
                notNormedTM.tm_mday = day; // 1-based
                notNormedTM.tm_isdst = -1;

                //normalize:
                *value_ = normalize(notNormedTM);

            }
            else throw std::exception("date is invalid");
        }

        /// <summary>Constructor from int.</summary>
        LocalDateImpl(int year, int month, int day)
        {
            tm notNormedTM = { 0 };
            notNormedTM.tm_year = year - 1900; // Years since 1900
            notNormedTM.tm_mon = month - 1; //Months sinsce January (0-based)
            notNormedTM.tm_mday = day; // 1-based
            notNormedTM.tm_isdst = -1;

            //normalize:
            *value_ = normalize(notNormedTM);
        }

        /// <summary>Returns true if the object is empty.</summary>
        virtual bool isNull() const
        {
            tm empty = { 0 };
            return mktime(value_) == mktime(&empty);
        }

        /// <summary>Convert atomic type to value.</summary>
        virtual LocalDate& value() { return *this; }

        /// <summary>Year.</summary>
        virtual int year() const { return value_->tm_year + 1900; }

        /// <summary>Month.</summary>
        virtual int month() const { return value_->tm_mon + 1; }

        /// <summary>Day.</summary>
        virtual int day() const { return value_->tm_mday; }

        /// <summary>Add years (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusYears(int years) const
        {
            tm notNormedTM = *value_;
            notNormedTM.tm_year += years;
            tm normedTM = normalize(notNormedTM);
            return LocalDate(normedTM.tm_year + 1900, normedTM.tm_mon + 1, normedTM.tm_mday);
        }

        /// <summary>Add month (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusMonths(int months)const
        {
            tm notNormedTM = *value_;
            notNormedTM.tm_mon += months;
            tm normedTM = normalize(notNormedTM);
            return LocalDate(normedTM.tm_year + 1900, normedTM.tm_mon + 1, normedTM.tm_mday);
        }

        /// <summary>Add days (returns result, the object itself remains unchanged).</summary>
        virtual LocalDate plusDays(int days)const
        {
            tm notNormedTM = *value_;
            notNormedTM.tm_mday += days;
            tm normedTM = normalize(notNormedTM);
            return LocalDate(normedTM.tm_year + 1900, normedTM.tm_mon + 1, normedTM.tm_mday);
        }

        /// <summary>Days from the specified date. Error message if zero or negative.</summary>
        virtual int daysFrom(LocalDate fromDate) const
        {
            time_t this_time = mktime(value_);
            tm from_date = { 0 };
            from_date.tm_year = fromDate.year();
            from_date.tm_mon = fromDate.month();
            from_date.tm_mday = fromDate.day();
            time_t from_time = mktime(&from_date);

            __int64 secondsInDay = 60 * 60 * 24;
            if (this_time - from_time > 0) return (int)((this_time - from_time) / secondsInDay);
            else throw std::exception("LocalDate.daysFrom() function should not be used when the argument date is after or equal this date");
            return 0;
        }

        /// <summary>Convert to string.</summary>
        virtual tstring ToString() const
        {
            //return String::format("{0:0000}-{1:00}-{2:00}", year(), month(), day());  //review this

            char buffer[10]; //10 - length of date in ISO format (YYYY-MM-DD)
            sprintf_s(buffer, "%4d-%2d-%2d", year(), month(), day());
            return String(buffer);
        }

        /// <summary>Convert to int using Excel format. Empty date is converted to empty int.</summary>
        virtual int toExcelInt() const
        {
            return  (!isNull()) ? daysFrom(LocalDate(1899, 12, 30)) : 0; //review, maybe 1900, 1, 1 and empty value of int
        }

        /// <summary>Convert to int using ISO format (YYYYMMDD). Empty date is converted to empty int.</summary>
        virtual int toIsoInt() const
        {
            return  (!isNull()) ? 10000 * year() + 100 * month() + day() : 0; //review empty value of int
        }

        /// <summary>Hash code.</summary>
        virtual int getHashCode() const
        {
            time_t ticks = mktime(value_);
            return (((int)ticks) ^ ((int)(ticks >> 32))); //formula from C# DateTime
        }

        /// <summary>Compare the current instance with another of the same type.
        /// Null is considered to be less than any other value.</summary>
        virtual int compareTo(LocalDate other)
        {
            time_t this_time = mktime(value_);
            tm from_date = { 0 };
            from_date.tm_year = other.year();
            from_date.tm_mon = other.month();
            from_date.tm_mday = other.day();
            time_t from_time = mktime(&from_date);

            return (this_time - from_time == 0) ? 0 : (int)std::copysign(1, this_time - from_time);
        }

        /// <summary>Error message if the argument is not a valid date in ISO format (YYYYMMDD).</summary>
        virtual void checkValid()
        {
            if ((value_->tm_hour != 0) || (value_->tm_min != 0) || (value_->tm_sec != 0))
                throw std::exception("To be converted to LocalDate, time must be set to UTC midnight");
        }

    };


    LocalDate::LocalDate() : impl_(new LocalDateImpl()) {}

    LocalDate::LocalDate(cl::String value) : impl_(new LocalDateImpl(value)) {}

    LocalDate::LocalDate(int year, int month, int day) : impl_(new LocalDateImpl(year, month, day)) {}
}