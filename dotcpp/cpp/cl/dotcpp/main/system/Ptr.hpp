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

namespace cl
{
    class Null;

    /// <summary>
    /// Reference counted smart pointer based on std::shared_ptr
    /// with emulation of selected features of .NET references including
    /// type conversion using 'is' and 'as'.
    /// </summary>
    template <class T>
    class Ptr
    {
        template<class R> friend class Ptr;
        std::shared_ptr<T> ptr_;

        typedef T element_type;
        typedef std::shared_ptr<T> pointer_type;

    public: // CONSTRUCTORS

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        /// </summary>
        Ptr() {}

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        /// </summary>
        Ptr(T* ptr);

        /// <summary>
        /// Create from pointer to template argument base type.
        /// Shares reference count with argument.
        /// </summary>
        template <class R> Ptr(const Ptr<R>& rhs);

        /// <summary>Copy constructor. Shares reference count with argument.</summary>
        Ptr(const Ptr<T>& rhs);

        /// <summary>Create from shared_ptr. Shares reference count with argument.</summary>
        Ptr(const pointer_type& ptr);

    public: // METHODS

        /// <summary>Dynamic cast to type R, returns 0 if the cast fails.</summary>
        template <typename R>
        R as() const;

        /// <summary>Dynamic cast to type R, throws exception if the cast fails.</summary>
        template <typename R>
        R cast() const;

        /// <summary>Returns true if pointer holds object of type R, and false otherwise.</summary>
        template <typename R>
        bool is() const;

    public: // OPERATORS

        /// <summary>Pointer dereference.</summary>
        T& operator*() const;

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains
        /// pointer to the same instance as self.</summary>
        bool operator==(const Ptr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const Ptr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(Null* rhs) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(Null* rhs) const;

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits assignment of pointer to type derived from T.
        /// </summary>
        Ptr<T>& operator=(T* rhs);

        /// <summary>
        /// Assign pointer to template argument base type.
        /// Shares reference count with argument.
        /// </summary>
        template <class R> Ptr<T>& operator=(const Ptr<R>& rhs);

        /// <summary>
        /// Assign pointer of the same type.
        /// Shares reference count with argument.
        /// </summary>
        Ptr<T>& operator=(const Ptr<T>& rhs);

        /// <summary>Const indexer operator for arrays.</summary>
        template <typename I>
        decltype(auto) operator[](I const& i) const;

        /// <summary>Non-const indexer operator for arrays.</summary>
        template <typename I>
        decltype(auto) operator[](I const& i);
    };

    template <class T> Ptr<T>::Ptr(T* ptr) : ptr_(ptr) {}
    template <class T> template <class R> Ptr<T>::Ptr(const Ptr<R>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> Ptr<T>::Ptr(const Ptr<T>& rhs) : ptr_(rhs.ptr_) {}
    template <class T> Ptr<T>::Ptr(const pointer_type & ptr) : ptr_(ptr) {}
    template <typename T> template <typename R> R Ptr<T>::as() const { return std::dynamic_pointer_cast<typename R::element_type>(ptr_); }
    template <typename T> template <typename R> bool Ptr<T>::is() const { if (!ptr_) return false; return typeid(*ptr_) == typeid(R::element_type); }
    template <class T> T& Ptr<T>::operator*() const { T* p = ptr_.get(); if (!p) throw std::runtime_error("Pointer is not initialized"); return *p; }
    template <class T> T* Ptr<T>::operator->() const { T* p = ptr_.get(); if (!p) throw std::runtime_error("Pointer is not initialized"); return p; }
    template <class T> bool Ptr<T>::operator==(const Ptr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    template <class T> bool Ptr<T>::operator!=(const Ptr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    template <class T> bool Ptr<T>::operator==(Null* rhs) const { return ptr_.get() == nullptr; }
    template <class T> bool Ptr<T>::operator!=(Null* rhs) const { return ptr_.get() != nullptr; }
    template <class T> Ptr<T>& Ptr<T>::operator=(T* rhs) { ptr_.reset(rhs); return *this; }
    template <class T> template <class R> Ptr<T>& Ptr<T>::operator=(const Ptr<R>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> Ptr<T>& Ptr<T>::operator=(const Ptr<T>& rhs) { ptr_ = rhs.ptr_; return *this; }
    template <class T> template <typename I> decltype(auto) Ptr<T>::operator[](I const& i) const { return (*ptr_)[i]; }
    template <class T> template <typename I> decltype(auto) Ptr<T>::operator[](I const& i) { return (*ptr_)[i]; }

    template <typename T> 
    template <typename R> 
    R Ptr<T>::cast() const 
    {
        typename R::pointer_type ret = std::dynamic_pointer_cast<typename R::element_type>(ptr_);
        if (ret) 
            return ret;
        else 
            throw std::runtime_error("Cast cannot be performed.");
    }
}

