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

#if !defined cl_tape_impl_struct_archive_struct_archive_hpp
# define cl_tape_impl_struct_archive_struct_archive_hpp

#if !defined MSVC_2013_ENABLED
#   include <boost/noncopyable.hpp>
#endif

#include <cl/system/detail/archive/serializable_types.hpp>

# if defined _MANAGED
#   pragma managed (push, off)
#   if defined CL_COMPILE_TIME_FILE_DEBUG
#       pragma message ("Managed compilation: " __FILE__)
#   endif
#else
#   if defined CL_COMPILE_TIME_FILE_DEBUG
#       pragma message ("Unmanaged compilation: " __FILE__)
#   endif
#endif

#ifndef BOOST_SERIALIZATION_NO_LIB
#   define BOOST_SERIALIZATION_NO_LIB
#endif

#include <iostream>
#include <fstream>
#include <cstdint>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/impl/basic_binary_oprimitive.ipp>
#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_binary_iarchive.ipp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>
#include <boost/archive/impl/basic_binary_oarchive.ipp>
#include <boost/serialization/map.hpp>

#include <cl/system/detail/archive/archive_traits.hpp>

//TODO
#include <valarray>
#include <complex>

namespace cl
{

    //TODO 
    // Type holder
    template <typename T> struct ho {};


    template <typename >
    struct tape_inner;

    template <typename > class s;

    /// <summary>Tape function forward declaration.</summary>
    template <typename Base>
    class tape_function;

    template <class Archive>
    struct stream_type_trait;

    template <>
    struct stream_type_trait<boost::archive::binary_iarchive>
    {
        enum { is_out = 0 };
        static const std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary;
        typedef std::ifstream fstream_type;
        typedef std::istream stream_type;

        template <typename F>
        inline static fstream_type::pos_type
        tell(F& f)  { return f.tellg(); }
    };

    template <>
    struct stream_type_trait<boost::archive::binary_oarchive>
    {
        enum { is_out = 1 };
        static const std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary;
        typedef std::ofstream fstream_type;
        typedef std::ostream stream_type;

        template <typename F>
        inline static fstream_type::pos_type
        tell(F& f)  { return f.tellp(); }
    };

    struct serialization_chains_base
    {
        enum {
            none = 0
            , atomic = 1
            , has_class_fields = 1 << 1
            , has_custom = 1 << 2
        };
    };

    /// This type is performs serialization approach
    template <typename Type>
    struct type_chain
    {
        template<typename >
        struct ho;

        enum {
                atomic = (std::is_fundamental<T>::value
                            || std::is_enum<T>::value)
                         ? serialization_chains_base::atomic:0
                , has_members = cl::is_has_type<
                                    cl::class_fields<ho<Type>>
                                >::value
        };
    };

    // This is perform serialization approach
    // classes and fundamental types and any else
    template <class T>
    struct serialization_chains
        : cl::int_type<std::is_fundamental<T>::value
                    || std::is_enum<T>::value >
    {};

    template <int I>
    struct map_chain
    {
        enum { value = I };
        typedef map_chain<I> type;
    };

    template <typename T>
    struct is_map
    {
        enum { value = 0 };
        typedef cl::empty_type key_type;
        typedef cl::empty_type value_type;
    };

    template <typename Key, typename Value, typename Pr, typename Alloc_type>
    struct is_map<std::map<Key, Value, Pr, Alloc_type>>
    {
        enum { value = 1 };
        typedef Key key_type;
        typedef Value value_type;
    };

    template <class Key, class Value>
    struct serialization_chains<std::map<Key, Value>>
    {
        enum { has_personal_serialization
            = !std::is_same<cl::empty_type, decltype(archive::serialize(*(empty*)0, *(Value*)0))>::value };

        typedef map_chain<has_personal_serialization ? 2 : 0> this_chain;

        typedef typename std::conditional<
            cl::is_map<Value>::value && !has_personal_serialization
                , typename serialization_chains<Value >::type
                , this_chain>::type type;
    };

    template <typename F>
    struct is_fields : std::false_type{};

#	if defined MSVC_2013_ENABLED
		template <typename... Fields>
		struct is_fields<cl::fields<Fields...>>:std::true_type{};
#	endif

