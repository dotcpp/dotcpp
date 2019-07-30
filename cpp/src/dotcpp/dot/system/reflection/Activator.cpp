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

#include <dot/implement.hpp>
#include <dot/system/reflection/Activator.hpp>
#include <dot/system/objectimpl.hpp>
#include <dot/system/Array1D.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/string.hpp>
#include <dot/system/collections/generic/List.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>

namespace dot
{
    object Activator::CreateInstance(type_t type)
    {
        return CreateInstance(type, nullptr);
    }

    object Activator::CreateInstance(type_t type, Array1D<object> params)
    {
        Array1D<ConstructorInfo> ctors = type->GetConstructors();

        // If no constructors
        if (ctors.IsEmpty() || ctors->count() == 0)
        {
            throw new_Exception(string::format("type_t {0}.{1} does not have registered constructors", type->Namespace, type->Name));
        }

        // Search for best matched constructor
        ConstructorInfo best_ctor = nullptr;
        int paramsCount = 0;
        if (!params.IsEmpty())
        {
            paramsCount = params->count();
        }

        for (auto ctor : ctors)
        {
            auto ctorParams = ctor->GetParameters();
            bool matches = true;

            // Continue if different parameters count
            if (ctorParams->count() != paramsCount)
                continue;

            // Compare all parameters types
            for (int i = 0; i < paramsCount; ++i)
            {
                if ((string)ctorParams[i]->ParameterType->Name != params[i]->type()->Name)
                {
                    matches = false;
                    break;
                }
            }

            // Break if found
            if (matches)
            {
                best_ctor = ctor;
                break;
            }
        }

        // If not found
        if (best_ctor == nullptr)
        {
            throw new_Exception("No matching public constructor was found.");
        }

        return best_ctor->Invoke(params);
    }

    object Activator::CreateInstance(string assemblyName, string typeName)
    {
        return CreateInstance(type_impl::GetType(typeName), nullptr);
    }

    object Activator::CreateInstance(string assemblyName, string typeName, Array1D<object> params)
    {
        return CreateInstance(type_impl::GetType(typeName), params);
    }
}
