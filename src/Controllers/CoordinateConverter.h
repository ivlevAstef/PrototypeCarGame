//
//File: CoordinateConverter.h
//Description:
//Author: Ivlev Alexander. Stef
//Created: 18:32 28/1/2016
//Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _CONTROLLERS_COORDINATE_CONVERTER_H__
#define _CONTROLLERS_COORDINATE_CONVERTER_H__

#include "Common/Math/SIAVector2.h"
#include "oxygine-framework.h"

namespace Controllers {

#define MULT 5
oxygine::Vector2 toView(const SIA::Vector2& pos) {
  return oxygine::Vector2(pos.x * MULT, pos.y * MULT);
}

SIA::Vector2 toModel(const oxygine::Vector2& pos) {
  return SIA::Vector2(pos.x / MULT, pos.y / MULT);
}
};

#endif  //_CONTROLLERS_COORDINATE_CONVERTER_H__
