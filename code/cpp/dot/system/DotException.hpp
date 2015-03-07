/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp project, an implementation of
selected .NET class libraries in native C++ available from

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

#ifndef __dot_system_DotException_hpp__
#define __dot_system_DotException_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    class DotString;

    /// <summary>Represents errors that occur during application execution.</summary>
    class DotException : public std::exception
    {
        std::string msg_;

    public: // CONSTRUCTORS

        /// <summary>Initializes a new instance of the Exception class with default message.</summary>
        DotException() : msg_("Exception of type 'System.Exception' was thrown.") {}

        /// <summary>Initializes a new instance of the Exception class with a specified error message.</summary>
        DotException(const DotString& msg);

        /// <summary>Initializes a new instance of the Exception class with a specified error message.</summary>
        DotException(const std::string& msg) : msg_(msg) {}

    public: // METHODS

        /// <summary>Pointer to a null-terminated string with explanatory information.</summary>
        virtual const char* what() const { return msg_.c_str(); }

        /// <summary>Message that describes the current exception.</summary>
        virtual DotString message() const;
    };
}

#endif // __dot_system_DotException_hpp__
