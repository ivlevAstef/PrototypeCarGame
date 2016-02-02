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

#include <vector>
#include "Common/Math/SIAVector2.h"

namespace Models {
class Map {
 public:
 private:
  std::vector<SIA::Vector2> m_mapPoints;
};
}

#endif /* _MODELS_MAP_H_ */
