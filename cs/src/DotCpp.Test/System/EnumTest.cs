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
using System.CodeDom.Compiler;
using System.IO;
using System.Text;
using Xunit;
using Xunit.Sdk;
using ApprovalTests;
using ApprovalTests.Reporters;
using ApprovalUtilities.SimpleLogger;

namespace DotCpp
{
    /// <summary>Enum sample.</summary>
    public enum EnumSample
    {
        /// <summary>Empty value.</summary>
        Empty,

        /// <summary>First value.</summary>
        First,

        /// <summary>Second value.</summary>
        Second
    }

    [UseReporter(typeof(DiffReporter))]
    public class EnumTest
    {
        private static IndentedTextWriter received = new IndentedTextWriter(new StringWriter());

        [Fact]
        public void Smoke()
        {
            // Serialization
            received.WriteLine("Serialization");
            received.Indent++;

            // Serialize
            EnumSample value = EnumSample.First;
            string serializedValue = value.ToString();
            received.WriteLine($"Serialized={serializedValue}");

            // Deserialize
            bool result1 = Enum.TryParse("First", out EnumSample value1);
            received.WriteLine($"Result={result1} Value={value1}");
            bool result2 = Enum.TryParse("UnknownValue", out EnumSample value2);
            received.WriteLine($"Result={result2} Value={value2}");

            // Reflection
            received.Indent = 0;
            received.WriteLine("Reflection");
            received.Indent++;

            Type type = typeof(EnumSample);
            received.WriteLine($"Name={type.Name}");
            received.WriteLine($"Namespace={type.Namespace}");
            received.WriteLine($"FullName={type.FullName}");
            received.WriteLine($"IsEnum={type.IsEnum}");

            Approvals.Verify(received.InnerWriter.ToString());
        }
    }
}
