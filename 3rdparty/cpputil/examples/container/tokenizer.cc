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

#include <iostream>
#include <string>

#include "include/container/tokenizer.h"

using namespace cpputil;
using namespace std;

int main() {
  Tokenizer<string> t;
  t.tokenize("Hello");
  t.tokenize("world");

  for (int n = 0; n < 2; ++n) {
    cout << "Tokenized strings: (" << t.size() << ") [ ";
    for (const auto& itr : t) {
      cout << "(" << itr.first << " " << itr.second << ") ";
    }
    cout << "]" << endl;

    t.clear();
  }

  return 0;
}

