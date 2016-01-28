//
//  ExampleMainActor.h
//  CarGame_ios
//
//  Created by Alexander.Ivlev on 1/28/16.
//  Copyright © 2016 Mac. All rights reserved.
//

#ifndef EXAMPLE_MAIN_ACTOR_H_
#define EXAMPLE_MAIN_ACTOR_H_

#include "oxygine-framework.h"

class ExampleMainActor : public oxygine::Actor {
public:
  ExampleMainActor();
  ~ExampleMainActor();

private:
  void buttonClicked(oxygine::Event *event);
  void runSprite();

private:
  oxygine::Resources m_resources;

  oxygine::spTextField m_text;
  oxygine::spSprite m_button;
};

#endif /* EXAMPLE_MAIN_ACTOR_H_ */
