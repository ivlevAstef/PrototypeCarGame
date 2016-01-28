//
// File: Application.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:00 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "Application.h"
#include "ExampleMainActor.h"

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
  ExampleMainActor* mainActor = new ExampleMainActor();
  mainActor->setName("MAIN_ACTOR");
  getStage()->addChild(mainActor);
}

void Application::destroyMainScene() {
  ExampleMainActor* mainActor = getStage()->getChildT<ExampleMainActor>("MAIN_ACTOR");
  SIAAssert(nullptr != mainActor);

  mainActor->detach();
}
