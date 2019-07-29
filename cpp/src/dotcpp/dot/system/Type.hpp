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
#include <dot/system/Object.hpp>
#include <dot/system/String.hpp>
#include <dot/system/Nullable.hpp>
#include <dot/system/Array1D.hpp>
#include <dot/system/collections/generic/List.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ParameterInfo.hpp>
#include <dot/system/reflection/PropertyInfo.hpp>
#include <dot/noda_time/LocalDate.hpp>
#include <dot/noda_time/LocalTime.hpp>
#include <dot/noda_time/LocalMinute.hpp>
#include <dot/noda_time/LocalDateTime.hpp>

namespace dot
{
    class StringImpl; class String;
    class TypeImpl; using Type = ptr<TypeImpl>;
    class TypeBuilderImpl; using TypeBuilder = ptr<TypeBuilderImpl>;
    class StringImpl; class String;
    class MethodInfoImpl; using MethodInfo = ptr<MethodInfoImpl>;
    class ConstructorInfoImpl; using ConstructorInfo = ptr<ConstructorInfoImpl>;
    class PropertyInfoImpl; using PropertyInfo = ptr<PropertyInfoImpl>;
    template <class T> class ListImpl; template <class T> using List = ptr<ListImpl<T>>;
    template <class T> class Array1DImpl; template <class T> using Array1D = ptr<Array1DImpl<T>>;
    template <class Class, class ... Args> class MemberConstructorInfoImpl;

    template <class T> Type typeof();

    /// <summary>Builder for Type.</summary>
    class DOT_CLASS TypeBuilderImpl final : public virtual ObjectImpl
    {
        template <class>
        friend TypeBuilder new_TypeBuilder(String nspace, String name);
        friend class TypeImpl;

    private:
        String fullName_;
        List<PropertyInfo> properties_;
        List<PropertyInfo> static_properties_;
        List<MethodInfo> methods_;
        List<ConstructorInfo> ctors_;
        Type type_;
        Type base_;
        List<Type> interfaces_;
        List<Type> generic_args_;
        bool is_class_;
        bool is_enum_ = false;

    public: // METHODS

        /// <summary>Add public field of the current Type.</summary>
        template <class Class, class Prop>
        TypeBuilder WithField(String name, Prop Class::*prop)
        {
            //! TODO add to fields_ ?
            if (properties_.IsEmpty())
            {
                properties_ = new_List<PropertyInfo>();
            }
            properties_->Add(new PropertyInfoFieldImpl<Prop, Class>(name, type_, dot::typeof<Prop>(), prop));
            return this;
        }

        /// <summary>Add public property of the current Type.</summary>
        template <class Class, class Prop>
        TypeBuilder WithProperty(String name, Prop Class::*prop)
        {
             if (properties_.IsEmpty())
             {
                 properties_ = new_List<PropertyInfo>();
             }
             properties_->Add(new PropertyInfoPropertyImpl<Prop, Class>(name, type_, dot::typeof<typename Prop::value_type>(), prop));
             return this;
        }

