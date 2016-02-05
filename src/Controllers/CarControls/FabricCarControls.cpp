//
// File: FabricCarControls.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 12:13 05/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "FabricCarControls.h"

#include "CarControlTouchScreenRudder.h"


using namespace Controllers;

CarControlPointer FabricCarControls::create(CarControlType type, oxygine::Actor* const gameView) {
  SIACheckRet(!gameView, CarControlPointer(nullptr));

  switch (type) {
  case CarControlType_TouchScreenRudder:
    return CarControlPointer(new CarControlTouchScreenRudder(gameView));
  }

  SIALogFatal("Incorrect car control type:%d", type);
  return CarControlPointer(nullptr);
}
