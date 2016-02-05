//
// File: TestScene.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 15:07 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "TestScene.h"

#include "Controllers/CarControls/FabricCarControls.h"
#include "Controllers/CoordinateConverter.h"

using namespace oxygine;
using namespace Controllers;

static Models::CarEquipment carEquipment;

TestScene::TestScene()
    : m_modelCar(carEquipment) {
  m_carControl = FabricCarControls::create(FabricCarControls::CarControlType_TouchScreenRudder, this);
  SIACheckRet(!m_carControl, );

  m_resources.loadXML("res.xml");
  this->setSize(getStage()->getSize());

  m_modelCar.setPosition(toModel(getStage()->getSize() / 2));

  m_background = new Actor();
  m_background->setAnchor(0.5, 0.5);
  m_background->setPosition(getStage()->getSize() / 2);
  m_background->attachTo(this);

  m_backgroundTexture = new Sprite();
  m_backgroundTexture->setResAnim(m_resources.getResAnim("bg"));
  m_backgroundTexture->setScale(5);
  m_backgroundTexture->attachTo(m_background);

  m_viewCar = new Sprite();
  m_viewCar->setResAnim(m_resources.getResAnim("car"));
  m_viewCar->setPosition(getStage()->getSize() / 2);
  m_viewCar->setAnchor(0.8, 0.5);
  m_viewCar->attachTo(this);

  createTrack();

  update(0);
}

TestScene::~TestScene() {
  m_resources.free();
}

void TestScene::update(const oxygine::UpdateState& us) {
  SIAAssert(m_carControl);
  m_modelCar.setEnginePower(m_carControl->enginePower());
  m_modelCar.setWheelTurn(m_carControl->wheelTurn());

  update(us.dt / 1000.0);
}

void TestScene::update(const double dt) {
  m_modelCar.update(dt);

  m_viewCar->setRotation(m_modelCar.angle());
  m_background->setPosition(m_background->getSize() - toView(m_modelCar.position()));
}

void TestScene::createTrack() {
  static std::vector<Vector2> pointsCenter;
  for (double len = 0; len < m_modelMap.length(); len += 5) {
    pointsCenter.push_back(toView(m_modelMap.get(len)));
  }

  static std::vector<Vector2> pointsLeft;
  for (double len = 0; len < m_modelMap.length(); len += 5) {
    pointsLeft.push_back(toView(m_modelMap.get(len, -0.75)));
  }

  static std::vector<Vector2> pointsRight;
  for (double len = 0; len < m_modelMap.length(); len += 5) {
    pointsRight.push_back(toView(m_modelMap.get(len, 0.75)));
  }

  m_raceWay = new PrimitiveDraw();
  m_raceWay->attachTo(m_background);

  m_raceWay->drawCommand = [this](PrimitiveDraw& draw, const RenderState& rs) {
    const Color color(255, 0, 0, 255);
    const Color colorBorder(0, 0, 255, 255);

    m_raceWay->drawPolyLine(pointsCenter, color, 1);
    m_raceWay->drawPolyLine(pointsLeft, colorBorder, 3);
    m_raceWay->drawPolyLine(pointsRight, colorBorder, 3);
  };
}
