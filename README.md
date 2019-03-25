# DotCpp (.C++)

DotCpp (.C++) project is a C++ implementation of popular .NET APIs including the .NET
Standard Library, NodaTime, and others. Its purpose is to facilitate code reuse between
C# and C++.

.C++ is developed and maintained by [CompatibL](http://www.compatibl.com "CompatibL"), a provider of custom software development services, market and credit risk solutions, and model validation consultancy for the financial industry.


## Purpose

When code is written in C# and has to be ported to C++, the fundamental differences
between two distinct API styles, one represented by the .NET Standard Library and the othe
by core C++ libraries such as STL and Boost, becomes major obstacle to code reuse.

As an example, consider this code in C#:

```
myList.OrderBy(_ => _.x).ThenBy(_ => _.y).ToList();
```

and this code in C++:

```
std::sort(begin(my_list), end(my_list),
    [](auto const& l, auto const& r)
    {
      return std::tie(l.y, l.x) < std::tie(r.y, r.x);
    }
);
```

Both code snippets perform the same function. However translating from one to
the other requires major changes in code structure, making the process of porting
slower and more error-prone.

The objective of the .C++ project is to provide .NET like API on top of STL and Boost.
This is accomplished by defining classes that implement .NET APIs and are derived from
STL and Boost classes. These classes work with STL algorithms as well as with C# like
code that can for the most part be obtained from C# by replacing . operator by -> and
new operator by new_ function prefix.

## Example

To illustrate the .C++ API style, we will use the following C# example that creates
an empty list, adds an element, and prints the result:

```
var myList = new List<double>();
myList.Add(1.0);
Console.WriteLine(myList);
```

In .C++, the same code would look as follows:

```
auto myList = new_List<double>();
myList->Add(1.0);
Console->WriteLine(myList);
```

By making it possible to write boilerplate code in C++ that mirrors the C# original,
the effort of porting from C# to C++ is simplified, reducing the need for complex code
changes.
