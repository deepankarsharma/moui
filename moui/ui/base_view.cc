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

#include "moui/ui/base_view.h"

#include <algorithm>
#include <cstdio>
#include <string>

#include "moui/native/native_view.h"
#include "moui/opengl_hook.h"

namespace moui {

BaseView::BaseView() : NativeView(nullptr), animation_count_(0) {
}

BaseView::~BaseView() {
}

GLuint BaseView::CompileShader(const GLenum shader_type,
                               const std::string& source) const {
  // Compiles the shader.
  GLuint shader_handle = glCreateShader(shader_type);
  const GLchar* source_string = static_cast<const GLchar*>(source.c_str());
  const int source_length = static_cast<int>(source.length());
  glShaderSource(shader_handle, 1, &source_string, &source_length);
  glCompileShader(shader_handle);
  GLint compile_result;
  glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_result);
  if (compile_result == GL_FALSE) {
#if DEBUG
    GLchar message[256];
    glGetShaderInfoLog(shader_handle, sizeof(message), 0, &message[0]);
    fprintf(stderr, "Failed to compile shader: %s\n", message);
#endif
    glDeleteShader(shader_handle);
    shader_handle = 0;
  }
  return shader_handle;
}

GLuint BaseView::CompileShaderAtPath(const GLenum shader_type,
                                     const std::string& source_path) const {
  std::FILE* file = std::fopen(source_path.c_str(), "r");
  if (file == NULL)
    return 0;
  GLuint shader_handle = 0;
  if (std::fseek(file, 0, SEEK_END) == 0) {
    const int kFileSize = static_cast<int>(std::ftell(file));
    std::fseek(file, 0, SEEK_SET);
    char source_buffer[kFileSize];
    if (std::fread(source_buffer, 1, kFileSize, file) == kFileSize) {
      shader_handle = CompileShader(shader_type,
                                    std::string(source_buffer, kFileSize));
    }
  }
  std::fclose(file);
  return shader_handle;
}

bool BaseView::IsAnimating() const {
  return animation_count_ > 0;
}

void BaseView::StartAnimation() {
  ++animation_count_;
  StartUpdatingNativeView();
}

void BaseView::StopAnimation() {
  --animation_count_;
  if (animation_count_ == 0)
    StopUpdatingNativeView();
  animation_count_ = std::max(0, animation_count_);
}

}  // namespace moui
