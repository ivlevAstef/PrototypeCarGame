//
// File: TestScene.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 15:07 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//


#include "TestScene.h"

using namespace oxygine;

static Models::CarEquipment carEquipment;

TestScene::TestScene()
    : m_modelCar(carEquipment) {
  m_resources.loadXML("res.xml");
  this->setSize(getStage()->getSize());

  this->addEventListener(TouchEvent::TOUCH_DOWN, [this](Event* e) -> void { beginTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::MOVE, [this](Event* e) -> void { moveTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::TOUCH_UP, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::OUT, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });
  this->addEventListener(TouchEvent::OVER, [this](Event* e) -> void { endTouch(safeCast<TouchEvent*>(e)); });

  auto windowCenter = getStage()->getSize() / 2;

  m_modelCar.setPosition(SIA::Vector2(windowCenter.x, windowCenter.y));

  m_viewCar = new Sprite();
  m_viewCar->setResAnim(m_resources.getResAnim("car"));
  m_viewCar->setAnchor(0.5, 0.5);
  m_viewCar->setPosition(windowCenter);
  addChild(m_viewCar);
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
  } else {
    m_modelCar.setEnginePower(0);
    m_modelCar.setWheelTurn(0);
  }

  update(us.dt / 1000.0);
}

void TestScene::setEnginePower(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  static const double backOffset = 0.15;
  double widht = getStage()->getSize().x;
  double trLeft = widht * (0.5 - backOffset) - left.x;
  double trRight = right.x - widht * (0.5 + backOffset);
  m_modelCar.setEnginePower((trLeft + trRight) / (2 * widht * (0.5 - backOffset)));
}

void TestScene::setWheelTurn(const oxygine::Vector2& left, const oxygine::Vector2& right) {
  double height = getStage()->getSize().y;
  double trLeft = height * 0.5 - left.y;
  double trRight = right.y - height * 0.5;

  m_modelCar.setWheelTurn((trLeft + trRight) / height);
}

void TestScene::update(const double dt) {
  m_modelCar.update(dt);

  m_viewCar->setRotation(m_modelCar.angle());
  auto pos = m_modelCar.position();
  m_viewCar->setPosition(Vector2(pos.x, pos.y));
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