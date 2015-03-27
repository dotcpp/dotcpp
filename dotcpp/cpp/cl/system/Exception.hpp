/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp project, an implementation of
selected .NET class libraries in native C++ available from

    http://github.com/compatibl/dotcpp (source)
    http://compatibl.com/dotcpp (documentation)

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

#ifndef __cl_system_Exception_hpp__
#define __cl_system_Exception_hpp__

#include <cl/system/declare.hpp>

namespace cl
{
    class String;

    /// <summary>Represents errors that occur during application execution.</summary>
    class CL_SYSTEM Exception : public std::exception
    {
        std::string msg_;

    public: // CONSTRUCTORS

        /// <summary>Create with default message.</summary>
        Exception() : msg_("Exception of type 'System.Exception' was thrown.") {}

        /// <summary>Create with a specified error message.</summary>
        Exception(const String& msg);

        /// <summary>Create with a specified error message.</summary>
        Exception(const std::string& msg) : msg_(msg) {}

        /// <summary>Create with a specified error message.</summary>
        Exception(const char* msg) : msg_(msg ? msg : "") {}

    public: // METHODS

        /// <summary>Pointer to a null-terminated string with explanatory information.</summary>
        virtual const char* what() const { return msg_.c_str(); }

        /// <summary>Message that describes the current exception.</summary>
        virtual String message() const;
    };
}

#endif // __cl_system_Exception_hpp__
