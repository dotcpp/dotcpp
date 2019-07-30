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

namespace dot
{
    class object_impl;
    class string;
    class object;
    class object_impl;

    namespace detail
    {
        /// <summary>Empty structure.</summary>
        class dummy_no_to_string : public virtual object_impl
        {};

        /// <summary>
        /// objects inherit this structure in case their inner struct class has method to_string
        /// so object also have these method.
        /// </summary>
        template <class W, class T>
        class obj_to_string : public virtual object_impl
        {
        public:
            virtual string to_string() override { return static_cast<T*>(static_cast<W*>(this))->to_string(); }
        };

        /// <summary>Detects existance of to_string method.</summary>
        template<class T>
        struct has_to_string
        {
        private:
            static dummy_no_to_string detect(...);
            template<class U> static decltype(std::declval<U>().to_string()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy_no_to_string, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>For inheritance of to_string method.</summary>
        template<class W, class T>
        class inherit_to_string : public std::conditional<
                has_to_string<T>::value,
                obj_to_string<W, T>,
                dummy_no_to_string
            >::type
        {};

        /// <summary>Empty structure.</summary>
        class dummy_no_get_hashcode : public virtual object_impl
        {};

        /// <summary>
        /// objects inherit this structure in case their inner struct class has method hash_code
        /// so object also have these method.
        /// </summary>
        template <class W, class T>
        class obj_get_hashcode : public virtual object_impl
        {
        public:
            virtual size_t hash_code() override { return static_cast<T*>(static_cast<W*>(this))->hash_code(); }
        };

        /// <summary>Detects existance of hash_code method.</summary>
        template<class T>
        struct has_get_hashcode
        {
        private:
            static dummy_no_get_hashcode detect(...);
            template<class U> static decltype(std::declval<U>().hash_code()) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy_no_get_hashcode, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>For inheritance of hash_code method.</summary>
        template<class W, class T>
        class inherit_get_hashcode : public std::conditional<
            has_get_hashcode<T>::value,
            obj_get_hashcode<W, T>,
            dummy_no_get_hashcode
        >::type
        {};

        /// <summary>Empty structure.</summary>
        class dummy_no_equals : public virtual object_impl
        {};

        /// <summary>
        /// objects inherit this structure in case their inner struct class has method Equals
        /// so object also have these method.
        /// </summary>
        template <class W, class T>
        class obj_equals : public virtual object_impl
        {
        public:
            bool equals(object obj) override { return static_cast<T*>(static_cast<W*>(this))->equals(obj); }
        };

        /// <summary>Detects existance of Equals method.</summary>
        template<class T>
        struct has_equals
        {
        private:
            static dummy_no_equals detect(...);
            template<class U> static decltype(std::declval<U>().Equals(std::declval<object>())) detect(const U&);
        public:
            static constexpr bool value = !std::is_same<dummy_no_equals, decltype(detect(std::declval<T>()))>::value;
            typedef std::integral_constant<bool, value> type;
        };

        /// <summary>For inheritance of Equals method.</summary>
        template<class W, class T>
        class inherit_equals : public std::conditional<
            has_equals<T>::value,
            obj_equals<W, T>,
            dummy_no_equals
        >::type
        {};
    }
}
