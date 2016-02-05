//
// File: TestScene.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 15:07 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef TEST_SCENE_H_
#define TEST_SCENE_H_

#include <map>
#include "Common/Oxygine/PrimitiveDraw.h"
#include "Controllers/CarControls/ICarControl.h"
#include "Models/Car.h"
#include "Models/Map.h"
#include "oxygine-framework.h"

class TestScene : public oxygine::Actor {
 public:
  TestScene();
  ~TestScene();

  void update(const oxygine::UpdateState& us) override;

 private:
  void update(const double dt);

  void createTrack();

 private:
  Controllers::CarControlPointer m_carControl;

  oxygine::Resources m_resources;
  oxygine::spSprite m_viewCar;
  oxygine::spSprite m_backgroundTexture;
  oxygine::spActor m_background;
  oxygine::spPrimitiveDraw m_raceWay;
  Models::Car m_modelCar;
  Models::Map m_modelMap;
};

#endif /* TEST_SCENE_H_ */
