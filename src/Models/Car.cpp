//
// File: Car.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 17:31 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "Car.h"

using namespace Models;
using namespace SIA;

const double Car::sWheelTurnChange = 2.0;
const double Car::sEnginePowerChange = 0.5;

const double Car::sWheelTurnFactor = 0.002;
const double Car::sAngleSpeedFactor = 0.05;

Car::Car(const CarEquipment& equipment) {
  m_currentEnginePower = 0;
  m_currentWheelTurn = 0;
  m_wheelTurn = 0;
  m_enginePower = 0;
  setAngle(0);
  m_angleSpeed = 0;
  m_dtSum = 0;

  m_equipment = equipment;
}

void Car::setPosition(SIA::Vector2 pos) {
  m_pos = pos;
}

const SIA::Vector2& Car::position() const {
  return m_pos;
}

const SIA::Vector2& Car::speed() const {
  return m_speed;
}

void Car::setAngle(double angle) {
  m_angle = angle;
  m_dir = Vector2::sincos(m_angle);
}

double Car::angle() const {
  return m_angle;
}

void Car::setEnginePower(double enginePower) {
  m_enginePower = limit(enginePower, 1.0);
}

void Car::setWheelTurn(double wheelTurn) {
  m_wheelTurn = limit(wheelTurn, 1.0);
}

void Car::useNitro() {
}

void Car::update(double dt) {
  m_dtSum += dt;
  if (m_dtSum < 1.0e-9) {
    return;
  }
  dt = m_dtSum;
  m_dtSum = 0;

  changeValueToNeedWithDelta(m_currentEnginePower, m_enginePower, sEnginePowerChange * dt);
  changeValueToNeedWithDelta(m_currentWheelTurn, m_wheelTurn, sWheelTurnChange * dt);

  double airFriction = pow(1 - m_equipment.airFriction(), dt);
  double rotateFriction = pow(1 - m_equipment.rotateFriction(), dt);

  //pos
  m_accel = m_dir * (m_currentEnginePower * m_equipment.enginePower() / m_equipment.mass());
  m_speed += m_accel * airFriction;

  Vector2 frictionLength = m_dir * m_speed.dot(m_dir) * m_equipment.wheelLengthFriction();
  Vector2 frictionCross = -m_dir.perdendicular() * m_speed.cross(m_dir) * m_equipment.wheelCrossFriction();
  m_speed = m_speed - frictionLength - frictionCross;

  m_pos += m_speed * dt;

  //angle
  double baseAngleSpeed = m_currentWheelTurn * m_speed.length() * sWheelTurnFactor + SIGN(m_currentWheelTurn) * m_speed.dot(m_dir) * sAngleSpeedFactor;
  setAngle(m_angle + m_angleSpeed * dt);

  m_angleSpeed = baseAngleSpeed + (m_angleSpeed - baseAngleSpeed) * rotateFriction;
  m_angleSpeed -= m_angleSpeed * m_equipment.rotateFriction() * dt;
}

double Car::changeValueToNeedWithDelta(double& value, double need, double delta) {
  int sign = SIGN(need - value);
  value += sign * delta;

  if (sign != SIGN(need - value)) {
    value = need;
  }

  return value;
}