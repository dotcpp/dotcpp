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
#include <dot/system/Nullable.hpp>
#include <dot/system/Array1D.hpp>
#include <dot/system/collections/generic/List.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ParameterInfo.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalMinute.hpp>
#include <dot/noda_time/LocalDateTime.hpp>

namespace dot
{
    class string_impl; class string;
    class type_impl; using type_t = ptr<type_impl>;
    class TypeBuilderImpl; using TypeBuilder = ptr<TypeBuilderImpl>;
    class string_impl; class string;
    class MethodInfoImpl; using MethodInfo = ptr<MethodInfoImpl>;
    class ConstructorInfoImpl; using ConstructorInfo = ptr<ConstructorInfoImpl>;
    template <class T> class ListImpl; template <class T> using List = ptr<ListImpl<T>>;
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;
    template <class Class, class ... Args> class MemberConstructorInfoImpl;

    template <class T> type_t typeof();

    /// <summary>Builder for Type.</summary>
    class DOT_CLASS TypeBuilderImpl final : public virtual object_impl
    {
        template <class>
        friend TypeBuilder make_type_builder(string nspace, string name);
        friend class type_impl;

    private:
        string fullName_;
        List<MethodInfo> methods_;
        List<ConstructorInfo> ctors_;
        type_t type_;
        type_t base_;
        List<type_t> interfaces_;
        List<type_t> generic_args_;
        bool is_class_;
        bool is_enum_ = false;

    public: // METHODS

        /// <summary>Add public field of the current Type.</summary>
        template <class Class, class Prop>
        TypeBuilder WithField(string name, Prop Class::*prop)
        {
            // TODO - implement
            return this;
        }

