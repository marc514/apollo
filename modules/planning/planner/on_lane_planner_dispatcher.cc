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

#include "modules/planning/planner/on_lane_planner_dispatcher.h"
#include "cyber/common/file.h"
#include "modules/planning/common/planning_gflags.h"
#include "modules/planning/proto/planning_config.pb.h"
// 通过编译生成的planning_config.pb.h，读取/planning/conf/planning_config.pb.txt
/**********！！！求解
 * standard_planning_config {
 *  planner_type: PUBLIC_ROAD
 *  planner_public_road_config {
 *  }
 *}
**********/

namespace apollo {
namespace planning {

std::unique_ptr<Planner> OnLanePlannerDispatcher::DispatchPlanner() {
  PlanningConfig planning_config;
  bool res_load_config = apollo::cyber::common::GetProtoFromFile(
      FLAGS_planning_config_file, &planning_config);
  if (!res_load_config) {
    return nullptr;
  }
  // planner_factory_创建PUBLIC_ROAD planner
  return planner_factory_.CreateObject(
      planning_config.standard_planning_config().planner_type(0));
}

}  // namespace planning
}  // namespace apollo
