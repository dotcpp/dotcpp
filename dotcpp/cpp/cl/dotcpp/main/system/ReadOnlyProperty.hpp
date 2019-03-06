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

#include <cl/dotcpp/main/declare.hpp>
#include <functional>

namespace cl
{
    /// <summary>Use this class to implement a non-static readonly property using a getter method.
    /// Define getter as static method taking reference to self as its argument.</summary>
    template <typename ObjType, typename PropType>
    class ReadOnlyProperty
    {
        ObjType& obj_;
        std::function<PropType(ObjType&)> getter_;

    public: // CONSTRUCTORS

        /// <summary>Create from reference to self and getter method address.
        /// Define getter as static method taking reference to self as its argument.</summary>
        ReadOnlyProperty(ObjType& obj, std::function<PropType(ObjType&)> getter) : obj_(obj), getter_(getter) {}

    public: // OPERATORS

        /// <summary>Provides property get behavior.</summary>
        operator PropType() const { return getter_(obj_); }

    private:
        // Private assignment operator ensures that property set always calls the setter.
        void operator=(const ReadOnlyProperty<ObjType, PropType>&);
    };
}
