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


#include <dot/implement.hpp>
#include <dot/system/type.hpp>
#include <dot/system/objectimpl.hpp>
#include <dot/system/reflection/MethodInfo.hpp>
#include <dot/system/reflection/ConstructorInfo.hpp>
#include <dot/system/Array1D.hpp>
#include <dot/system/collections/generic/List.hpp>
#include <dot/system/string.hpp>

namespace dot
{
    /// <summary>Built type_t from the current object.</summary>
    type_t TypeBuilderImpl::Build()
    {
        type_->Fill(this);

        // Fill derived types map
        type_t base_type = base_;
        while (base_type != nullptr)
        {
            auto iter = type_impl::GetDerivedTypesMap().find(base_type->FullName);
            if (iter == type_impl::GetDerivedTypesMap().end())
            {
                iter = type_impl::GetDerivedTypesMap().insert({base_type->FullName, new_List<type_t>()}).first;
            }
            else if (iter->second == nullptr)
            {
                iter->second = new_List<type_t>();
            }
            iter->second->Add(type_);
            base_type = base_type->BaseType;
        }

        return type_;
    }

    /// <summary>
    /// Fill data from builder.
    /// </summary>
    void type_impl::Fill(const TypeBuilder& data)
    {
        if (!data->base_.IsEmpty() && data->base_->GetMethods()->count())
        {
            if (data->methods_.IsEmpty())
            {
                data->methods_ = new_List<MethodInfo>();
            }

            Array1D<MethodInfo> baseMethods = data->base_->GetMethods();
            List<MethodInfo> newMethods = new_List<MethodInfo>();
            for (MethodInfo methInfoData : baseMethods)
            {

                newMethods->Add(methInfoData);
            }

            for (MethodInfo methInfoData : data->methods_)
            {
                newMethods->Add(methInfoData);
            }

            data->methods_ = newMethods;
        }

        if (!data->methods_.IsEmpty())
        {
            this->methods_ = new_Array1D<MethodInfo>(data->methods_->count());
            int i = 0;
            for (MethodInfo methInfoData : data->methods_)
            {
                this->methods_[i++] = methInfoData;
            }
        }
        else
            this->methods_ = new_Array1D<MethodInfo>(0);

        if (!data->ctors_.IsEmpty())
        {
            this->ctors_ = new_Array1D<ConstructorInfo>(data->ctors_->count());
            int i = 0;
            for (ConstructorInfo ctorInfoData : data->ctors_)
            {
                this->ctors_[i++] = ctorInfoData;
            }
        }
        else
            this->ctors_ = new_Array1D<ConstructorInfo>(0);

        if (!data->interfaces_.IsEmpty())
        {
            this->interfaces_ = new_Array1D<type_t>(data->interfaces_->count());
            int i = 0;
            for (type_t interface : data->interfaces_)
            {
                this->interfaces_[i++] = interface;
            }
        }
        else
            this->interfaces_ = new_Array1D<type_t>(0);

        if (!data->generic_args_.IsEmpty())
        {
            this->generic_args_ = new_Array1D<type_t>(data->generic_args_->count());
            int i = 0;
            for (type_t arg : data->generic_args_)
            {
                this->generic_args_[i++] = arg;
            }
        }
        else
            this->generic_args_ = new_Array1D<type_t>(0);

        this->base_ = data->base_;
        this->IsClass = data->is_class_;
        this->IsEnum = data->is_enum_;
    }

    /// <summary>
    /// Create from builder.
    ///
    /// This constructor is private. Use TypeBuilder->Build() method instead.
    /// </summary>
    type_impl::type_impl(string nspace, string name)
    {
        this->Namespace = nspace;
        this->Name = name;
    }


    TypeBuilderImpl::TypeBuilderImpl(string Namespace, string Name, string CppName)
        : fullName_(Namespace + "." + Name)
    {
        type_ = new type_impl(Namespace, Name);
        type_impl::GetTypeMap()[fullName_] = type_;
        type_impl::GetTypeMap()[Name] = type_;
        type_impl::GetTypeMap()[CppName] = type_;
    }

    MethodInfo type_impl::GetMethod(string name)
    {
        if (methods_.IsEmpty()) return nullptr;

        for (auto method : methods_)
        {
            if (method->Name == name)
                return method;
        }

        return nullptr;
    }

    type_t type_impl::GetInterface(string name)
    {
        if (interfaces_.IsEmpty()) return nullptr;

        for (auto interface : interfaces_)
        {
            if (interface->Name == name)
                return interface;
        }

        return nullptr;
    }

    bool type_impl::Equals(object obj)
    {
        if (obj.is<type_t>())
            return this->FullName == ((type_t)obj)->FullName;

        return false;
    }

    size_t type_impl::GetHashCode()
    {
        return this->FullName->GetHashCode();
    }
}
