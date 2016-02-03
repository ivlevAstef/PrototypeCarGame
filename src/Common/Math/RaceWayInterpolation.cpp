//
//  RaceWayInterpolation.cpp
//  CarGame_ios
//
//  Created by Alexander.Ivlev on 2/2/16.
//  Copyright © 2016 Mac. All rights reserved.
//

#include <float.h>
#include "RaceWayInterpolation.h"

using namespace SIA;

static const double sInterpolationMult = 10;

const size_t RaceWayInterpolation::sMinPointsCount = 3;
const SIA::Vector2 RaceWayInterpolation::sIncorrectPoint = Vector2(DBL_MIN, DBL_MIN);

RaceWayInterpolation::RaceWayInterpolation(const std::vector<WayPoint>& points) {
  SIACheckRet(points.size() < sMinPointsCount, );

  m_interpolateMult = sInterpolationMult;
  m_points = points;
  setupLength();
}

Vector2 RaceWayInterpolation::get(double len, double dWeight) const {
  SIACheckRet(len < 0 || len > m_length, sIncorrectPoint);

  const size_t count = m_points.size();

  SIAAssert(count >= sMinPointsCount);
  SIAAssert(count == m_lengths.size());

  double lengthSum = 0;
  for (size_t i = 0; i < count; i++) {
    if (lengthSum + m_lengths[i] > len) {
      double dt = (len - lengthSum) / m_lengths[i];

      return interpolate(m_points[i], m_points[(i + 1) % count], dt, dWeight);
    }

    lengthSum += m_lengths[i];
  }

  SIAAssertMsg(false, "Incorrect situation. Check function on bugs.");
  return sIncorrectPoint;
}

double RaceWayInterpolation::length() const {
  return m_length;
}

void RaceWayInterpolation::setupLength() {
  const size_t count = m_points.size();
  m_lengths.clear();
  m_lengths.resize(count);

  m_length = 0;
  for (size_t i = 0; i < count; ++i) {
    double length = calculateLength(m_points[i], m_points[(i + 1) % count]);

    m_lengths[i] = length;
    m_length += length;
  }
}

double RaceWayInterpolation::calculateLength(const WayPoint& wayP1, const WayPoint& wayP2) const {
  double length = 0;

  size_t iterations = (wayP2.pos - wayP1.pos).length() * m_interpolateMult;
  iterations = MIN(1, iterations);

  SIA::Vector2 lastPos = wayP1.pos;
  for (size_t i = 1; i <= iterations; i++) {
    double dt = double(i) / double(iterations);

    SIA::Vector2 pos = interpolate(wayP1, wayP2, dt);
    length += (pos - lastPos).length();
    lastPos = pos;
  }

  return length;
}

SIA::Vector2 RaceWayInterpolation::interpolate(const WayPoint& wayP1, const WayPoint& wayP2, double dt, double dWeight) const {
  SIA::Vector2 dir1 = wayP1.dir.normalized();
  SIA::Vector2 dir2 = wayP2.dir.normalized();

  SIA::Vector2 p1 = wayP1.pos - dir1.perdendicular() * dWeight * wayP1.weight / 2;
  SIA::Vector2 p2 = wayP2.pos - dir2.perdendicular() * dWeight * wayP2.weight / 2;
  SIA::Vector2 linear = p2 - p1;

  SIA::Vector2 p1h = p1 + dir1 * linear.dot(dir1);
  SIA::Vector2 p2h = p2 - dir2 * linear.dot(dir2);

  return bezie3Interplolate(p1, p1h, p2h, p2, dt);
}

SIA::Vector2 RaceWayInterpolation::bezie3Interplolate(const SIA::Vector2& p1, const SIA::Vector2& p1h, const SIA::Vector2& p2h, const SIA::Vector2& p2, double dt) const {
  const double A = (1 - dt) * (1 - dt) * (1 - dt);
  const double B = 3 * dt * (1 - dt) * (1 - dt);
  const double C = 3 * dt * dt * (1 - dt);
  const double D = dt * dt * dt;

  return p1 * A + p1h * B + p2h * C + p2 * D;
}