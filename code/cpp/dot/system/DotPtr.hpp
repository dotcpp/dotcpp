/*
Copyright (C) 2003-2015 CompatibL

This file is part of DotCpp project, an implementation of
selected .NET class libraries in native C++ available from

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

#ifndef __dot_system_DotPtr_hpp__
#define __dot_system_DotPtr_hpp__

#include <dot/system/declare.hpp>

namespace dot
{
    class DotNull;

    /// <summary>Reference counted smart pointer based on std::shared_ptr
    /// with emulation of selected features of .NET references including
    /// type conversion using 'is' and 'as'.</summary>
    template <class T>
    class DotPtr
    {
        template<class R> friend class DotPtr;
        std::shared_ptr<T> ptr_;

    public: // CONSTRUCTORS

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits construction from null pointer.</summary>
        DotPtr(T* ptr);

        /// <summary>Create from pointer to template argument base type.\\
        /// Shares reference count with argument.</summary>
        template <class R> DotPtr(const DotPtr<R>& rhs);

        /// <summary>Copy constructor. Shares reference count with argument.</summary>
        DotPtr(const DotPtr<T>& rhs);

    public: // OPERATORS

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains
        /// pointer to the same instance as self.</summary>
        bool operator==(const DotPtr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const DotPtr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(DotNull* rhs) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(DotNull* rhs) const;

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits assignment of pointer to type derived from T.</summary>
        DotPtr<T>& operator=(T* rhs);

        /// <summary>Assign pointer to template argument base type.
        /// Shares reference count with argument.</summary>
        template <class R> DotPtr<T>& operator=(const DotPtr<R>& rhs);

        /// <summary>Assign pointer of the same type.\\
        /// Shares reference count with argument.</summary>
        DotPtr<T>& operator=(const DotPtr<T>& rhs);
    };

    template <class T> DotPtr<T>::DotPtr(T* ptr) : ptr_(ptr) {}
    template <class T> template <class R> DotPtr<T>::DotPtr(const DotPtr<R>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> DotPtr<T>::DotPtr(const DotPtr<T>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> T* DotPtr<T>::operator->() const { T* p = ptr_.get(); if (!p) throw DotException("Pointer is not initialized"); return p; }
    template <class T> bool DotPtr<T>::operator==(const DotPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    template <class T> bool DotPtr<T>::operator!=(const DotPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    template <class T> bool DotPtr<T>::operator==(DotNull* rhs) const { return ptr_.get() == nullptr; }
    template <class T> bool DotPtr<T>::operator!=(DotNull* rhs) const { return ptr_.get() != nullptr; }
    template <class T> DotPtr<T>& DotPtr<T>::operator=(T* rhs) { ptr_.reset(rhs); return *this; }
    template <class T> template <class R> DotPtr<T>& DotPtr<T>::operator=(const DotPtr<R>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> DotPtr<T>& DotPtr<T>::operator=(const DotPtr<T>& rhs) { ptr_ = rhs.ptr_; return *this; }
}

#endif  // __dot_system_DotPtr_hpp__
