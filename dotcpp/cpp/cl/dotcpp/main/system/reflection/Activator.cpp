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
#include <cl/dotcpp/main/system/reflection/Activator.hpp>
#include <cl/dotcpp/main/system/ObjectImpl.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/Exception.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/reflection/ConstructorInfo.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>

namespace cl
{
    Object Activator::CreateInstance(Type type)
    {
        return CreateInstance(type, nullptr);
    }

    Object Activator::CreateInstance(Type type, Array1D<Object> params)
    {
        Array1D<ConstructorInfo> ctors = type->GetConstructors();

        // if no constructors
        if (ctors.IsEmpty() || ctors->Count == 0)
        {
            throw Exception(String::Format("Type {0}.{1} does not have registered constructors", type->Namespace, type->Name));
        }

        // search for best matched constructor
        
        ConstructorInfo best_ctor = nullptr;
        int paramsCount = params.IsEmpty() ? 0 : params->Count;

        for (auto ctor : ctors)
        {
            auto ctorParams = ctor->GetParameters();
            bool matches = true;

            // continue if different parameters count
            if (ctorParams->Count != paramsCount)
                continue;

            // compare all parameters types
            for (int i = 0; i < params->Count; ++i)
            {
                if ((String)ctorParams[i]->ParameterType->Name != params[i]->GetType()->Name)
                {
                    matches = false;
                    break;
                }
            }

            // break if found
            if (matches)
            {
                best_ctor = ctor;
                break;
            }
        }

        // if not constructor found
        if (best_ctor == nullptr)
        {
            throw Exception("No matching public constructor was found.");
        }

        return best_ctor->Invoke(params);
    }

    Object Activator::CreateInstance(String assemblyName, String typeName)
    {
        return CreateInstance(TypeImpl::GetType(typeName), nullptr);
    }

    Object Activator::CreateInstance(String assemblyName, String typeName, Array1D<Object> params)
    {
        return CreateInstance(TypeImpl::GetType(typeName), params);
    }
}
