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
# pragma warning(push)
# pragma warning(disable:4267)

#include <map>
#include <boost/dynamic_bitset.hpp>


namespace cl
{
	// archiving additional types
	namespace archive
	{
		template <typename Serializer, typename T, typename Allocator>
		inline Serializer&
		serialize(Serializer& ss, boost::dynamic_bitset<T, Allocator>& bs)
		{
			typedef boost::dynamic_bitset<T, Allocator>::size_type size_type;
			size_type size_of = 0;
			if (ss.is_out){
				ss & (size_of = bs.size());
			}
			else {
				ss & size_of;
				bs.resize(size_of);
			}

			for (size_type w = 0; w != bs.size(); ++w)
			{
				bool v = false;
				if (ss.is_out)
				{
					v = bs[w];
					ss & v;
				}
				else { ss & v; bs[w] = v; }
			}
			
			return ss;
		}

		namespace detail {
			template <typename Serializer, typename Key_type, typename Type>
			inline typename std::enable_if<Serializer::is_out, Serializer&>::type
			serialize__(Serializer& ss, std::map<Key_type, Type>& mp, size_t size_of)
			{
				typedef std::map<Key_type, Type>::iterator iterator_type;
				typedef std::map<Key_type, Type>::value_type value_type;
				
				for (iterator_type where = mp.begin(); where != mp.end(); ++where)
				{
					ss & const_cast<Key_type&>(where->first);
					ss & const_cast<Type&>(where->second);
				}

				return ss;
			}

			template <typename Serializer, typename Key_type, typename Type>
			inline typename std::enable_if<!Serializer::is_out, Serializer&>::type
			serialize__(Serializer& ss, std::map<Key_type, Type>& mp, size_t size_of)
			{
				typedef std::map<Key_type, Type>::iterator iterator_type;
				typedef std::map<Key_type, Type>::value_type value_type;
				
				for (iterator_type& where = mp.begin(); size_of--;)
				{
					Key_type key = Key_type();
					Type value = Type();
					ss & key;
					//ss & value;
					
					where = mp.insert(where, std::make_pair(key, std::move(value)));
					ss & where->second;
				}

				return ss;
			}
		}

		template <typename Serializer, typename Key_type, typename Type>
		inline Serializer&
		serialize(Serializer& ss, std::map<Key_type, Type>& mp)
		{
			size_t size_of = mp.size();
			ss & size_of;

			return detail::serialize__(ss, mp, size_of);
		}

		template <typename Serializer>
		inline Serializer&
		serialize(Serializer& ss, std::string& s)
		{
			// use base archiver functionality
			// but in future we will use lazy logic
			ss.ss_ & s;
			return ss;
		}

		template <typename Serializer, typename Type>
		inline Serializer&
		serialize(Serializer& ss, std::set<Type>& s)
		{
			// for iterable serialization
			typedef typename std::set<Type>::iterator iterator_type;
			typedef typename std::set<Type>::value_type value_type;

			if (ss.is_out)
			{
				size_t size_of = s.size();
				ss & size_of;

				// We should or create temporary object
				//, or change infrastructure to directly write object
				//, but this case it will not change garanty
				for (auto& w : s)
					ss & const_cast<Type& >(w);
			}
			else
			{
				s.clear();
				iterator_type where = s.begin();

				size_t size_of = 0;
				ss & size_of;
				for (; size_of--;)
				{
					value_type v;

					ss & v;
					where = s.insert(where, std::move(v));
				}
			}

			return ss;
		}

	}
}

# pragma warning(pop)