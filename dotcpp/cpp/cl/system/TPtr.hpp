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

#ifndef cl_system_TPtr_hpp
#define cl_system_TPtr_hpp

# include <boost/shared_ptr.hpp>
# include <boost/intrusive_ptr.hpp>
# include <cl/system/detail/assert.hpp>
# include <cl/system/detail/check_operators.hpp>
# include <cl/system/detail/ref_counter.hpp>
# include <cl/system/detail/intrusive_ptr_reliable.hpp>


namespace cl
{
    /// <summary>Traits of ptr.</summary>
    struct traits_ptr
    {
        static const size_t PointerTag = 0x270926F50F90F486;
    };

    /// <summary>Reference counted smart pointer type.
    /// T must inherit from IClObject.</summary>
    template <class T>
    class TPtr
        : public ::cl::type_operators_resolver<T>::type
    {
        template<class R> friend class TPtr;

        template <typename T>
        friend typename std::enable_if<cl::ref_countable<T>::value, void>::type
        create_TPtr(TPtr<T> const* c);

        template <typename T>
        friend typename std::enable_if<!cl::ref_countable<T>::value, void>::type
        create_TPtr(TPtr<T> const* c);

        template <typename Type, typename Other>
        friend inline TPtr<Type> dynamic_cast_clptr(TPtr<Other> const& ptr);

        template <class Interface>
        friend class cl::TPtr;

        template <typename Type>
        using InnerPtr = typename detail::take_type_ptr<Type>::type;

        TPtr(InnerPtr<T> const& ptr)
            : ptr_(ptr)
        {}

    public: //  CONSTRUCTORS

        /// <summary>
        ///   Empty value created
        /// </summary>
        TPtr() : ptr_()
        {}

        /// <summary>Take ownership of raw pointer to template argument type.
        /// This also permits construction from null pointer.</summary>
        TPtr(T* ptr);

        /// <summary>Create from pointer to template argument base type. Shares reference count with argument.</summary>
        template <class R> TPtr(const TPtr<R>& rhs);

        /// <summary>Copy constructor. Shares reference count with argument.</summary>
        TPtr(const TPtr<T>& rhs);

        /// <summary>Associate with the specified field in a data structure.</summary>
        TPtr(const ClFieldInfo& fieldInfo);

        inline T* check_(bool enable_default_ctor = true);

        void* operator new(size_t size);

        template <typename... Arg>
        TPtr(Arg... args);

        TPtr(TPtr<T>* p);

        template <class R> TPtr(TPtr<R> * rhs);

        TPtr(nullptr_t);

        virtual ~TPtr() = default;

    public: //  METHODS

        /// <summary>(IClObject) Perform dynamic cast to the specified interface.
        /// This method returns null pointer if the cast fails.</summary>
        //template <class R> TPtr<R> as() const;

    public: //  OPERATORS

        /// <summary>Pointer dereference.</summary>
        T* operator->() const;

        /// <summary>Returns true if the argument contains pointer to the same instance as self.</summary>
        bool operator==(const TPtr<T>& rhs) const;

        /// <summary>Returns true if the argument does not contain pointer to the same instance as self.</summary>
        bool operator!=(const TPtr<T>& rhs) const;

        /// <summary>Supports ptr == nullptr.</summary>
        bool operator==(ClNull* rhs) const;

        /// <summary>Supports ptr != nullptr.</summary>
        bool operator!=(ClNull* rhs) const;

        /// <summary>Take ownership of raw pointer to template argument type.</summary>
        /// This also permits assignment of pointer to type derived from T.</summary>
        TPtr<T>& operator=(T* rhs);

        /// <summary> Get pointer value.</summary>
        operator bool()
        {
            return this->get() != nullptr;
        }

        /// <summary>Assign pointer to template argument base type. Shares reference count with argument.</summary>
        template <class R> TPtr<T>& operator=(const TPtr<R>& rhs);

        /// <summary>Assign pointer of the same type. Shares reference count with argument.</summary>
        TPtr<T>& operator=(const TPtr<T>& rhs);

        /// <summary> Get pointer value.</summary>
        inline T* get() const
        {
            return ptr_.get();
        }

        /// <summary> take pointer refference  </summary>
        typename T& operator* () const
        {
            return *ptr_;
        }

        /// <summary>Set field from fields lookup.</summary>
        void SetIsField(bool isField) { isField_ = isField; }
    private: // PRIVATE METHODS

        /// <summary>Create on demand if self is marked as a field, do nothing otherwise.</summary>
        TPtr<T> const& createIfField() const;

    public:
        /// <summary> private fields </summary>
        mutable typename detail::take_type_ptr<T>::type ptr_;

        /// TODO: m/b is reasonable to move this logic
        /// <summary>
        ///   is field traits
        /// </summary>
        bool isField_ = false;
    };

