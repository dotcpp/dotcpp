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

namespace Cl.DotCpp.Test
{
    [UseReporter(typeof(DiffReporter))]
    public class LocalDateTest
    {
        private static StringBuilder received = new StringBuilder();
        private static LocalDatePattern pattern_ { get; } = LocalDatePattern.CreateWithInvariantCulture("uuuu'-'MM'-'dd");

        [Fact]
        public void Smoke()
        {
            received.AppendLine("Default constructed");
            var defaultConstructed = new LocalDate();
            var yearMonthDayOneConstructed = new LocalDate(1,1,1);
            Print(nameof(defaultConstructed), defaultConstructed);
            Print(nameof(yearMonthDayOneConstructed), yearMonthDayOneConstructed);
            Print("equal", defaultConstructed == yearMonthDayOneConstructed);

            received.AppendLine();
            received.AppendLine("Constructed from Y,M,D");
            var ymdConstructed = new LocalDate(2003, 5, 1);
            Print(nameof(ymdConstructed), ymdConstructed);

            Approvals.Verify(received.ToString());
            received.Clear();
        }

        void Print(string name, LocalDate value)
        {
            received.AppendLine(String.Format("{0}: {1}", name, pattern_.Format(value)));
        }

        void Print(string name, bool value)
        {
            received.AppendLine(String.Format("{0}: {1}", name, value));
        }
    }
}
