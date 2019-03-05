/*
Copyright (C) 2003-present CompatibL

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to faciliate
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

#ifndef cl_dotcpp_main_Exception_hpp
#define cl_dotcpp_main_Exception_hpp

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    /// <summary>Represents errors that occur during application execution.</summary>
    class Exception : public std::runtime_error
    {
    public: // CONSTRUCTORS

        /// <summary>Create with default message.</summary>
        Exception() : std::runtime_error("Exception of type 'System.Exception' was thrown.") {}

        /// <summary>Create with a specified error message.</summary>
        Exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}

        /// <summary>Create with a specified error message.</summary>
        Exception(const char* msg) : std::runtime_error(msg ? msg : "") {}

    public: // METHODS

        /// <summary>Message that describes the current exception.</summary>
        virtual String Message() const { return String(what()); }
    };
}

#endif // cl_dotcpp_main_Exception_hpp
