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
#if !defined cl_system_detail_cl_def_hpp
#define cl_system_detail_cl_def_hpp

namespace cl
{
    struct empty_type;
    namespace detail
    {
        template <typename Type> struct extract_type { typedef cl::empty_type type; };

        template <typename Type, typename R, typename... Args>
        struct extract_type<R(Type::*)(Args...)>{ typedef Type type; };

        template <typename C, typename... Args>
        inline void lookup_fields(Args...);

        struct ctor_context {};

        class object;
    }
}

namespace cl{ namespace detail { namespace memory {

    template <typename T>
    inline typename std::enable_if<std::is_base_of<cl::detail::object, T>::value, void*>::type
    alloc__(size_t size)
    {
        //TODO: make as marked
        return alloc(size);
    }

    template <typename T>
    inline typename std::enable_if<!std::is_base_of<cl::detail::object, T>::value, void*>::type
    alloc__(size_t size)
    {
        return alloc(size);
    }

}}}

#define CL_CLASS(classname)                                                             \
    public:                                                                             \
    typedef classname Meta_class_type;                                                  \
    template <typename, typename >                                                      \
    struct mem_accessor;                                                                \
    private:                                                                            \
    template <typename C, typename... Args>                                             \
    friend void cl::detail::lookup_fields(Args...);                                     \
    public:                                                                             \
    classname(cl::detail::ctor_context)                                                 \
    { cl::detail::lookup_fields(this); }                                                \
    

#define CL_CLASS_EX(classname)                                                          \
    CL_CLASS(classname)                                                                 \
    public:                                                                             \
    classname() {                                                                       \
        cl::detail::lookup_fields(this);                                                \
    }                                                                                   \
    


#define CL_RPC(name)                                                                    \
    typedef type_resolver_##name;                                                       \
    friend struct field_tag##name;                                                      \
    typedef                                                                             \
    type_resolver_##name return_type_##name;                                            \
    struct Has_fields;                                                                  \
    template <typename T> struct sh;							                        \
    struct accessor_##name{ typedef Meta_class_type class_type; };					    \
    HL_REGISTRATE_REFLACTION_TYPE(ftbl, accessor_##name);                               \
    template <template <typename > class mem, typename Type>	                        \
    struct mem_accessor<mem<accessor_##name>, Type >				                    \
    {																                    \
        struct impl;                                                                    \
        typedef Fn<decltype(&Type::name)> acc;						                    \
        static decltype(&Type::name) get() { return &Type::name; }	                    \
        template <typename C>                                                           \
        static type_resolver_##name& get(C *c) { return c->*&Type::name; }              \
    };																                    \
    return_type_##name name                                                             \

# define field(identifier, name_tag) CL_RPC(identifier)

#endif //#define cl_system_detail_cl_def_hpp