﻿#ifndef BABYLON_SHADERS_SHADERS_INCLUDE_BUMP_FRAGMENT_FX_H
#define BABYLON_SHADERS_SHADERS_INCLUDE_BUMP_FRAGMENT_FX_H

namespace BABYLON {

extern const char* bumpFragment;

const char* bumpFragment
  = "vec2 uvOffset = vec2(0.0, 0.0);\n"
    "\n"
    "#if defined(BUMP) || defined(PARALLAX)\n"
    "  #ifdef NORMALXYSCALE\n"
    "  float normalScale = 1.0;\n"
    "  #else    \n"
    "  float normalScale = vBumpInfos.y;\n"
    "  #endif\n"
    "\n"
    "  #if defined(TANGENT) && defined(NORMAL)\n"
    "  mat3 TBN = vTBN;\n"
    "  #else\n"
    "  mat3 TBN = cotangent_frame(normalW * normalScale, vPositionW, vBumpUV);\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "#ifdef PARALLAX\n"
    "  mat3 invTBN = transposeMat3(TBN);\n"
    "\n"
    "  #ifdef PARALLAXOCCLUSION\n"
    "  uvOffset = parallaxOcclusion(invTBN * -viewDirectionW, invTBN * normalW, vBumpUV, vBumpInfos.z);\n"
    "  #else\n"
    "  uvOffset = parallaxOffset(invTBN * viewDirectionW, vBumpInfos.z);\n"
    "  #endif\n"
    "#endif\n"
    "\n"
    "#ifdef BUMP\n"
    "#ifdef OBJECTSPACE_NORMALMAP\n"
    "  normalW = normalize(texture2D(bumpSampler, vBumpUV).xyz  * 2.0 - 1.0);\n"
    "  normalW = normalize(mat3(normalMatrix) * normalW);  \n"
    "#else\n"
    "  normalW = perturbNormal(TBN, vBumpUV + uvOffset);\n"
    "#endif\n"
    "#endif\n";

} // end of namespace BABYLON

#endif // end of BABYLON_SHADERS_SHADERS_INCLUDE_BUMP_FRAGMENT_FX_H
