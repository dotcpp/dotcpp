/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

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

#ifndef cl_dotcpp_main_ITEnumerator_hpp
#define cl_dotcpp_main_ITEnumerator_hpp

#include <cl/dotcpp/main/declare.hpp>

namespace cl
{
    namespace detail {

        template <typename T>
        struct std_iterator_base
        {
            virtual std_iterator_base& operator++ () = 0;

            virtual std::unique_ptr<std_iterator_base> operator++ (int)
            {
                std::unique_ptr<std_iterator_base> old(this->copy());
                this->operator ++();
                return old;
            }

            virtual std::unique_ptr<std_iterator_base> copy() = 0;

            virtual std::reference_wrapper<T>
                get() = 0;

            virtual std::reference_wrapper<T> const
                get() const = 0;

            inline bool
            operator == (std_iterator_base<T> const& iter)
            {
                return this->compare(iter) == 0;
            }

            inline bool
            operator > (std_iterator_base<T> const& iter)
            {
                return this->compare(iter) > 0;
            }

            inline bool
            operator < (std_iterator_base<T> const& iter)
            {
                return this->compare(iter) < 0;
            }
        private:
            /// this is actually similar compare string if equals = 0
            /// if this < cmp -> rslt < 0 : this > cmp -> rslt > 0
            virtual int compare(std_iterator_base<T> const&, bool only_equals = true) = 0;
        };

        template <typename Iterator>
        struct std_iterator;

        template <typename Iterator>
        inline std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type > >
            make_iterator(Iterator const& iter);

        template <typename Iterator>
        struct std_iterator : std_iterator_base<
                                typename std::remove_reference<decltype(Iterator(). operator*()) >::type
                            >
        {
            typedef typename
                std::remove_reference<decltype(Iterator(). operator*()) >::type value_type;

            typedef std_iterator_base<value_type> base;

            std_iterator(Iterator const& iter)
                : iter_(iter)
            {   }

            virtual std_iterator_base& operator++ ()  {
                ++iter_;
                return *this;
            }

            virtual std::unique_ptr<base> copy()
            {
                std::unique_ptr<base> old(make_iterator(iter_));
                return old;
            }

            virtual std::reference_wrapper<value_type>
            get()
            {
                return std::reference_wrapper<value_type >(*iter_);
            }

            virtual std::reference_wrapper<value_type> const
            get() const
            {
                return std::reference_wrapper<value_type >(*iter_);
            }

            virtual int compare(std_iterator_base<value_type> const& cmp, bool only_equals = true)
            {
                CHECK_TYPE_CAST(std_iterator<Iterator> const&, cmp);
                Iterator const& oth = static_cast<std_iterator<Iterator> const&>(cmp).iter_;
                return only_equals ?
                    (int)!(oth == this->iter_) : (false/*iter_ > oth*/ ? 1 : -((int)(oth == this->iter_)));
            }

            Iterator iter_;
        };

        template <typename Iterator>
        inline std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type > >
        make_iterator(Iterator const& iter)
        {
            typedef std::unique_ptr<std_iterator_base<typename std_iterator<Iterator>::value_type > > return_type;
            return return_type(new std_iterator<Iterator>(iter));
        }
    }

    class TBool {};

    /// Supports a simple iteration over a generic collection.
    template <class T>
    class ITEnumerator
        : std::random_access_iterator_tag
    {
    public: // METHODS
        typedef std::unique_ptr<detail::std_iterator_base<T > > iterator_type;

        // should be null
        ITEnumerator() = default;

        //!! Explicit constructor to converible from any other
        template <typename Iterator>
        explicit ITEnumerator(Iterator const& iter)
            : iterator_(detail::make_iterator(iter))
        {   }

        /// Gets the element in the collection at the current position of the enumerator.
        /// TODO can be reference
        std::reference_wrapper<T> current()
        {
            return iterator_->get();
        }

        /// Advances the enumerator to the next element of the collection.\\
        /// Returns true if the enumerator was successfully advanced to the next element;
        /// false if the enumerator has passed the end of the collection.
        TBool moveNext()
        {
            return TBool();
        }

        /// Sets the enumerator to its initial position, which is before the first element in the collection.
        void reset()
        {}

        inline ITEnumerator<T>& operator ++()
        {
            ++(*iterator_);
            return *this;
        }

        inline ITEnumerator<T> operator ++(int)
        {
            ITEnumerator<T> old(iterator_->copy());
            this->operator ++();
            return old;
        }

        std::reference_wrapper<T> operator*()
        {
            return iterator_->get();
        }

        std::reference_wrapper<T> const operator*() const
        {
            return iterator_->get();
        }

    private:
        inline detail::std_iterator_base<T > const& i_() const
        {
            return
        }
    public:
        ///
        inline bool
        compare(cl::ITEnumerator<T> const& c) const
        {
            // we should compare
            if (iterator_ && c.iterator_)
                return (*iterator_.get() == *c.iterator_.get());

            // TODO if both is null return true
            if (!iterator_ && !c.iterator_)
                return true;

            return false;
        }

    private:
        std::unique_ptr<detail::std_iterator_base<T > > iterator_;
    };

    template <typename Type>
    inline bool operator == (cl::ITEnumerator<Type> const& left
        , cl::ITEnumerator<Type> const& right)
    {
        return left.compare(right);
    }

    template <typename Type>
    inline bool operator != (cl::ITEnumerator<Type> const& left
        , cl::ITEnumerator<Type> const& right)
    {
        return !(left == right);
    }
}

#endif // cl_dotcpp_main_ITEnumerator_hpp
