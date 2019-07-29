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
    namespace detail
    {

        struct std_object_iterator_base
        {

            using iterator_category = std::forward_iterator_tag;

            /// Destructor
            virtual ~std_object_iterator_base() {}

            /// Prefix notation (++iter)
            virtual std_object_iterator_base& operator++() = 0;

            /// Prefix notation, implemented via prefix notation
            inline std::unique_ptr<std_object_iterator_base> operator++(int)
            {
                std::unique_ptr<std_object_iterator_base> old(this->copy());
                this->operator++();
                return old;
            }

            /// Deep copy
            virtual std::unique_ptr<std_object_iterator_base> copy() = 0;

            /// Get wrapper (const version)
            virtual object const get() const = 0;

            /// Get wrapper (non-const version)
            virtual object get() = 0;

            /// Equality
            virtual bool operator ==(std_object_iterator_base const& iter) = 0;

            /// Inequality
            virtual bool operator !=(std_object_iterator_base const& iter) = 0;

            /// Dereference (const version)
            inline object const operator*() const { return get(); }

            /// Dereference (non-const version)
            inline object operator*() { return get(); }

        };

        template <class Iterator>
        inline std::unique_ptr<std_object_iterator_base>
            make_obj_iterator(Iterator const& iter);

        template <class Iterator>
        struct std_object_iterator : std_object_iterator_base
        {
            typedef object value_type;
            typedef std_object_iterator_base base;
            Iterator iter_;

            /// Create from the underlying STL iterator
            std_object_iterator(Iterator const& iter) : iter_(iter) {}

            /// Destructor
            virtual ~std_object_iterator() {}

            /// Prefix notation (++iter); postfix notation is implemented in base
            virtual base& operator++() override
            {
                ++iter_;
                return *this;
            }

            /// Deep copy
            virtual std::unique_ptr<base> copy() override
            {
                std::unique_ptr<base> old(make_obj_iterator(iter_));
                return old;
            }

            /// Get reference to the underlying type (const version)
            virtual value_type const get() const override
            {
                return *iter_;
            }

            /// Get reference to the underlying type (non-const version)
            virtual value_type get() override
            {
                return *iter_;
            }

            /// Equality
            virtual bool operator==(std_object_iterator_base const& iter) override
            {
                Iterator const& other = static_cast<std_object_iterator<Iterator> const&>(iter).iter_;
                return iter_ == other;
            }

            /// Inequality
            virtual bool operator!=(std_object_iterator_base const& iter) override
            {
                Iterator const& other = static_cast<std_object_iterator<Iterator> const&>(iter).iter_;
                return iter_ != other;
            }

        };

        struct std_object_iterator_wrapper
        {
            using iterator_category = std::forward_iterator_tag;

            std::unique_ptr<std_object_iterator_base> iter_;

            /// Create from unique pointer to the wrapped object
            std_object_iterator_wrapper(std::unique_ptr<std_object_iterator_base> && iter)
                :iter_(std::move(iter))
            {
            }

            /// Prefix notation (++iter)
            inline std_object_iterator_wrapper& operator++()
            {
                (*iter_)++;
                return *this;
            }

            /// Postfix notation (iter++)
            inline std_object_iterator_wrapper operator++(int)
            {
                std_object_iterator_wrapper old(this->copy());
                this->operator++();
                return old;
            }

            /// Deep copy
            inline std_object_iterator_wrapper copy()
            {
                return std_object_iterator_wrapper(iter_->copy());
            }

            /// Get reference to the underlying type (const version)
            inline object get() const
            {
                return iter_->get();
            }

            /// Get reference to the underlying type (non-const version)
            inline object get()
            {
                return iter_->get();
            }

            /// Equality
            inline bool operator==(std_object_iterator_wrapper const& iter)
            {
                return *iter_ == *(iter.iter_);
            }

            /// Inequality
            inline bool operator!=(std_object_iterator_wrapper const& iter)
            {
                return *iter_ != *(iter.iter_);
            }

            /// Dereference (const version)
            inline object operator*() const
            {
                return get();
            }

            /// Dereference (non-const version)
            inline object operator*()
            {
                return get();
            }
        };

        /// Unique pointer to std_iterator_base to permit assignment by base class
        template <class Iterator>
        inline std::unique_ptr<std_object_iterator_base>
            make_obj_iterator(Iterator const& iter)
        {
            typedef std::unique_ptr<std_object_iterator_base> return_type;
            return return_type(new std_object_iterator<Iterator>(iter));
        }
    }

}