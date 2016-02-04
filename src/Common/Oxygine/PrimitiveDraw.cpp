//
// File: PrimitiveDraw.cpp
// Description:
// Author: Ivlev Alexander. Stef
// Created: 13:41 3/2/2016
// Copyright (c) SIA 2016. All Right Reserved.
//

#include "PrimitiveDraw.h"

#include "Material.h"
#include "RenderState.h"
#include "STDMaterial.h"
#include "core/VideoDriver.h"
#include "core/gl/ShaderProgramGL.h"
#include "core/gl/VideoDriverGLES20.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846 /* pi */
#endif

using namespace oxygine;

PrimitiveDraw::PrimitiveDraw() {
  const char* vertexShaderData =
      "\
									uniform mediump mat4 projection;\
									attribute vec2 a_position;\
									void main() {\
									vec4 position = vec4(a_position, 0.0, 1.0);\
									gl_Position = projection * position;\
									}\
									";

  const char* fragmentShaderData =
      "\
									  uniform mediump vec4 color;\
									  void main() { \
									  gl_FragColor = color; \
									  } \
									  ";

  m_pProgram = decltype(m_pProgram)(new ShaderProgramGL());

  int vs = ShaderProgramGL::createShader(GL_VERTEX_SHADER, vertexShaderData, 0, 0);
  int fs = ShaderProgramGL::createShader(GL_FRAGMENT_SHADER, fragmentShaderData, 0, 0);

  int pr = ShaderProgramGL::createProgram(vs, fs, (VertexDeclarationGL*)IVideoDriver::instance->getVertexDeclaration(VERTEX_POSITION));
  m_pProgram->init(pr);
}

void PrimitiveDraw::doRender(const RenderState& rs) {
  SIACheckRet(!drawCommand, );

  SIAAssert(m_pProgram);

  Material::setCurrent(0);

  IVideoDriver* driver = IVideoDriver::instance;

  driver->setShaderProgram(m_pProgram.get());

  Matrix m = Matrix(rs.transform) * STDMaterial::instance->getRenderer()->getViewProjection();
  driver->setUniform("projection", &m);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  drawCommand(*this, rs);
}

void PrimitiveDraw::drawSolidPolygon(const std::vector<Vector2>& vertices, const Color& color) {
  drawTriangles(vertices, color);
}

void PrimitiveDraw::drawCircle(const Vector2& center, double radius, size_t segments, const Color& color, double lineWidth) {
  createCircleVertices(center, radius, segments);
  drawLines(m_verticesMemory, color, lineWidth);
}

void PrimitiveDraw::drawSolidCircle(const Vector2& center, double radius, size_t segments, const Color& color) {
  createCircleVertices(center, radius, segments);
  drawTriangles(m_verticesMemory, color);
}

void PrimitiveDraw::drawLine(const Vector2& p1, const Vector2& p2, const Color& color, double lineWidth) {
  m_verticesMemory.resize(2);
  m_verticesMemory[0] = p1;
  m_verticesMemory[1] = p2;
  drawLines(m_verticesMemory, color, lineWidth);
}

void PrimitiveDraw::drawPolyLine(const std::vector<Vector2>& points, const Color& color, double lineWidth) {
  drawLines(points, color, lineWidth);
}

void PrimitiveDraw::createCircleVertices(const Vector2& center, size_t segments, double radius) {
  m_verticesMemory.resize(segments);
  const double k_increment = 2.0f * M_PI / segments;
  double theta = 0.0f;

  for (size_t i = 0; i < segments; ++i) {
    m_verticesMemory[i] = center + Vector2(cos(theta), sin(theta)) * radius;
    theta += k_increment;
  }
}

//------------------------------------------------------------------------
void PrimitiveDraw::drawTriangles(const std::vector<Vector2>& vertices, const Color& color) {
  oxglEnableVertexAttribArray(0);
  oxglVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat*)&vertices[0].x);

  Vector4 c(color.r, color.g, color.b, color.a);
  IVideoDriver::instance->setUniform("color", &c, 1);
  glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

  oxglDisableVertexAttribArray(0);
}

void PrimitiveDraw::drawLines(const std::vector<Vector2>& vertices, const Color& color, double lineWidth) {
  glLineWidth(lineWidth);
  oxglEnableVertexAttribArray(0);
  oxglVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat*)&vertices[0].x);

  Vector4 c(color.r, color.g, color.b, color.a);
  IVideoDriver::instance->setUniform("color", &c, 1);
  glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

  oxglDisableVertexAttribArray(0);
  glLineWidth(1);
}
