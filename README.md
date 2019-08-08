# DotCpp

DotCpp project is a partial port of popular .NET libraries including the .NET Standard Library, NodaTime, and others to native C++17. Its purpose is to facilitate code reuse between C# and C++.

DotCpp is developed and maintained by [CompatibL](http://www.compatibl.com "CompatibL"), a provider of custom software development services, market and credit risk solutions, and model validation consultancy for the financial industry.

## Purpose

When code is written in C# and has to be ported to C++, the fundamental differences between two distinct API styles, one represented by the .NET Standard Library and the other by core C++ libraries such as STL and Boost, becomes major obstacle to code reuse.

As an example, consider this code in C# to sort a structure of type Foo with two properties A and B using LINQ:
```
List<Foo> x = new List<Foo>();
... populate the list here ...
List<Foo> y = x.OrderBy(_ => _.A).ThenBy(_ => _.B).ToList();
```
and this code in C++:
```
std::vector<foo> x;
... populate the list here ...
std::sort(begin(x), end(x),
    [](auto const& l, auto const& r)
    {
      return std::tie(l.a, l.b) < std::tie(r.b, r.a);
    }
);
```
Both code snippets perform the same function. However translating from one to the other requires major changes in code structure, making the process of porting slower and more error prone. With DotCpp, the C++ code becomes more similar to the C# code:
```
dot::list<foo> x = dot::make_list<foo>();
... populate the list here ...
dot::list<foo> y = x.order_by(foo_impl::a).then_by(foo_impl::b).to_list();
```
The main difference is now mostly cosmetic - C# code uses the standard .NET naming convention, while DotCpp code uses the canonical snake_case naming convention of STL and Boost.

## Reference semantics

DotCpp types based on C# classes have reference semantics implemented using std::shared_ptr, with full support for System.Object (mapped to dot::object) and boxing/unboxing behavior for value types and support for C# like cast, is, and as operators.

A DotCpp pointer has implicit conversion to a pointer to base, and explicit conversion (cast operator) to a pointer to derived, providing behavior that is similar to type conversion in .NET.

## Reflection

.NET reflection based on GetType() and typeof(T) methods is supported for classes and enums, providing support for serialization and invoking methods with parameters.

## STL compatibility

Because core DotCpp containers are either derived from the corresponding STL containers, or directly implement begin/end and iterators, they can be passed to methods expecting STL containers or specific STL types:
```
dot::list<double> x = dot::make_list<double>();
... populate the list here ...
std::sort(*x);
```