//
// File: SIACheckMacros.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 21:22 16/7/2015
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_CHECK_MACROS_H__
#define _SIA_CHECK_MACROS_H__

/// SIAAssertMsg
/// SIAAssert

/// SIACheck
/// SIACheckRet

#ifdef ENABLE_DEBUG
#define SIAAssertMsg(CONDITION, MSG, ...)                      \
  if (!(CONDITION)) {                                          \
    SIA::logToStream("Assert", SIALogMsg(MSG, ##__VA_ARGS__)); \
    exit(EXIT_FAILURE);                                        \
  }

#define SIAAssert(CONDITION) \
  { SIAAssertMsg(CONDITION, #CONDITION " failed."); }

#else
#define SIAAssertMsg(CONDITION, MSG, ...) \
  {}
#define SIAAssert(CONDITION) \
  {}
#endif

#define SIACheck(CONDITION)                                      \
  if (CONDITION) {                                               \
    SIA::logToStream("Check", SIALogMsg(#CONDITION " failed.")); \
  }

#define SIACheckRet(CONDITION, RET_VALUE)                        \
  if (CONDITION) {                                               \
    SIA::logToStream("Check", SIALogMsg(#CONDITION " failed.")); \
    return RET_VALUE;                                            \
  }

#endif /* _SIA_CHECK_MACROS_H__ */
