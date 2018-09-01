﻿#ifndef BABYLON_MATERIALS_LIBRARY_GRADIENT_GRADIENT_FRAGMENT_FX_H
#define BABYLON_MATERIALS_LIBRARY_GRADIENT_GRADIENT_FRAGMENT_FX_H

namespace BABYLON {

extern const char* gradientPixelShader;

const char* gradientPixelShader
  = "#ifdef GL_ES\n"
    "precision highp float;\n"
    "#endif\n"
    "\n"
    "// Constants\n"
    "uniform vec3 vEyePosition;\n"
    "uniform vec4 vDiffuseColor;\n"
    "\n"
    "// Gradient variables\n"
    "uniform vec4 topColor;\n"
    "uniform vec4 bottomColor;\n"
    "uniform float offset;\n"
    "uniform float scale;\n"
    "uniform float smoothness;\n"
    "\n"
    "// Input\n"
    "varying vec3 vPositionW;\n"
    "varying vec3 vPosition;\n"
    "\n"
    "#ifdef NORMAL\n"
    "varying vec3 vNormalW;\n"
    "#endif\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "varying vec4 vColor;\n"
    "#endif\n"
    "\n"
    "// Helper functions\n"
    "#include<helperFunctions>\n"
    "\n"
    "// Lights\n"
    "#include<__decl__lightFragment>[0]\n"
    "#include<__decl__lightFragment>[1]\n"
    "#include<__decl__lightFragment>[2]\n"
    "#include<__decl__lightFragment>[3]\n"
    "\n"
    "\n"
    "#include<lightsFragmentFunctions>\n"
    "#include<shadowsFragmentFunctions>\n"
    "\n"
    "// Samplers\n"
    "#ifdef DIFFUSE\n"
    "varying vec2 vDiffuseUV;\n"
    "uniform sampler2D diffuseSampler;\n"
    "uniform vec2 vDiffuseInfos;\n"
    "#endif\n"
    "\n"
    "#include<clipPlaneFragmentDeclaration>\n"
    "\n"
    "// Fog\n"
    "#include<fogFragmentDeclaration>\n"
    "\n"
    "void main(void) {\n"
    "#include<clipPlaneFragment>\n"
    "\n"
    "  vec3 viewDirectionW = normalize(vEyePosition - vPositionW);\n"
    "\n"
    "  float h = vPosition.y * scale + offset;\n"
    "  float mysmoothness = clamp(smoothness, 0.01, max(smoothness, 10.));\n"
    "\n"
    "  vec4 baseColor = mix(bottomColor, topColor, max(pow(max(h, 0.0), mysmoothness), 0.0));\n"
    "\n"
    "  // Base color\n"
    "  vec3 diffuseColor = baseColor.rgb;\n"
    "\n"
    "  // Alpha\n"
    "  float alpha = baseColor.a;\n"
    "\n"
    "\n"
    "#ifdef ALPHATEST\n"
    "  if (baseColor.a < 0.4)\n"
    "  discard;\n"
    "#endif\n"
    "\n"
    "#include<depthPrePass>\n"
    "\n"
    "#ifdef VERTEXCOLOR\n"
    "  baseColor.rgb *= vColor.rgb;\n"
    "#endif\n"
    "\n"
    "  // Bump\n"
    "#ifdef NORMAL\n"
    "  vec3 normalW = normalize(vNormalW);\n"
    "#else\n"
    "  vec3 normalW = vec3(1.0, 1.0, 1.0);\n"
    "#endif\n"
    "\n"
    "  // Lighting\n"
    "  vec3 diffuseBase = vec3(0., 0., 0.);\n"
    "  lightingInfo info;\n"
    "  float shadow = 1.;\n"
    "  float glossiness = 0.;\n"
    "  \n"
    "#include<lightFragment>[0]\n"
    "#include<lightFragment>[1]\n"
    "#include<lightFragment>[2]\n"
    "#include<lightFragment>[3]\n"
    "\n"
    "#ifdef VERTEXALPHA\n"
    "  alpha *= vColor.a;\n"
    "#endif\n"
    "\n"
    "  vec3 finalDiffuse = clamp(diffuseBase * diffuseColor, 0.0, 1.0) * baseColor.rgb;\n"
    "\n"
    "  // Composition\n"
    "  vec4 color = vec4(finalDiffuse, alpha);\n"
    "\n"
    "#include<fogFragment>\n"
    "\n"
    "  gl_FragColor = color;\n"
    "}\n";

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_LIBRARY_GRADIENT_GRADIENT_FRAGMENT_FX_H
