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

#pragma once

#include <dot/system/object.hpp>

namespace dot
{
    class MemberInfoImpl; using MemberInfo = ptr<MemberInfoImpl>;
    class MemberInfoDataImpl; using MemberInfoData = ptr<MemberInfoDataImpl>;
    class type_impl; using type_t = ptr<type_impl>;

    /// <summary>Data for MemberInfo.</summary>
    class DOT_CLASS MemberInfoDataImpl : public virtual object_impl
    {
        typedef MemberInfoDataImpl self;

    public: // PROPERTIES

        /// <summary>Gets the name of the current member.</summary>
        string Name; // TODO - replace by method

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of MemberInfoData.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        MemberInfoDataImpl() = default;
    };

    /// <summary>
    /// Obtains information about the attributes of a member and provides access to member metadata.
    /// </summary>
    class MemberInfoImpl : public virtual object_impl
    {
        typedef MemberInfoImpl self;

    public: // METHODS

        /// <summary>Gets the name of the current member.</summary>
        string Name; // TODO - convert to method

        /// <summary>Gets the class that declares this member.</summary>
        type_t DeclaringType; // TODO - convert to method

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return "MemberInfo"; }

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from property name and declaring type.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        MemberInfoImpl(const string& name, type_t declaringType)
        {
            Name = name;
            DeclaringType = declaringType;
        }
    };
}
