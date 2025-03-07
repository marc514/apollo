/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <memory>

#include "modules/routing/routing.h"

namespace apollo {
namespace routing {

class RoutingComponent final
    : public ::apollo::cyber::Component<RoutingRequest> {
 public:
  RoutingComponent() = default;
  ~RoutingComponent() = default;

 public:
  bool Init() override;
  bool Proc(const std::shared_ptr<RoutingRequest>& request) override;

 private:
  // ‘::’位于开头 means 全局命名空间
  std::shared_ptr<::apollo::cyber::Writer<RoutingResponse>> response_writer_ =
      nullptr;
  std::shared_ptr<::apollo::cyber::Writer<RoutingResponse>>
      response_history_writer_ = nullptr;
  Routing routing_;
  std::shared_ptr<RoutingResponse> response_ = nullptr;
  std::unique_ptr<::apollo::cyber::Timer> timer_;
  std::mutex mutex_;
};

CYBER_REGISTER_COMPONENT(RoutingComponent)

}  // namespace routing
}  // namespace apollo
