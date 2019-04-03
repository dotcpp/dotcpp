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

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/Ptr.hpp>

namespace cl
{
    class Object;
    class StringImpl; class String;
    class TypeImpl; using Type = Ptr<TypeImpl>;

    /// <summary>
    /// All classes with reference semantics should derive from this type.
    /// It works with Ptr to provide an emulation of reference semantics in C++.
    /// </summary>
    class CL_DOTCPP_MAIN ObjectImpl
    {
        template<typename T>
        friend class Ptr;

    private: // FIELDS

        /// <summary>Reference count for intrusive pointer.</summary>
        std::atomic<unsigned int> refCount_ = 0;

    public: // DESTRUCTOR

        /// <summary>
        /// Virtual destructor to ensure that destructor
        /// of the derived type is called by Ptr.
        /// </summary>
        virtual ~ObjectImpl() = default;

    public: // METHODS

        /// <summary>Determines whether the specified object is equal to the current object.</summary>
        virtual bool Equals(Object obj);

        /// <summary>Serves as the default hash function.</summary>
        virtual size_t GetHashCode();

        /// <summary>Gets the Type of the current instance.</summary>
        virtual Type GetType();

        /// <summary>
        /// String that represents the current object.
        ///
        /// Default implementation returns full name of the class.
        /// </summary>
        virtual String ToString() const;

    protected: // CONSTRUCTORS

        /// <summary>Prevent construction on stack.</summary>
        ObjectImpl() = default;

    private: // CONSTRUCTORS

        /// <summary>Prevent copying object instead of copying pointer.</summary>
        ObjectImpl(const ObjectImpl&) = delete;

    private: // METHODS

        /// <summary>Increment reference count.</summary>
        void addRef()
        {
            ++refCount_;
        }

        /// <summary>Decrement reference count, deletes if decremented count is zero.</summary>
        void release()
        {
            if (!--refCount_)
            {
                delete this;
            }
        }

    private: // OPERATORS

        /// <summary>Prevent assignment of object instead of assignment of pointer.</summary>
        ObjectImpl& operator=(const ObjectImpl& rhs) = delete;
    };
}