    template <typename T, int Is_T = cl::is_has_type<T>::value>
    struct is_has_fields : std::false_type {};

    template <typename T>
    struct is_has_fields<T, 1> : cl::is_fields<typename T::type> {};

    namespace archive
    {
        template <typename S, typename T>
        inline cl::empty_type serialize(S&, T&);
    }

    template <class T>
    struct serialization_traits
        : cl::int_type<std::is_fundamental<T>::value
                || std::is_enum<T>::value
                // is it is have type as fields
                || cl::is_has_fields<cl::class_fields<ho<T>>>::value >
    {};

    struct empty{};

    template <class First, class Second>
    struct serialization_traits<std::pair<First, Second>>
        : cl::int_type<serialization_traits<First>::value
        && (serialization_traits<Second>::value ||
            !std::is_same<cl::empty_type, decltype(archive::serialize(*(empty*)0, *(Second*)0))>::value)>
    {};

    template <class Key, class Value>
    struct serialization_traits<std::map<Key, Value>>
            : cl::int_type<serialization_traits<Key>::value
              && ((serialization_traits<Value>::value &&
					!std::is_same<cl::empty_type, decltype(archive::serialize(*(empty*)0, *(Value*)0))>::value) && !cl::is_has_fields<Value>::value)>
    {};

    template <class Type>
    struct serialization_traits<std::set<Type>>
        : cl::int_type<serialization_traits<Type>::value ||
            !std::is_same<cl::empty_type, decltype(archive::serialize(*(empty*)0, *(Type*)0))>::value>
    {};


    template <class Type>
    struct serialization_traits<std::vector<Type>>
        : serialization_traits<Type>
    {};


    template <typename Type>
    struct serialization_traits<const Type>
        : serialization_traits<Type>
    {};

    struct default_traits_chain {};

