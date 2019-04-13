#pragma once
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

/// <summary>
/// Methods typeof() and GetType() are thread safe because the implementation uses lambda
/// </summary>

#define DOT_TYPE_BEGIN(nspace, name, ...)                                                      \
        virtual Type GetType() { return typeof(); }                                               \
        static Type typeof()                                                                      \
        {                                                                                         \
            static Type type = []()-> Type                                                        \
            {                                                                                     \
                Type type = new_TypeBuilder<self>(nspace, name)

#define DOT_TYPE_END()                                                                         \
                    ->Build();                                                                    \
                return type;                                                                      \
            }();                                                                                  \
            return type;                                                                          \
        }                                                                                         \

#define DOT_TYPE_PROP(prop_name)             ->WithProperty(#prop_name, &self::prop_name)
#define DOT_TYPE_METHOD(meth_name, ...)          ->WithMethod(#meth_name, &self::meth_name, { __VA_ARGS__ })
#define DOT_TYPE_CTOR(ctor_name, ...)            ->WithConstructor(&ctor_name, { __VA_ARGS__ })
#define DOT_TYPE_INTERFACE(interface)            ->WithInterface<interface>()
#define DOT_TYPE_BASE(base)                      ->WithBase<base>()  
#define DOT_TYPE_GENERIC_ARGUMENT(arg)           ->WithGenericArgument<arg>()
