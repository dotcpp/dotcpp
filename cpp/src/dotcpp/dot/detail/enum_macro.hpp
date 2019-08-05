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
    static dot::object new_Self() { return self(); }                         \
                                                                        \
public:                                                                 \
    typedef self element_type;                                          \
    typedef dot::StructWrapperImpl<self>* pointer_type;                      \
    using dot::Enum::Enum;                                                   \
                                                                        \
    operator dot::object() { return new dot::StructWrapperImpl<self>(*this); }    \
    operator int() const { return value_; }                             \
    self& operator=(int rhs) { value_ = rhs; return *this; }            \
    self& operator=(const self& other) { value_ = other.value_; return *this; } \
    virtual dot::type_t type() { return typeof(); }                         \
    static dot::type_t typeof()                                                \
    {                                                                   \
        static dot::type_t type = []()->dot::type_t                                   \
        {                                                               \
            dot::type_t type = dot::make_type_builder<self>(nspace, name)             \
                ->IsEnum()                                              \
                ->WithConstructor(&self::new_Self, {})                  \
                ->WithBase<Enum>()                                      \
                ->Build();                                              \
            return type;                                                \
        }();                                                            \
        return type;                                                    \
    }                                                                   \
                                                                        \
protected:                                                              \
    virtual dot::dictionary<dot::string, int> get_enum_map() override               \
    {                                                                   \
        static dot::dictionary<dot::string, int> enumMap_ = []()                  \
        {                                                               \
            auto map_ = dot::make_dictionary<dot::string, int>();


#define DOT_ENUM_VALUE(value) \
    map_[#value] = value;


#define DOT_ENUM_END()                                                  \
            return map_;                                                \
        }();                                                            \
        return enumMap_;                                                \
    }