    template <class Base
            , class Serializer, class Traits_chain /*= default_traits_chain*/>
    struct archive_abstract : serializer<Base>
#	    if !defined MSVC_2013_ENABLED
            , boost::noncopyable
#       endif
    {
        enum {
            io_type_value = cl::serializer_type::io_binary
                | cl::serializer_type::io_text
            , io_binary = cl::serializer_type::io_binary
            , is_out = stream_type_trait<Serializer>::is_out
        };

        typedef Base base_type;
        typedef Serializer serializer_type;
        typedef archive_abstract<Base, Serializer, Traits_chain> this_type;

        typedef typename stream_type_trait<Serializer>::stream_type stream_type;
        typedef typename stream_type_trait<Serializer>::fstream_type fstream_type;
        typedef Traits_chain traits_chain_type;

        template <typename > struct ho{};
        typedef archive_abstract serialize__;

        typedef __int64 ssize_type;

        archive_abstract(fstream_type& stream, int archive_type)
            : serializer<Base>()
            , os_(stream)
            , ss_(os_)
            , archive_type_(archive_type)
        {}

        archive_abstract(fstream_type& stream)
            : serializer<Base>()
            , os_(stream)
            , ss_(os_)
            , archive_type_(io_binary)
        {}

#       if defined MSVC_2013_ENABLED
            archive_abstract(archive_abstract const& stream) = delete;
#       endif

        // Maps with custom serialization
        // chain
        template <typename Ty_, int V>
        serialize__& io__(Ty_& v, cl::map_chain<V>)
        {
            typedef typename std::remove_const<Ty_>::type nc_type;
            typedef typename Ty_::iterator iterator_type;
            typedef typename cl::is_map<Ty_>::value_type value_type;
            typedef typename cl::is_map<Ty_>::key_type   key_type;

            nc_type& nc = const_cast<nc_type&>(v);

            ssize_type ix = is_out ? (ssize_type)v.size() : 0;

            (*this)(ix);

            iterator_type where = v.begin();
			if (!is_out)
			{
				key_type key = key_type();
				value_type value = value_type();
				for (; ix--;)
				{
                    (*this)(key);
                    (*this)(value);
                    if (!is_out)
                    where = v.insert(where
                        , typename Ty_::value_type(key, value));
                }
            }
            else
            {
                for (;where != v.end(); ++where)
                {
                    (*this)(where->first);
                    (*this)(where->second);
            	}
			}
#if !defined NDEBUG && defined CL_TRACE_ENABLE
            std::cout << v << " ";
#endif
            return *this;
        }

        // Maps with native fundamental types
        template <typename Ty_>
        serialize__& io__(Ty_& v, cl::map_chain<0>)
        {
            typedef typename
                std::remove_const<Ty_>::type nc_type;

            nc_type& nc = const_cast<nc_type&>(v);
            this->ss_ & nc;

            chain_processing(Traits_chain(), nc, *this);
#if !defined NDEBUG && defined CL_TRACE_ENABLE
            std::cout << v << " ";
#endif
            return *this;
        }

        // begin input output operations
        template <typename Ty_>
        serialize__& io__(Ty_& v, std::true_type)
        {
            typedef typename
                std::remove_const<Ty_>::type nc_type;

            nc_type& nc = const_cast<nc_type&>(v);
            this->ss_ & nc;

#if !defined NDEBUG && defined CL_TRACE_ENABLE
            std::cout << v << " ";
#endif
            return *this;
        }

        template <typename Ty_>
        serialize__& io__(Ty_& v, std::false_type)
        {
            this->io_and_after(v, *this);
            return *this;
        }

        template <typename Ty_>
        serialize__& io0(Ty_& v)
        {
            this->io__(v, serialization_chains<Ty_>::type());
            return *this;
        }

        template <typename Ty_>
            typename std::enable_if<serialization_traits<Ty_>::value
            , this_type& >::type
        operator ()(Ty_& v)
        {
            return this->io0(v);
        }

        template <typename Ty_>
        typename std::enable_if<!serialization_traits<Ty_>::value
            , this_type& >::type
        operator ()(Ty_& v)
        {
            static_assert(std::is_same<this_type&
                , decltype(archive::serialize(*this, v))>::value, "Serialization is not implemented for this type.");
            return archive::serialize(*this, v);
        }

        template <typename Ty_>
        serialize__& operator ()(Ty_* v)
        {
            this->operator ()(*const_cast<typename std::remove_const<Ty_>::type*>(v));
            return *this;
        }


        template <typename Vector>
        serialize__& io_vector(Vector& v, std::true_type)
        {
            ssize_type ix = (ssize_type) v.size();
            this->io0(ix);

            for (; --ix >= 0;)
                this->operator ()(v[ix]);

            return *this;
        }

        template <typename Vector>
        serialize__& io_vector(Vector& v, std::false_type)
        {
            ssize_type ix = 0;
            this->io0(ix);
            if (ix > 0)
            {
                v.resize(ix);

                for (; --ix >= 0;)
                    this->operator ()(v[ix]);
            }

            return *this;
        }

        template <typename Ty_>
        serialize__& operator ()(std::vector<Ty_ >& v)
        {
            return io_vector(v, std::integral_constant<bool
                , is_out>());
        }

        template <typename Ty_>
        serialize__& operator ()(std::deque<Ty_ >& v)
        {
            return io_vector(v, std::integral_constant<bool
                , is_out>());
        }


        template <typename Ty_>
        serialize__& operator ()(std::valarray<Ty_ >& v)
        {
            return io_vector(v, std::integral_constant<bool
                , is_out>());
        }

        template <typename Ty_>
        serialize__& operator ()(std::set<Ty_ >& v)
        {
            return cl::archive::serialize(*this, v);
        }

        // end basic input\output operations
        template <typename Ty_>
        this_type& io_(Ty_* v, std::true_type)
        {
            io_(*v, cl::is_atomic_serializable<Ty_>());
            return *this;
        }

        template <typename Ty_>
        this_type& io_(Ty_& v, std::true_type)
        {
            ss_ & v;
#if !defined NDEBUG
            //std::cout << v << " ";
#endif
            return *this;
        }

        template <typename Ty_>
        inline this_type&
        io_(std::valarray<Ty_>& v, std::false_type)
        {
            (*this)(v);
            return *this;
        }

        template <typename Ty_>
        inline this_type&
        io_(std::vector<Ty_>& v, std::false_type)
        {
            serialize__& ss_imp = *this;
            ss_imp(v);

            return *this;
        }


        template <typename Ty_>
        this_type& io_(Ty_& v, std::false_type)
        {
            this->io_and_after(v, *this);

            return *this;
        }

        // global operator input output
        // for fundamental types and chained
        template <typename Ty_>
        friend inline typename std::enable_if<serialization_traits<Ty_>::value
            , this_type& >::type
        operator &(this_type& s, Ty_& v)
        {
            s.io_(v, serialization_chains<Ty_>());
            return s;
        }

        // global serialization for type with custom chained
        template <typename Ty_>
        friend inline typename std::enable_if<!serialization_traits<Ty_>::value
                && !std::is_same<decltype(cl::archive::serialize(*(this_type*)0, *(Ty_*)0)), cl::empty_type>::value
            , this_type& >::type
        operator &(this_type& s, Ty_& v)
        {
            return cl::archive::serialize(s, v);
        }

        // Stopper of compilation
        template <typename Ty_>
        friend inline typename std::enable_if<!serialization_traits<Ty_>::value
                && std::is_same<decltype(cl::archive::serialize(*(this_type*)0, *(Ty_*)0)), cl::empty_type>::value
                , this_type& >::type
            operator &(this_type& s, Ty_& v)
        {
            typedef decltype(cl::archive::serialize(*(this_type*)0, *(Ty_*)0)) result_type;

            // stop compilation
            static_assert(!std::is_same<result_type, cl::empty_type>::value, "Serialization for this type is not implemented.");

            return s;
        }

        template <class Ty, class Serializer>
        void io_and_after(Ty& v, Serializer& ss)
        {
			typedef class_fields<ho<typename std::remove_const<Ty>::type>> class_fields_holder;

#			if defined MSVC_2013_ENABLED
				
				typedef typename
					class_fields_holder::type class_fields_type;
#			else
				typedef typename
                    cl::detail::serializable_class_trait<Ty>::type class_fields_type;
#			endif

            this->io(&v, ss, class_fields_type());

            after_(v, cl::is_has_after<class_fields_holder>());
        }

        template <typename Ty>
        inline void after_(Ty& v, std::false_type){}

        template <typename Ty>
        void after_(Ty& v, std::true_type)
        {
            class_fields<ho<typename std::remove_const<Ty>::type>>().after_io(v, *this);
        }

        // type of serializer
        virtual unsigned int io_type()
        {
            return (archive_type_);
        }

        typename fstream_type::pos_type tell()
        {
            return stream_type_trait<Serializer>::tell(os_);
        }

        inline this_type* this_() { return this; }

        fstream_type &os_;
        Serializer ss_;
        int        archive_type_;
    };


