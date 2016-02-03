//
// File: Map.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 09:37 29/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _MODELS_MAP_H_
#define _MODELS_MAP_H_

#include <memory>
#include "Common/Math/RaceWayInterpolation.h"

namespace Models {
class Map {
 public:
  Map();
  
  ///dWeight [-1, 1]
  SIA::Vector2 get(double len, double dWeight = 0) const;
  
  double length() const;
  
 private:
  std::unique_ptr<SIA::RaceWayInterpolation>  m_pRaceWay;
};
}

#endif /* _MODELS_MAP_H_ */
