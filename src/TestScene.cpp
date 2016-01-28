//
// File: TestScene.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 15:07 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "TestScene.h"

using namespace oxygine;

TestScene::TestScene() {
  m_resources.loadXML("res.xml");
  this->setSize(getStage()->getSize());

  this->addEventListener(TouchEvent::TOUCH_DOWN, [this](Event* e) -> void { beginTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::MOVE, [this](Event* e) -> void { moveTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::TOUCH_UP, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::OUT, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::OVER, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });

  m_enginePower = 0.0f;
  m_wheelTurn = 0.0f;

  m_car = new Sprite();
  m_car->setResAnim(m_resources.getResAnim("car"));
  m_car->setAnchor(0.5, 0.5);
  m_car->setPosition(getStage()->getSize() / 2);
  addChild(m_car);
}

TestScene::~TestScene() {
  m_resources.free();
}

void TestScene::update(const oxygine::UpdateState& us) {
  if (2 == m_touchPositions.size()) {
    std::vector<Vector2> touches;

    for (const auto& iter : m_touchPositions) {
      touches.push_back(iter.second);
    }

    bool reverse = touches[0].x < touches[1].x;
    Vector2 left = reverse ? touches[0] : touches[1];
    Vector2 right = reverse ? touches[1] : touches[0];
    setEnginePower(left, right);
    setWheelTurn(left, right);
  }

  update(us.dt / 1000.0);
}

void TestScene::setEnginePower(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  static const double backOffset = 0.15;
  double widht = getStage()->getSize().x;
  double trLeft = widht * (0.5 - backOffset) - left.x;
  double trRight = right.x - widht * (0.5 + backOffset);
  m_enginePower = (trLeft + trRight) / (2 * widht * (0.5 - backOffset));
}

void TestScene::setWheelTurn(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  double height = getStage()->getSize().y;
  double trLeft = height * 0.5 - left.y;
  double trRight = right.y - height * 0.5;

  m_wheelTurn = (trLeft + trRight) / height;
}

void TestScene::update(const double dt) {
  SIALogDebug("ENGINE POWER:%f, WHEEL TURN:%f", m_enginePower, m_wheelTurn);

  double rotation = m_car->getRotation();
  rotation += m_wheelTurn * M_PI_4 * dt * 4;

  Vector2 position = m_car->getPosition();
  position += Vector2(cos(rotation), sin(rotation)) * m_enginePower * 200 * dt;

  m_car->setRotation(rotation);
  m_car->setPosition(position);

  double enginePowerDt = SIGN(m_enginePower) * dt * 0.2;
  m_enginePower -= enginePowerDt;

  double wheelTurnDt = SIGN(m_wheelTurn) * dt * 0.2;
  m_wheelTurn -= wheelTurnDt;
}


void TestScene::beginTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions[touch->index] = touch->position;
  SIALogDebug("BEGIN TOUCH: %d", touch->index);
}
void TestScene::moveTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions[touch->index] = touch->position;
  SIALogDebug("MOVE TOUCH: %d", touch->index);
}
void TestScene::endTouch(oxygine::TouchEvent* touch) {
  SIAAssert(nullptr != touch);

  m_touchPositions.erase(touch->index);
  SIALogDebug("END TOUCH: %d", touch->index);
}