//
//  Application.cpp
//  CarGame_ios
//
//  Created by Alexander.Ivlev on 1/28/16.
//  Copyright © 2016 Mac. All rights reserved.
//

#include "Application.h"
#include "ExampleMainActor.h"

using namespace oxygine;

Application::Application() {
  ExampleMainActor *mainActor = new ExampleMainActor();
  mainActor->setName("MAIN_ACTOR");
  getStage()->addChild(mainActor);
}

Application::~Application() { getStage()->getChild("MAIN_ACTOR")->detach(); }

void Application::update() {}