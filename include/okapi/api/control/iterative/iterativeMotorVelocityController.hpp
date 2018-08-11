/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_ITERATIVEMOTORVELOCITYCONTROLLER_HPP_
#define _OKAPI_ITERATIVEMOTORVELOCITYCONTROLLER_HPP_

#include "okapi/api/control/iterative/iterativeVelocityController.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include <array>
#include <memory>

namespace okapi {
class IterativeMotorVelocityController : public IterativeVelocityController<double, double> {
  public:
  /**
   * Velocity controller that automatically writes to the motor.
   */
  IterativeMotorVelocityController(
    std::shared_ptr<AbstractMotor> imotor,
    std::shared_ptr<IterativeVelocityController<double, double>> icontroller);

  /**
   * Do one iteration of the controller.
   *
   * @param inewReading new measurement
   * @return controller output
   */
  double step(double ireading) override;

  /**
   * Sets the target for the controller.
   */
  void setTarget(double itarget) override;

  /**
   * Returns the last calculated output of the controller.
   */
  double getOutput() const override;

  /**
   * Returns the last error of the controller.
   */
  double getError() const override;

  /**
   * Returns whether the controller has settled at the target. Determining what settling means is
   * implementation-dependent.
   *
   * @return whether the controller is settled
   */
  bool isSettled() override;

  /**
   * Set time between loops in ms.
   *
   * @param isampleTime time between loops in ms
   */
  void setSampleTime(QTime isampleTime) override;

  /**
   * Set controller output bounds.
   *
   * @param imax max output
   * @param imin min output
   */
  void setOutputLimits(double imax, double imin) override;

  /**
   * Resets the controller so it can start from 0 again properly. Keeps configuration from
   * before.
   */
  void reset() override;

  /**
   * Changes whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   */
  void flipDisable() override;

  /**
   * Sets whether the controller is off or on. Turning the controller on after it was off will
   * cause the controller to move to its last set target, unless it was reset in that time.
   *
   * @param iisDisabled whether the controller is disabled
   */
  void flipDisable(bool iisDisabled) override;

  /**
   * Returns whether the controller is currently disabled.
   *
   * @return whether the controller is currently disabled
   */
  bool isDisabled() const override;

  /**
   * Get the last set sample time.
   *
   * @return sample time
   */
  QTime getSampleTime() const override;

  protected:
  std::shared_ptr<AbstractMotor> motor;
  std::shared_ptr<IterativeVelocityController<double, double>> controller;
};
} // namespace okapi

#endif
