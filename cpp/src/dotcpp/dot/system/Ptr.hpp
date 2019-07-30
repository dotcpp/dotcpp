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

#include <dot/declare.hpp>
#include <dot/detail/reference_counter.hpp>

namespace dot
{
    class Null;

    /// <summary>
    /// Reference counted smart pointer based on std::shared_ptr
    /// with emulation of selected features of .NET references including
    /// type conversion using 'is' and 'as'.
    /// </summary>
    template <class T>
    class ptr
    {
        template<class R> friend class ptr;

    public: // TYPEDEF

        typedef T element_type;
        typedef T* pointer_type;

    private: // FIELDS

        T* ptr_;

    public: // CONSTRUCTORS

        /// <summary>Create empty pointer.</summary>
        ptr();

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        /// </summary>
        ptr(T* p);

        /// <summary>Implicit conversion from derived to base pointer (does not use dynamic cast).</summary>
        template <class R> ptr(const ptr<R>& rhs, typename std::enable_if<std::is_base_of<T, R>::value>::type* p = 0);

        /// <summary>
        /// Explicit conversion from base to derived or sibling pointer (uses dynamic cast).
        ///
        /// Error message if the cast fails because the two types are unrelated.
        /// </summary>
        template <class R> explicit ptr(const ptr<R>& rhs, typename std::enable_if<!std::is_base_of<T, R>::value>::type* p = 0);

        /// <summary>Copy constructor for the pointer (does not copy T).</summary>
        ptr(const ptr<T>& rhs);

    public: // DESTRUCTOR

        /// <summary>Decrements reference count if not empty.</summary>
        ~ptr();

    public: // METHODS

        /// <summary>Dynamic cast to type R, returns 0 if the cast fails.</summary>
        template <class R>
        R as() const;

        /// <summary>Returns true if pointer holds object of type R, and false otherwise.</summary>
        template <class R>
        bool is() const;

        /// <summary>Returns true if pointer holds object, and false otherwise.</summary>
        bool IsEmpty();

    public: // OPERATORS

        /// <summary>Pointer dereference.</summary>
        T& operator*() const;

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains
        /// pointer to the same instance as self.</summary>
        bool operator==(const ptr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const ptr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(nullptr_t) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(nullptr_t) const;

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits assignment of pointer to type derived from T.
        /// </summary>
        ptr<T>& operator=(T* rhs);

        /// <summary>
        /// Assign pointer to template argument base type. // TODO - use SFINAE to detemine if dynamic cast is needed
        /// </summary>
        template <class R> ptr<T>& operator=(const ptr<R>& rhs);

        /// <summary>Assign pointer of the same type.</summary>
        ptr<T>& operator=(const ptr<T>& rhs);

        /// <summary>Const indexer operator for arrays.</summary>
        template <class I>
        decltype(auto) operator[](I const& i) const;

        /// <summary>Non-const indexer operator for arrays.</summary>
        template <class I>
        decltype(auto) operator[](I const& i);
    };

    template <class T> ptr<T>::ptr() : ptr_(nullptr) {}
    template <class T> ptr<T>::ptr(T* p) : ptr_(p) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> template <class R> ptr<T>::ptr(const ptr<R>& rhs, typename std::enable_if<std::is_base_of<T, R>::value>::type* p) : ptr_(rhs.ptr_) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> template <class R> ptr<T>::ptr(const ptr<R>& rhs, typename std::enable_if<!std::is_base_of<T, R>::value>::type* p) : ptr_(nullptr)
    {
        // If argument is null, ptr_ should also remain null
        if (rhs.ptr_)
        {
            // Perform dynamic cast from base to derived
            T* p = dynamic_cast<T*>(rhs.ptr_);

            // Check that dynamic cast succeeded
            if (!p) throw std::runtime_error("Cast cannot be performed."); // TODO Use typeof(...) and type() to provide specific types in the error message

            // Current pointer now contains the result of dynamic_cast
            ptr_ = p;

            // Increment reference count
            ptr_->IncrementReferenceCount();
        }
    }
    template <class T> ptr<T>::ptr(const ptr<T>& rhs) : ptr_(rhs.ptr_) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> ptr<T>::~ptr() { if (ptr_) ptr_->DecrementReferenceCount(); }
    template <class T> template <class R> R ptr<T>::as() const { typename R::pointer_type p = dynamic_cast<typename R::pointer_type>(ptr_); return p; }
    template <class T> template <class R> bool ptr<T>::is() const { return dynamic_cast<typename R::pointer_type>(ptr_); }
    template <class T> T& ptr<T>::operator*() const
    {
        if (!ptr_)
            throw std::runtime_error("Pointer is not initialized");
        return *ptr_;
    }
    template <class T> T* ptr<T>::operator->() const
    {
        if (!ptr_)
            throw std::runtime_error("Pointer is not initialized");
        return ptr_;
    }
    template <class T> bool ptr<T>::operator==(const ptr<T>& rhs) const { return ptr_ == rhs.ptr_; } // TODO check when comparison is performed by value
    template <class T> bool ptr<T>::operator!=(const ptr<T>& rhs) const { return ptr_ != rhs.ptr_; } // TODO check when comparison is performed by value
    template <class T> bool ptr<T>::operator==(nullptr_t) const { return ptr_ == nullptr; }
    template <class T> bool ptr<T>::operator!=(nullptr_t) const { return ptr_ != nullptr; }
    template <class T> ptr<T>& ptr<T>::operator=(T* rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs) rhs->IncrementReferenceCount(); ptr_ = rhs; return *this; }
    template <class T> template <class R> ptr<T>& ptr<T>::operator=(const ptr<R>& rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs.ptr_) rhs.ptr_->IncrementReferenceCount(); ptr_ = rhs.ptr_; return *this; }
    template <class T> ptr<T>& ptr<T>::operator=(const ptr<T>& rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs.ptr_) rhs.ptr_->IncrementReferenceCount(); ptr_ = rhs.ptr_; return *this; }
    template <class T> template <class I> decltype(auto) ptr<T>::operator[](I const& i) const { return (*ptr_)[i]; }
    template <class T> template <class I> decltype(auto) ptr<T>::operator[](I const& i) { return (*ptr_)[i]; }
    template <class T> bool ptr<T>::IsEmpty() { return !ptr_; }

    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(dot::ptr<T> & obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(dot::ptr<T> & obj)
    {
        return obj->end();
    }

    /// <summary>Implements begin() used by STL and similar algorithms.</summary>
    template <class T>
    auto begin(dot::ptr<T> const& obj)
    {
        return obj->begin();
    }

    /// <summary>Implements end() used by STL and similar algorithms.</summary>
    template <class T>
    auto end(dot::ptr<T> const& obj)
    {
        return obj->end();
    }
}

namespace std
{
    /// <summary>Implements hash struct used by STL unordered_map for ptr.</summary>
    template <typename T>
    struct hash<dot::ptr<T>>
    {
        size_t operator()(const dot::ptr<T>& obj) const
        {
            return obj->GetHashCode();
        }
    };

    /// <summary>Implements equal_to struct used by STL unordered_map for ptr.</summary>
    template <typename T>
    struct equal_to<dot::ptr<T>>
    {
        bool operator()(const dot::ptr<T>& lhs, const dot::ptr<T>& rhs) const
        {
            return lhs->Equals(rhs);
        }
    };
}
