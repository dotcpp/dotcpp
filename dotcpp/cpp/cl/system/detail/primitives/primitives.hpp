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

#pragma once

#if ! defined cl_tape_impl_detail_primitives_primitives_hpp
#       define cl_tape_impl_detail_primitives_primitives_hpp

namespace cl
{
	namespace detail
	{
		// this class is base for props base classes
		class object_base {};

		// this notifier about that class
		// case base_class_type
		struct has_base_class {};

		// This class used for define that it is
		// has a base class fields
		template <typename Base>
		struct base_class : has_base_class
		{
			typedef Base base_class_type;
		};
	}

	class Object : public detail::object_base {};
}

namespace cl
{
    struct dummy {};
    struct empty_type {};
    struct null_type;

    template <int I>
    struct int_ : std::integral_constant<int , I> {};

	template <typename... T>
	inline void print_type()
	{
#        pragma message (__FUNCSIG__)
	}

	template <typename H> struct h;
}

#endif