    template <class T> 
    inline T* TPtr<T>::check_(bool enable_default_ctor /*= true*/)
    {
        bool is_new_used = *(reinterpret_cast<__int64*>(this)) == traits_ptr::PointerTag;

        if (!enable_default_ctor && !is_new_used)
            cl::throw_("Check error, m\b allocated on a stack.");

        return reinterpret_cast<T*>(is_new_used ? traits_ptr::PointerTag : 0);
    }

    template <class T>
    void* TPtr<T>::operator new(size_t size)
    {
        //TODO: m\b indentyifier set vefore,
        //and return pointer after id
        //like return ptr + sizeof(ID);
        //it means we will able to check id of object by ptr
        void* ptr = malloc(sizeof(T));
        *(__int64 *)ptr = traits_ptr::PointerTag;

        return ptr;
    }

    template <class T>
    template <typename... Arg>
    TPtr<T>::TPtr(Arg... args) : ptr_(check_(), false)
    {
        static_assert(sizeof(typename detail::take_type_ptr<T>::type) < sizeof(T) || std::is_abstract<T>::value
            , "Can not use this type for TPtr.");

        T* ptr = (T*)this;
        new (ptr)T(args...);
    }

    template <class T>
    TPtr<T>::TPtr(TPtr<T>* p) : ptr_((T*)p)
    {
    }

    template <class T>
    template <class R>
    TPtr<T>::TPtr(TPtr<R> * rhs)
        : ptr_(boost::dynamic_pointer_cast<T>((T*)rhs))
    {
    }

    template <class T>
    TPtr<T>::TPtr(nullptr_t) : ptr_(nullptr)
    {
    }

    template <class T> TPtr<T>::TPtr(T* ptr)
        : ptr_(ptr)
    {
    }

    template <class T> template <class R> TPtr<T>::TPtr(const TPtr<R>& rhs)
        : ptr_(boost::dynamic_pointer_cast<T>(rhs.createIfField().ptr_))
    {}

    template <class T> TPtr<T>::TPtr(const TPtr<T>& rhs)
        : ptr_(rhs.createIfField().ptr_) {}

    template <class T> TPtr<T>::TPtr(const ClFieldInfo& fieldInfo) : isField_(true) { fieldInfo.registerField(this); }
    template <class T> T* TPtr<T>::operator->() const { createIfField(); T* p = ptr_.get(); if (!p) throw std::exception("Pointer is not initialized"); return p; }
    template <class T> bool TPtr<T>::operator==(const TPtr<T>& rhs) const { return ptr_ == rhs.ptr_; }
    template <class T> bool TPtr<T>::operator!=(const TPtr<T>& rhs) const { return ptr_ != rhs.ptr_; }
    template <class T> bool TPtr<T>::operator==(ClNull* rhs) const { return ptr_.get() == nullptr; }
    template <class T> bool TPtr<T>::operator!=(ClNull* rhs) const { return ptr_.get() != nullptr; }
    template <class T> TPtr<T>& TPtr<T>::operator=(T* rhs) { ptr_.reset(rhs); return *this; }
    template <class T> template <class R> TPtr<T>& TPtr<T>::operator=(const TPtr<R>& rhs) { ptr_ = rhs.createIfField().ptr_; return *this; }
    template <class T> TPtr<T>& TPtr<T>::operator=(const TPtr<T>& rhs) { ptr_ = rhs.createIfField().ptr_; return *this; }

