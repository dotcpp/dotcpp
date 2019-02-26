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

#ifndef cl_dotcpp_main_Object_hpp
#define cl_dotcpp_main_Object_hpp

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>

namespace cl
{
    class TString; using tstring = TString;
    class TType;

    /// <summary>All classes with reference semantics should derive from this type.
    /// It works with TPtr to provide an emulation of reference semantics in C++.
    /// Classes with value semantics should not derive from this type.</summary>
    class CL_SYSTEM TObject : public TRefCounter
    {
    public:

        /// <summary>Virtual destructor to ensure that destructor
        /// of the derived type is called by TPtr.</summary>
        virtual ~TObject() = default;

    public: // METHODS

        /// <summary>Gets the type of the current instance.</summary>
        virtual TType GetType() const;

        /// <summary>Returns a string that represents the current object.
        /// Default implementation uses full name of the class.</summary>
        virtual tstring ToString() const;

    protected:
        TObject() = default;
    };
}

#endif // cl_dotcpp_main_Object_hpp
