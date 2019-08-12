/*
Copyright (C) 2015-present The DotCpp Authors.

This file is part of .C++, a native C++ implementation of
popular .NET class library APIs developed to facilitate
code reuse between C# and C++.

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

#pragma once

#include <dot/detail/traits.hpp>
#include <dot/detail/reflection_macro.hpp>
#include <dot/system/object.hpp>
#include <dot/system/string.hpp>
#include <dot/system/nullable.hpp>
#include <dot/system/collections/generic/list.hpp>
#include <dot/system/reflection/constructor_info.hpp>
#include <dot/system/reflection/method_info.hpp>
#include <dot/system/reflection/parameter_info.hpp>
#include <dot/system/reflection/field_info.hpp>
#include <dot/noda_time/local_date.hpp>
#include <dot/noda_time/local_time.hpp>
#include <dot/noda_time/local_minute.hpp>
#include <dot/noda_time/local_date_time.hpp>

namespace dot
{
    class string_impl; class string;
    class type_impl; using type_t = ptr<type_impl>;
    class type_builder_impl; using type_builder = ptr<type_builder_impl>;
    class string_impl; class string;
    class method_info_impl; using method_info = ptr<method_info_impl>;
    class constructor_info_impl; using constqructor_info = ptr<constructor_info_impl>;
    template <class T> class list_impl; template <class T> using list = ptr<list_impl<T>>;
    template <class class_t, class ... Args> class member_constructor_info_impl;

    template <class T> type_t typeof();

    /// builder for Type.
    class DOT_CLASS type_builder_impl final : public virtual object_impl
    {
        template <class>
        friend type_builder make_type_builder(string nspace, string name);
        friend class type_impl;

    private:
        string full_name_;
        list<method_info> methods_;
        list<constructor_info> ctors_;
        list<field_info> fields_;
        type_t type_;
        type_t base_;
        list<type_t> interfaces_;
        list<type_t> generic_args_;
        bool is_class_;
        bool is_enum_ = false;

    public: // METHODS

        /// Add public field of the current Type.
        template <class class_t, class fld>
        type_builder with_field(string name, fld class_t::*prop)
        {
            if (fields_.is_empty())
            {
                fields_ = make_list<field_info>();
            }
            fields_->add(make_field_info<fld, class_t>(name, type_, dot::typeof<fld>(), prop));
            return this;
        }

        /// Add public member method of the current Type.
        template <class class_t, class return_t, class ... args>
        type_builder with_method(string name, return_t(class_t::*mth) (args ...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int args_count = sizeof...(args);
            if (args_count != names.size())
                throw exception("Wrong number of parameters for method " + full_name_);

            if (methods_.is_empty())
            {
                methods_ = make_list<method_info>();
            }

            list<parameter_info> parameters = make_list<parameter_info>(sizeof...(args));
            std::vector<type_t> param_types = { dot::typeof<args>()... };

            for (int i = 0; i < args_count; ++i)
            {
                parameters[i] = make_parameter_info(names[i], param_types[i], i);
            }

            method_info method_info = new member_method_info_impl<class_t, return_t, args...>(name, type_, dot::typeof<return_t>(), mth);
            method_info->parameters = parameters;

            methods_->add(method_info);

            return this;
        }

        /// Add public static method of the current Type.
        template <class return_t, class ... args>
        type_builder with_method(string name, return_t(*mth) (args ...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int args_count = sizeof...(args);
            if (args_count != names.size())
                throw exception("Wrong number of parameters for method " + full_name_);

            if (methods_.is_empty())
            {
                methods_ = make_list<method_info>();
            }

            list<parameter_info> parameters = make_list<parameter_info>(sizeof...(args));
            std::vector<type_t> param_types = { dot::typeof<args>()... };

            for (int i = 0; i < args_count; ++i)
            {
                parameters[i] = make_parameter_info(names[i], param_types[i], i);
            }

            method_info method_info = new static_method_info_impl<return_t, args...>(name, type_, dot::typeof<return_t>(), mth);
            method_info->parameters = parameters;

            methods_->add(method_info);

            return this;
        }

        /// Add public constructor of the current Type.
        template <class class_t, class ... args>
        type_builder with_constructor(class_t(*ctor)(args...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int args_count = sizeof...(args);
            if (args_count != names.size())
                throw exception("Wrong number of parameters for method " + full_name_);

            if (ctors_.is_empty())
            {
                ctors_ = make_list<constructor_info>();
            }

            list<parameter_info> parameters = make_list<parameter_info>(sizeof...(args));
            std::vector<type_t> param_types = { dot::typeof<args>()... };

            for (int i = 0; i < args_count; ++i)
            {
                parameters[i] = make_parameter_info(names[i], param_types[i], i);
            }

            constructor_info ctor_info = new member_constructor_info_impl<class_t, args...>(type_, ctor);
            ctor_info->parameters = parameters;

            ctors_->add(ctor_info);

            return this;
        }

        /// Set IsEnum to true.
        type_builder is_enum()
        {
            this->is_class_ = false;
            this->is_enum_ = true;
            return this;
        }

        /// Add base type of the current Type.
        template <class class_t>
        type_builder with_base()
        {
            if (!(this->base_.is_empty()))
                throw exception("Base already defined in class " + full_name_);

            this->base_ = dot::typeof<class_t>();
            return this;
        }

        /// Add interface type of the current Type.
        template <class class_t>
        type_builder with_interface()
        {
            if (this->interfaces_.is_empty())
                this->interfaces_ = make_list<type_t>();

            this->interfaces_->add(dot::typeof<class_t>());
            return this;
        }

        /// Add generic argument type of the current Type.
        template <class class_t>
        type_builder with_generic_argument()
        {
            if (this->generic_args_.is_empty())
                this->generic_args_ = make_list<type_t>();

            this->generic_args_->add(dot::typeof<class_t>());
            return this;
        }


        /// Built type_t from the current object.
        type_t build();

    private: // CONSTRUCTORS

        /// Create an empty instance of type_builder.
        ///
        /// This constructor is private. Use make_type_builder() function instead.
        type_builder_impl(string nspace, string name, string cppname);
    };

    /// Create an empty instance of type_builder.
    template <class T>
    inline type_builder make_type_builder(string nspace, string name)
    {
        type_builder td = new type_builder_impl(nspace, name, typeid(T).name());
        td->is_class_ = std::is_base_of<object_impl, T>::value;
        return td;
    }

    /// Represents type declarations: class types, interface types, array types, value types, enumeration types,
    /// type parameters, generic type definitions, and open or closed constructed generic types.
    ///
    /// type_t is the root of the System.Reflection functionality and is the primary way to access metadata.
    /// Use the members of type_t to get information about a type declaration, about the members of a type
    /// (such as the constructors, methods, fields, properties, and events of a class), as well as the module
    /// and the assembly in which the class is deployed.
    ///
    /// The type_t object associated with a particular type can be obtained in the following ways:
    ///
    /// \begin{itemize}
    ///
    /// \item The instance object.Gettype_t method returns a type_t object that represents the type of an instance.
    /// Because all managed types derive from object, the Gettype_t method can be called on an instance of any type.
    ///
    /// \item The typeof method obtains the type_t object for the argument type.
    ///
    /// \end{itemize}
    class DOT_CLASS type_impl final : public virtual object_impl
    {
        friend class type_builder_impl;
        template <class T>
        friend struct type_traits;

        typedef type_impl self;

    private: // FIELDS

        list<method_info> methods_;
        list<constructor_info> ctors_;
        list<type_t> interfaces_;
        list<type_t> generic_args_;
        type_t base_;
        list<field_info> fields_;

    public: // PROPERTIES

        /// Gets the name of the current type, excluding namespace.
        string name; // TODO - replace by method

        /// Gets the fully qualified name of the type, including its namespace but not its assembly.
        string name_space; // TODO - replace by method

        /// Gets the fully qualified name of the type, including its namespace but not its assembly.
        string full_name() const { return string::format("{0}.{1}", this->name_space, this->name); } // TODO - replace by string::Join

        /// Gets the base type if current type.
        type_t base_type() { return base_; }

        /// Gets a value indicating whether the System.type_t is a class or a delegate; that is, not a value type or interface.
        bool is_class; // TODO - replace by method

        /// Gets a value indicating whether the current System.type_t represents an enumeration.
        bool is_enum; // TODO - replace by method

    public: // METHODS

        /// Returns methods of the current type.
        list<method_info> get_methods() { return methods_; }

        /// Returns constructors of the current type.
        list<constructor_info> get_constructors() { return ctors_; }

        /// Returns fields of the current type.
        list<field_info> get_fields() { return fields_; }

        /// Returns interfaces of the current type.
        list<type_t> get_interfaces() { return interfaces_; }

        /// Returns interfaces of the current type.
        list<type_t> get_generic_arguments() { return generic_args_; }

        /// Searches for the public method with the specified name.
        method_info get_method(string name);

        /// Searches for the interface with the specified name.
        type_t get_interface(string name);

        /// Searches for the field with the specified name.
        field_info get_field(string name);

        /// A string representing the name of the current type.
        virtual string to_string() override { return full_name(); }

        /// Get type_t object for the name.
        static type_t get_type(string name) { return get_type_map()[name]; }

        /// Get derived types list for the name.
        static list<type_t> get_derived_types(string name) { return get_derived_types_map()[name]; }

        /// Get derived types list for the type.
        static list<type_t> get_derived_types(type_t type) { return get_derived_types_map()[type->full_name()]; }

        bool equals(object obj) override;

        virtual size_t hash_code() override;

    private: // METHODS

        /// Fill data from builder.
        void fill(const type_builder& data);

        static std::map<string, type_t>& get_type_map()
        {
            static std::map<string, type_t> map_;
            return map_;
        }

        static std::map<string, list<type_t>>& get_derived_types_map()
        {
            static std::map<string, list<type_t>> map_;
            return map_;
        }

    private: // CONSTRUCTORS

        /// Create from builder.
        ///
        /// This constructor is private. Use type_builder->build() method instead.
        type_impl(string nspace, string name);
    };

    /// Initializes a new instance of the type_t class for untyped instance of object.
    inline type_t object_impl::type()
    {
        return typeof();
    }

    inline type_t object_impl::typeof()
    {
        static type_t type_ = make_type_builder<object_impl>("System", "object")->build();
        return type_;
    }

    template <class T> type_t list_impl<T>::typeof()
    {
        static type_t type_ = make_type_builder<list_impl<T>>("System.Collections.Generic", "List`1")
            //DOT_TYPE_CTOR(make_list<T>)
            ->with_constructor(static_cast<list<T>(*)()>(&make_list<T>), { })
            DOT_TYPE_GENERIC_ARGUMENT(T)
            ->template with_interface<dot::list_base>()
            ->build();
        return type_;
    }

    template <class T>
    struct type_traits
    {
        static type_t typeof()
        {
            string cppname = typeid(typename T::element_type).name(); // TODO - is it faster to use typeid rather than string as key?
            auto p = type_impl::get_type_map().find(cppname);
            if (p == type_impl::get_type_map().end())
            {
                type_t type = T::element_type::typeof();
                return type;
            }

            return p->second;
        }
    };

    template <>
    struct type_traits<double>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<double>("System", "Double")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<int64_t>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<int64_t>("System", "Int64")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<int>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<int>("System", "Int32")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<void>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<void>("System", "Void")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<bool>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<bool>("System", "Bool")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<char>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<char>("System", "Char")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<local_date>
    {
        static type_t typeof()
    {
        static type_t type_ = make_type_builder<local_date>("System", "local_date")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<local_time>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<local_time>("System", "local_time")->build();
            return type_;
        }
    };

    template <>
    struct type_traits<local_minute>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<local_time>("System", "local_minute")->build();
        return type_;
    }
    };

    template <>
    struct type_traits<local_date_time>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<local_date_time>("System", "local_date_time")->build();
            return type_;
        }
    };

    template <>
    struct type_traits<period>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<local_date_time>("System", "Period")->build();
            return type_;
        }
    };

    template <class T>
    struct type_traits<nullable<T>>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<nullable<T>>("System", "nullable<" + dot::typeof<T>()->name + ">")
                ->template with_generic_argument<T>()
                ->build();
        return type_;
    }
    };

    template <>
    struct type_traits<std::tuple<>>
    {
        static type_t typeof()
        {
            static type_t type_ = make_type_builder<std::tuple<>>("System", "Tuple<>")
                ->build();
            return type_;
        }

    };

    template <class ... T>
    struct type_traits<std::tuple<T...>>
    {
        static type_t typeof()
        {
            static type_builder type_builder =
            []()
            {
                type_builder type_builder = make_type_builder<std::tuple<T...>>("System", "Tuple<" + get_name<T...>() + ">");
                set_generic_args<T ...>(type_builder);
                type_builder->with_method("GetItem", &get_item, { "tuple", "index" })
                    ->with_method("SetItem", &set_item, { "tuple", "index", "value" })
                    ->with_constructor(&contructor, {})
                    ;
                return type_builder;
            }();

            static type_t type_ = type_builder->build();
            return type_;
        }
    private:

        static object contructor()
        {
            return object(std::tuple<T...>());
        }

        struct dummy{};

        template <int I, typename Dummy = dummy>
        struct get_item_impl
        {
            static object impl(object tuple, int index)
            {
                if (I == index) return std::get<I>(*(struct_wrapper<std::tuple<T...>>)tuple);
                    else return get_item_impl<I + 1>::Impl(tuple, index);
            }
        };

        template <typename Dummy>
        struct get_item_impl<sizeof...(T), Dummy>
        {
            static object impl(object tuple, int index)
            {
                throw exception("Tuple index out of bounds");
            }
        };

        static object get_item(object tuple, int index)
        {
            return get_item_impl<0>::impl(tuple, index);
        }

        template <int I, typename Dummy = dummy>
        struct set_item_impl
        {
            static void impl(object tuple, int index, object value)
            {
                if (I == index) std::get<I>(*(struct_wrapper<std::tuple<T...>>)tuple) = (std::tuple_element_t<I, std::tuple<T...>>)value;
                else SetItemImpl<I + 1>::impl(tuple, index, value);
            }
        };

        template <typename Dummy>
        struct set_item_impl<sizeof...(T), Dummy>
        {
            static void impl(object tuple, int index, object value)
            {
                throw exception("Tuple index out of bounds");
            }
        };

        static void set_item(object tuple, int index, object value)
        {
            SetItemImpl<0>::impl(tuple, index, value);
        }


        template <class Head, class Second, class ... Tail>
        static string get_name()
        {
            return dot::typeof<Head>()->name + get_name<Second, Tail...>();
        }

        template <class Head>
        static string get_name()
        {
            return dot::typeof<Head>()->name;
        }

        template <class Head, class Second, class ... Tail>
        static type_builder set_generic_args(type_builder tb)
        {
            return set_generic_args<Second, Tail ... >(tb->with_generic_argument<Head>());
        }

        template <class Head>
        static type_builder set_generic_args(type_builder tb)
        {
            return tb->with_generic_argument<Head>();
        }

    };

    /// Get type_t object for the argument.
    template <class T>
    type_t typeof()
    {
        return type_traits<T>::typeof();
    }
}
