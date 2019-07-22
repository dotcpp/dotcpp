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

#include <dot/system/Object.hpp>

namespace dot
{
    class MemberInfoImpl; using MemberInfo = Ptr<MemberInfoImpl>;
    class MemberInfoDataImpl; using MemberInfoData = Ptr<MemberInfoDataImpl>;
    class TypeImpl; using Type = Ptr<TypeImpl>;

    /// <summary>Data for MemberInfo.</summary>
    class CL_DOTCPP_MAIN MemberInfoDataImpl : public virtual ObjectImpl
    {
        typedef MemberInfoDataImpl self;

    public: // PROPERTIES

        /// <summary>Gets the name of the current member.</summary>
        DOT_AUTO_PROP(String, Name)

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
    class MemberInfoImpl : public virtual ObjectImpl
    {
        typedef MemberInfoImpl self;

    public: // METHODS

        /// <summary>Gets the name of the current member.</summary>
        DOT_AUTO_GET(String, Name)

        /// <summary>Gets the class that declares this member.</summary>
        DOT_AUTO_GET(Type, DeclaringType)

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() override { return "MemberInfo"; }

    protected: // CONSTRUCTORS

        /// <summary>
        /// Create from property name and declaring type.
        ///
        /// This constructor is protected. It is used by derived classes only.
        /// </summary>
        MemberInfoImpl(const String& name, Type declaringType)
        {
            Name.Name = name;
            DeclaringType.DeclaringType = declaringType;
        }
    };
}
