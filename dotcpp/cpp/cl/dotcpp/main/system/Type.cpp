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
#include <cl/dotcpp/main/system/Type.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/String.hpp>

namespace cl
{
    /// <summary>Set the name of the current type, excluding namespace.</summary>
    TypeData TypeDataImpl::WithName(const String& name) { name_ = name; return this; }

    /// <summary>Set the namespace of the Type.</summary>
    TypeData TypeDataImpl::WithNamespace(const String& ns) { namespace_ = ns; return this; }

    /// <summary>Built Type from the current object.</summary>
    Type TypeDataImpl::Build() { return new TypeImpl(this); }

    /// <summary>
    /// Create from builder.
    ///
    /// This constructor is private. Use TypeBuilder->Build() method instead.
    /// </summary>
    TypeImpl::TypeImpl(const TypeData& data)
        : Name(data->name_)
        , Namespace(data->namespace_)
    {
        for (auto propInfoData : data->properties_)
        {
            // TODO auto propInfo = new_PropertyInfo(propInfoData->Name, this, propInfoData->PropertyType, propInfoData->PropertyPointer);
        }
    }

}
