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

#ifndef MOUI_WIDGETS_WIDGET_H_
#define MOUI_WIDGETS_WIDGET_H_

#include <vector>

#include "moui/base.h"

struct NVGcontext;

namespace moui {

class Widget {
 public:
  explicit Widget();
  ~Widget();

  // Adds child widget.
  void AddChild(Widget* child);

  // Implements the logic for rendering the widget.
  virtual void Render(struct NVGcontext* context) {}

  // Sets the bounds of the widget.
  void SetBounds(const int x, const int y, const int width, const int height);

  // Setters and accessors.
  std::vector<Widget*>& children() { return children_; }
  int height() const { return height_; }
  void set_height(int height) { height_ = height; }
  bool hidden() const { return hidden_; }
  void set_hidden(bool hidden) { hidden_ = hidden; }
  int width() const { return width_; }
  void set_width(int width) { width_ = width; }
  int x() const { return x_; }
  void set_x(int x) { x_ = x; }
  int y() const { return y_; }
  void set_y(int y) { y_ = y; }

 private:
  // Holds a list of child widgets.
  std::vector<Widget*> children_;

  // The height of the widget.
  int height_;

  // Indicates whether the widget is hidden.
  bool hidden_;

  // The width of the widget.
  int width_;

  // The horizontal position related to its parent.
  int x_;

  // The vertical position related to its parent.
  int y_;

  DISALLOW_COPY_AND_ASSIGN(Widget);
};

}  // namespace moui

#endif  // MOUI_WIDGETS_WIDGET_H_
