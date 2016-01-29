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

  m_data.resize(MAX(m_data.size(), touch->index));

  m_data[touch->index - 1] = touch->position;
}

void UniqueTouchPositions::moveTouch(oxygine::TouchEvent* touch) {
  SIACheckRet(nullptr == touch || touch->index < 1, );

  if (m_data.size() < touch->index) {
    SIALogError("Incorrect touch data. Something went wrong.");
    return;
  }

  m_data[touch->index - 1] = touch->position;
}

void UniqueTouchPositions::removeTouch(oxygine::TouchEvent* touch) {
  SIACheckRet(nullptr == touch || touch->index < 1, );

  if (m_data.size() < touch->index) {
    SIALogError("Incorrect touch data. Something went wrong.");
    return;
  }

  m_data[touch->index - 1] = sIncorrectTouch;
  trim();
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

void UniqueTouchPositions::trim() {
  size_t firstCorrect = 0;
  size_t lastCorrect = 0;

  for (size_t i = 0; i < m_data.size(); i++) {
    if (sIncorrectTouch == m_data[i]) {
      firstCorrect += (i == firstCorrect) ? 1 : 0;
    } else {
      lastCorrect = i;
    }
  }

  m_data.erase(m_data.begin(), m_data.begin() + firstCorrect);
  m_data.erase(m_data.begin() + lastCorrect, m_data.end());
}
