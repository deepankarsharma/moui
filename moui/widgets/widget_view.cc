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

#include "moui/widgets/widget_view.h"

#include "moui/core/device.h"
#include "moui/nanovg_hook.h"
#include "moui/opengl_hook.h"
#include "moui/ui/native_view.h"
#include "moui/ui/view.h"
#include "moui/widgets/widget.h"

namespace moui {

WidgetView::WidgetView() : View(), context_(nullptr), widget_(new Widget) {
  widget_->set_widget_view(this);
}

WidgetView::~WidgetView() {
  if (context_ != nullptr) {
    nvgDeleteGL(context_);
  }
  delete widget_;
}

void WidgetView::Render() {
  if (context_ == nullptr) {
    context_ = nvgCreateGL(NVG_ANTIALIAS);
  }

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);

  nvgBeginFrame(context_, GetWidth(), GetHeight(),
                Device::GetScreenScaleFactor());
  RenderWidget(widget_);
  nvgEndFrame(context_);
}

void WidgetView::RenderWidget(Widget* widget) {
  if (widget->IsHidden())
    return;
  const int kWidgetWidth = widget->GetWidth();
  if (kWidgetWidth <= 0)
    return;
  const int kWidgetHeight = widget->GetHeight();
  if (kWidgetHeight <= 0)
    return;
  const int kWidgetX = widget->GetX();
  if ((kWidgetX + kWidgetWidth) < 0)
    return;
  const int kWidgetY = widget->GetY();
  if ((kWidgetY + kWidgetHeight) < 0)
    return;

  nvgSave(context_);
  nvgScissor(context_, kWidgetX, kWidgetY, kWidgetWidth, kWidgetHeight);
  nvgTranslate(context_, kWidgetX, kWidgetY);
  widget->Render(context_);
  // Renders visible children.
  for (Widget* child : widget->children()) {
    if (child->GetX() > kWidgetWidth || child->GetY() > kWidgetHeight)
      continue;
    RenderWidget(child);
  }
  nvgRestore(context_);
}

void WidgetView::SetBounds(const int x, const int y, const int width,
                           const int height) const {
  NativeView::SetBounds(x, y, width, height);
  widget_->SetWidth(Widget::Unit::kPixel, width);
  widget_->SetHeight(Widget::Unit::kPixel, height);
  Redraw();
}

}  // namespace moui
