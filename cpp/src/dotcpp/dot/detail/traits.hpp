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

namespace dot
{
    namespace detail
    {
        /// <summary>Helper class for MemberInfo.Invoke.</summary>
        template <int... I>
        struct index_sequence {};

        /// <summary>Helper class for MemberInfo.Invoke.</summary>
        template <int N, int... I>
        struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...>
        {
            typedef typename make_index_sequence<N - 1, N - 1, I...>::type type;
        };

        /// <summary>Helper class for MemberInfo.Invoke.</summary>
        template <int... I>
        struct make_index_sequence<0, I...> : public index_sequence<I...>
        {
            typedef index_sequence<I...> type;
        };
    }
}