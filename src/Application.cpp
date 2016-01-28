//
// File: Application.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:00 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "Application.h"
#include "ExampleMainActor.h"
#include "TestScene.h"

using namespace oxygine;

Application::Application() {
  SIALogDebug("Application Validate State.");
  validateCurrentState();

  SIALogDebug("Application PreInit.");
  initModule();

  SIALogDebug("Application Init.");
  createMainScene();

  SIALogDebug("Application Init Success.");
}

Application::~Application() {
  SIALogDebug("Application Destruct.");
  destroyMainScene();

  SIALogDebug("Application Destruct Success.");
}

void Application::update() {
  SIALogTrace("Application update.");

  validateCurrentState();
}

void Application::initModule() {
}

void Application::validateCurrentState() {
  SIAAssert(getStage());
}

void Application::createMainScene() {
  Actor* mainActor = new TestScene();
  mainActor->setName("MAIN_ACTOR");
  getStage()->addChild(mainActor);
}

void Application::destroyMainScene() {
  Actor* mainActor = getStage()->getChildT<Actor>("MAIN_ACTOR");
  SIAAssert(nullptr != mainActor);

  mainActor->detach();
}
