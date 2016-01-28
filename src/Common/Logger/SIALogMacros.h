//
// File: SIALogMacros.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 21:22 16/7/2015
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_LOG_MACROS_H__
#define _SIA_LOG_MACROS_H__

/// SIALogFatal
/// SIALogError
/// SIALogWarning
/// SIALogDebug
/// SIALogInfo
/// SIALogTrace

#define SIALogMsg(MSG, ...) __FILE__, __LINE__, SIADefaultModuleName<const char*>(), MSG, ##__VA_ARGS__

#define SIALogFatal(MSG, ...)                                 \
  {                                                           \
    SIA::logToStream("Fatal", SIALogMsg(MSG, ##__VA_ARGS__)); \
    exit(EXIT_FAILURE);                                       \
  }

#ifdef ENABLE_DEBUG
#define SIALogError(MSG, ...)                                 \
  {                                                           \
    SIA::logToStream("Error", SIALogMsg(MSG, ##__VA_ARGS__)); \
    exit(EXIT_FAILURE);                                       \
  }
#else
#define SIALogError(MSG, ...) \
  { SIA::logToStream("Error", SIALogMsg(MSG, ##__VA_ARGS__)); }
#endif

#define SIALogWarning(MSG, ...) \
  { SIA::logToStream("Warning", SIALogMsg(MSG, ##__VA_ARGS__)); }

#ifdef ENABLE_DEBUG
#define SIALogDebug(MSG, ...) \
  { SIA::logToStream("Debug", SIALogMsg(MSG, ##__VA_ARGS__)); }
#define SIALogInfo(MSG, ...) \
  { SIA::logToStream("Info", SIALogMsg(MSG, ##__VA_ARGS__)); }

#ifdef ENABLE_TRACE
#define SIALogTrace(MSG, ...) \
  { SIA::logToStream("Trace", SIALogMsg(MSG, ##__VA_ARGS__)); }
#else
#define SIALogTrace(MSG, ...) \
  {}
#endif

#else
#define SIALogDebug(MSG, ...) \
  {}
#define SIALogInfo(MSG, ...) \
  {}
#endif

#endif /* _SIA_LOG_MACROS_H__ */
