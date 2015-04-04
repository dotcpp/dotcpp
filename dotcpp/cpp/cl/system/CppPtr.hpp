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

#ifndef __cl_system_CppPtr_hpp__
#define __cl_system_CppPtr_hpp__

#include <cl/system/declare.hpp>

namespace cl
{
    class CppNull;

    /// <summary>Reference counted smart pointer based on std::shared_ptr
    /// with emulation of selected features of .NET references including
    /// type conversion using 'is' and 'as'.</summary>
    template <class T>
    class CppPtr
    {
        template<class R> friend class CppPtr;
        std::shared_ptr<T> ptr_;

    public: // CONSTRUCTORS

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits construction from null pointer.</summary>
        CppPtr(T* ptr);

        /// <summary>Create from pointer to template argument base type.\\
        /// Shares reference count with argument.</summary>
        template <class R> CppPtr(const CppPtr<R>& rhs);

        /// <summary>Copy constructor. Shares reference count with argument.</summary>
        CppPtr(const CppPtr<T>& rhs);

    public: // OPERATORS

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains
        /// pointer to the same instance as self.</summary>
        bool operator==(const CppPtr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const CppPtr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(CppNull* rhs) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(CppNull* rhs) const;

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits assignment of pointer to type derived from T.</summary>
        CppPtr<T>& operator=(T* rhs);

        /// <summary>Assign pointer to template argument base type.
        /// Shares reference count with argument.</summary>
        template <class R> CppPtr<T>& operator=(const CppPtr<R>& rhs);

        /// <summary>Assign pointer of the same type.\\
        /// Shares reference count with argument.</summary>
        CppPtr<T>& operator=(const CppPtr<T>& rhs);
    };

    template <class T> CppPtr<T>::CppPtr(T* ptr) : ptr_(ptr) {}
    template <class T> template <class R> CppPtr<T>::CppPtr(const CppPtr<R>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> CppPtr<T>::CppPtr(const CppPtr<T>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> T* CppPtr<T>::operator->() const { T* p = ptr_.get(); if (!p) throw CppException("Pointer is not initialized"); return p; }
    template <class T> bool CppPtr<T>::operator==(const CppPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    template <class T> bool CppPtr<T>::operator!=(const CppPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    template <class T> bool CppPtr<T>::operator==(CppNull* rhs) const { return ptr_.get() == nullptr; }
    template <class T> bool CppPtr<T>::operator!=(CppNull* rhs) const { return ptr_.get() != nullptr; }
    template <class T> CppPtr<T>& CppPtr<T>::operator=(T* rhs) { ptr_.reset(rhs); return *this; }
    template <class T> template <class R> CppPtr<T>& CppPtr<T>::operator=(const CppPtr<R>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> CppPtr<T>& CppPtr<T>::operator=(const CppPtr<T>& rhs) { ptr_ = rhs.ptr_; return *this; }
}

#endif  // __cl_system_CppPtr_hpp__
