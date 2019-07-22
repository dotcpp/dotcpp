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

#include <dot/declare.hpp>
#include <dot/detail/reference_counter.hpp>

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

    public: // TYPEDEF

        typedef T element_type;
        typedef T* pointer_type;

    private: // FIELDS

        T* ptr_;

    public: // CONSTRUCTORS

        /// <summary>Create empty pointer.</summary>
        Ptr();

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.
        /// </summary>
        Ptr(T* ptr);

        /// <summary>Implicit conversion from derived to base pointer (does not use dynamic cast).</summary>
        template <class R> Ptr(const Ptr<R>& rhs, typename std::enable_if<std::is_base_of<T, R>::value>::type* p = 0);

        /// <summary>
        /// Explicit conversion from base to derived or sibling pointer (uses dynamic cast).
        ///
        /// Error message if the cast fails because the two types are unrelated.
        /// </summary>
        template <class R> explicit Ptr(const Ptr<R>& rhs, typename std::enable_if<!std::is_base_of<T, R>::value>::type* p = 0);

        /// <summary>Copy constructor for the pointer (does not copy T).</summary>
        Ptr(const Ptr<T>& rhs);

    public: // DESTRUCTOR

        /// <summary>Decrements reference count if not empty.</summary>
        ~Ptr();

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
        bool operator==(const Ptr<T>& rhs) const;

        /// <summary>Returns true if the argument does
        /// not contain pointer to the same instance as self.</summary>
        bool operator!=(const Ptr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(nullptr_t) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(nullptr_t) const;

        /// <summary>
        /// Take ownership of raw pointer to template argument type.
        /// This also permits assignment of pointer to type derived from T.
        /// </summary>
        Ptr<T>& operator=(T* rhs);

        /// <summary>
        /// Assign pointer to template argument base type. // TODO - use SFINAE to detemine if dynamic cast is needed
        /// </summary>
        template <class R> Ptr<T>& operator=(const Ptr<R>& rhs);

        /// <summary>Assign pointer of the same type.</summary>
        Ptr<T>& operator=(const Ptr<T>& rhs);

        /// <summary>Const indexer operator for arrays.</summary>
        template <class I>
        decltype(auto) operator[](I const& i) const;

        /// <summary>Non-const indexer operator for arrays.</summary>
        template <class I>
        decltype(auto) operator[](I const& i);
    };

    template <class T> Ptr<T>::Ptr() : ptr_(nullptr) {}
    template <class T> Ptr<T>::Ptr(T* ptr) : ptr_(ptr) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> template <class R> Ptr<T>::Ptr(const Ptr<R>& rhs, typename std::enable_if<std::is_base_of<T, R>::value>::type* p) : ptr_(rhs.ptr_) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> template <class R> Ptr<T>::Ptr(const Ptr<R>& rhs, typename std::enable_if<!std::is_base_of<T, R>::value>::type* p) : ptr_(nullptr)
    {
        // If argument is null, ptr_ should also remain null
        if (rhs.ptr_)
        {
            // Perform dynamic cast from base to derived
            T* ptr = dynamic_cast<T*>(rhs.ptr_);

            // Check that dynamic cast succeeded
            if (!ptr) throw std::runtime_error("Cast cannot be performed."); // TODO Use typeof(...) and GetType() to provide specific types in the error message

            // Current pointer now contains the result of dynamic_cast
            ptr_ = ptr;

            // Increment reference count
            ptr_->IncrementReferenceCount();
        }
    }
    template <class T> Ptr<T>::Ptr(const Ptr<T>& rhs) : ptr_(rhs.ptr_) { if (ptr_) ptr_->IncrementReferenceCount(); }
    template <class T> Ptr<T>::~Ptr() { if (ptr_) ptr_->DecrementReferenceCount(); }
    template <class T> template <class R> R Ptr<T>::as() const { typename R::pointer_type ptr = dynamic_cast<typename R::pointer_type>(ptr_); return ptr; }
    template <class T> template <class R> bool Ptr<T>::is() const { return dynamic_cast<typename R::pointer_type>(ptr_); }
    template <class T> T& Ptr<T>::operator*() const
    {
        if (!ptr_)
        throw std::runtime_error("Pointer is not initialized");
    return *ptr_;
    }
    template <class T> T* Ptr<T>::operator->() const
    {
        if (!ptr_)
            throw std::runtime_error("Pointer is not initialized");
        return ptr_;
    }
    template <class T> bool Ptr<T>::operator==(const Ptr<T>& rhs) const { return ptr_ == rhs.ptr_; } // TODO check when comparison is performed by value
    template <class T> bool Ptr<T>::operator!=(const Ptr<T>& rhs) const { return ptr_ != rhs.ptr_; } // TODO check when comparison is performed by value
    template <class T> bool Ptr<T>::operator==(nullptr_t) const { return ptr_ == nullptr; }
    template <class T> bool Ptr<T>::operator!=(nullptr_t) const { return ptr_ != nullptr; }
    template <class T> Ptr<T>& Ptr<T>::operator=(T* rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs) rhs->IncrementReferenceCount(); ptr_ = rhs; return *this; }
    template <class T> template <class R> Ptr<T>& Ptr<T>::operator=(const Ptr<R>& rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs.ptr_) rhs.ptr_->IncrementReferenceCount(); ptr_ = rhs.ptr_; return *this; }
    template <class T> Ptr<T>& Ptr<T>::operator=(const Ptr<T>& rhs) { if (ptr_) ptr_->DecrementReferenceCount(); if (rhs.ptr_) rhs.ptr_->IncrementReferenceCount(); ptr_ = rhs.ptr_; return *this; }
    template <class T> template <class I> decltype(auto) Ptr<T>::operator[](I const& i) const { return (*ptr_)[i]; }
    template <class T> template <class I> decltype(auto) Ptr<T>::operator[](I const& i) { return (*ptr_)[i]; }
    template <class T> bool Ptr<T>::IsEmpty() { return !ptr_; }
}

namespace std
{
    /// <summary>Implements hash struct used by STL unordered_map for Ptr.</summary>
    template <typename T>
    struct hash<cl::Ptr<T>>
    {
        size_t operator()(const cl::Ptr<T>& obj) const
        {
            return obj->GetHashCode();
        }
    };

    /// <summary>Implements equal_to struct used by STL unordered_map for Ptr.</summary>
    template <typename T>
    struct equal_to<cl::Ptr<T>>
    {
        bool operator()(const cl::Ptr<T>& lhs, const cl::Ptr<T>& rhs) const
        {
            return lhs->Equals(rhs);
        }
    };
}
