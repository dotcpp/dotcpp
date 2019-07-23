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

#include <dot/system/collections/generic/IEnumerator.hpp>

namespace dot
{
    template <class T> class IEnumerableImpl; template <class T> using IEnumerable = Ptr<IEnumerableImpl<T>>;
    template <class T> class IEnumeratorImpl; template <class T> using IEnumerator = Ptr<IEnumeratorImpl<T>>;

    /// <summary>
    /// Exposes the enumerator, which supports a simple iteration over a collection of a specified type.
    /// </summary>
    template <class T>
    class IEnumerableImpl : public virtual ObjectImpl
    {
    public: // METHODS

        /// <summary>Returns an enumerator that iterates through the collection.</summary>
        virtual IEnumerator<T> GetEnumerator() = 0;

        /// <summary>Returns forward begin iterator based on IEnumerator.</summary>
        detail::std_iterator_wrapper<T> begin()
        {
            return detail::std_iterator_wrapper<T>(std::move(GetEnumerator()->begin_iterator_));
        }

        /// <summary>Returns forward end iterator based on IEnumerator.</summary>
        detail::std_iterator_wrapper<T> end()
        {
            return detail::std_iterator_wrapper<T>(std::move(GetEnumerator()->end_iterator_));
        }
    };
}

namespace dot
{

    inline dot::detail::std_object_iterator_wrapper begin(dot::Ptr<dot::IObjectEnumerableImpl> & obj);
    inline dot::detail::std_object_iterator_wrapper end(dot::Ptr<dot::IObjectEnumerableImpl>& obj);

    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(dot::Ptr<T> & obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(dot::Ptr<T> & obj)
    {
        return obj->end();
    }

    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(dot::Ptr<T> const& obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(dot::Ptr<T> const& obj)
    {
        return obj->end();
    }

}