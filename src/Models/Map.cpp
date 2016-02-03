//
// File: Map.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 09:37 29/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "Map.h"

using namespace Models;
using namespace SIA;

Map::Map() {
  const double weight = 100;
  const double weight2 = weight / 2;
  const double size = weight * 10;
  const std::vector<RaceWayInterpolation::WayPoint> wayPoints = {
      {Vector2(weight, weight2), Vector2(1, 0), weight},
      {Vector2(size - weight, weight2), Vector2(1, 0), weight},

      {Vector2(size - weight2, weight), Vector2(0, 1), weight},
      {Vector2(size - weight2, size - weight), Vector2(0, 1), weight},

      {Vector2(size - weight, size - weight2), Vector2(-1, 0), weight},
      {Vector2(weight, size - weight2), Vector2(-1, 0), weight},

      {Vector2(weight2, size - weight), Vector2(0, -1), weight},
      {Vector2(weight2, weight), Vector2(0, -1), weight},
  };

  m_pRaceWay = decltype(m_pRaceWay)(new RaceWayInterpolation(wayPoints));
}

SIA::Vector2 Map::get(double len, double dWeight) const {
  SIAAssert(m_pRaceWay);
  return m_pRaceWay->get(len, dWeight);
}

double Map::length() const {
  SIAAssert(m_pRaceWay);
  return m_pRaceWay->length();
}