//
// File: PrimitiveDraw.h
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:41 3/2/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#pragma once
#ifndef _SIA_OXYGINE_PRIMITIVE_DRAW_H__
#define _SIA_OXYGINE_PRIMITIVE_DRAW_H__

#include "Actor.h"

namespace oxygine {
class ShaderProgramGL;

DECLARE_SMART(PrimitiveDraw, spPrimitiveDraw);

class PrimitiveDraw : public Actor {
 public:
  PrimitiveDraw();

  void drawPolygon(const std::vector<Vector2>& vertices, const Color& color);
  void drawSolidPolygon(const std::vector<Vector2>& vertices, const Color& color);

  void drawCircle(const Vector2& center, double radius, size_t segments, const Color& color);
  void drawSolidCircle(const Vector2& center, double radius, size_t segments, const Color& color);

  void drawLine(const Vector2& p1, const Vector2& p2, const Color& color);

  void drawPolyLine(const std::vector<Vector2>& points, const Color& color);

  std::function<void(PrimitiveDraw&, const RenderState&)> drawCommand;

 protected:
  void doRender(const RenderState& rs) override;

  void createCircleVertices(const Vector2& center, size_t segments, double radius);
  void createPolygonVertices(const std::vector<Vector2>& vertices);

  void drawTriangles(const std::vector<Vector2>& vertices, const Color& color);
  void drawLines(const std::vector<Vector2>& vertices, const Color& color);

  std::vector<Vector2> m_verticesMemory;
  std::unique_ptr<ShaderProgramGL> m_pProgram;
};
};

#endif  // _SIA_OXYGINE_PRIMITIVE_DRAW_H__
