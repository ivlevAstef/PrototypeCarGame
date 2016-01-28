//
// File: Application.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:00 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef SIA_CAR_GAME_APPLICATION_H_
#define SIA_CAR_GAME_APPLICATION_H_

class Application {
 public:
  Application();
  ~Application();

  void update();

 private:
  void validateCurrentState();
  void initModule();

  void createMainScene();
  void destroyMainScene();
};

#endif /* SIA_CAR_GAME_APPLICATION_H_ */