    template <class Base, class Serializer, class Traits_chain = default_traits_chain>
    struct struct_archive
        : stream_type_trait<Serializer>::fstream_type
            , archive_abstract<Base, Serializer, Traits_chain>
    {
        typedef stream_type_trait<Serializer> trait;
        typedef typename trait::fstream_type fstream_type;
        typedef archive_abstract<Base, Serializer, Traits_chain> archive_base;

        struct_archive(const std::string& path)
            : fstream_type(path, trait::mode)
            , archive_base(static_cast<fstream_type&>(*this), trait::mode)
        {}

        template <typename Args>
        struct_archive(const std::string& path, Args& args)
            : fstream_type(path, trait::mode)
            , archive_base(
                static_cast<fstream_type&>(*this)
                , args)
        {}

        template <typename Args>
        struct_archive(const std::string& path, int archive_type, Args& args)
            : fstream_type(path, trait::mode)
                , archive_base(
                    static_cast<fstream_type&>(*this)
                    , archive_type, args)
        {}
        
#       if defined MSVC_2016_ENABLED
            struct_archive(const struct_archive&) = delete;
#       endif
    };

    template <typename S>
    struct callback_chain{};

    // This is fields processing callback
    // we need to get full size
    template <typename Base
            , typename Serializer, typename F>
    struct struct_archive_callback
        : struct_archive<Base, Serializer
            , callback_chain<struct_archive_callback<Base, Serializer, F>>>
    {
        typedef callback_chain<struct_archive_callback<Base, Serializer, F>> chain_type;

        typedef struct_archive<Base, Serializer
            , callback_chain<struct_archive_callback<Base, Serializer, F>>> archive_base;

        template <typename Func, typename Args>
        struct_archive_callback(Func f, size_t sizeof_file, short coarsening, Args args)
                        : archive_base(args)
                        , f_(f), sizeof_file_(sizeof_file)
                        , read_buffer_(), coarsening_(coarsening)
        {}

        F f_;
        size_t sizeof_file_, read_buffer_;
        short coarsening_;
    };

