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
    public class ListTest
    {
        private static StringBuilder received = new StringBuilder();

        /// <summary>Print double vector to received on one line in JSON format.</summary>
        static void PrintList(String name, List<double> v)
        {
            received.Append("\"" + name + "\" : [ ");
            for (int i = 0; i < v.Count; ++i)
            {
                if (i > 0) received.Append(", ");
                received.Append(v[i]);
            }
            received.AppendLine(" ]");
        }

        [Fact]
        public void Smoke()
        {
            List<double> a = new List<double>();
            a.Add(0.0);
            a.Add(1.0);
            a.Add(2.0);

            Assert.True(a.Count == 3);
        }

        [Fact]
        public void Interfaces()
        {
            List<double> a = new List<double>();

            // Add elements to IList interface
            IList<double> b = a;
            b.Add(2.0);
            b.Add(1.0);
            b.Add(0.0);

            // Check size of the original class and the interface
            Assert.True(a.Count == 3);
            Assert.True(b.Count == 3);

            // Access the underlying std::vector<double> class
            PrintList("Unsorted", a);
            a.Sort();
            PrintList("Sorted", a);

            // Access by Object and check the return value of ToString() 
            Object obj = b;
            received.AppendLine(a.ToString());
 
            Approvals.Verify(received.ToString());
            received.Clear();
        }

        [Fact]
        public void Iterators()
        {
            List<String> stringList = new List<String>();
            stringList.Add("000");
            stringList.Add("111");
            stringList.Add("222");
            Assert.True(stringList.Count == 3);

            int i = 0;
            foreach (String str in stringList)
            {
                Assert.True(stringList[i++] == str);
            }
        }

        [Fact]
        public void Capacity()
        {
            List<String> stringList = new List<String>();
            stringList.Capacity = 100;
            Assert.True(stringList.Capacity == 100);
        }

        [Fact]
        public void Find()
        {
            List<String> stringList = new List<String>();
            stringList.Add("000");
            stringList.Add("111");
            stringList.Add("222");
            stringList.Add("333");
            stringList.Add("444");

            // TODO stringList.findLast([](std::string const& s) { return s == "222"; }) = "57";
            // TODO Assert.True(stringList.findLastIndex([](std::string const& s) { return s == "111"; }) == 0);
        }

        [Fact]
        public void Enumerator()
        {
            // Create list
            List<String> stringList = new List<String>();
            stringList.Add("000");
            stringList.Add("111");
            stringList.Add("222");
            Assert.True(stringList.Count == 3);

            // Iterate using foreach
            int i = 0;
            foreach (String str in stringList)
            {
                Assert.True(stringList[i++] == str);
            }

            // Iterate using enumerator
            i = 0;
            IEnumerator<String> en = stringList.GetEnumerator();
            for (; en.MoveNext();)
            {
                Assert.True(stringList[i++] == en.Current);
            }

            // Reset the enumerator and iterate again
            i = 0;
            en.Reset();
            for (; en.MoveNext();)
            {
                Assert.True(stringList[i++] == en.Current);
            }
        }
    }
}