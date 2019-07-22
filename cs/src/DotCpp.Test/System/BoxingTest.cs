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

Unless Assert.Trued by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

using System;
using Xunit;
using Xunit.Sdk;
using ApprovalTests;

namespace DotCpp
{
    public class BoxingTest
    {
        [Fact]
        public void Smoke()
        {
            {
                // Boxing bool
                bool x = false;
                Object boxed = x;
                Assert.True((bool) boxed == false);
                boxed = true;
                Assert.True((bool) boxed == true);
            }

            {
                // Boxing bool?
                bool? x = null;
                Object boxed = x;
                Assert.True(((bool?) boxed) == null);
                bool? y = true;
                boxed = y;
                Assert.True((bool) boxed == true);
            }

            {
                // Boxing double
                double x = 1.0;
                Object boxed = x;
                Assert.True((double) boxed == 1.0);
                boxed = 2.0;
                Assert.True((double) boxed == 2.0);
            }

            {
                // Boxing double?
                double? x = null;
                Object boxed = x;
                Assert.True(((double?) boxed) == null);
                double? y = 2.0;
                boxed = y;
                Assert.True((double) boxed == 2.0);
            }

            {
                // Boxing int
                int x = 1;
                Object boxed = x;
                Assert.True((int) boxed == 1);
                boxed = 2;
                Assert.True((int) boxed == 2);
            }

            {
                // Boxing int?
                int? x = null;
                Object boxed = x;
                Assert.True(((int?) boxed) == null);
                int? y = 2;
                boxed = y;
                Assert.True((int) boxed == 2);
            }
        }
    }
}
