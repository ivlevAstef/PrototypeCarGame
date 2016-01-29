//
// File: CarEquipment.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 18:57 28/01/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _MODELS_CAR_EQUIPMENT_H_
#define _MODELS_CAR_EQUIPMENT_H_

namespace Models {
class CarEquipment {
 public:
  double mass() const {
    return 1250;  //kg
  }

  double enginePower() const {
    return 250;  //hp - horse power
  }

  double airFriction() const {
    return 0.001;
  }

  double rotateFriction() const {
    return 0.35;
  }

  double wheelLengthFriction() const {
    return 0.001;
  }

  double wheelCrossFriction() const {
    return 0.05;
  }

 private:
};
};

#endif /* _MODELS_CAR_EQUIPMENT_H_ */
