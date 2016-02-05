//
// File: CarControlTouchScreenRudder.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 12:00 05/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "CarControlTouchScreenRudder.h"

using namespace Controllers;
using namespace oxygine;

CarControlTouchScreenRudder::CarControlTouchScreenRudder(oxygine::Actor* const gameView) {
  SIAAssertMsg(gameView, "Can't init Car control because game view is nullptr");
  setGameView(gameView);
}

void CarControlTouchScreenRudder::setGameView(oxygine::Actor* const gameView) {
  SIACheckRet(!gameView, );

  gameView->addEventListener(TouchEvent::TOUCH_DOWN, [this](Event* e) -> void { beginTouch(safeCast<TouchEvent*>(e)); });
  gameView->addEventListener(TouchEvent::MOVE, [this](Event* e) -> void { moveTouch(safeCast<TouchEvent*>(e)); });
  gameView->addEventListener(TouchEvent::TOUCH_UP, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });
}

void CarControlTouchScreenRudder::beginTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions.addTouch(touch);
  update();
}

void CarControlTouchScreenRudder::moveTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions.moveTouch(touch);
  update();
}

void CarControlTouchScreenRudder::endTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions.removeTouch(touch);
  update();
}

void CarControlTouchScreenRudder::update() {
  std::vector<Vector2> touches = m_touchPositions.touchPositions();

  if (2 == touches.size()) {
    bool reverse = touches[0].x < touches[1].x;
    Vector2 left = reverse ? touches[0] : touches[1];
    Vector2 right = reverse ? touches[1] : touches[0];

    m_enginePower = enginePowerByTouches(left, right);
    m_wheelTurn = wheelTurnByTouches(left, right);
  } else {
    m_enginePower = 0;
    m_wheelTurn = 0;
  }
}

double CarControlTouchScreenRudder::enginePowerByTouches(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  static const double backOffset = 0.15;
  double widht = getStage()->getSize().x;
  double trLeft = widht * (0.5 - backOffset) - left.x;
  double trRight = right.x - widht * (0.5 + backOffset);

  double enginePower = (trLeft + trRight) / (2 * widht * (0.5 - backOffset));
  return enginePower * 1.25;
}

double CarControlTouchScreenRudder::wheelTurnByTouches(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  double height = getStage()->getSize().y;
  double trLeft = height * 0.5 - left.y;
  double trRight = right.y - height * 0.5;

  double wheelTurn = (trLeft + trRight) / height;
  return SIGN(wheelTurn) * wheelTurn * wheelTurn;
}
