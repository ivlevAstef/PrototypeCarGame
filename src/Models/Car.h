//
// File: Car.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 17:31 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _MODELS_CAR_H_
#define _MODELS_CAR_H_

#include "CarEquipment.h"
#include "Common/Math/SIAVector2.h"

namespace Models {

class Car {
 private:
  static const double sWheelTurnChange;
  static const double sEnginePowerChange;

  static const double sAngleSpeedFactor;

 public:
  Car(const CarEquipment& equipment);

  void setPosition(SIA::Vector2 pos);
  const SIA::Vector2& position() const;

  void setAngle(double angle);
  double angle() const;

  const SIA::Vector2& speed() const;

  void setEnginePower(double enginePower);
  void setWheelTurn(double wheelTurn);

  void useNitro();

  void update(double dt);

 private:
  static double changeValueToNeedWithDelta(double& value, double need, double delta);

 private:
  SIA::Vector2 m_accel;
  SIA::Vector2 m_speed;
  SIA::Vector2 m_pos;

  SIA::Vector2 m_dir;

  double m_angle;
  double m_angleSpeed;

  double m_enginePower;
  double m_wheelTurn;

  double m_currentEnginePower;
  double m_currentWheelTurn;

  double m_dtSum;

  CarEquipment m_equipment;
};
}

#endif /* TEST_SCENE_H_ */
