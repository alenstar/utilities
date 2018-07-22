// Copyright 2014 eric schkufza
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPPUTIL_INCLUDE_META_IS_64_BIT_H
#define CPPUTIL_INCLUDE_META_IS_64_BIT_H

#include <stdint.h>
#include <type_traits>

namespace cpputil {

template <typename T>
struct is_64_bit : public std::false_type { };

template <>
struct is_64_bit<uint64_t> : public std::true_type { };

template <>
struct is_64_bit<const uint64_t> : public std::true_type { };

template <>
struct is_64_bit<int64_t> : public std::true_type { };

template <>
struct is_64_bit<const int64_t> : public std::true_type { };

template <>
struct is_64_bit<double> : public std::true_type { };

template <>
struct is_64_bit<const double> : public std::true_type { };

} // namespace cpputil

#endif



