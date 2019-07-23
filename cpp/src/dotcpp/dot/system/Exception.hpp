/*
Copyright (C) 2003-present CompatibL

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

namespace dot
{
    class String;
    class StringImpl;

    /// <summary>Represents errors that occur during application execution.</summary>
    class DOT_CLASS Exception : public std::runtime_error
    {
        typedef std::runtime_error base;

    protected: // CONSTRUCTORS

        /// <summary>Create with default message.</summary>
        Exception();

        /// <summary>Create with a specified error message.</summary>
        Exception(const std::string& msg);

        /// <summary>Create with a specified error message.</summary>
        Exception(const char* msg);

        /// <summary>Create with a specified error message.</summary>
        Exception(String msg);

    public: // METHODS

        /// <summary>Message that describes the current exception.</summary>
        virtual String Message() const;
    };

    /// <summary>
    /// Represents errors that occur during application execution.
    ///
    /// For compatibility with both C++ and C\# style catch blocks,
    /// this class is syntactic sugar on top of Exception class which
    /// has value semantics.
    /// </summary>
    class DOT_CLASS new_Exception : public Exception
    {
        typedef Exception base;

    public: // CONSTRUCTORS

        /// <summary>Create with default message.</summary>
        new_Exception();

        /// <summary>Create with a specified error message.</summary>
        new_Exception(const std::string& msg);

        /// <summary>Create with a specified error message.</summary>
        new_Exception(const char* msg);

        /// <summary>Create with a specified error message.</summary>
        new_Exception(String msg);
    };
}
