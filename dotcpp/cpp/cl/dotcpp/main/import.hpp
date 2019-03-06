﻿/*
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

#ifndef cl_dotcpp_main_import_hpp
#define cl_dotcpp_main_import_hpp

// Supports compilation into Windows DLL
#ifndef CL_IMPLEMENT
#   if defined(_WIN32) && !defined(__MINGW32__)
#       define CL_IMPLEMENT __declspec(dllexport)
#       define CL_DECLARE __declspec(dllimport)
#   else
#       define CL_IMPLEMENT
#       define CL_DECLARE
#   endif
#endif

// Avoid problems with macros min/max on windows(windows.h)
#define NOMINMAX

#ifdef WIN32
// Avoid compiler warning about DLL export for STL types
#   pragma warning(disable : 4251)
// Avoid compiler warning about conversion from size_t to int
#   pragma warning(disable : 4267)
#endif

// Standard STL includes
#include <string>
#include <vector>
#include <set>
#include <memory>
#include <limits>
#include <stdexcept>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

#endif // cl_dotcpp_main_import_hpp
