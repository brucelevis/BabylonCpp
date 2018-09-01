﻿#ifndef BABYLON_MATERIALS_LIBRARY_MIX_MIX_VERTEX_FX_H
#define BABYLON_MATERIALS_LIBRARY_MIX_MIX_VERTEX_FX_H

namespace BABYLON {

extern const char* mixVertexShader;

const char* mixVertexShader
  = "#ifdef GL_ES\n"
    "precision highp float;\n"
    "#endif\n"
    "\n"
    "// Attributes\n"
    "attribute vec3 position;\n"
    "#ifdef NORMAL\n"
    "attribute vec3 normal;\n"
    "#endif\n"
    "#ifdef UV1\n"
    "attribute vec2 uv;\n"
    "#endif\n"
    "#ifdef UV2\n"
    "attribute vec2 uv2;\n"
    "#endif\n"
    "#ifdef VERTEXCOLOR\n"
    "attribute vec4 color;\n"
    "#endif\n"
    "\n"
    "#include<bonesDeclaration>\n"
    "\n"
    "// Uniforms\n"
    "#include<instancesDeclaration>\n"
    "\n"
    "uniform mat4 view;\n"
    "uniform mat4 viewProjection;\n"
    "\n"
    "#ifdef DIFFUSE\n"
    "varying vec2 vTextureUV;\n"
    "uniform mat4 textureMatrix;\n"
    "uniform vec2 vTextureInfos;\n"
    "#endif\n"
    "\n"
    "#ifdef POINTSIZE\n"
    "uniform float pointSize;\n"
    "#endif\n"
    "\n"
    "// Output\n"
    "varying vec3 vPositionW;\n"
    "#ifdef NORMAL\n"
    "varying vec3 vNormalW;\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "varying vec4 vColor;\n"
    "#endif\n"
    "\n"
    "#include<clipPlaneVertexDeclaration>\n"
    "#include<fogVertexDeclaration>\n"
    "#include<__decl__lightFragment>[0..maxSimultaneousLights]\n"
    "\n"
    "void main(void) {\n"
    "  #include<instancesVertex>\n"
    "  #include<bonesVertex>\n"
    "  \n"
    "  gl_Position = viewProjection * finalWorld * vec4(position, 1.0);\n"
    "\n"
    "  vec4 worldPos = finalWorld * vec4(position, 1.0);\n"
    "  vPositionW = vec3(worldPos);\n"
    "\n"
    "#ifdef NORMAL\n"
    "  vNormalW = normalize(vec3(finalWorld * vec4(normal, 0.0)));\n"
    "#endif\n"
    "\n"
    "  // Texture coordinates\n"
    "#ifndef UV1\n"
    "  vec2 uv = vec2(0., 0.);\n"
    "#endif\n"
    "#ifndef UV2\n"
    "  vec2 uv2 = vec2(0., 0.);\n"
    "#endif\n"
    "\n"
    "#ifdef DIFFUSE\n"
    "  if (vTextureInfos.x == 0.)\n"
    "  {\n"
    "  vTextureUV = vec2(textureMatrix * vec4(uv, 1.0, 0.0));\n"
    "  }\n"
    "  else\n"
    "  {\n"
    "  vTextureUV = vec2(textureMatrix * vec4(uv2, 1.0, 0.0));\n"
    "  }\n"
    "#endif\n"
    "\n"
    "  // Clip plane\n"
    "  #include<clipPlaneVertex>\n"
    "\n"
    "  // Fog\n"
    "  #include<fogVertex>\n"
    "  \n"
    "  // Shadows\n"
    "  #include<shadowsVertex>[0..maxSimultaneousLights]\n"
    "\n"
    "  // Vertex color\n"
    "#ifdef VERTEXCOLOR\n"
    "  vColor = color;\n"
    "#endif\n"
    "\n"
    "  // Point size\n"
    "#ifdef POINTSIZE\n"
    "  gl_PointSize = pointSize;\n"
    "#endif\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_LIBRARY_MIX_MIX_VERTEX_FX_H
