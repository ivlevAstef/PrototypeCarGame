//
// File: FabricCarControls.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 12:13 05/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _CONTROLLERS_CAR_CONTROL_FABRIC_H_
#define _CONTROLLERS_CAR_CONTROL_FABRIC_H_

#include "ICarControl.h"
#include "oxygine-framework.h"

namespace Controllers {
class FabricCarControls : public ICarControl {
 public:
  enum CarControlType {
    CarControlType_TouchScreenRudder
  };

 public:
  static CarControlPointer create(CarControlType type, oxygine::Actor* const gameView);
};
};

#endif /* _CONTROLLERS_CAR_CONTROL_FABRIC_H_ */
