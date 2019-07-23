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

#define DOT_ENUM_BEGIN(nspace, name)                                    \
private:                                                                \
    static Object new_Self() { return self(); }                         \
                                                                        \
public:                                                                 \
    typedef self element_type;                                          \
    typedef StructWrapperImpl<self>* pointer_type;                      \
    using Enum::Enum;                                                   \
                                                                        \
    operator Object() { return new StructWrapperImpl<self>(*this); }    \
    operator int() const { return value_; }                             \
    self& operator=(int rhs) { value_ = rhs; return *this; }            \
    self& operator=(const self& other) { value_ = other.value_; return *this; } \
    virtual Type GetType() { return typeof(); }                         \
    static Type typeof()                                                \
    {                                                                   \
        static Type type = []()->Type                                   \
        {                                                               \
            Type type = new_TypeBuilder<self>(nspace, name)             \
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
    virtual Dictionary<String, int> GetEnumMap() override               \
    {                                                                   \
        static Dictionary<String, int> enumMap_ = []()                  \
        {                                                               \
            auto map_ = new_Dictionary<String, int>();


#define DOT_ENUM_VALUE(value) \
    map_[#value] = value;


#define DOT_ENUM_END()                                                  \
            return map_;                                                \
        }();                                                            \
        return enumMap_;                                                \
    }
