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
#include <dot/system/array1d.hpp>
#include <dot/system/Exception.hpp>
#include <dot/system/string.hpp>
#include <dot/system/collections/generic/list.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>

namespace dot
{
    object activator::create_instance(type_t type)
    {
        return create_instance(type, nullptr);
    }

    object activator::create_instance(type_t type, array<object> params)
    {
        array<constructor_info> ctors = type->get_constructors();

        // If no constructors
        if (ctors.IsEmpty() || ctors->count() == 0)
        {
            throw exception(string::format("type_t {0}.{1} does not have registered constructors", type->name_space, type->name));
        }

        // Search for best matched constructor
        constructor_info best_ctor = nullptr;
        int params_count = 0;
        if (!params.IsEmpty())
        {
            params_count = params->count();
        }

        for (auto ctor : ctors)
        {
            auto ctor_params = ctor->get_parameters();
            bool matches = true;

            // Continue if different parameters count
            if (ctor_params->count() != params_count)
                continue;

            // Compare all parameters types
            for (int i = 0; i < params_count; ++i)
            {
                if ((string)ctor_params[i]->parameter_type->name != params[i]->type()->name)
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
            throw exception("No matching public constructor was found.");
        }

        return best_ctor->invoke(params);
    }

    object activator::create_instance(string assembly_name, string type_name)
    {
        return create_instance(type_impl::get_type(type_name), nullptr);
    }

    object activator::create_instance(string assembly_name, string type_name, array<object> params)
    {
        return create_instance(type_impl::get_type(type_name), params);
    }
}
