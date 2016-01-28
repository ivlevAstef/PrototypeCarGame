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
    return 1250;
  }
  double enginePower() const {
    return 1;
  }

  double airFriction() const {
    return 0.001;
  }

  double airCrossFriction() const {
    return 0.05;
  }

  double wheelLengthFriction() const {
    return 0.01;
  }

  double wheelCrossFriction() const {
    return 0.25;
  }

 private:
};
};

#endif /* _MODELS_CAR_EQUIPMENT_H_ */
