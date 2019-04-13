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

#include <cl/dotcpp/main/implement.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>
#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Type.hpp>

namespace cl
{
    /// <summary>
    /// Determines whether the specified object is equal to the current object.
    ///
    /// Default implementation in Object compares pointers. Derived classes
    /// can override this method to compare by value.
    /// </summary>
    bool ObjectImpl::Equals(Object obj)
    {
        return this == &(*obj);
    }

    /// <summary>
    /// Serves as the default hash function.
    ///
    /// Default implementation in Object uses hash based on the pointer.
    /// Derived classes can override this method to provide value based hash.
    ///
    /// Methods Equals() and GetHashCode() must always be overriden together
    /// to avoid the situation when objects are equal but hash is not.
    /// </summary>
    size_t ObjectImpl::GetHashCode()
    {
        return size_t(this);
    }

    /// <summary>
    /// String that represents the current object.
    ///
    /// Default implementation in Object returns full name
    /// of the class by calling GetType().FullName. Derived types
    /// can override this method to provide custom conversion
    /// to string.
    /// </summary>
    String ObjectImpl::ToString()
    {
        return GetType()->FullName;
    }
}
