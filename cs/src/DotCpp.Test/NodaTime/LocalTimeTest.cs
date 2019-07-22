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
using ApprovalTests;
using ApprovalTests.Reporters;
using NodaTime;
using NodaTime.Text;

namespace DotCpp
{
    [UseReporter(typeof(DiffReporter))]
    public class LocalTimeTest
    {
        private static StringBuilder received = new StringBuilder();
        private static LocalTimePattern pattern_ { get; } = LocalTimePattern.CreateWithInvariantCulture("HH':'mm':'ss.FFF");

        [Fact]
        public void Smoke()
        {
            received.AppendLine("Default constructed");
            var defaultConstructed = new LocalTime();
            var midnightConstructed = new LocalTime(0,0,0);
            Print(nameof(defaultConstructed), defaultConstructed);
            Print(nameof(midnightConstructed), midnightConstructed);
            Print("equal", defaultConstructed == midnightConstructed);

            received.AppendLine();
            received.AppendLine("Constructed from H,M,S with and without milliseconds");
            var withoutMilliseconds = new LocalTime(11, 15, 30);
            var withMilliseconds = new LocalTime(11, 15, 30, 123);
            Print(nameof(withoutMilliseconds), withoutMilliseconds);
            Print(nameof(withMilliseconds), withMilliseconds);

            Approvals.Verify(received.ToString());
            received.Clear();
        }

        void Print(string name, LocalTime value)
        {
            received.AppendLine(String.Format("{0}: {1}", name, pattern_.Format(value)));
        }

        void Print(string name, bool value)
        {
            received.AppendLine(String.Format("{0}: {1}", name, value));
        }
    }
}
