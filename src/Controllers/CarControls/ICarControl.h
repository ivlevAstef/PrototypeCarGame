//
// File: ICarControl.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 11:52 05/02/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _CONTROLLERS_CAR_CONTROL_INTERFACE_H_
#define _CONTROLLERS_CAR_CONTROL_INTERFACE_H_

#include <memory>

namespace Controllers {
class ICarControl {
 public:
  ICarControl() {
    m_enginePower = 0;
    m_wheelTurn = 0;
    m_useNitro = false;
  }

  inline double enginePower() const {
    return m_enginePower;
  }
  inline double wheelTurn() const {
    return m_wheelTurn;
  }

  inline bool useNitro() const {
    return m_useNitro;
  }

 protected:
  double m_enginePower;
  double m_wheelTurn;
  double m_useNitro;
};

typedef std::unique_ptr<ICarControl> CarControlPointer;
};

#endif /* _CONTROLLERS_CAR_CONTROL_INTERFACE_H_ */
