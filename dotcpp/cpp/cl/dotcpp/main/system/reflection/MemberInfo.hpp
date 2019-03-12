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

#include <cl/dotcpp/main/system/Object.hpp>

namespace cl
{
    class MemberInfoImpl; using MemberInfo = Ptr<MemberInfoImpl>;
    class TypeImpl; using Type = Ptr<TypeImpl>;

    /// <summary>
    /// Obtains information about the attributes of a member and provides access to member metadata.
    /// </summary>
    class CL_DOTCPP_MAIN MemberInfoImpl : public virtual ObjectImpl
    {
    public: // METHODS

        /// <summary>Gets the name of the current member.</summary>
        virtual String getName() const = 0;

        /// <summary>Gets the class that declares this member.</summary>
        virtual Type getDeclaringType() const = 0;

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "MemberInfo"; }

    protected:
        MemberInfoImpl() = default;
    };
}
