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

#pragma once

#define DOT_ENUM_BEGIN(nspace, name)                                    \
private:                                                                \
    static dot::object make_self() { return self(); }                         \
                                                                        \
public:                                                                 \
    typedef self element_type;                                          \
    typedef dot::struct_wrapper_impl<self>* pointer_type;                      \
    using dot::enum_base::enum_base;                                                   \
                                                                        \
    operator dot::object() { return new dot::struct_wrapper_impl<self>(*this); }    \
    operator int() const { return value_; }                             \
    self& operator=(int rhs) { value_ = rhs; return *this; }            \
    self& operator=(const self& other) { value_ = other.value_; return *this; } \
    virtual dot::type_t get_type() { return typeof(); }                         \
    static dot::type_t typeof()                                                \
    {                                                                   \
        static dot::type_t result = []()->dot::type_t                                   \
        {                                                               \
            dot::type_t t = dot::make_type_builder<self>(nspace, name)             \
                ->is_enum()                                              \
                ->with_constructor(&self::make_self, {})                  \
                ->with_base<enum_base>()                                      \
                ->build();                                              \
            return t;                                                \
        }();                                                            \
        return result;                                                    \
    }                                                                   \
                                                                        \
protected:                                                              \
    virtual dot::dictionary<dot::string, int> get_enum_map() override               \
    {                                                                   \
        static dot::dictionary<dot::string, int> enum_map_ = []()                  \
        {                                                               \
            auto map_ = dot::make_dictionary<dot::string, int>();


#define DOT_ENUM_VALUE(value) \
    map_[#value] = value;


#define DOT_ENUM_END()                                                  \
            return map_;                                                \
        }();                                                            \
        return enum_map_;                                                \
    }
