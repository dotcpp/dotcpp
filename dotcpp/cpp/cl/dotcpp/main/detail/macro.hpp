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

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#define CAT_IMPL(s1, s2) s1##s2
#define CAT(s1, s2) CAT_IMPL(s1, s2)


#define GET_ARG_COUNT(...)  EXPAND__(CONVERT_TO_ARGS(__VA_ARGS__))

#define CONVERT_TO_ARGS(...) unused, __VA_ARGS__
#define EXPAND(x) x

#define EXPAND__(...) EXPAND(GET_ARG_COUNT___(__VA_ARGS__, \
                                     124, 123, 122, 121, 120, \
            119, 118, 117, 116, 115, 114, 113, 112, 111, 110, \
            109, 108, 107, 106, 105, 104, 103, 102, 101, 100, \
             99,  98,  97,  96,  95,  94,  93,  92,  91,  90, \
             89,  88,  87,  86,  85,  84,  83,  82,  81,  80, \
             79,  78,  77,  76,  75,  74,  73,  72,  71,  70, \
             69,  68,  67,  66,  65,  64,  63,  62,  61,  60, \
             59,  58,  57,  56,  55,  54,  53,  52,  51,  50, \
             49,  48,  47,  46,  45,  44,  43,  42,  41,  40, \
             39,  38,  37,  36,  35,  34,  33,  32,  31,  30, \
             29,  28,  27,  26,  25,  24,  23,  22,  21,  20, \
             19,  18,  17,  16,  15,  14,  13,  12,  11,  10, \
              9,   8,   7,   6,   5,   4,   3,   2,   1,   0))

#define GET_ARG_COUNT___(                                                                       \
                           _0_,   _1_,   _2_,   _3_,   _4_,   _5_,   _6_,   _7_,   _8_,   _9_,  \
                          _10_,  _11_,  _12_,  _13_,  _14_,  _15_,  _16_,  _17_,  _18_,  _19_,  \
                          _20_,  _21_,  _22_,  _23_,  _24_,  _25_,  _26_,  _27_,  _28_,  _29_,  \
                          _30_,  _31_,  _32_,  _33_,  _34_,  _35_,  _36_,  _37_,  _38_,  _39_,  \
                          _40_,  _41_,  _42_,  _43_,  _44_,  _45_,  _46_,  _47_,  _48_,  _49_,  \
                          _50_,  _51_,  _52_,  _53_,  _54_,  _55_,  _56_,  _57_,  _58_,  _59_,  \
                          _60_,  _61_,  _62_,  _63_,  _64_,  _65_,  _66_,  _67_,  _68_,  _69_,  \
                          _70_,  _71_,  _72_,  _73_,  _74_,  _75_,  _76_,  _77_,  _78_,  _79_,  \
                          _80_,  _81_,  _82_,  _83_,  _84_,  _85_,  _86_,  _87_,  _88_,  _89_,  \
                          _90_,  _91_,  _92_,  _93_,  _94_,  _95_,  _96_,  _97_,  _98_,  _99_,  \
                         _100_, _101_, _102_, _103_, _104_, _105_, _106_, _107_, _108_, _109_,  \
                         _110_, _111_, _112_, _113_, _114_, _115_, _116_, _117_, _118_, _119_,  \
                         _120_, _121_, _122_, _123_, _124_,                                     \
                                                                            count, ...) count
