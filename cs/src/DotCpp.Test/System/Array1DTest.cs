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
using System.Linq;
using System.Text;
using Xunit;
using Xunit.Sdk;
using ApprovalTests;
using ApprovalTests.Reporters;

namespace Cl.DotCpp.Test
{
    [UseReporter(typeof(DiffReporter))]
    public class Array1DTest
    {
        private static StringBuilder received = new StringBuilder();

        /// <summary>Test members of dimensional array.</summary>
        [Fact]
        public void Smoke()
        {
            double[] x = new double[] {1, 2, 3};
            received.AppendLine("x.Length: " + x.Length);
            received.AppendLine("x.Rank: " + x.Rank);
            received.AppendLine("x.GetLength(0): " + x.GetLength(0));
            received.AppendLine("x[2]: " + x[2]);
            x[2] = 4;
            received.AppendLine("x[2]: " + x[2]);

            Array y = x;
            received.AppendLine("y.Length: " + y.Length);

            Approvals.Verify(received.ToString());
            received.Clear();
        }

        /// <summary>Test Array class.</summary>
        [Fact]
        public void Static()
        {
            double[] x = new double[] {3, 2, 1};
            Array.Sort(x);
            received.AppendLine("Sorted: " + x[0] + ", " + x[1] + ", " + x[2]);

            Approvals.Verify(received.ToString());
            received.Clear();
        }
    }
}
