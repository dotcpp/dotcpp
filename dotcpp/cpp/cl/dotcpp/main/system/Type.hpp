/*
Copyright (C) 2003-present CompatibL

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

#include <cl/dotcpp/main/system/Object.hpp>
#include <cl/dotcpp/main/system/String.hpp>
#include <cl/dotcpp/main/system/Array1D.hpp>
#include <cl/dotcpp/main/system/collections/generic/List.hpp>
#include <cl/dotcpp/main/system/reflection/MethodInfo.hpp>
#include <cl/dotcpp/main/system/reflection/ParameterInfo.hpp>
#include <cl/dotcpp/main/system/reflection/PropertyInfo.hpp>

namespace cl
{
    class StringImpl; class String;
    class TypeImpl; using Type = Ptr<TypeImpl>;
    class TypeDataImpl; using TypeData = Ptr<TypeDataImpl>;
    class StringImpl; class String;
    class MethodInfoImpl; using MethodInfo = Ptr<MethodInfoImpl>;
    class ConstructorInfoImpl; using ConstructorInfo = Ptr<ConstructorInfoImpl>;
    class PropertyInfoImpl; using PropertyInfo = Ptr<PropertyInfoImpl>;
    template <class T> class ListImpl; template <class T> using List = Ptr<ListImpl<T>>;
    template <class T> class Array1DImpl; template <class T> using Array1D = Ptr<Array1DImpl<T>>;
    template <class Class, class ... Args> class MemberConstructorInfoImpl;

    template <class T> Type typeof();

    /// <summary>Builder for Type.</summary>
    class CL_DOTCPP_MAIN TypeDataImpl final : public virtual ObjectImpl
    {
        template <class>
        friend TypeData new_TypeData(String, String);
        friend class TypeImpl;

    private:
        String fullName_;
        List<PropertyInfo> properties_;
        List<MethodInfo> methods_;
        List<ConstructorInfo> ctors_;
        Type type_;

    public: // METHODS

        /// <summary>Add public property of the current Type.</summary>
        template <class Class, class Prop>
        TypeData WithProperty(String name, Prop Class::*prop)
        {
             if (properties_.IsEmpty())
             {
                 properties_ = new_List<PropertyInfo>();
             }
             properties_->Add(new PropertyInfoPropertyImpl<Prop, Class>(name, type_, typeof<typename Prop::value_type>(), prop));
             return this;
        }

        /// <summary>Add public member method of the current Type.</summary>
        template <class Class, class Return, class ... Args>
        TypeData WithMethod(String name, Return(Class::*mth) (Args ...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { typeof<Args>()... };

            for (int i = 0; i < argsCount; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            MethodInfo methodInfo_ = new MemberMethodInfoImpl<Class, Return, Args...>(name, type_, typeof<Return>(), mth);
            methodInfo_->Parameters = parameters;

            methods_->Add(methodInfo_);

            return this;
        }

        /// <summary>Add public static method of the current Type.</summary>
        template <class Return, class ... Args>
        TypeData WithMethod(String name, Return(*mth) (Args ...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount = sizeof...(Args);
            if (argsCount != names.size())
                throw Exception("Wrong number of parameters for method " + fullName_);

            if (methods_.IsEmpty())
            {
                methods_ = new_List<MethodInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { typeof<Args>()... };

            for (int i = 0; i < argsCount; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            MethodInfo methodInfo_ = new StaticMethodInfoImpl<Return, Args...>(name, type_, typeof<Return>(), mth);
            methodInfo_->Parameters = parameters;

            methods_->Add(methodInfo_);

            return this;
        }

        /// <summary>Add public constructor of the current Type.</summary>
        template <class Class, class ... Args>
        TypeData WithConstructor(Class(*ctor)(Args...), std::vector<String> const& names) // TODO Change to List? Make overload?
        {
            const int argsCount_ = sizeof...(Args);
            if (argsCount_ != names.size())
                throw Exception("Wrong number of parameters for method " + fullName_);

            if (ctors_.IsEmpty())
            {
                ctors_ = new_List<ConstructorInfo>();
            }

            Array1D<ParameterInfo> parameters = new_Array1D<ParameterInfo>(sizeof...(Args));
            std::vector<Type> paramTypes = { typeof<Args>()... };

            for (int i = 0; i < argsCount_; ++i)
            {
                parameters[i] = new_ParameterInfo(names[i], paramTypes[i], i);
            }

            ConstructorInfo ctorInfo = new MemberConstructorInfoImpl<Class, Args...>(type_, ctor);
            ctorInfo->Parameters = parameters;

            ctors_->Add(ctorInfo);

            return this;
        }


        /// <summary>Built Type from the current object.</summary>
        Type Build();

    private: // CONSTRUCTORS

        /// <summary>
        /// Create an empty instance of TypeData.
        ///
        /// This constructor is private. Use new_TypeData() function instead.
        /// </summary>
        TypeDataImpl(String Name, String Namespace, String CppName);
    };

    /// <summary>
    /// Create an empty instance of TypeData.
    /// </summary>
    template <class T>
    inline TypeData new_TypeData(String Name, String Namespace) { return new TypeDataImpl(Name, Namespace, typeid(T).name()); }

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
    class CL_DOTCPP_MAIN TypeImpl final : public virtual ObjectImpl
    {
        friend class TypeDataImpl;
        template <class T>
        friend Type typeof();


    private: // FIELDS

        Array1D<PropertyInfo> properties_;
        Array1D<MethodInfo> methods_;
        Array1D<ConstructorInfo> ctors_;

    public: // PROPERTIES

        /// <summary>Gets the name of the current type, excluding namespace.</summary>
        DOT_AUTO_GET(String, Name);

        /// <summary>Gets the fully qualified name of the type, including its namespace but not its assembly.</summary>
        DOT_AUTO_GET(String, Namespace);

    public: // METHODS

        /// <summary>Returns all the public properties of the current Type.</summary>
        Array1D<PropertyInfo> GetProperties() { return properties_; }

        /// <summary>Returns methods of the current type.</summary>
        Array1D<MethodInfo> GetMethods() { return methods_; }

        /// <summary>Returns constructors of the current type.</summary>
        Array1D<ConstructorInfo> GetConstructors() { return ctors_; }

        /// <summary>Searches for the public property with the specified name.</summary>
        PropertyInfo GetProperty(String name);

        /// <summary>Searches for the public method with the specified name.</summary>
        MethodInfo GetMethod(String name);

        /// <summary>A string representing the name of the current type.</summary>
        virtual String ToString() const { return "Type"; } // TODO - return name

        /// <summary>Get Type object for the name.</summary>
        static Type GetType(String name) { return GetTypeMap()[name]; }

    private: // METHODS

        /// <summary>
        /// Fill data from builder.
        /// </summary>
        void Fill(const TypeData& data);

        static std::map<String, Type>& GetTypeMap()
        {
            static std::map<String, Type> map_;
            return map_;
        }

    private: // CONSTRUCTORS

        /// <summary>
        /// Create from builder.
        ///
        /// This constructor is private. Use TypeBuilder->Build() method instead.
        /// </summary>
        TypeImpl(String Name, String Namespace);
    };

    /// <summary>Get Type object for the argument.</summary>
    template <class T>
    Type typeof()
    {
        String cpp_name = typeid(typename T::element_type).name();
        auto wh = TypeImpl::GetTypeMap().find(cpp_name);
        if (wh == TypeImpl::GetTypeMap().end())
        {
            Type type = T::element_type::typeof();
            return type;
        }

        return wh->second;
    }

    /// <summary>
    /// Initializes a new instance of the Type class for untyped instance of Object.
    /// </summary>
    inline Type ObjectImpl::GetType()
    {
        return new_TypeData<ObjectImpl>("Object", "System")->Build();
    }

    template <>
    inline Type typeof<String>() { return new_TypeData<String>("String", "System")->Build(); }

    template <>
    inline Type typeof<double>() { return new_TypeData<double>("Double", "System")->Build(); }

    template <>
    inline Type typeof<int64_t>() { return new_TypeData<int64_t>("Int64", "System")->Build(); }

    template <>
    inline Type typeof<int>() { return new_TypeData<int>("Int32", "System")->Build(); }

    template <>
    inline Type typeof<void>() { return new_TypeData<void>("Void", "System")->Build(); }
}
