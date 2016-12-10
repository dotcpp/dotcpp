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

#if !defined cl_system_detail_reflection_hpp
#define cl_system_detail_reflection_hpp

# include <xtr1common>
# include <type_traits>

typedef void* instance_ptr;

template <typename >
struct Fn {};

template <typename I, typename R, typename... Args>
struct Fn <R(I::*)(Args...)>
{
    typedef R(I::*Mem)(Args...);
    template <Mem m>
    struct specify {};
};

template<typename T> struct resolve_type_ptr { typedef T type; };
template<typename T> struct resolve_type_ptr<T*> { typedef T type; };

# define __USE_HL_MPL


namespace cl
{
    template <typename T>
    struct alias;

    class ClObject;
    class ClData;
    typedef alias<ClObject> Object;

}

#include <cl/system/detail/reflection/reflection.hpp>
#include <cl/system/detail/cl_def.hpp>

namespace cl
{
    struct dummy;
    template <typename Dummy> struct solve_dummy { typedef dummy type; };

#   define SFINAE_DECLARE(sfinae_id, type_of_tag)       \
    template <typename Ty_, typename Ch_ = cl::dummy>   \
    struct sfinae_id : std::false_type                  \
    {                                                   \
        typedef cl::dummy type_of_tag;                  \
    };                                                  \
                                                        \
    template <typename Ty_>                             \
    struct sfinae_id<Ty_, typename cl::solve_dummy<     \
    typename Ty_::type_of_tag>::type > : std::true_type \
    {                                                   \
        typedef typename Ty_::type_of_tag type_of_tag;  \
    };                                                  \

    ///Case when we don't have implement tag
    SFINAE_DECLARE(has_fields, Has_fields);

    /// Is it empty struct
    SFINAE_DECLARE(is_impl, impl);

    /// Check is it has metadata
    SFINAE_DECLARE(has_meta, Meta_class_type);

    namespace detail
    {
        namespace fields_conch
        {
            template <typename > struct sh;
            template <typename C, typename Last/*, typename... Args*/>
            inline void lookup_fields_(C* c, Last/*, Args const&... args*/)
            {}

            template <typename Not_ptr_type>
            inline void setisfield(Not_ptr_type& p, bool b)
            {}

            template <typename T>
            inline void setisfield(cl::alias<T>& p, bool b)
            {
                p.SetIsField(b);
            }

            template <typename Acc, typename C>
            inline typename std::enable_if<!is_impl<Acc>::value, void>::type
            setisfield_(C *c, bool b)
            {}

            template <typename Acc, typename C>
            inline typename std::enable_if<is_impl<Acc>::value, void>::type
            setisfield_(C *c, bool b)
            {
                setisfield(Acc::get(c), true);
            }

            template <typename C, typename Field_acc, typename Tail, int Dir, typename... Args>
            inline typename std::enable_if<is_impl<typename C::template mem_accessor<sh<Field_acc>, C>>::value, void>::type
            lookup_fields_(C* c, cl::v_item<Field_acc, Tail, Dir>)
            {
                typedef C::mem_accessor<sh<Field_acc>, C> acc;
                setisfield_<acc>(c, true);
                lookup_fields_(c, Tail());
            }

            template <typename C, typename Field_acc, typename Tail, int Dir>
            inline typename std::enable_if<!is_impl<typename C::template mem_accessor<sh<Field_acc>, C>>::value, void>::type
            lookup_fields_(C* c, cl::v_item<Field_acc, Tail, Dir>/*, Args const&... args*/)
            {
                typedef C::mem_accessor<sh<Field_acc>, C> acc;
            }
        }

        template <typename C>
        inline typename std::enable_if<!has_fields<C>::value, void>::type
        lookup_fields_(C *c){}

        template <typename C>
        inline typename std::enable_if<std::is_base_of<cl::ClData, C>::value, void>::type
        set_is_lokupfields(C *c)
        {
            //c->ClData::isFieldLookup_ = true;
        }

        template <typename C>
        inline typename std::enable_if<!std::is_base_of<cl::ClData, C>::value, void>::type
        set_is_lokupfields(C *c)
        {}

        template <typename C>
        inline typename std::enable_if<has_fields<C>::value, void>::type
        lookup_fields_(C *c)
        {
            typedef cl::refl_extract<typename C::ftbl>::type fields;
            set_is_lokupfields(c);
            fields_conch::lookup_fields_(c, fields());
        }

        template <typename C>
        inline void
        lookup_fields(C *c)
        {
            lookup_fields_(c);
        }

    }
}


#endif //#define cl_system_detail_reflection_hpp