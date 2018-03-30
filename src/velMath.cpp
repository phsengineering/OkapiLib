/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/filter/velMath.hpp"
#include "api.h"

namespace okapi {
VelMathArgs::VelMathArgs(const double iticksPerRev, const double ialpha, const double ibeta)
  : ticksPerRev(iticksPerRev), alpha(ialpha), beta(ibeta) {
}

VelMathArgs::~VelMathArgs() = default;

VelMath::VelMath(const double iticksPerRev, const double ialpha, const double ibeta)
  : ticksPerRev(iticksPerRev), filter(ialpha, ibeta) {
}

VelMath::VelMath(const VelMathArgs &iparams)
  : ticksPerRev(iparams.ticksPerRev), filter(iparams.alpha, iparams.beta) {
}

double VelMath::step(const double inewPos) {
  const uint32_t now = millis();

  vel = static_cast<double>((1000 / (now - lastTime))) * (inewPos - lastPos) * (60 / ticksPerRev);
  vel = filter.filter(vel);
  accel = static_cast<double>((1000 / (now - lastTime))) * (vel - lastVel);

  lastVel = vel;
  lastPos = inewPos;
  lastTime = now;

  return vel;
}

void VelMath::setGains(const double ialpha, const double ibeta) {
  filter.setGains(ialpha, ibeta);
}

void VelMath::setTicksPerRev(const double iTPR) {
  ticksPerRev = iTPR;
}

double VelMath::getOutput() const {
  return vel;
}

double VelMath::getAccel() const {
  return accel;
}
} // namespace okapi
