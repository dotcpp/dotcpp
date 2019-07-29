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

#include <dot/detail/macro.hpp>

namespace dot
{
    namespace detail
    {
        /// <summary>Helper function to implement properties.</summary>
        template <class Class, class Ret, class ... Args>
        Class get_method_class(Ret (Class::*)(Args...));

        /// <summary>Empty structure.</summary>
        struct dummy_no_begin {};
        struct dummy_no_arrow {};

        /// <summary>Struct checks if T has method begin() using SFINAE.</summary>
        template<class T>
        struct has_begin
        {
        private:
            static dummy_no_begin detect(...);
            template<class U> static decltype(std::declval<U>()->begin()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy_no_begin, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>Struct checks if T has operator-> using SFINAE.</summary>
        template<class T>
        struct has_operator_arrow
        {
        private:
            static dummy_no_begin detect(...);
            template<class U> static decltype(std::declval<U>().operator->()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy_no_begin, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>
        /// Properties inherit this structure in case their inner class has operator->
        /// so properties also have these operator.
        /// </summary>
        template <class T>
        struct operator_arrow
        {
            auto operator->() { return static_cast<T*>(this)->operator typename T::value_type(); }
        };

        /// <summary>
        /// Properties inherit this structure in case their inner class has methods begin/end
        /// so properties also have these methods and may be used in foreach loop.
        /// </summary>
        template <class T>
        struct begin_end
        {
            auto begin() { return static_cast<T*>(this)->operator typename T::value_type()->begin(); }
            auto end() { return static_cast<T*>(this)->operator typename T::value_type()->end(); }
        };

        /// <summary>Helper class to implement readonly property.</summary>
        struct decl_get {};

        /// <summary>Helper class to implement read/write property.</summary>
        struct decl_prop : decl_get {};

        /// <summary>Helper class to implement readonly auto property.</summary>
        template <class T>
        class auto_get : public std::conditional<detail::has_begin<T>::value     // Check if T has begin()
                                               , detail::begin_end<auto_get<T>>  // true: inherit begin_end with begin/end
                                               , detail::dummy_no_begin          // false: inherit dummy_no_begin (just empty struct)
                                                >::type
                       , public detail::decl_get
        {
        public: // CONSTRUCTORS

            typedef T value_type;

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
        class auto_prop : public std::conditional<detail::has_begin<T>::value
                                                , detail::begin_end<auto_prop<T>>
                                                , detail::dummy_no_begin
                                                 >::type
                        , public detail::decl_prop
        {
        public: // CONSTRUCTORS

            typedef T value_type;

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

// ------------------------------- __DOT_PROP_STRUCT__ ------------------------------- //


#define __DOT_PROP_STRUCT_DECL__(ptype, name, base, ...)                                        \
    struct CAT(name, _prop) : base                                                              \
                            , std::conditional<::dot::detail::has_begin<ptype>::value            \
                                             , ::dot::detail::begin_end<CAT(name, _prop)>        \
                                             , ::dot::detail::dummy_no_begin                     \
                                              >::type                                           \
                            , std::conditional<::dot::detail::has_operator_arrow<ptype>::value   \
                                             , ::dot::detail::operator_arrow<CAT(name, _prop)>   \
                                             , ::dot::detail::dummy_no_arrow                     \
                                              >::type                                           \
    {                                                                                           \
        friend self;                                                                            \
        typedef ptype value_type;                                                               \
        typedef CAT(name, _prop) prop_struct;                                                   \
                                                                                                \
    private:                                                                                    \
        self* this_;                                                                            \
                                                                                                \
    public:                                                                                     \
        CAT(name, _prop)(self* this_) : this_(this_) {}                                         \
        CAT(name, _prop)(const CAT(name, _prop)&) = delete;                                     \
                                                                                                \
        __VA_ARGS__                                                                             \
                                                                                                \
        template <class T_>                                                                     \
        bool operator==(const T_& rhs) const { return operator value_type() == rhs; }           \
                                                                                                \
        template <class T_>                                                                     \
        bool operator!=(const T_& rhs) const { return operator value_type() != rhs; }           \
                                                                                                \
        template <class T_>                                                                     \
        bool operator>(const T_& rhs) const { return operator value_type() > rhs; }             \
                                                                                                \
        template <class T_>                                                                     \
        bool operator>=(const T_& rhs) const { return operator value_type() >= rhs; }           \
                                                                                                \
        template <class T_>                                                                     \
        bool operator<(const T_& rhs) const { return operator value_type() < rhs; }             \
                                                                                                \
        template <class T_>                                                                     \
        bool operator<=(const T_& rhs) const { return operator value_type() <= rhs; }           \
                                                                                                \
        template <class I>                                                                      \
        decltype(auto) operator[](const I& i) const { return operator value_type()[i]; }        \
                                                                                                \
        template <class I>                                                                      \
        decltype(auto) operator[](const I& i) { return operator value_type()[i]; }              \
    };


#define __DOT_PROP_STRUCT__(ptype, name, base, ...)                 \
    private:                                                        \
        __DOT_PROP_STRUCT_DECL__(ptype, name, base, __VA_ARGS__)    \
    public:                                                         \
        CAT(name, _prop) name = CAT(name, _prop)(this);


// ------------------------- __DOT_PROP_STRUCT_METHODS__ --------------------------- //


#define __DOT_PROP_STRUCT_GETTER__(ptype, name) \
    operator value_type() const { return this_->CAT(get, name)(); }


#define __DOT_PROP_STRUCT_SETTER__(ptype, name)         \
    prop_struct& operator=(const value_type& value)     \
        { this_->CAT(set, name)(value); return *this; }


#define __DOT_PROP_STRUCT_EMPTY_COPY__(ptype, name)     \
    private:                                            \
        prop_struct& operator=(const prop_struct& rhs)  \
            { return *this; }                           \
    public:


#define __DOT_PROP_STRUCT_AUTO_COPY__(ptype, name)      \
    private:                                            \
        prop_struct& operator=(const prop_struct& rhs)  \
            { name = rhs.name; return *this; }          \
    public:


#define __DOT_PROP_STRUCT_COPY__(ptype, name)           \
    prop_struct& operator=(const prop_struct& rhs)      \
        { *this = rhs.operator value_type(); return *this; }


#define __DOT_PROP_STRUCT_AUTO__(ptype, name)           \
    public:                                             \
        value_type name = value_type();                 \
    public:


#define __DOT_PROP_STRUCT_FLUENT__(ptype, name)         \
    dot::ptr<self> operator()(const value_type& value)       \
        { *this = value; return dot::ptr<self>(this_); }


#define __DOT_PROP_STRUCT_PROP__(ptype, name)           \
    __DOT_PROP_STRUCT_GETTER__(ptype, name)             \
    __DOT_PROP_STRUCT_SETTER__(ptype, name)             \
    __DOT_PROP_STRUCT_COPY__(ptype, name)


// ----------------------- __DOT_PROP_DECL_CLASS_METHODS__ ------------------------ //


#define __DOT_PROP_DECL_GET__(ptype, name, getter) \
    virtual ptype CAT(get, name)() getter


#define __DOT_PROP_DECL_SET__(ptype, name, setter) \
    virtual void CAT(set, name)(const ptype& value) setter


#define __DOT_PROP_DECL_AUTO_GET__(ptype, name) \
    __DOT_PROP_DECL_GET__(ptype, name, { return name.name; })


#define __DOT_PROP_DECL_AUTO_SET__(ptype, name) \
    __DOT_PROP_DECL_SET__(ptype, name, { name.name = value; })


// ------------------------------- DOT_PROPERTIES ------------------------------- //


#define DOT_GET(ptype, name, getter)                                    \
    private:                                                            \
        __DOT_PROP_DECL_GET__(ptype, name, getter)                      \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_get,        \
            __DOT_PROP_STRUCT_GETTER__(ptype, name)                     \
            __DOT_PROP_STRUCT_EMPTY_COPY__(ptype, name)                 \
        )


#define DOT_PROP(ptype, name, getter, setter)                           \
    private:                                                            \
        __DOT_PROP_DECL_GET__(ptype, name, getter)                      \
        __DOT_PROP_DECL_SET__(ptype, name, setter)                      \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_prop,       \
            __DOT_PROP_STRUCT_PROP__(ptype, name)                       \
        )


#define DOT_AUTO_GET(ptype, name)                                       \
    private:                                                            \
        __DOT_PROP_DECL_AUTO_GET__(ptype, name)                         \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_get,        \
            __DOT_PROP_STRUCT_GETTER__(ptype, name)                     \
            __DOT_PROP_STRUCT_AUTO_COPY__(ptype, name)                  \
            __DOT_PROP_STRUCT_AUTO__(ptype, name)                       \
        )


#define DOT_AUTO_PROP(ptype, name)                                      \
    private:                                                            \
        __DOT_PROP_DECL_AUTO_GET__(ptype, name)                         \
        __DOT_PROP_DECL_AUTO_SET__(ptype, name)                         \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_prop,       \
            __DOT_PROP_STRUCT_PROP__(ptype, name)                       \
            __DOT_PROP_STRUCT_AUTO__(ptype, name)                       \
        )


#define DOT_FLUENT(ptype, name, getter, setter)                         \
    private:                                                            \
        __DOT_PROP_DECL_GET__(ptype, name, getter)                      \
        __DOT_PROP_DECL_SET__(ptype, name, setter)                      \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_prop,       \
            __DOT_PROP_STRUCT_PROP__(ptype, name)                       \
            __DOT_PROP_STRUCT_FLUENT__(ptype, name)                     \
        )


#define DOT_AUTO_FLUENT(ptype, name)                                    \
    private:                                                            \
        __DOT_PROP_DECL_AUTO_GET__(ptype, name)                         \
        __DOT_PROP_DECL_AUTO_SET__(ptype, name)                         \
        __DOT_PROP_STRUCT__(ptype, name, ::dot::detail::decl_prop,       \
            __DOT_PROP_STRUCT_PROP__(ptype, name)                       \
            __DOT_PROP_STRUCT_AUTO__(ptype, name)                       \
            __DOT_PROP_STRUCT_FLUENT__(ptype, name)                     \
        )


#define DOT_DECL_GET(ptype, name) DOT_GET(ptype, name, = 0;)


#define DOT_DECL_PROP(ptype, name) DOT_PROP(ptype, name, = 0;, = 0;)


#define DOT_DECL_FLUENT(ptype, name) DOT_FLUENT(ptype, name, = 0;, = 0;)


#define DOT_IMPL_GET(ptype, name, getter)                               \
    private:                                                            \
        __DOT_PROP_DECL_GET__(ptype, name, override getter)


#define DOT_IMPL_PROP(ptype, name, getter, setter)                      \
    private:                                                            \
        __DOT_PROP_DECL_GET__(ptype, name, override getter)             \
        __DOT_PROP_DECL_SET__(ptype, name, override setter)


#define DOT_IMPL_FLUENT(ptype, name, getter, setter) DOT_IMPL_PROP(ptype, name, getter, setter)
