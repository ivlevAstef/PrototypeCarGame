//
//File: SIAFinctions.h
//Description:
//Author: Ivlev Alexander. Stef
//Created: 18:32 28/1/2016
//Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_FUNCTIONS_H__
#define _SIA_FUNCTIONS_H__

#include "SIAMacros.h"

namespace {

template <typename T>
T interval(T min, T v, T max) {
  return MAX(min, MIN(v, max));
}

template <typename T>
T limit(T v, T limitV) {
  return MAX(-limitV, MIN(v, limitV));
}
};

#endif  //_SIA_FUNCTIONS_H__
