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

#include "include/io/fail.h"

using namespace cpputil;
using namespace std;

int main() {
	fail(cout) << "cout is broken";
	if (failed(cout)) {
		clog << "Should see this: " << fail_msg(cout) << endl;	
	}
	if (failed(cerr)) {
		clog << "Shouldn't see this" << endl;
	}

  if (warned(cerr)) {
    clog << "Shouldn't see this" << endl;
  }
  warn(cerr) << "cerr is sort of okay";
  if (warned(cout)) {
    clog << "Shouldn't see this" << endl;
  }
  if (warned(cerr)) {
    clog << "Should see this: " << warn_msg(cerr) << endl;
  }

	stringstream ss;
	fail(ss) << "An iostream is broken";
	if (failed(ss)) {
		clog << "Should see this: " << fail_msg(ss) << endl;
	}

  return 0;
}