    template <typename Callback_origin, typename T, typename S, typename Args>
    inline void
    chain_processing(callback_chain<Callback_origin>, T& v, S& s, Args& args)
    {
        Callback_origin* c = static_cast<Callback_origin*>(s.this_());
        c->read_buffer_ += sizeof(T);
        if ((c->read_buffer_ * (100 + c->coarsening_))
                >= c->sizeof_file_)
        {
            c->read_buffer_ = 0;
            // if callback was set
            if (c->f_)
                c->f_(c->tellg());
        }
    }
}



/// traits to implementation certain classes
namespace cl
{
    template <class Base>
    struct serializer;

#	if defined MSVC_2013_ENABLED
#		 if !defined CL_USE_MAPPED_SERIALIZER
		   template <class Base>
		   using tape_writer = struct_archive<Base, boost::archive::binary_oarchive>;

		   template <class Base>
		   using tape_reader = struct_archive<Base, boost::archive::binary_iarchive>;

		   template <class Base, class F>
		   using tape_reader_callback = struct_archive_callback<Base, boost::archive::binary_iarchive, F>;

		   template <class Base, class F>
		   using tape_writer_callback = struct_archive_callback<Base, boost::archive::binary_oarchive, F>;
#		 else
		   template <class Base>
		   using tape_writer = struct_archive<Base, mapped_archiver<archive_strategy::native, std::true_type>>;

		   template <class Base>
		   using tape_reader = struct_archive<Base, mapped_archiver<archive_strategy::native, std::false_type>>;

		   template <class Base, class F>
		   using tape_reader_callback = struct_archive_callback<Base, mapped_archiver<archive_strategy::native, std::false_type>, F>;

		   template <class Base, class F>
		   using tape_writer_callback = struct_archive_callback<Base, mapped_archiver<archive_strategy::native, std::true_type>, F>;
#		 endif
#	endif

    template <class Base>
	struct tape_writer
        : struct_archive<Base, boost::archive::binary_oarchive>
	{
        tape_writer(std::string const& path)
            : struct_archive<Base, boost::archive::binary_oarchive>(path) {}
	};

	template <class Base>
	struct tape_reader
        : struct_archive<Base, boost::archive::binary_iarchive>
	{
        tape_reader(std::string const &path)
            : struct_archive<Base, boost::archive::binary_iarchive>(path) {}
	};
}

namespace cl
{
    template <class Base
        , class Serializer, class Traits_chain>
    struct struct_archive;
}

#	define serializers_list boost::mpl::vector

namespace CppAD
{
    template <typename >
    class vector;

    template <template <typename, typename, typename > class Serializer, typename Archive>
    struct ho_serializer2
    {
        template <typename Base, typename Traits_chain = default_traits_chain>
        struct apply { typedef Serializer<Base, Archive, Traits_chain> type; };
    };

    template <typename >
    struct serializer_traits;

#   if defined CL_USE_ARCHIVE_IN_FORWARD
        template <>
        struct serializer_traits <double>
        {
            typedef cl::serializer<double> type;

            typedef serializers_list <
                    ho_serializer2<cl::struct_archive
                        , boost::archive::binary_iarchive>
                    , ho_serializer2<cl::struct_archive
                        , boost::archive::binary_oarchive>
                > certain_archivers;
        };
#   endif


}

# if defined _MANAGED
#   pragma managed (pop)
#endif

#endif
