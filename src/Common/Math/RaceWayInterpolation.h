//
// File: RaceWayInterpolation.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 14:51 02/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_RACE_WAY_INERPOLATION_H_
#define _SIA_RACE_WAY_INERPOLATION_H_

#include <vector>
#include "SIAVector2.h"

namespace SIA {
class RaceWayInterpolation {
 public:
  static const size_t sMinPointsCount;
  static const SIA::Vector2 sIncorrectPoint;

  struct WayPoint {
    SIA::Vector2 pos;
    SIA::Vector2 dir;
    double weight;
    double bezieFactor;
  };

 public:
  RaceWayInterpolation(const std::vector<WayPoint>& points);

  ///dWeight [-1, 1]
  SIA::Vector2 get(double len, double dWeight = 0) const;

  double length() const;

 private:
  void setupLength();

  double calculateLength(const WayPoint& wayP1, const WayPoint& wayP2) const;
  SIA::Vector2 interpolate(const WayPoint& p1, const WayPoint& p2, double dt, double dWeight = 0) const;
  SIA::Vector2 bezie3Interplolate(const SIA::Vector2& p1, const SIA::Vector2& p1h, const SIA::Vector2& p2h, const SIA::Vector2& p2, double dt) const;

 private:
  double m_interpolateMult;

  std::vector<WayPoint> m_points;
  std::vector<double> m_lengths;
  double m_length;
};
}

#endif /* _SIA_RACE_WAY_INERPOLATION_H_ */
