//
//File: UniqueTouchPositions.cpp
//Description:
//Author: Ivlev Alexander. Stef
//Created: 16:27 29/1/2016
//Copyright (c) SIA 2016. All Right Reserved.
//

#include "UniqueTouchPositions.h"

using namespace oxygine;

Vector2 UniqueTouchPositions::sIncorrectTouch = Vector2(-1, -1);

void UniqueTouchPositions::addTouch(oxygine::TouchEvent* touch) {
  SIACheckRet(nullptr == touch || touch->index < 1, );

  m_data.resize(MAX(m_data.size(), touch->index), sIncorrectTouch);

  m_data[touch->index - 1] = touch->localPosition;
  SIALogInfo("Add Touch with index:%d", touch->index);
}

void UniqueTouchPositions::moveTouch(oxygine::TouchEvent* touch) {
  SIACheckRet(nullptr == touch || touch->index < 1, );

  if (m_data.size() < touch->index) {
    SIALogError("Incorrect touch data (Touch index:%d). Something went wrong.", touch->index);
    return;
  }

  m_data[touch->index - 1] = touch->localPosition;

  SIALogTrace("Move Touch with index:%d", touch->index);
}

void UniqueTouchPositions::removeTouch(oxygine::TouchEvent* touch) {
  SIACheckRet(nullptr == touch || touch->index < 1, );

  if (m_data.size() < touch->index || sIncorrectTouch == m_data[touch->index - 1]) {
    SIALogError("Incorrect touch data. Something went wrong.");
    return;
  }

  m_data[touch->index - 1] = sIncorrectTouch;

  SIALogInfo("Remove Touch with index:%d", touch->index);
}

std::vector<oxygine::Vector2> UniqueTouchPositions::touchPositions() {
  std::vector<oxygine::Vector2> result;
  for (const auto& pos : m_data) {
    if (pos != sIncorrectTouch) {
      result.push_back(pos);
    }
  }

  return result;
}
