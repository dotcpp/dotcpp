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
        /// <summary>Helper function to implement properties.</summary>
        template <class Class, class Ret, class ... Args>
        Class get_method_class(Ret (Class::*)(Args...));

        /// <summary>Helper class to implement readonly property.</summary>
        struct decl_get {};

        /// <summary>Helper class to implement read/write property.</summary>
        struct decl_prop : decl_get {};

        /// <summary>Helper class to implement readonly auto property.</summary>
        template <class T>
        class auto_get
        {
        public: // CONSTRUCTORS

            /// <summary>Create by passing arguments to the constructor of T.</summary>
            template <typename... Args>
            explicit auto_get(Args... args) : value_(args...) {}

        public: // OPERATORS

            /// <summary>Provides property get behavior.</summary>
            operator T() const { return value_; }

            /// <summary>Forwards operator* to the underlying type.</summary>
            auto& operator*() const { return *value_; }

            /// <summary>Forwards operator-> to the underlying type.</summary>
            auto operator->() const { return value_.operator->(); }

            /// <summary>Provides comparison operator.</summary>
            template <typename U> bool operator==(const U& u) const { return value_ == u; }

            /// <summary>Const indexer operator for arrays.</summary>
            template <class I>
            decltype(auto) operator[](I const& i) const { return value_[i]; }

            /// <summary>Non-const indexer operator for arrays.</summary>
            template <class I>
            decltype(auto) operator[](I const& i) { return value_[i]; }

        private:
            T value_;
        };

        /// <summary>Helper class to implement read/write auto property.</summary>
        template <class T>
        class auto_prop
        {
        public: // CONSTRUCTORS

            /// <summary>Create by passing arguments to the constructor of T.</summary>
            template <typename... Args>
            explicit auto_prop(Args... args) : value_(args...) {}

        public: // OPERATORS

            /// <summary>Provides property set behavior.</summary>
            void operator=(const T& value) { value_ = value; }

            /// <summary>Provides property get behavior.</summary>
            operator T() const { return value_; }

            /// <summary>Forwards operator* to the underlying type.</summary>
            auto& operator*() const { return *value_; }

            /// <summary>Forwards operator-> to the underlying type.</summary>
            auto operator->() const { return value_.operator->(); }

            /// <summary>Comparison operator.</summary>
            template <typename U> bool operator==(const U& u) const { return value_ == u; }

            /// <summary>Const indexer operator for arrays.</summary>
            template <class I>
            decltype(auto) operator[](I const& i) const { return value_[i]; }

            /// <summary>Non-const indexer operator for arrays.</summary>
            template <class I>
            decltype(auto) operator[](I const& i) { return value_[i]; }

        private:
            T value_;
        };
    }
}


#define DOT_DECL_GET(Class, type, name)                                     \
    private:                                                                \
        virtual type CAT(get, name)(type name) = 0;                         \
        struct CAT(name, _prop) : detail::decl_get                          \
        {                                                                   \
            typedef type value_type;                                        \
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
        struct CAT(name, _prop) : detail::decl_prop                      \
        {                                                                   \
            typedef type value_type;                                        \
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


#define DOT_IMPL_GET(Class, type, name, getter)                             \
    private:                                                                \
        virtual type CAT(get, name)(type name) override getter


#define DOT_IMPL_PROP(Class, type, name, getter, setter)                    \
    private:                                                                \
        virtual type CAT(get, name)(type name) override getter              \
        virtual void CAT(set, name)(type & name, type const& value) override setter


#define DOT_GET(Class, type, name, getter)                                  \
    private:                                                                \
        virtual type CAT(get, name)(type name) getter                       \
        struct CAT(name, _prop) : detail::decl_get                          \
        {                                                                   \
            typedef type value_type;                                        \
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
        struct CAT(name, _prop) : detail::decl_prop                      \
        {                                                                   \
            typedef type value_type;                                        \
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


#define DOT_AUTO_GET(Class, type, name)                                     \
    public:                                                                 \
        detail::auto_get<type> name;                                        \
        virtual type CAT(get, name)() { return name; }


#define DOT_AUTO_PROP(Class, type, name)                                    \
    public:                                                                 \
        detail::auto_prop<type> name;                                       \
        virtual type CAT(get, name)() { return name; }                      \
        void CAT(set, name)(type const& value) { name = value; }