    template <class T, typename R> TPtr<T> operator+ (TPtr<T> const& lhs, R const& rhs) { return lhs->operator+(rhs); }
    template <class T, typename R> TPtr<T> operator- (TPtr<T> const& lhs, R const& rhs) { return lhs->operator-(rhs); }
    template <class T, typename R> TPtr<T> operator* (TPtr<T> const& lhs, R const& rhs) { return lhs->operator*(rhs); }
    template <class T, typename R> TPtr<T> operator/ (TPtr<T> const& lhs, R const& rhs) { return lhs->operator/(rhs); }

    namespace detail
    {
        template <typename T>
        typename std::enable_if<cl::ref_countable<T>::value, void>::type
        create_TPtr(TPtr<T> const* c)
        {
            c->ptr_ = boost::dynamic_pointer_cast<T>(detail::create_<T>(std::is_abstract<T>()).ptr_);
        }

        template <typename T>
        typename std::enable_if<!cl::ref_countable<T>::value, void>::type
        create_TPtr(TPtr<T> const* c)
        {
#	pragma message(false, "Not completed field is create :" __FUNCSIG__);
        }

    }

    template <class T>
    TPtr<T> const& TPtr<T>::createIfField() const
    {
        if (isField_ && !ptr_.get())
        {
            //    Try to create object, if it is abstract will throw exception
            // no call create in compile time
            // also we should check is it possible compile version with TPtr this case
            //ptr_ = boost::dynamic_pointer_cast<T>(detail::create_<T>(std::is_abstract<T>()).ptr_);
            detail::create_TPtr(this);
        }
        return *this;
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    class TPtr<Interface<Ts_...>>
        : public type_operators_resolver<Interface<Ts_...>>::type
    {
    public:
        typedef Interface<Ts_...> InterfaceType;

        TPtr();

        template <template <typename... Tys_> class other_Interface>
        TPtr(TPtr<other_Interface<Ts_...>> const& instance);

        TPtr(InterfaceType* instance) : ptr_(instance) {}

        template <typename Toth_>
        TPtr(Toth_* instance);

        template <typename Toth_>
        TPtr(TPtr<Toth_ > const& instance);

        TPtr(TPtr<InterfaceType > const& instance)
            : ptr_(instance.ptr_)
        {}

        __if_exists(cl::finalizable_reference)
        {
            template <typename Toth_>
            TPtr(cl::finalizable_reference<Toth_> ref)
                : ptr_(ref.get().ptr_.get())
            {
            }
        }

        TPtr(ClFieldInfo const& instance);

        inline InterfaceType* check_(bool enable_default_ctor = true);

        void* operator new(size_t size);

        template <typename A0, typename... Arg>
        TPtr(A0 a, Arg... args);

        TPtr(TPtr<InterfaceType>* p);

        template <class R> TPtr(TPtr<R> * rhs);


        Interface<Ts_...>* operator->() const;

        Interface<Ts_...>* get() const;

        template <typename Ty_>
        inline TPtr& operator = (Ty_ const& v)
        {
            ptr_ = boost::intrusive_ptr<Interface<Ts_...> >(v);

            return *this;
        }

        void SetIsField(bool isField)
        {
            isField_ = isField;
        }

        /// <summary>Create on demand if self is marked as a field, do nothing otherwise.</summary>
        TPtr<InterfaceType> const& createIfField() const;

        /// Use intrusive ptr for types which is derived from object ref counter
        mutable typename detail::take_type_ptr<Interface<Ts_...>>::type ptr_;

        bool isField_ = false;
    };


    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    inline Interface<Ts_...>* TPtr<Interface<Ts_... >>::check_(bool enable_default_ctor/* = true*/)
    {
        bool is_new_used = *(reinterpret_cast<__int64*>(this)) == traits_ptr::PointerTag;

        if (!enable_default_ctor && !is_new_used)
           cl::throw_("Check error, m\b allocated on a stack.");

        return reinterpret_cast<Interface<Ts_... >*>(is_new_used ? traits_ptr::PointerTag : 0);
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    void* TPtr<Interface<Ts_...>>::operator new(size_t size)
    {
        //TODO: m\b indentyifier set vefore,
        //and return pointer after id
        //like return ptr + sizeof(ID);
        //it means we will able to check id of object by ptr
        void* ptr = malloc(sizeof(Interface<Ts_...>));
        *(__int64 *)ptr = traits_ptr::PointerTag;

        return ptr;
    }

    namespace detail
    {
        template <typename T, typename... Args>
        typename std::enable_if<!std::is_abstract<T>::value, void>::type
        ctor__(T* p, Args... args)
        {
            new (p) T(args...);
        }

        template <typename T, typename... Args>
        typename std::enable_if<std::is_abstract<T>::value, void>::type
        ctor__(T* p, Args... args)
        {
#           pragma message ("Can not create abstract class :" __FUNCSIG__)
        }
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    template <typename A0, typename... Arg>
    TPtr<Interface<Ts_...>>::TPtr(A0 a0, Arg... args) : ptr_(check_())
    {
        static_assert(sizeof(typename detail::take_type_ptr<type>::type) < sizeof(type) || std::is_abstract<type>::value
            , "Can not use this type for TPtr.");

        detail::ctor__((Interface<Ts_...>*)this, a0, args...);
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    TPtr<Interface<Ts_...>>::TPtr(TPtr<Interface<Ts_...>>* p) : ptr_((Interface<Ts_...>*)p)
    {}

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
    template <class R>
    TPtr<Interface<Ts_...>>::TPtr(TPtr<R> * rhs)
        : ptr_(boost::dynamic_pointer_cast<Interface<Ts_...>>((Interface<Ts_...>*)rhs))
    {
    }


    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        TPtr<Interface<Ts_...>>::TPtr()
        : ptr_(check_(), false)
    {
        if (*((__int64*)this) == traits_ptr::PointerTag)
            detail::ctor__((Interface<Ts_...>*)this);
        else ptr_ = nullptr;
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        template <template <typename... Tys_> class other_Interface>
    TPtr<Interface<Ts_...>>::TPtr(TPtr<other_Interface<Ts_...>> const& instance)
        : ptr_(instance.ptr_)
    {
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        template <typename Toth_>
    TPtr<Interface<Ts_...>>::TPtr(Toth_* instance)
        : ptr_(dynamic_cast<type* >(instance))
    {
    }

    template <typename Tiy_, typename Argi>
    static Tiy_* create__(Argi const&, std::integral_constant<bool, true>)
    {
#           pragma message ("Abstract type can not be created in :" __FUNCSIG__)
        return nullptr;
    }

    template <typename Tiy_, typename Argi> static Tiy_* create__(Argi const& a, std::integral_constant<bool, false>)
    {
        return new Tiy_(a);
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        TPtr<Interface<Ts_...>>::TPtr(ClFieldInfo const& instance)
        : ptr_(create__<Interface<Ts_...> >(instance, std::is_abstract<Interface<Ts_...>>()))
    {
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        template <typename Toth_>
    TPtr<Interface<Ts_...>>::TPtr(TPtr<Toth_ > const& instance)
        : ptr_(dynamic_cast<Interface<Ts_...>*>(instance.ptr_.get()))
    {
        CL_ASSERT(instance.ptr_.get() ? (bool)ptr_.get() : true, "Can not convert to targed type.");
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        Interface<Ts_...>* TPtr<Interface<Ts_...>>::operator->() const
    {
        typedef Interface<Ts_...> type;
        if (!ptr_ && isField_)
        {
            ptr_ = detail::create_<type>(std::is_abstract<type>()).ptr_;
        }
        return ptr_.get();
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        Interface<Ts_...>* TPtr<Interface<Ts_...>>::get() const
    {
        return ptr_.get();
    }

    template <template <typename... Ts_> class Interface
        , typename... Ts_>
        TPtr<Interface<Ts_...>> const& TPtr<Interface<Ts_...>>::createIfField() const
    {
        if (isField_ && !ptr_.get())
        {
            //    Try to create object, if it is abstract will throw exception
            // no call create in compile time
            // also we should check is it possible compile version with TPtr this case
            ptr_ = boost::dynamic_pointer_cast<Interface<Ts_...>>(detail::create_<Interface<Ts_...>>(std::is_abstract<Interface<Ts_...>>()).ptr_);
        }
        return *this;
    }


    namespace detail
    {

        template <typename T>
        struct is_holder : std::false_type{ typedef T held_type; };

        template <template <typename... Ts_> class Interface
            , typename... Ts_>
        struct is_holder<TPtr<Interface<Ts_...>>> : std::true_type
        {
            typedef Interface<Ts_...> held_type;
        };

        template <template <typename... Ts_> class Interface
            , typename... Ts_>
        struct is_holder<TPtr<Interface<Ts_...>> const> : std::true_type
        {
            typedef Interface<Ts_...> const held_type;
        };

        template <class T>
        struct is_holder<TPtr<T>> : std::true_type{ typedef T held_type; };


        template <typename Type, typename Other>
        inline TPtr<Type> dynamic_cast_clptr(TPtr<Other> const& ptr)
        {
            return TPtr<Type>(boost::dynamic_pointer_cast<Type>(ptr.ptr_));
        }

        template <typename T>
        inline typename std::enable_if<!std::has_trivial_constructor<T>::value
            , T>::type
        alloc__()
        {
#           if defined CL_COMPILE_TIME_DEBUG_ON
#               pragma message ("The class is not completed useful.: " __FUNCSIG__)
#           else
                // We should notify it, there are no classes
                // we can create this place. Need to modify Vadim's team.
                CL_ASSERT(false, "The class is not complete.");
#           endif
            return T();
        }

        template <typename T>
        inline typename std::enable_if<std::has_trivial_constructor<T>::value
            , T>::type
        alloc__()
        {
            return T(new cl::detail::is_holder<T>::held_type());
        }

        template <typename Ty_>
        inline Ty_ construct__(std::true_type)
        {
            __if_exists(cl::detail::is_holder<Ty_>::held_type::create)
            {
                return Ty_(cl::detail::is_holder<Ty_>::held_type::create());
            }
            __if_not_exists(cl::detail::is_holder<Ty_>::held_type::create)
            {
                return alloc__<Ty_>();
            }
        }

        template <typename Ty_>
        inline Ty_ construct__(std::false_type){ return Ty_(); }

    }

    template <typename Ty_>
    inline Ty_ construct(){ return detail::construct__<Ty_>(cl::detail::is_holder<Ty_>()); }

    namespace detail
    {
        template <typename Ty_>
        inline typename std::enable_if<has_meta<Ty_>::value, TPtr<Ty_>>::type
        create_(std::integral_constant<bool, false>)
        {
            return new Ty_();
        }

        template <typename Ty_>
        inline typename std::enable_if<!has_meta<Ty_>::value, TPtr<Ty_>>::type
        create_(std::integral_constant<bool, false>)
        {
            return Ty_::create();
        }

        template <typename Ty_>
        inline cl::TPtr<Ty_> create_(std::integral_constant<bool, true>)
        {
            throw TException("Attempting to create an instance of abstract type.");

            return TPtr<Ty_>();
        }

    }
}

namespace std
{

    template<typename T>
    struct is_class;

    template<typename T>
    struct is_class<cl::TPtr<T>> : integral_constant<bool, false>{};

}

#endif // cl_system_TPtr_hpp