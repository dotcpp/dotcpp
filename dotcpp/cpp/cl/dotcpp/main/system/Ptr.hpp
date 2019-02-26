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

#ifndef cl_dotcpp_main_Ptr_hpp
#define cl_dotcpp_main_Ptr_hpp

#include <cl/system/declare.hpp>

namespace cl
{
    class TNull;

    /// <summary>Reference counted smart pointer based on std::shared_ptr
    /// with emulation of selected features of .NET references including
    /// type conversion using 'is' and 'as'.</summary>
    template <class T>
    class TPtr
    {
        template<class R> friend class TPtr;
        std::shared_ptr<T> ptr_;

    public: // CONSTRUCTORS

    	/// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits construction from null pointer.</summary>
		TPtr() {}

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits construction from null pointer.</summary>
        TPtr(T* ptr);

        /// <summary>Create from pointer to template argument base type.\\
        /// Shares reference count with argument.</summary>
        template <class R> TPtr(const TPtr<R>& rhs);

        /// <summary>Copy constructor. Shares reference count with argument.</summary>
        TPtr(const TPtr<T>& rhs);

    public: // OPERATORS

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains
        /// pointer to the same instance as self.</summary>
        bool operator==(const TPtr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const TPtr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(TNull* rhs) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(TNull* rhs) const;

        /// <summary>Take ownership of raw pointer to template argument type.\\
        /// This also permits assignment of pointer to type derived from T.</summary>
        TPtr<T>& operator=(T* rhs);

        /// <summary>Assign pointer to template argument base type.
        /// Shares reference count with argument.</summary>
        template <class R> TPtr<T>& operator=(const TPtr<R>& rhs);

        /// <summary>Assign pointer of the same type.\\
        /// Shares reference count with argument.</summary>
        TPtr<T>& operator=(const TPtr<T>& rhs);

        /// <summary>Const indexer operator for arrays.</summary>
        auto operator[](int i) const;

        /// <summary>Non-const ndexer operator for arrays.</summary>
        auto operator[](int i);
    };

    template <class T> TPtr<T>::TPtr(T* ptr) : ptr_(ptr) {}
    template <class T> template <class R> TPtr<T>::TPtr(const TPtr<R>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> TPtr<T>::TPtr(const TPtr<T>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> T* TPtr<T>::operator->() const { T* p = ptr_.get(); if (!p) throw std::exception("Pointer is not initialized"); return p; }
    template <class T> bool TPtr<T>::operator==(const TPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    template <class T> bool TPtr<T>::operator!=(const TPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    template <class T> bool TPtr<T>::operator==(TNull* rhs) const { return ptr_.get() == nullptr; }
    template <class T> bool TPtr<T>::operator!=(TNull* rhs) const { return ptr_.get() != nullptr; }
    template <class T> TPtr<T>& TPtr<T>::operator=(T* rhs) { ptr_.reset(rhs); return *this; }
    template <class T> template <class R> TPtr<T>& TPtr<T>::operator=(const TPtr<R>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> TPtr<T>& TPtr<T>::operator=(const TPtr<T>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> auto TPtr<T>::operator[](int i) const { return (*ptr_)[i]; }
    template <class T> auto TPtr<T>::operator[](int i) { return (*ptr_)[i]; }
}

#endif  // cl_dotcpp_main_Ptr_hpp
