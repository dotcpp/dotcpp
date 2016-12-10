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
namespace cl
{
    // TODO : implement reflection to find cuitable class
    template <typename T>
    struct activator_traits { typedef T type; };
    
    namespace detail
    {
        template <typename Obj_type, typename Data>
        inline alias<Obj_type> build(alias<Data> data)
        {
            typedef typename activator_traits<Data>::type object_type;
            return alias<object_type>(new object_type(data));
        }
    }
}