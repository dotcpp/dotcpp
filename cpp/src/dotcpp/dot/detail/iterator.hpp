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


#include <dot/declare.hpp>

namespace cl
{
    namespace detail
    {
        /// Base class of virtual iterators, depends only on the item type T
        template <class T>
        struct std_iterator_base
        {
            using iterator_category = std::forward_iterator_tag;

            /// Destructor
            virtual ~std_iterator_base() {}

            /// Prefix notation (++iter)
            virtual std_iterator_base& operator++() = 0;

            /// Prefix notation, implemented via prefix notation
            inline std::unique_ptr<std_iterator_base> operator++(int)
            {
                std::unique_ptr<std_iterator_base> old(this->copy());
                this->operator++();
                return old;
            }

            /// Deep copy
            virtual std::unique_ptr<std_iterator_base> copy() = 0;

            /// Get wrapper (const version)
            virtual std::reference_wrapper<T> const get() const = 0;

            /// Get wrapper (non-const version)
            virtual std::reference_wrapper<T> get() = 0;

            /// Equality
            virtual bool operator ==(std_iterator_base<T> const& iter) = 0;

            /// Inequality
            virtual bool operator !=(std_iterator_base<T> const& iter) = 0;

            /// Dereference (const version)
            inline std::reference_wrapper<T> const operator*() const { return get(); }

            /// Dereference (non-const version)
            inline std::reference_wrapper<T> operator*() { return get(); }
        };

        template <class Iterator>
        struct std_iterator;

        template <class Iterator>
        inline std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type >> make_iterator(Iterator const& iter);

        /// Provides implementation, depends on iterator type rather than item type
        template <class Iterator>
        struct std_iterator : std_iterator_base<typename Iterator::value_type>
        {
            typedef typename Iterator::value_type value_type;
            typedef std_iterator_base<value_type> base;
            Iterator iter_;

            /// Create from the underlying STL iterator
            std_iterator(Iterator const& iter) : iter_(iter) {}

            /// Destructor
            virtual ~std_iterator() {}

            /// Prefix notation (++iter); postfix notation is implemented in base
            virtual base& operator++() override
            {
                ++iter_;
                return *this;
            }

            /// Deep copy
            virtual std::unique_ptr<base> copy() override
            {
                std::unique_ptr<base> old(make_iterator(iter_));
                return old;
            }

            /// Get reference to the underlying type (const version)
            virtual std::reference_wrapper<value_type> const get() const override
            {
                return std::reference_wrapper<value_type >(*iter_);
            }

            /// Get reference to the underlying type (non-const version)
            virtual std::reference_wrapper<value_type> get() override
            {
                return std::reference_wrapper<value_type >(*iter_);
            }

            /// Equality
            virtual bool operator==(std_iterator_base<value_type> const& iter) override
            {
                Iterator const& other = static_cast<std_iterator<Iterator> const&>(iter).iter_;
                return iter_ == other;
            }

            /// Inequality
            virtual bool operator!=(std_iterator_base<value_type> const& iter) override
            {
                Iterator const& other = static_cast<std_iterator<Iterator> const&>(iter).iter_;
                return iter_ != other;
            }
        };

        /// Unique pointer to std_iterator_base to permit assignment by base class
        template <class Iterator>
        inline std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type >>
            make_iterator(Iterator const& iter)
        {
            typedef std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type > > return_type;
            return return_type(new std_iterator<Iterator>(iter));
        }

        /// Inline wrapper providing dot dereference for std_iterator_base
        template <class T>
        struct std_iterator_wrapper
        {
            using iterator_category = std::forward_iterator_tag;

            std::unique_ptr<std_iterator_base<T>> iter_;

            /// Create from unique pointer to the wrapped object
            std_iterator_wrapper(std::unique_ptr<std_iterator_base<T>> && iter)
                :iter_(std::move(iter))
            {
            }

            /// Prefix notation (++iter)
            inline std_iterator_wrapper<T>& operator++()
            {
                (*iter_)++;
                return *this;
            }

            /// Postfix notation (iter++)
            inline std_iterator_wrapper<T> operator++(int)
            {
                std_iterator_wrapper old(this->copy());
                this->operator++();
                return old;
            }

            /// Deep copy
            inline std_iterator_wrapper copy()
            {
                return std_iterator_wrapper<T>(iter_->copy());
            }

            /// Get reference to the underlying type (const version)
            inline T const& get() const
            {
                return iter_->get();
            }

            /// Get reference to the underlying type (non-const version)
            inline T& get()
            {
                return iter_->get();
            }

            /// Equality
            inline bool operator==(std_iterator_wrapper const& iter)
            {
                return *iter_ == *(iter.iter_);
            }

            /// Inequality
            inline bool operator!=(std_iterator_wrapper const& iter)
            {
                return *iter_ != *(iter.iter_);
            }

            /// Dereference (const version)
            inline T const& operator*() const
            {
                return get();
            }

            /// Dereference (non-const version)
            inline T& operator*()
            {
                return get();
            }
        };
    }
}
