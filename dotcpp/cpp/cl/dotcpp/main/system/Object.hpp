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
#include <cl/dotcpp/main/system/Ptr.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    class Object;

    /// <summary>
    /// All classes with reference semantics should derive from this type.
    /// It works with Ptr to provide an emulation of reference semantics in C++.
    /// </summary>
    class CL_DOTCPP_MAIN ObjectImpl
    {
    public: // DESTRUCTOR

        /// <summary>
        /// Virtual destructor to ensure that destructor
        /// of the derived type is called by Ptr.
        /// </summary>
        virtual ~ObjectImpl() = default;

    public: // METHODS

        /// <summary>
        /// String that represents the current object.
        ///
        /// Default implementation returns full name of the class.
        /// </summary>
        virtual String ToString() const { return "Object"; }

    protected:
        ObjectImpl() = default;
    };

    class ValueTypeImpl; using ValueType = Ptr<ValueTypeImpl>;

    /// <summary>Based class for boxed value types.</summary>
    class ValueTypeImpl : public ObjectImpl
    {
    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "System.ValueType"; }
    };

    /// <summary>Wrapper around double to make it convertible to Object (boxing).</summary>
    class DoubleImpl : public ValueTypeImpl
    {
        friend Object;
        double value_;

    public: // CONSTRUCTORS

        /// <summary>Create from value (box).</summary>
        DoubleImpl(double value) : value_(value) {}

    public: // METHODS

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "System.Double"; }
    };

    /// <summary>Adds support for boxing value types to Ptr(ObjectImpl).</summary>
    class CL_DOTCPP_MAIN Object : public Ptr<ObjectImpl>
    {
        typedef Ptr<ObjectImpl> base;

    public: // CONSTRUCTORS

        /// <summary>Construct Object from Ptr(T).</summary>
        Object(const Ptr<ObjectImpl>& ptr) : base(ptr) {}

        /// <summary>Construct Object from double by boxing.</summary>
        Object(double value) : base(new DoubleImpl(value)) {}

    public: // OPERATORS

        /// <summary>Assign Ptr(T) to Object.</summary>
        Object& operator=(const Ptr<ObjectImpl>& ptr) { base::operator=(ptr); return *this; }

        /// <summary>Assign double to Object by boxing.</summary>
        Object& operator=(double value) { base::operator=(new DoubleImpl(value)); return *this; }

        /// <summary>Convert to double by unboxing.</summary>
        operator double() const { return cast<Ptr<DoubleImpl>>()->value_; }
    };
}