        /// <summary>Add public member method of the current Type.</summary>
        template <class Class, class Return, class ... Args>
        TypeBuilder WithMethod(string name, Return(Class::*mth) (Args ...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<type_t> paramTypes = { dot::typeof<Args>()... };

            for (int i = 0; i < argsCount; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            MethodInfo methodInfo_ = new MemberMethodInfoImpl<Class, Return, Args...>(name, type_, dot::typeof<Return>(), mth);
            methodInfo_->Parameters = parameters;

            methods_->Add(methodInfo_);

            return this;
        }

        /// <summary>Add public static method of the current Type.</summary>
        template <class Return, class ... Args>
        TypeBuilder WithMethod(string name, Return(*mth) (Args ...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<type_t> paramTypes = { dot::typeof<Args>()... };

            for (int i = 0; i < argsCount; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            MethodInfo methodInfo_ = new StaticMethodInfoImpl<Return, Args...>(name, type_, dot::typeof<Return>(), mth);
            methodInfo_->Parameters = parameters;

            methods_->Add(methodInfo_);

            return this;
        }

        /// <summary>Add public constructor of the current Type.</summary>
        template <class Class, class ... Args>
        TypeBuilder WithConstructor(Class(*ctor)(Args...), std::vector<string> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount_ = sizeof...(Args);
            if (argsCount_ != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (ctors_.IsEmpty())
            {
                ctors_ = new_List<ConstructorInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<type_t> paramTypes = { dot::typeof<Args>()... };

            for (int i = 0; i < argsCount_; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            ConstructorInfo ctorInfo = new MemberConstructorInfoImpl<Class, Args...>(type_, ctor);
            ctorInfo->Parameters = parameters;

            ctors_->Add(ctorInfo);

            return this;
        }

        /// <summary>Set IsEnum to true.</summary>
        TypeBuilder IsEnum()
        {
            this->is_class_ = false;
            this->is_enum_ = true;
            return this;
        }

        /// <summary>Add base type of the current Type.</summary>
        template <class Class>
        TypeBuilder WithBase()
        {
            if (!(this->base_.IsEmpty()))
                throw new_Exception("Base already defined in class " + fullName_);

            this->base_ = dot::typeof<Class>();
            return this;
        }

        /// <summary>Add interface type of the current Type.</summary>
        template <class Class>
        TypeBuilder WithInterface()
        {
            if (this->interfaces_.IsEmpty())
                this->interfaces_ = new_List<type_t>();

            this->interfaces_->Add(dot::typeof<Class>());
            return this;
        }

        /// <summary>Add generic argument type of the current Type.</summary>
        template <class Class>
        TypeBuilder WithGenericArgument()
        {
            if (this->generic_args_.IsEmpty())
                this->generic_args_ = new_List<type_t>();

            this->generic_args_->Add(dot::typeof<Class>());
            return this;
        }


        /// <summary>Built type_t from the current object.</summary>
        type_t Build();

    private: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of TypeBuilder.
        ///
        /// This constructor is private. Use make_type_builder() function instead.
        /// </summary>
        TypeBuilderImpl(string nspace, string name, string cppname);
    };

    /// <summary>
    /// Create an empty instance of TypeBuilder.
    /// </summary>
    template <class T>
    inline TypeBuilder make_type_builder(string nspace, string name)
    {
        TypeBuilder td = new TypeBuilderImpl(nspace, name, typeid(T).name());
        td->is_class_ = std::is_base_of<object_impl, T>::value;
        return td;
    }

    /// <summary>
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
    /// </summary>
    class DOT_CLASS type_impl final : public virtual object_impl
    {
        friend class TypeBuilderImpl;
        template <class T>
        friend struct typeof_impl;

        typedef type_impl self;

    private: // FIELDS

        Array1D<MethodInfo> methods_;
        Array1D<ConstructorInfo> ctors_;
        Array1D<type_t> interfaces_;
        Array1D<type_t> generic_args_;
        type_t base_;

    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        string Name; // TODO - replace by method

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        string Namespace; // TODO - replace by method

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_GET(string, FullName, { return string::format("{0}.{1}", this->Namespace, this->Name); }) // TODO - replace by string::Join

        /// <summary>Gets the base type if current type.</summary>
        DOT_GET(type_t, BaseType, { return base_; })

        /// <summary>Gets a value indicating whether the System.type_t is a class or a delegate; that is, not a value type or interface.</summary>
        bool IsClass; // TODO - replace by method

        /// <summary>Gets a value indicating whether the current System.type_t represents an enumeration.</summary>
        bool IsEnum; // TODO - replace by method

    public: // METHODS

        /// <summary>Returns methods of the current type.</summary>
        Array1D<MethodInfo> GetMethods() { return methods_; }

        /// <summary>Returns constructors of the current type.</summary>
        Array1D<ConstructorInfo> GetConstructors() { return ctors_; }

        /// <summary>Returns interfaces of the current type.</summary>
        Array1D<type_t> GetInterfaces() { return interfaces_; }

        /// <summary>Returns interfaces of the current type.</summary>
        Array1D<type_t> GetGenericArguments() { return generic_args_; }

        /// <summary>Searches for the public method with the specified name.</summary>
        MethodInfo GetMethod(string name);

        /// <summary>Searches for the interface with the specified name.</summary>
        type_t GetInterface(string name);

        /// <summary>A string representing the name of the current type.</summary>
        virtual string to_string() override { return FullName; }

        /// <summary>Get type_t object for the name.</summary>
        static type_t GetType(string name) { return GetTypeMap()[name]; }

        /// <summary>Get derived types list for the name.</summary>
        static List<type_t> GetDerivedTypes(string name) { return GetDerivedTypesMap()[name]; }

        /// <summary>Get derived types list for the type.</summary>
        static List<type_t> GetDerivedTypes(type_t type) { return GetDerivedTypesMap()[type->FullName]; }

        virtual bool Equals(object obj) override;

        virtual size_t hash_code() override;

    private: // METHODS

        /// <summary>
        /// Fill data from builder.
        /// </summary>
        void Fill(const TypeBuilder& data);

        static std::map<string, type_t>& GetTypeMap()
        {
            static std::map<string, type_t> map_;
            return map_;
        }

        static std::map<string, List<type_t>>& GetDerivedTypesMap()
        {
            static std::map<string, List<type_t>> map_;
            return map_;
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from builder.
        ///
        /// This constructor is private. Use TypeBuilder->Build() method instead.
        /// </summary>
        type_impl(string nspace, string name);
    };

    /// <summary>
    /// Initializes a new instance of the type_t class for untyped instance of object.
    /// </summary>
    inline type_t object_impl::type()
    {
        return typeof();
    }

    inline type_t object_impl::typeof()
    {
        static type_t type_ = make_type_builder<object_impl>("System", "object")->Build();
        return type_;
    }

    template <class T> type_t ListImpl<T>::typeof()
    {
        static type_t type_ = make_type_builder<ListImpl<T>>("System.Collections.Generic", "List`1")
            //DOT_TYPE_CTOR(new_List<T>)
            ->WithConstructor(static_cast<List<T>(*)()>(&new_List<T>), { })
            DOT_TYPE_GENERIC_ARGUMENT(T)
            ->Build();
        return type_;
    }

    /// <summary>
    /// Private ctor of the array with the zero size to use in serealization.
    /// </summary>
    template <class T>
    Array1D<T> private_new_Array1D() { return new Array1DImpl<T>(0); }



    template <class T> type_t Array1DImpl<T>::typeof()
    {
        static type_t type_ = make_type_builder<Array1DImpl<T>>(dot::typeof<T>()->Namespace, dot::typeof<T>()->Name +"[]")
            //DOT_TYPE_CTOR(new_Array1D<T>)
            DOT_TYPE_GENERIC_ARGUMENT(T)
            DOT_TYPE_CTOR(private_new_Array1D<T>)
            ->Build();
        return type_;
    }

    template <class T>
    struct typeof_impl
    {
        static type_t get_typeof()
        {
            string cppname = typeid(typename T::element_type).name(); // TODO - is it faster to use typeid rather than string as key?
            auto p = type_impl::GetTypeMap().find(cppname);
            if (p == type_impl::GetTypeMap().end())
            {
                type_t type = T::element_type::typeof();
                return type;
            }

            return p->second;
        }

    };

    template <>
    struct typeof_impl<double>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<double>("System", "Double")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<int64_t>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<int64_t>("System", "Int64")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<int>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<int>("System", "Int32")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<void>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<void>("System", "Void")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<bool>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<bool>("System", "Bool")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<char>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<char>("System", "Char")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalDate>
    {
        static type_t get_typeof()
    {
        static type_t type_ = make_type_builder<LocalDate>("System", "LocalDate")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalTime>
    {
        static type_t get_typeof()
        {
            static type_t type_ = make_type_builder<LocalTime>("System", "LocalTime")->Build();
            return type_;
        }
    };

    template <>
    struct typeof_impl<LocalMinute>
    {
        static type_t get_typeof()
        {
            static type_t type_ = make_type_builder<LocalTime>("System", "LocalMinute")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalDateTime>
    {
        static type_t get_typeof()
        {
            static type_t type_ = make_type_builder<LocalDateTime>("System", "LocalDateTime")->Build();
            return type_;
        }
    };

    template <class T>
    struct typeof_impl<Nullable<T>>
    {
        static type_t get_typeof()
        {
            static type_t type_ = make_type_builder<Nullable<T>>("System", "Nullable<" + dot::typeof<T>()->Name + ">")
                ->template WithGenericArgument<T>()
                ->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<std::tuple<>>
    {
        static type_t get_typeof()
        {
            static type_t type_ = make_type_builder<std::tuple<>>("System", "Tuple<>")
                ->Build();
            return type_;
        }

    };

    template <class ... T>
    struct typeof_impl<std::tuple<T...>>
    {
        static type_t get_typeof()
        {
            static TypeBuilder type_builder =
            []()
            {
                TypeBuilder type_builder = make_type_builder<std::tuple<T...>>("System", "Tuple<" + get_name<T...>() + ">");
                set_generic_args<T ...>(type_builder);
                type_builder->WithMethod("GetItem", &GetItem, { "tuple", "index" })
                    ->WithMethod("SetItem", &SetItem, { "tuple", "index", "value" })
                    ->WithConstructor(&Contructor, {})
                    ;
                return type_builder;
            }();

            static type_t type_ = type_builder->Build();
            return type_;
        }
    private:

        static object Contructor()
        {
            return object(std::tuple<T...>());
        }

        struct dummy{};

        template <int I, typename Dummy = dummy>
        struct GetItemImpl
        {
            static object Impl(object tuple, int index)
            {
                if (I == index) return std::get<I>(*(StructWrapper<std::tuple<T...>>)tuple);
                    else return GetItemImpl<I + 1>::Impl(tuple, index);
            }
        };

        template <typename Dummy>
        struct GetItemImpl<sizeof...(T), Dummy>
        {
            static object Impl(object tuple, int index)
            {
                throw new_Exception("Tuple index out of bounds");
            }
        };

        static object GetItem(object tuple, int index)
        {
            return GetItemImpl<0>::Impl(tuple, index);
        }

        template <int I, typename Dummy = dummy>
        struct SetItemImpl
        {
            static void Impl(object tuple, int index, object value)
            {
                if (I == index) std::get<I>(*(StructWrapper<std::tuple<T...>>)tuple) = (std::tuple_element_t<I, std::tuple<T...>>)value;
                else SetItemImpl<I + 1>::Impl(tuple, index, value);
            }
        };

        template <typename Dummy>
        struct SetItemImpl<sizeof...(T), Dummy>
        {
            static void Impl(object tuple, int index, object value)
            {
                throw new_Exception("Tuple index out of bounds");
            }
        };

        static void SetItem(object tuple, int index, object value)
        {
            SetItemImpl<0>::Impl(tuple, index, value);
        }


        template <class Head, class Second, class ... Tail>
        static string get_name()
        {
            return dot::typeof<Head>()->Name + get_name<Second, Tail...>();
        }

        template <class Head>
        static string get_name()
        {
            return dot::typeof<Head>()->Name;
        }

        template <class Head, class Second, class ... Tail>
        static TypeBuilder set_generic_args(TypeBuilder tb)
        {
            return set_generic_args<Second, Tail ... >(tb->WithGenericArgument<Head>());
        }

        template <class Head>
        static TypeBuilder set_generic_args(TypeBuilder tb)
        {
            return tb->WithGenericArgument<Head>();
        }

    };


    /// <summary>Get type_t object for the argument.</summary>
    template <class T>
    type_t typeof()
    {
        return typeof_impl<T>::get_typeof();
    }

}
