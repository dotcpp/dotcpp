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

#include <cl/dotcpp/main/detail/macro.hpp>

namespace cl
{
    namespace detail
    {
        template <typename Class, typename Ret, typename ... Args>
        Class get_method_class(Ret (Class::*)(Args...));
    }
}



#define DOT_DECL_PROP_GET(Class, type, name)                                \
    private:                                                                \
        virtual type CAT(get, name)(type name) = 0;                         \
        struct CAT(name, _prop)                                             \
        {                                                                   \
                                                                            \
            CAT(name, _prop)(Class * this_) : this_(this_) {}               \
            type name;                                                      \
                                                                            \
            type & operator = (const type &) = delete;                      \
            operator type() const { return this_->CAT(get, name)(name); }   \
                                                                            \
            Class * this_;                                                  \
                                                                            \
        };                                                                  \
    public:                                                                 \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_DECL_PROP(Class, type, name)                                    \
    private:                                                                \
        virtual type CAT(get, name)(type name) = 0;                         \
        virtual void CAT(set, name)(type & name, type const& value) = 0;    \
        struct CAT(name, _prop)                                             \
        {                                                                   \
                                                                            \
            CAT(name, _prop)(Class * this_) : this_(this_) {}               \
            type name;                                                      \
                                                                            \
            void operator = (const type &value )                            \
                { return this_->CAT(set, name)(name, value); }              \
            operator type() const { return this_->CAT(get, name)(name); }   \
                                                                            \
            Class * this_;                                                  \
                                                                            \
        };                                                                  \
    public:                                                                 \
        CAT(name, _prop) name = CAT(name, _prop)(this);



#define DOT_IMPL_PROP_GET(Class, type, name, getter)                        \
    private:                                                                \
        virtual type CAT(get, name)(type name) getter


#define DOT_IMPL_PROP(Class, type, name, getter, setter)                    \
    private:                                                                \
        virtual type CAT(get, name)(type name) getter                       \
        virtual void CAT(set, name)(type & name, type const& value) setter

#define DOT_PROP_GET(Class, type, name, getter)                             \
    private:                                                                \
        virtual type CAT(get, name)(type name) getter                       \
        struct CAT(name, _prop)                                             \
        {                                                                   \
                                                                            \
            CAT(name, _prop)(Class * this_) : this_(this_) {}               \
            type name;                                                      \
                                                                            \
            type & operator = (const type &) = delete;                      \
            operator type() const { return this_->CAT(get, name)(name); }   \
                                                                            \
            Class * this_;                                                  \
                                                                            \
        };                                                                  \
    public:                                                                 \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_PROP(Class, type, name, getter, setter)                         \
    private:                                                                \
        virtual type CAT(get, name)(type name) getter                       \
        virtual void CAT(set, name)(type & name, type const& value) setter  \
        struct CAT(name, _prop)                                             \
        {                                                                   \
                                                                            \
            CAT(name, _prop)(Class * this_) : this_(this_) {}               \
            type name;                                                      \
                                                                            \
            void operator = (const type &value )                            \
                { return this_->CAT(set, name)(name, value); }              \
            operator type() const { return this_->CAT(get, name)(name); }   \
                                                                            \
            Class * this_;                                                  \
                                                                            \
        };                                                                  \
    public:                                                                 \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_AUTO_PROP_GET(Class, type, name)                                \
    public:                                                                 \
        type name;                                                          \
        virtual type CAT(get, name)() { return name; }


#define DOT_AUTO_PROP(Class, type, name)                                    \
    public:                                                                 \
        type name;                                                          \
        virtual type CAT(get, name)() { return name; }                      \
        void CAT(set, name)(type const& value) { name = value; }
