/*
Copyright (C) 2003-2015 CompatibL

This file is part of TapeScript, an open source library and tape encoding
standard for adjoint algorithmic differentiation (AAD), available from

http://github.com/compatibl/tapescript (source)
http://tapescript.org (documentation)

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

#if !defined cl_tape_impl_struct_archive_archive_traits_hpp
#	  define  cl_tape_impl_struct_archive_archive_traits_hpp

# define HL_INCLUDE_IGNORE

#include <cl/system/detail/archive/archive_def.hpp>

namespace cl
{
    enum serializer_type
    {
        no_info = 0, io_binary = 1 << 1, io_text = 1 << 2
    };

    namespace detail
    {
        // trait of serializable classes
        // this class provide getting is able to fields seralization
        template <typename T
            , int I = has_fields<cl::class_fields<ho<typename std::remove_const<T>::type>>>::value
				|| std::is_base_of<cl::detail::object_base, T>::value
            >
        struct serializable_class_trait
        {
            template <typename > struct h;
			typedef cl::empty_type type;
        };

        template <typename T>
        struct serializable_class_trait<T, 1>
        {
            typedef typename ::cl::class_fields<cl::ho<T>>::type type;
        };
    }
}

namespace cl
{
    template <typename >
    struct tape_inner;

    /// <summary>Tape function forward declaration.</summary>
    template <typename Base>
    class tape_function;

    template <typename Branch = struct tapearchive_tag_branch>
    struct traits { typedef struct {} type; };

    template <int I>
    struct int_type : std::integral_constant<int, I> {};

    template <>
    struct int_type <0> : std::false_type
    {};

    template <>
    struct int_type <1> : std::true_type
    {};

    typedef int_type<1> true_type;
    typedef int_type<0> false_type;

    template <typename Archive, typename Ty_>
    inline void extern_io(Archive &s, Ty_& v)
    {
#       if !defined NDEBUG
#         pragma message ("Please implement serialization for: " __FUNCSIG__)
#       endif
    }

	template <typename Callback_origin, typename T, typename S, typename Args>
    inline void
    chain_processing(Callback_origin, T& v, S& s, Args& args)
    {}
	
    template <typename T>
    class TPtr;

    template <typename Type>
    struct remove_t_ptr
    {
        template <typename T>
        inline Type& ref(T& v)
        {
            return v;
        }
    };

    template <typename Type>
    struct remove_t_ptr<TPtr<Type>>
    {
        template <typename T>
        inline Type& ref(T& v)
        {
            v.operator -> ();
            return *v.get();
        }
    };

	struct empty_text_struct_archive
	{
	};

	template <typename Base>
	struct serializer_vi_items
	{
		template <class Class, class Serializer>
		inline void io__(Class obj, Serializer& ss, cl::empty_type)
		{
#           if defined CL_COMPILE_TIME_DEBUG
#               pragma message (__FUNCSIG__)
#           endif
		}
	};

    template <typename Base>
    struct serializer
        : std::conditional < cl::is_implemented<traits<>::type>::value
                , typename traits<>::type
                , empty_text_struct_archive >::type
		 , serializer_vi_items<Base>
    {
        struct impl {};
        struct io_typed {};

        serializer()
        {}

        template <typename Member, typename Class, typename Serializer>
        inline void io_chained_(Class obj, Serializer& ss, std::false_type)
        {
            typedef typename std::remove_pointer<Class>::type class_type;
            typedef typename class_type::template Mem_iterator<ho<Member>>::type member_type;

            typename typename member_type m;
            static_assert(!std::is_pointer<Serializer>::value, "Shouldn't be pointer");
            
            ss.operator ()(remove_t_ptr<member_type::return_type>().ref(obj->*(m())));
        }

        template <typename Chain, typename Class, typename Serializer>
        inline void io_chained_(Class obj, Serializer& ss, std::true_type)
        {
            Chain().io(obj, ss);
        }

		template <typename Member, typename Class, typename Serializer, typename Spec_chain>
		inline typename
		std::enable_if<std::is_base_of<std::integral_constant<int, 2>, Spec_chain>::value, void>::type
		io_chained_(Class obj, Serializer& ss, Spec_chain c)
		{
			c.io<Member>(obj, ss);
		}

		template <typename Class, typename Serializer>
		inline void
		io_base_(Class obj, Serializer& ss, std::false_type)
		{}

		template <typename Class, typename Serializer>
		inline void
		io_base_(Class obj, Serializer& ss, std::true_type)
		{
			typedef std::remove_pointer<Class>::type class_type;
			typedef ::cl::class_fields<ho<class_type>> class_fields_type;

			typedef typename class_fields_type::base_class_type base_class_type;
			ss & *static_cast<base_class_type*>(obj);
		}


		template <typename Class, typename S, typename... Rest >
		inline void
		io__(Class obj, S& ss, ::cl::fields<Rest...>)
		{
		}

		// Iteration by fields
		template <typename Class, typename S, typename Member, typename... Rest >
		inline void
		io__(Class obj, S& ss, ::cl::fields<Member, Rest...>)
		{
			typedef std::remove_pointer<Class>::type class_type;
			typedef Member member_type;

			io_chained_<Member>(obj, ss, cl::is_chain<typename member_type::type>());

			this->io__(obj, ss, ::cl::fields<Rest...>());
		}
		
		// This is field oriented inpput output
		template <typename Class, typename S, typename... Members>
		inline void
		io(Class obj, S& ss, ::cl::fields<Members...>)
		{
			typedef std::remove_pointer<Class>::type class_type;
			typedef ::cl::class_fields<ho<class_type>> class_fields_type;

			io_base_(obj, ss
				, std::is_base_of<cl::detail::has_base_class, class_fields_type>());

			this->io__(obj, ss, ::cl::fields<Members...>());
		}

        virtual unsigned int io_type()
        {
            return 0;
        }

        virtual ~serializer(){}
    };
}

# endif
