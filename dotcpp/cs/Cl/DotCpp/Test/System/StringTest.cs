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
using System.Text;
using Xunit;
using Xunit.Sdk;
using ApprovalTests;
using ApprovalTests.Reporters;

namespace Cl.DotCpp.Test
{
    [UseReporter(typeof(DiffReporter))]
    public class StringTest
    {
        private static StringBuilder received = new StringBuilder();

        [Fact]
        public void Smoke()
        {
            // Empty string
            String empty = String.Empty;
            received.AppendLine(empty);

            // Create using new
            String usingCtor = new String("abcd");
            received.AppendLine(usingCtor);

            // Create using assignment
            String usingAssignment = "abcd";
            received.AppendLine(usingAssignment);

            Approvals.Verify(received.ToString());
            received.Clear();
        }

        [Fact]
        public void Compare()
        {
            // Compare to literal strings
            String str = "abcd";
            Assert.True(str == "abcd");

            // Check comparison case sensitivity
            Assert.False(str == "Abcd");

            // Compare two strings that have the same value but are not the same instances
            String str2 = "abcd";
            Assert.True(str == str2);

            // Compare two strings that have the same value but are not the same instances
            // after casting one or both to object
            Assert.True(str == (Object)str2);
            Assert.True((Object)str == (Object)str2);
        }

        [Fact]
        public void Char()
        {
            // Access character inside string by index
            {
                String str = "abcd";
                Char x = str[1];
                received.AppendLine(x.ToString());
            }

            // Iterate over characters in string
            {
                String str = "abcd";
                foreach (Char x in str)
                {
                    received.Append(x.ToString());
                }
                received.AppendLine();
            }

            Approvals.Verify(received.ToString());
            received.Clear();
        }
    }
}
