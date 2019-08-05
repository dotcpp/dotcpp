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

#include <dot/implement.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    /// <summary>Create with default message.</summary>
    exception::exception() : base("Exception of type 'System.Exception' was thrown.") {}

    /// <summary>Create with a specified error message.</summary>
    exception::exception(const std::string& msg) : base(msg.c_str()) {}

    /// <summary>Create with a specified error message.</summary>
    exception::exception(const char* msg) : base(msg ? msg : "") {}

    /// <summary>Create with a specified error message.</summary>
    exception::exception(string msg) : base(*msg) {}

    /// <summary>Message that describes the current exception.</summary>
    string exception::message() const { return string(what()); }


}
