//
// File: SIALogger.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 21:21 16/7/2015
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_LOGGER_H__
#define _SIA_LOGGER_H__

/// Fatal - log and exit. (use only if can't be corrected data)
/// Error - log and if enable debug then exit. (use if can't be corrected data
/// but the application can run)
/// Warning - log. (use if can be correct data, but they should not be
/// сorrectly)
/// Debug - if enable debug then log. (use for log important code/event)
/// Info - if enable debug then log. (use for log not often code/event)
/// Trace - if enable debug and trace then log. (use for unimportant code/event)

/// Assert - if conditional then equivalent error, else not log.
/// Check - if conditional then log.

// fatal,error,warning, check worked always.
// enable debug,info,assert level, also error stoped program.
#define ENABLE_DEBUG
// enable trace level
//#define ENABLE_TRACE

namespace SIA {
extern void logToStream(const char* logLevel, const char* file, int line, const char* module, const char* message, ...);
};

/// SIASetModuleName
template <typename T>
static T SIADefaultModuleName() {
  static T value = nullptr;
  return value;
}

#define SIASetModuleName(NAME)                             \
  template <>                                              \
  static const char* SIADefaultModuleName<const char*>() { \
    static const char* value = #NAME;                      \
    return value;                                          \
  }

#include "SIACheckMacros.h"
#include "SIALogMacros.h"

#endif  // _SIA_LOGGER_H__
