/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

# ifndef cl_tape_impl_reflection_engine_register_type_hpp
# define cl_tape_impl_reflection_engine_register_type_hpp

# include <cl/system/detail/reflection/engine/sfinae.hpp>
# include <cl/system/detail/reflection/engine/vi_item.hpp>

namespace cl
{
    // The null_type we use e.g. to finalization some operation
    struct null_type {};

    template <typename type, typename Branch, typename sfinae_test = sfinae_empty>
    struct reg_sfinae : std::false_type
    {};
    
    template <typename type, typename Branch>
    struct reg_sfinae<type, Branch
            , typename cl::refl_dummy<typename type::registered>::dummy_type> : std::true_type
    {};

} // namespace cl

#endif
