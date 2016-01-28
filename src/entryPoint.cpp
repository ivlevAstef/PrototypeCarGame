//
// File: entryPoint.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 12:55 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "DebugActor.h"
#include "Stage.h"
#include "core/oxygine.h"

#include "Application.h"

using namespace oxygine;

static bool updateScene() {
  getStage()->update();

  if (core::beginRendering()) {
    Color clearColor(32, 32, 32, 255);
    Rect viewport(Point(0, 0), core::getDisplaySize());

    getStage()->render(clearColor, viewport);
    core::swapDisplayBuffers();
  }

  bool done = core::update();
  return done;
}

static void init() {
  ObjectBase::__startTracingLeaks();

  core::init_desc desc;
  desc.title = "Oxygine Application";

#if OXYGINE_SDL
  desc.w = 960;
  desc.h = 640;
#endif

  core::init(&desc);

  Stage::instance = new Stage(true);
  Point size = core::getDisplaySize();
  getStage()->setSize(size);

  DebugActor::show();
}

static void desctruct() {
  core::release();

  ObjectBase::dumpCreatedObjects();

  ObjectBase::__stopTracingLeaks();
}

// it is application entry point
static void run() {
  init();

  Application* app = new Application();

  bool done = false;
  do {
    app->update();
    done = updateScene();
  } while (!done);

  delete app;

  desctruct();
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
extern "C" {

int main(int argc, char* argv[]) {
  run();
  return 0;
}
};
#endif
