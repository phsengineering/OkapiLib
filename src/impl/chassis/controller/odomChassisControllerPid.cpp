/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/impl/chassis/controller/odomChassisControllerPid.hpp"
#include "okapi/api/odometry/odomMath.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"
#include <cmath>

namespace okapi {
OdomChassisControllerPID::OdomChassisControllerPID(
  std::shared_ptr<SkidSteerModel> imodel, std::unique_ptr<Odometry> iodometry,
  const IterativePosPIDControllerArgs &idistanceArgs,
  const IterativePosPIDControllerArgs &iangleArgs, const float imoveThreshold)
  : ChassisController(imodel),
    OdomChassisController(imodel, std::move(iodometry), imoveThreshold),
    ChassisControllerPID(TimeUtilFactory::create(), imodel, idistanceArgs, iangleArgs) {
}

void OdomChassisControllerPID::driveToPoint(const float ix, const float iy, const bool ibackwards,
                                            const float ioffset) {
  DistanceAndAngle daa = OdomMath::computeDistanceAndAngleToPoint(ix, iy, odom->getState());

  if (ibackwards) {
    daa.theta += 180;
    daa.length *= -1;
  }

  if (std::abs(daa.theta) > 1) {
    ChassisControllerPID::turnAngle(daa.theta);
  }

  if (std::abs(daa.length - ioffset) > moveThreshold) {
    ChassisControllerPID::moveDistance(static_cast<int>(daa.length - ioffset));
  }
}

void OdomChassisControllerPID::turnToAngle(const float iangle) {
  ChassisControllerPID::turnAngle(iangle - odom->getState().theta);
}
} // namespace okapi
