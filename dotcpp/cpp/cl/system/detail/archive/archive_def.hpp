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

# if !defined cl_tape_impl_struct_archive_archive_def_hpp
#	  define  cl_tape_impl_struct_archive_archive_def_hpp

#include <xtr1common>

#include <cl/system/detail/sfinae.hpp>

#include <cl/system/detail/reflection/mem_access.hpp>

namespace cl
{
	// reflected_type_holder
	// it is about gcc compiler bug about
	// specialization in scoped child type
	template <typename > struct ho;

	template <typename Field>
	struct field_access
	{
        typedef Field type;
    };

	template <typename>
	struct is_fields;

	struct Able_to_archive {};

	template <>
	struct is_fields <Able_to_archive>
		: std::true_type {};
}

// Need to approach used in 
// MSVC 2013
#	if defined MSVC_2013_ENABLED
#		define Reflection_Begin typedef fields <
#		define Reflection_End	cl::null_type > type;
#	else
#		define Reflection_Begin
#		define Reflection_End
#	endif

#	define fieldclass(classname, mem)														\
		template <typename T> struct sh;							                        \
		typedef field_access<decl_mem(classname##::##mem)> accessor_##mem;				    \
		typedef Able_to_archive type;														\
		HL_REGISTRATE_REFLACTION_TYPE(ftbl, accessor_##mem);								


# endif