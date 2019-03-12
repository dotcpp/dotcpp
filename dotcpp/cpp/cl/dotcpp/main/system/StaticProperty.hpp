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
    /// <summary>Use this class to implement a static read/write property using getter and setter methods.
    /// This template is designed to work with setter method that takes const reference to value.</summary>
    template <class PropType>
    class StaticProperty
    {
        std::function<PropType()> getter_;
        std::function<void(const PropType&)> setter_;

    public:

        /// <summary>Create from reference to self and getter method address.
        /// Define getter as static method taking reference to self as its argument.</summary>
        StaticProperty(std::function<PropType()> getter,
            std::function<void(const PropType&)> setter) : getter_(getter), setter_(setter) {}

        /// <summary>Provides property get behavior.</summary>
        operator PropType() const { return getter_(); }

        /// <summary>Provides property get behavior.</summary>
        const PropType& operator=(const PropType& value) { setter_(value); return value; }

    private:
        // Private assignment operator ensures that property set always calls the setter.
        void operator=(const StaticProperty<PropType>&);
    };
}
