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
    /// All classes with reference semantics should derive from this type.
    /// It works with ptr to provide an emulation of reference semantics in C++.
    class reference_counter
    {
    private: // FIELDS

        /// Reference count for intrusive pointer.
        std::atomic<unsigned int> reference_count_ = 0;

    public: // DESTRUCTOR

        /// Virtual destructor to ensure that destructor
        /// of the derived type is called by ptr.
        virtual ~reference_counter() = default;

    public: // METHODS

        /// Increment reference count.
        void increment_reference_count()
        {
            ++reference_count_;
        }

        /// Decrement reference count, deletes if decremented count is zero.
        void decrement_reference_count()
        {
            if (!--reference_count_)
            {
                delete this;
            }
        }

    protected: // CONSTRUCTORS

        /// Prevent construction on stack.
        reference_counter() = default;

    private: // CONSTRUCTORS

        /// Prevent copying object instead of copying pointer.
        reference_counter(const reference_counter&) = delete;

    private: // OPERATORS

        /// Prevent assignment of object instead of assignment of pointer.
        reference_counter& operator=(const reference_counter& rhs) = delete;
    };
}
