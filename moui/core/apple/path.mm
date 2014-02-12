// Copyright (c) 2014 Ollix. All rights reserved.
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
//
// ---
// Author: olliwang@ollix.com (Olli Wang)

#include "moui/core/path.h"

#include <string>

#import <Foundation/Foundation.h>

namespace moui {

std::string Path::GetResourceDirectory() const {
  NSBundle* bundle = [NSBundle mainBundle];
  if (bundle == nil)
    return "";
  return std::string([[bundle resourcePath] UTF8String]);
}

}  // namespace moui
