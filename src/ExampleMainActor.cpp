//
// File: ExampleMainActor.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:05 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include <functional>
#include "ExampleMainActor.h"

using namespace oxygine;

ExampleMainActor::ExampleMainActor() {
  m_resources.loadXML("res.xml");

  spSprite button = new Sprite();
  button->setResAnim(m_resources.getResAnim("button"));

  // centered button at screen
  Vector2 pos = getStage()->getSize() / 2 - button->getSize() / 2;
  button->setPosition(pos);

  button->addEventListener(TouchEvent::CLICK,
                           [this](Event* e) -> void { buttonClicked(e); });

  // attach button as child to current actor
  addChild(button);

  m_button = button;

  // second part

  // create TextField Actor
  spTextField text = new TextField();
  // attach it as child to button
  text->attachTo(button);
  // centered in button
  text->setPosition(button->getSize() / 2);

  // initialize text style
  TextStyle style;
  style.font = m_resources.getResFont("main")->getFont();
  style.color = Color::White;
  style.vAlign = TextStyle::VALIGN_MIDDLE;
  style.hAlign = TextStyle::HALIGN_CENTER;

  text->setStyle(style);
  text->setText("Click\nMe!");

  m_text = text;
}

ExampleMainActor::~ExampleMainActor() {
  m_resources.free();
}

void ExampleMainActor::buttonClicked(Event* event) {
  // user clicked to button

  // animate button by chaning color
  m_button->setColor(Color::White);
  m_button->addTween(Sprite::TweenColor(Color::Green), 500, 1, true);

  // animate text by scaling
  m_text->setScale(1.0f);
  m_text->addTween(Actor::TweenScale(1.1f), 500, 1, true);

  // and change text
  m_text->setText("Clicked!");

  // lets create and run sprite with simple animation
  runSprite();
}

void ExampleMainActor::runSprite() {
  spSprite sprite = new Sprite();
  addChild(sprite);

  int duration = 500;  // 500 ms
  int loops = -1;      // infinity loops

  // animation has 7 columns, check 'res.xml'
  ResAnim* animation = m_resources.getResAnim("anim");

  // add animation tween to sprite
  // TweenAnim would change animation frames
  sprite->addTween(Sprite::TweenAnim(animation), duration, loops);

  Vector2 destPos = getStage()->getSize() - sprite->getSize();
  Vector2 srcPos = Vector2(0, destPos.y);
  // set sprite initial position
  sprite->setPosition(srcPos);

  // add another tween: TweenQueue
  // TweenQueue is a collection of tweens
  spTweenQueue tweenQueue = new TweenQueue();
  tweenQueue->setDelay(1500);
  // first, move sprite to dest position
  tweenQueue->add(Sprite::TweenPosition(destPos), 15000, 1);
  // then fade it out smoothly
  tweenQueue->add(Sprite::TweenAlpha(0), 500, 1);

  sprite->addTween(tweenQueue);

  // and remove sprite from tree when tweenQueue is empty
  // if you don't hold any references to sprite it would be deleted
  // automatically
  tweenQueue->setDetachActor(true);
}
