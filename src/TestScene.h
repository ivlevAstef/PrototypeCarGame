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
#include "Models/Car.h"
#include "oxygine-framework.h"

class TestScene : public oxygine::Actor {
 public:
  TestScene();
  ~TestScene();

  void update(const oxygine::UpdateState& us) override;

 private:
  void beginTouch(oxygine::TouchEvent* touch);
  void moveTouch(oxygine::TouchEvent* touch);
  void endTouch(oxygine::TouchEvent* touch);

  void setEnginePower(const oxygine::Vector2& left, const oxygine::Vector2& right);
  void setWheelTurn(const oxygine::Vector2& left, const oxygine::Vector2& right);

  void update(const double dt);

 private:
  std::map<oxygine::pointer_index, oxygine::Vector2> m_touchPositions;

  oxygine::Resources m_resources;
  oxygine::spSprite m_viewCar;
  oxygine::spSprite m_background;
  Models::Car m_modelCar;
};

#endif /* TEST_SCENE_H_ */