        /// <summary>Add public member method of the current Type.</summary>
        template <class Class, class Return, class ... Args>
        TypeBuilder WithMethod(String name, Return(Class::*mth) (Args ...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { dot::typeof<Args>()... };

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
        TypeBuilder WithMethod(String name, Return(*mth) (Args ...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { dot::typeof<Args>()... };

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
        TypeBuilder WithConstructor(Class(*ctor)(Args...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount_ = sizeof...(Args);
            if (argsCount_ != names.size())
                throw new_Exception("Wrong number of parameters for method " + fullName_);

            if (ctors_.IsEmpty())
            {
                ctors_ = new_List<ConstructorInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { dot::typeof<Args>()... };

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
                this->interfaces_ = new_List<Type>();

            this->interfaces_->Add(dot::typeof<Class>());
            return this;
        }

        /// <summary>Add generic argument type of the current Type.</summary>
        template <class Class>
        TypeBuilder WithGenericArgument()
        {
            if (this->generic_args_.IsEmpty())
                this->generic_args_ = new_List<Type>();

            this->generic_args_->Add(dot::typeof<Class>());
            return this;
        }


        /// <summary>Built Type from the current object.</summary>
        Type Build();

    private: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of TypeBuilder.
        ///
        /// This constructor is private. Use new_TypeBuilder() function instead.
        /// </summary>
        TypeBuilderImpl(String nspace, String name, String cppname);
    };

    /// <summary>
    /// Create an empty instance of TypeBuilder.
    /// </summary>
    template <class T>
    inline TypeBuilder new_TypeBuilder(String nspace, String name)
    {
        TypeBuilder td = new TypeBuilderImpl(nspace, name, typeid(T).name());
        td->is_class_ = std::is_base_of<ObjectImpl, T>::value;
        return td;
    }

    /// <summary>
    /// Represents type declarations: class types, interface types, array types, value types, enumeration types,
    /// type parameters, generic type definitions, and open or closed constructed generic types.
    ///
    /// Type is the root of the System.Reflection functionality and is the primary way to access metadata.
    /// Use the members of Type to get information about a type declaration, about the members of a type
    /// (such as the constructors, methods, fields, properties, and events of a class), as well as the module
    /// and the assembly in which the class is deployed.
    ///
    /// The Type object associated with a particular type can be obtained in the following ways:
    ///
    /// \begin{itemize}
    ///
    /// \item The instance Object.GetType method returns a Type object that represents the type of an instance.
    /// Because all managed types derive from Object, the GetType method can be called on an instance of any type.
    ///
    /// \item The typeof method obtains the Type object for the argument type.
    ///
    /// \end{itemize}
    /// </summary>
    class DOT_CLASS TypeImpl final : public virtual ObjectImpl
    {
        friend class TypeBuilderImpl;
        template <class T>
        friend struct typeof_impl;

        typedef TypeImpl self;

    private: // FIELDS

        Array1D<PropertyInfo> properties_;
        Array1D<MethodInfo> methods_;
        Array1D<ConstructorInfo> ctors_;
        Array1D<Type> interfaces_;
        Array1D<Type> generic_args_;
        Type base_;

    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        DOT_AUTO_GET(String, Name)

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_AUTO_GET(String, Namespace)

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_GET(String, FullName, { return String::Format("{0}.{1}", this->Namespace, this->Name); }) // TODO - replace by String::Join

        /// <summary>Gets the base type if current type.</summary>
        DOT_GET(Type, BaseType, { return base_; })

        /// <summary>Gets a value indicating whether the System.Type is a class or a delegate; that is, not a value type or interface.</summary>
        DOT_AUTO_GET(bool, IsClass);

        /// <summary>Gets a value indicating whether the current System.Type represents an enumeration.</summary>
        DOT_AUTO_GET(bool, IsEnum);

    public: // METHODS

        /// <summary>Returns all the public properties of the current Type.</summary>
        Array1D<PropertyInfo> GetProperties() { return properties_; }

        /// <summary>Returns methods of the current type.</summary>
        Array1D<MethodInfo> GetMethods() { return methods_; }

        /// <summary>Returns constructors of the current type.</summary>
        Array1D<ConstructorInfo> GetConstructors() { return ctors_; }

        /// <summary>Returns interfaces of the current type.</summary>
        Array1D<Type> GetInterfaces() { return interfaces_; }

        /// <summary>Returns interfaces of the current type.</summary>
        Array1D<Type> GetGenericArguments() { return generic_args_; }

        /// <summary>Searches for the public property with the specified name.</summary>
        PropertyInfo GetProperty(String name);

        /// <summary>Searches for the public method with the specified name.</summary>
        MethodInfo GetMethod(String name);

        /// <summary>Searches for the interface with the specified name.</summary>
        Type GetInterface(String name);

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() override { return FullName; }

        /// <summary>Get Type object for the name.</summary>
        static Type GetType(String name) { return GetTypeMap()[name]; }

        /// <summary>Get derived types list for the name.</summary>
        static List<Type> GetDerivedTypes(String name) { return GetDerivedTypesMap()[name]; }

        /// <summary>Get derived types list for the type.</summary>
        static List<Type> GetDerivedTypes(Type type) { return GetDerivedTypesMap()[type->FullName]; }

        virtual bool Equals(Object obj) override;

        virtual size_t GetHashCode() override;

    private: // METHODS

        /// <summary>
        /// Fill data from builder.
        /// </summary>
        void Fill(const TypeBuilder& data);

        static std::map<String, Type>& GetTypeMap()
        {
            static std::map<String, Type> map_;
            return map_;
        }

        static std::map<String, List<Type>>& GetDerivedTypesMap()
        {
            static std::map<String, List<Type>> map_;
            return map_;
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from builder.
        ///
        /// This constructor is private. Use TypeBuilder->Build() method instead.
        /// </summary>
        TypeImpl(String nspace, String name);
    };

    /// <summary>
    /// Initializes a new instance of the Type class for untyped instance of Object.
    /// </summary>
    inline Type ObjectImpl::GetType()
    {
        return typeof();
    }

    inline Type ObjectImpl::typeof()
    {
        static Type type_ = new_TypeBuilder<ObjectImpl>("System", "Object")->Build();
        return type_;
    }

    template <class T> Type ListImpl<T>::typeof()
    {
        static Type type_ = new_TypeBuilder<ListImpl<T>>("System.Collections.Generic", "List`1")
            //DOT_TYPE_CTOR(new_List<T>)
            ->WithConstructor(static_cast<List<T>(*)()>(&new_List<T>), { })
            DOT_TYPE_GENERIC_ARGUMENT(T)
            DOT_TYPE_INTERFACE(IObjectEnumerable)
            DOT_TYPE_INTERFACE(IObjectCollection)
            ->Build();
        return type_;
    }

    /// <summary>
    /// Private ctor of the array with the zero size to use in serealization.
    /// </summary>
    template <class T>
    Array1D<T> private_new_Array1D() { return new Array1DImpl<T>(0); }



    template <class T> Type Array1DImpl<T>::typeof()
    {
        static Type type_ = new_TypeBuilder<Array1DImpl<T>>(dot::typeof<T>()->Namespace, dot::typeof<T>()->Name +"[]")
            //DOT_TYPE_CTOR(new_Array1D<T>)
            DOT_TYPE_GENERIC_ARGUMENT(T)
            DOT_TYPE_INTERFACE(IObjectEnumerable)
            DOT_TYPE_INTERFACE(IObjectCollection)
            DOT_TYPE_CTOR(private_new_Array1D<T>)
            ->Build();
        return type_;
    }

    template <class T>
    struct typeof_impl
    {
        static Type get_typeof()
        {
            String cppname = typeid(typename T::element_type).name(); // TODO - is it faster to use typeid rather than string as key?
            auto p = TypeImpl::GetTypeMap().find(cppname);
            if (p == TypeImpl::GetTypeMap().end())
            {
                Type type = T::element_type::typeof();
                return type;
            }

            return p->second;
        }

    };

    template <>
    struct typeof_impl<double>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<double>("System", "Double")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<int64_t>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<int64_t>("System", "Int64")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<int>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<int>("System", "Int32")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<void>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<void>("System", "Void")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<bool>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<bool>("System", "Bool")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<char>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<char>("System", "Char")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalDate>
    {
        static Type get_typeof()
    {
        static Type type_ = new_TypeBuilder<LocalDate>("System", "LocalDate")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalTime>
    {
        static Type get_typeof()
        {
            static Type type_ = new_TypeBuilder<LocalTime>("System", "LocalTime")->Build();
            return type_;
        }
    };

    template <>
    struct typeof_impl<LocalMinute>
    {
        static Type get_typeof()
        {
            static Type type_ = new_TypeBuilder<LocalTime>("System", "LocalMinute")->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<LocalDateTime>
    {
        static Type get_typeof()
        {
            static Type type_ = new_TypeBuilder<LocalDateTime>("System", "LocalDateTime")->Build();
            return type_;
        }
    };

    template <class T>
    struct typeof_impl<Nullable<T>>
    {
        static Type get_typeof()
        {
            static Type type_ = new_TypeBuilder<Nullable<T>>("System", "Nullable<" + dot::typeof<T>()->Name + ">")
                ->template WithGenericArgument<T>()
                ->Build();
        return type_;
    }
    };

    template <>
    struct typeof_impl<std::tuple<>>
    {
        static Type get_typeof()
        {
            static Type type_ = new_TypeBuilder<std::tuple<>>("System", "Tuple<>")
                ->Build();
            return type_;
        }

    };

    template <class ... T>
    struct typeof_impl<std::tuple<T...>>
    {
        static Type get_typeof()
        {
            static TypeBuilder type_builder =
            []()
            {
                TypeBuilder type_builder = new_TypeBuilder<std::tuple<T...>>("System", "Tuple<" + get_name<T...>() + ">");
                set_generic_args<T ...>(type_builder);
                type_builder->WithMethod("GetItem", &GetItem, { "tuple", "index" })
                    ->WithMethod("SetItem", &SetItem, { "tuple", "index", "value" })
                    ->WithConstructor(&Contructor, {})
                    ;
                return type_builder;
            }();

            static Type type_ = type_builder->Build();
            return type_;
        }
    private:

        static Object Contructor()
        {
            return Object(std::tuple<T...>());
        }

        struct dummy{};

        template <int I, typename Dummy = dummy>
        struct GetItemImpl
        {
            static Object Impl(Object tuple, int index)
            {
                if (I == index) return std::get<I>(*(StructWrapper<std::tuple<T...>>)tuple);
                    else return GetItemImpl<I + 1>::Impl(tuple, index);
            }
        };
        
        template <typename Dummy>
        struct GetItemImpl<sizeof...(T), Dummy>
        {
            static Object Impl(Object tuple, int index)
            {
                throw new_Exception("Tuple index out of bounds");            
            }
        };

        static Object GetItem(Object tuple, int index)
        {
            return GetItemImpl<0>::Impl(tuple, index);
        }

        template <int I, typename Dummy = dummy>
        struct SetItemImpl
        {
            static void Impl(Object tuple, int index, Object value)
            {
                if (I == index) std::get<I>(*(StructWrapper<std::tuple<T...>>)tuple) = (std::tuple_element_t<I, std::tuple<T...>>)value;
                else SetItemImpl<I + 1>::Impl(tuple, index, value);
            }
        };

        template <typename Dummy>
        struct SetItemImpl<sizeof...(T), Dummy>
        {
            static void Impl(Object tuple, int index, Object value)
            {
                throw new_Exception("Tuple index out of bounds");
            }
        };

        static void SetItem(Object tuple, int index, Object value)
        {
            SetItemImpl<0>::Impl(tuple, index, value);
        }


        template <class Head, class Second, class ... Tail>
        static String get_name()
        {
            return dot::typeof<Head>()->Name + get_name<Second, Tail...>();
        }

        template <class Head>
        static String get_name()
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


    /// <summary>Get Type object for the argument.</summary>
    template <class T>
    Type typeof()
    {
        return typeof_impl<T>::get_typeof();
    }

}
