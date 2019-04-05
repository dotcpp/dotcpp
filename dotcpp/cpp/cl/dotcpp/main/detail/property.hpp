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

        /// <summary>Empty structure.</summary>
        struct dummy {};
        struct dummy_ {}; // RENAME

        /// <summary>Struct checks if T has method begin() using SFINAE.</summary>
        template<class T>
        struct has_begin
        {
        private:
            static dummy detect(...);
            template<class U> static decltype(std::declval<U>()->begin()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>Struct checks if T has operator-> using SFINAE.</summary>
        template<class T>
        struct has_operator_arrow
        {
        private:
            static dummy detect(...);
            template<class U> static decltype(std::declval<U>().operator->()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>
        /// Properies inherit this structure in case their inner class has operator->
        /// so properties also have these operator.
        /// </summary>
        template <class T>
        struct operator_arrow
        {
            auto operator->() { return static_cast<T*>(this)->operator typename T::value_type().operator->(); }

        };

        /// <summary>
        /// Properies inherit this structure in case their inner class has methods begin/end
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
                                               , detail::dummy                   // false: inherit dummy (just empty struct)
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
                                                , detail::dummy
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


#define DOT_DECL_GET(ptype, name)                                                            \
    private:                                                                                 \
        virtual ptype CAT(get, name)(ptype name) = 0;                                        \
        struct CAT(name, _prop) : detail::decl_get                                           \
                                , std::conditional<detail::has_begin<ptype>::value           \
                                                 , detail::begin_end<CAT(name, _prop)>       \
                                                 , detail::dummy                             \
                                                  >::type                                    \
                                , std::conditional<detail::has_operator_arrow<ptype>::value  \
                                                 , detail::operator_arrow<CAT(name, _prop)>  \
                                                 , detail::dummy_                            \
                                                  >::type                                    \
        {                                                                                    \
            typedef ptype value_type;                                                        \
            CAT(name, _prop)(ThisType * this_) : this_(this_) {}                             \
            ptype name;                                                                      \
                                                                                             \
            ptype & operator = (const ptype &) = delete;                                     \
            operator ptype() const { return this_->CAT(get, name)(name); }                   \
            CAT(name, _prop) & operator = (const CAT(name, _prop) & rhs)                     \
                { name = rhs.name; return *this;  }                                          \
                                                                                             \
            ThisType * this_;                                                                \
                                                                                             \
        };                                                                                   \
    public:                                                                                  \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_DECL_PROP(ptype, name)                                                           \
    private:                                                                                 \
        virtual ptype CAT(get, name)(ptype name) = 0;                                        \
        virtual void CAT(set, name)(ptype & name, ptype const& value) = 0;                   \
        struct CAT(name, _prop) : detail::decl_prop                                          \
                                , std::conditional<detail::has_begin<ptype>::value           \
                                                 , detail::begin_end<CAT(name, _prop)>       \
                                                 , detail::dummy                             \
                                                  >::type                                    \
                                , std::conditional<detail::has_operator_arrow<ptype>::value  \
                                                 , detail::operator_arrow<CAT(name, _prop)>  \
                                                 , detail::dummy_                            \
                                                  >::type                                    \
        {                                                                                    \
            typedef ptype value_type;                                                        \
            CAT(name, _prop)(ThisType * this_) : this_(this_) {}                             \
            ptype name;                                                                      \
                                                                                             \
            void operator = (const ptype &value )                                            \
                { return this_->CAT(set, name)(name, value); }                               \
            operator ptype() const { return this_->CAT(get, name)(name); }                   \
            CAT(name, _prop) & operator = (const CAT(name, _prop) & rhs)                     \
                { name = rhs.operator ptype(); return *this;  }                              \
                                                                                             \
            ThisType * this_;                                                                \
                                                                                             \
        };                                                                                   \
    public:                                                                                  \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_IMPL_GET(ptype, name, getter)                                               \
    private:                                                                            \
        virtual ptype CAT(get, name)(ptype name) override getter


#define DOT_IMPL_PROP(ptype, name, getter, setter)                                      \
    private:                                                                            \
        virtual ptype CAT(get, name)(ptype name) override getter                        \
        virtual void CAT(set, name)(ptype & name, ptype const& value) override setter


#define DOT_GET(ptype, name, getter)                                                         \
    private:                                                                                 \
        virtual ptype CAT(get, name)(ptype name) getter                                      \
        struct CAT(name, _prop) : detail::decl_get                                           \
                                , std::conditional<detail::has_begin<ptype>::value           \
                                                 , detail::begin_end<CAT(name, _prop)>       \
                                                 , detail::dummy                             \
                                                  >::type                                    \
                                , std::conditional<detail::has_operator_arrow<ptype>::value  \
                                                 , detail::operator_arrow<CAT(name, _prop)>  \
                                                 , detail::dummy_                            \
                                                  >::type                                    \
        {                                                                                    \
            typedef ptype value_type;                                                        \
            CAT(name, _prop)(ThisType * this_) : this_(this_) {}                             \
            ptype name;                                                                      \
                                                                                             \
            ptype & operator = (const ptype &) = delete;                                     \
            operator ptype() const { return this_->CAT(get, name)(name); }                   \
            CAT(name, _prop) & operator = (const CAT(name, _prop) & rhs)                     \
                { name = rhs.name; return *this;  }                                          \
            template <class T_>                                                              \
            bool operator==(T_ const& rhs) { return operator ptype() == rhs; }               \
                                                                                             \
            ThisType * this_;                                                                \
                                                                                             \
        };                                                                                   \
    public:                                                                                  \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_PROP(ptype, name, getter, setter)                                                \
    private:                                                                                 \
        virtual ptype CAT(get, name)(ptype name) getter                                      \
        virtual void CAT(set, name)(ptype & name, ptype const& value) setter                 \
        struct CAT(name, _prop) : detail::decl_prop                                          \
                                , std::conditional<detail::has_begin<ptype>::value           \
                                                 , detail::begin_end<CAT(name, _prop)>       \
                                                 , detail::dummy                             \
                                                  >::type                                    \
                                , std::conditional<detail::has_operator_arrow<ptype>::value  \
                                                 , detail::operator_arrow<CAT(name, _prop)>  \
                                                 , detail::dummy_                            \
                                                  >::type                                    \
        {                                                                                    \
            typedef ptype value_type;                                                        \
            CAT(name, _prop)(ThisType * this_) : this_(this_) {}                             \
            ptype name;                                                                      \
                                                                                             \
            void operator = (const ptype &value )                                            \
                { return this_->CAT(set, name)(name, value); }                               \
            operator ptype() const { return this_->CAT(get, name)(name); }                   \
            CAT(name, _prop) & operator = (const CAT(name, _prop) & rhs)                     \
                { name = rhs.operator ptype(); return *this;  }                              \
            template <class T_>                                                              \
            bool operator==(T_ const& rhs) { return operator ptype() == rhs; }               \
                                                                                             \
            ThisType * this_;                                                                \
                                                                                             \
        };                                                                                   \
    public:                                                                                  \
        CAT(name, _prop) name = CAT(name, _prop)(this);


#define DOT_AUTO_GET(type, name) DOT_GET(type, name, { return name; })


#define DOT_AUTO_PROP(type, name) DOT_PROP(type, name, { return name; }, { name = value; })
