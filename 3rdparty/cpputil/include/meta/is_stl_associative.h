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

#ifndef CPPUTIL_META_IS_STL_ASSOCIATIVE_H
#define CPPUTIL_META_IS_STL_ASSOCIATIVE_H

#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

namespace cpputil {

template <typename T>
struct is_stl_associative : public std::false_type { };

template <typename Key, typename Comp, typename Alloc>
struct is_stl_associative<std::multiset<Key, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename Comp, typename Alloc>
struct is_stl_associative<const std::multiset<Key, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename Comp, typename Alloc>
struct is_stl_associative<std::set<Key, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename Comp, typename Alloc>
struct is_stl_associative<const std::set<Key, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<std::unordered_set<Key, Hash, Eq, Alloc>> : public std::true_type { };

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<const std::unordered_set<Key, Hash, Eq, Alloc>> : public
        std::true_type { };

template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<std::unordered_multiset<Key, Hash, Eq, Alloc>> : public
        std::true_type { };
template <typename Key, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<const std::unordered_multiset<Key, Hash, Eq, Alloc>> : public
        std::true_type { };

template <typename Key, typename T, typename Comp, typename Alloc>
struct is_stl_associative<std::map<Key, T, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename T, typename Comp, typename Alloc>
struct is_stl_associative<const std::map<Key, T, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename T, typename Comp, typename Alloc>
struct is_stl_associative<std::multimap<Key, T, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename T, typename Comp, typename Alloc>
struct is_stl_associative<const std::multimap<Key, T, Comp, Alloc>> : public std::true_type { };

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<std::unordered_map<Key, T, Hash, Eq, Alloc>> : public std::true_type { };

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<const std::unordered_map<Key, T, Hash, Eq, Alloc>> : public
        std::true_type { };

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public
        std::true_type { };

template <typename Key, typename T, typename Hash, typename Eq, typename Alloc>
struct is_stl_associative<const std::unordered_multimap<Key, T, Hash, Eq, Alloc>> : public
        std::true_type { };

} // namespace cpputil

#endif
