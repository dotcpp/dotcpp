/*
Copyright (C) 2013-present CompatibL. All rights reserved.

This file is part of CompatibL TapeLib (the "Software"); you may not use the
Software except by obtaining a written commercial license from CompatibL.
The Software contains valuable trade secrets and may be used, copied, stored,
or distributed only in compliance with the terms of its license and with the
inclusion of this copyright notice.
*/

# if !defined cl_tape_impl_reflection_mem_access_hpp
# define cl_tape_impl_reflection_mem_access_hpp

namespace cl
{
    template <typename Mem_, typename Ty_>
    inline void debug_mem(Mem_, Ty_&);

    namespace tapescript
    {
        template <class Ty_>
        struct mem_accessor
        {
            enum { value = 0 };
            typedef struct is_not_implemented_mem_for_this_type { } mem_type;

            template <Ty_ V>
            struct spec
            {
                typedef struct not_found_return_type {} return_type;
                typedef struct not_found_class_type {} class_type;

                typedef mem_type type;
                
                static mem_type mem() { return V; }
                mem_type operator()() { return V; }
            };
        };

        template <class R_, class Ty_>
        struct mem_accessor<R_ Ty_::*>
        {
            enum { value = 1 };
            typedef R_ Ty_::*mem_type;

            template <mem_type V>
            struct spec
            {
                typedef R_ return_type;
                typedef mem_type type;
                typedef Ty_ class_type;

                static mem_type mem() { return V; }
                
                mem_type operator()()
                {
                    return V;
                }
            };
        };
    }

#   define decl_mem(m) typename cl::tapescript::mem_accessor<decltype(&m)>::template spec<&m>

    template <typename Mem, typename Ty>
    inline void debug_mem(Mem, Ty&)
    {
        /* Overload this function to debug member IO */
    }

    namespace detail {
        namespace foreach_fields {
            template <typename > struct h;
        }
    }

#   if defined MSVC_2013_ENABLED
    template <template<typename > class L
        , typename Object_type, typename... Args, typename... Members>
    inline void for_each_fields_(Object_type, Args...
        , cl::fields<Members...>)
    {}

    template <template<typename > class L
        , typename Object_type, typename... Args
        , typename Member, typename... Members>
    inline void for_each_fields_(Object_type obj, Args... args
        , cl::fields<Member, Members...>)
    {
        L<Member>()(obj, args...);
        for_each_fields_<L, Object_type, Args...>(obj
            , args..., cl::fields<Members...>());
    }

    template <template<typename > class L
        , typename Object_type, typename... Args>
    inline void
    for_each_fields(Object_type obj, Args... args)
    {
        typedef typename
            cl::class_fields<detail::foreach_fields::h<
                    typename std::remove_pointer<Object_type>::type>
            >::type fields;

        for_each_fields_<L, Object_type, Args...>(obj
            , args..., fields());
    }

    // This class is fields list we use for iterable fields
    template <typename... Ty_>
    struct fields
    {};
#	endif

    // Class fields
    template <class Ty_>
    struct class_fields;
}


# endif  // cl_tape_impl_reflection_mem_access_hpp