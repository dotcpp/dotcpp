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

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/NullableBool.hpp>
#include <cl/dotcpp/main/system/NullableDouble.hpp>
#include <cl/dotcpp/main/system/NullableInt.hpp>

namespace cl
{
    /// <summary>Construct Object from bool by boxing.</summary>
    Object::Object(bool value) : base(new BoolImpl(value)) {}

    /// <summary>Construct Object from NullableBool by boxing.</summary>
    Object::Object(const NullableBool& value) : base(value.IsEmpty() ? nullptr : new BoolImpl(value)) {}

    /// <summary>Construct Object from double by boxing.</summary>
    Object::Object(double value) : base(new DoubleImpl(value)) {}

    /// <summary>Construct Object from NullableDouble by boxing.</summary>
    Object::Object(const NullableDouble& value) : base( value.IsEmpty() ? nullptr : new DoubleImpl(value)) {}

    /// <summary>Construct Object from int by boxing.</summary>
    Object::Object(int value) : base(new IntImpl(value)) {}

    /// <summary>Construct Object from NullableInt by boxing.</summary>
    Object::Object(const NullableInt& value) : base(value.IsEmpty() ? nullptr : new IntImpl(value)) {}

    /// <summary>Assign String to Object by boxing.</summary>
    Object& Object::operator=(const String& value) { base::operator=(value); return *this; }

    /// <summary>Assign bool to Object by boxing.</summary>
    Object& Object::operator=(bool value) { base::operator=(new BoolImpl(value)); return *this; }

    /// <summary>Assign NullableDouble to Object by boxing.</summary>
    Object& Object::operator=(const NullableBool& value) { base::operator=(value.IsEmpty() ? nullptr : new BoolImpl(value)); return *this; }

    /// <summary>Assign double to Object by boxing.</summary>
    Object& Object::operator=(double value) { base::operator=(new DoubleImpl(value)); return *this; }

    /// <summary>Assign NullableDouble to Object by boxing.</summary>
    Object& Object::operator=(const NullableDouble& value) { base::operator=(value.IsEmpty() ? nullptr : new DoubleImpl(value)); return *this; }

    /// <summary>Assign int to Object by boxing.</summary>
    Object& Object::operator=(int value) { base::operator=(new IntImpl(value)); return *this; }

    /// <summary>Assign NullableInt to Object by boxing.</summary>
    Object& Object::operator=(const NullableInt& value) { base::operator=(value.IsEmpty() ? nullptr : new IntImpl(value)); return *this; }

    /// <summary>Convert Object to bool by unboxing. Error if Object does is not a boxed double.</summary>
    Object::operator bool() const { return Ptr<BoolImpl>(*this)->value_; }

    /// <summary>Convert Object to double by unboxing. Error if Object does is not a boxed double.</summary>
    Object::operator double() const { return Ptr<DoubleImpl>(*this)->value_; }

    /// <summary>Convert Object to int by unboxing. Error if Object does is not a boxed int.</summary>
    Object::operator int() const { return Ptr<IntImpl>(*this)->value_; }
}
