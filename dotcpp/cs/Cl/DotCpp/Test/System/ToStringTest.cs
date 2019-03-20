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
using System.Collections.Generic;
using System.Text;
using Xunit;
using Xunit.Sdk;
using ApprovalTests;
using ApprovalTests.Reporters;

namespace Cl.DotCpp.Test
{
    [UseReporter(typeof(DiffReporter))]
    public class ToStringTest
    {
        private static StringBuilder received = new StringBuilder();

        [Fact]
        public void Smoke()
        {
            // Validate return value of ToString() for a variety of classes

            Object obj = new Object();
            received.AppendLine("Object: " + obj.ToString());

            String emptyStr = String.Empty;
            received.AppendLine("Empty String: " + emptyStr.ToString());

            String str = "abc";
            received.AppendLine("String: " + str.ToString());
            received.AppendLine("String Type: " + str.GetType().ToString());

            double? emptyDbl = null;
            received.AppendLine("Empty Double: " + emptyDbl.ToString());

            double dbl = 1.23;
            received.AppendLine("Double: " + dbl.ToString());
            received.AppendLine("Double Type: " + dbl.GetType().ToString());

            double[] doubleArr = new double[3];
            received.AppendLine("Double Array: " + doubleArr.ToString());
            received.AppendLine("Double Array Type: " + doubleArr.GetType().ToString());

            List<double> doubleList = new List<double> {1.0, 2.0, 3.0};
            received.AppendLine("Double List: " + doubleList.ToString());
            received.AppendLine("Double List Type: " + doubleList.GetType().ToString());

            Approvals.Verify(received.ToString());
            received.Clear();
        }
    }
}
