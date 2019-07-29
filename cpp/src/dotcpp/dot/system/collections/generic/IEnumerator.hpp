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

#include <dot/system/Object.hpp>
#include <dot/detail/iterator.hpp>

namespace dot
{
    template <class T> class IEnumeratorImpl; template <class T> using IEnumerator = ptr<IEnumeratorImpl<T>>;

    /// <summary>
    /// Supports a simple iteration over a generic collection.
    /// </summary>
    template <class T>
    class IEnumeratorImpl : public virtual ObjectImpl
    {
        template <class Iterator> friend IEnumerator<typename Iterator::value_type> new_Enumerator(Iterator const&, Iterator const&);
        template <class R> friend class IEnumerableImpl;

    private: // FIELDS

        std::unique_ptr<detail::std_iterator_base<T> > begin_iterator_;
        std::unique_ptr<detail::std_iterator_base<T> > end_iterator_;
        std::unique_ptr<detail::std_iterator_base<T> > current_iterator_;

        template <class Iterator>
        explicit IEnumeratorImpl(Iterator const& beginPos, Iterator const& endPos)
            :
            begin_iterator_(detail::make_iterator(beginPos)),
            end_iterator_(detail::make_iterator(endPos)),
            current_iterator_()
        {
        }

    public: // METHODS

        /// <summary>
        /// Gets the element in the collection at the current position of the enumerator (const version).
        /// </summary>
        T getCurrent() const
        {
            return current_iterator_->get();
        }

        /// <summary>
        /// Advances the enumerator to the next element of the collection.
        ///
        /// Returns true if the enumerator was successfully advanced to the next element;
        /// false if the enumerator has passed the end of the collection.
        /// </summary>
        bool MoveNext()
        {
            // Create if null
            if (!current_iterator_)
            {
                current_iterator_ = begin_iterator_->copy();
            }
            else
            {
                // Check before advancing because the iterator may already be at
                // the end of the collection, e.g. if the collection has zero size
                if (*current_iterator_ == *end_iterator_)
                    return false;

                // Advance iterator to the next position
                current_iterator_->operator ++();
            }

            // Check again after advancing if we are now at the end of the collection
            if (*current_iterator_ == *end_iterator_) return false;
            else return true;
        }

        /// <summary>
        /// Sets the enumerator to its initial position, which is
        /// before the first element in the collection.
        /// </summary>
        void Reset()
        {
            current_iterator_.reset();
        }
    };

    /// <summary>
    /// Create from begin() and end() iterator positions for the underlying collection.
    /// </summary>
    template <class Iterator>
    IEnumerator<typename Iterator::value_type> new_Enumerator(Iterator const& beginPos, Iterator const& endPos)
    {
        return new IEnumeratorImpl<typename Iterator::value_type>(beginPos, endPos);
    }
}
