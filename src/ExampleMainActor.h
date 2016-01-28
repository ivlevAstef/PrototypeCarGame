//
// File: ExampleMainActor.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:05 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef EXAMPLE_MAIN_ACTOR_H_
#define EXAMPLE_MAIN_ACTOR_H_

#include "oxygine-framework.h"

class ExampleMainActor : public oxygine::Actor {
 public:
  ExampleMainActor();
  ~ExampleMainActor();

 private:
  void buttonClicked(oxygine::Event* event);
  void runSprite();

 private:
  oxygine::Resources m_resources;

  oxygine::spTextField m_text;
  oxygine::spSprite m_button;
};

#endif /* EXAMPLE_MAIN_ACTOR_H_ */
