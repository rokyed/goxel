/* Goxel 3D voxels editor
 *
 * copyright (c) 2018 Guillaume Chereau <guillaume@noctua-software.com>
 *
 * Goxel is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.

 * Goxel is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * goxel.  If not, see <http://www.gnu.org/licenses/>.
 */

/* This file is autogenerated by tools/create_assets.py */

{.path = "data/shaders/background.glsl", .size = 570, .data =
    "varying lowp vec4 v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "attribute highp vec3 a_pos;\n"
    "attribute lowp  vec4 a_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(a_pos, 1.0);\n"
    "    v_color = a_color;\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color;\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    ""
},
{.path = "data/shaders/model3d.glsl", .size = 2766, .data =
    "#if defined(GL_ES) && defined(FRAGMENT_SHADER)\n"
    "#extension GL_OES_standard_derivatives : enable\n"
    "#endif\n"
    "\n"
    "uniform highp   mat4  u_model;\n"
    "uniform highp   mat4  u_view;\n"
    "uniform highp   mat4  u_proj;\n"
    "uniform highp   mat4  u_clip;\n"
    "uniform lowp    vec4  u_color;\n"
    "uniform mediump vec2  u_uv_scale;\n"
    "uniform lowp    float u_grid_alpha;\n"
    "uniform mediump vec3  u_l_dir;\n"
    "uniform mediump float u_l_diff;\n"
    "uniform mediump float u_l_emit;\n"
    "\n"
    "uniform mediump sampler2D u_tex;\n"
    "uniform mediump float     u_strip;\n"
    "uniform mediump float     u_time;\n"
    "\n"
    "varying mediump vec3 v_normal;\n"
    "varying highp   vec3 v_pos;\n"
    "varying lowp    vec4 v_color;\n"
    "varying mediump vec2 v_uv;\n"
    "varying mediump vec4 v_clip_pos;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "attribute highp   vec3  a_pos;\n"
    "attribute lowp    vec4  a_color;\n"
    "attribute mediump vec3  a_normal;\n"
    "attribute mediump vec2  a_uv;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    lowp vec4 col = u_color * a_color;\n"
    "    highp vec3 pos = (u_view * u_model * vec4(a_pos, 1.0)).xyz;\n"
    "    if (u_clip[3][3] > 0.0)\n"
    "        v_clip_pos = u_clip * u_model * vec4(a_pos, 1.0);\n"
    "    gl_Position = u_proj * vec4(pos, 1.0);\n"
    "    mediump float diff = max(0.0, dot(u_l_dir, a_normal));\n"
    "    col.rgb *= (u_l_emit + u_l_diff * diff);\n"
    "    v_color = col;\n"
    "    v_uv = a_uv * u_uv_scale;\n"
    "    v_pos = (u_model * vec4(a_pos, 1.0)).xyz;\n"
    "    v_normal = a_normal;\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color * texture2D(u_tex, v_uv);\n"
    "    if (u_strip > 0.0) {\n"
    "       mediump float p = gl_FragCoord.x + gl_FragCoord.y + u_time * 4.0;\n"
    "       if (mod(p, 8.0) < 4.0) gl_FragColor.rgb *= 0.5;\n"
    "    }\n"
    "    if (u_clip[3][3] > 0.0) {\n"
    "        if (    v_clip_pos[0] < -v_clip_pos[3] ||\n"
    "                v_clip_pos[1] < -v_clip_pos[3] ||\n"
    "                v_clip_pos[2] < -v_clip_pos[3] ||\n"
    "                v_clip_pos[0] > +v_clip_pos[3] ||\n"
    "                v_clip_pos[1] > +v_clip_pos[3] ||\n"
    "                v_clip_pos[2] > +v_clip_pos[3]) discard;\n"
    "    }\n"
    "\n"
    "    // Grid effect.\n"
    "#if !defined(GL_ES) || defined(GL_OES_standard_derivatives)\n"
    "    if (u_grid_alpha > 0.0) {\n"
    "        mediump vec2 c;\n"
    "        if (abs((u_model * vec4(v_normal, 0.0)).x) > 0.5) c = v_pos.yz;\n"
    "        if (abs((u_model * vec4(v_normal, 0.0)).y) > 0.5) c = v_pos.zx;\n"
    "        if (abs((u_model * vec4(v_normal, 0.0)).z) > 0.5) c = v_pos.xy;\n"
    "        mediump vec2 grid = abs(fract(c - 0.5) - 0.5) / fwidth(c);\n"
    "        mediump float line = min(grid.x, grid.y);\n"
    "        gl_FragColor.rgb *= mix(1.0 - u_grid_alpha, 1.0, min(line, 1.0));\n"
    "    }\n"
    "#endif\n"
    "\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    ""
},
{.path = "data/shaders/pos_data.glsl", .size = 788, .data =
    "varying lowp  vec2 v_pos_data;\n"
    "uniform highp mat4 u_model;\n"
    "uniform highp mat4 u_view;\n"
    "uniform highp mat4 u_proj;\n"
    "uniform lowp  vec2 u_tile_id;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "attribute highp vec3 a_pos;\n"
    "attribute lowp  vec2 a_pos_data;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    highp vec3 pos = a_pos;\n"
    "    gl_Position = u_proj * u_view * u_model * vec4(pos, 1.0);\n"
    "    v_pos_data = a_pos_data;\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor.rg = u_tile_id;\n"
    "    gl_FragColor.ba = v_pos_data;\n"
    "}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    ""
},
{.path = "data/shaders/shadow_map.glsl", .size = 639, .data =
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "attribute highp   vec3  a_pos;\n"
    "uniform   highp   mat4  u_model;\n"
    "uniform   highp   mat4  u_view;\n"
    "uniform   highp   mat4  u_proj;\n"
    "uniform   mediump float u_pos_scale;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = u_proj * u_view * u_model * vec4(a_pos * u_pos_scale, 1.0);\n"
    "}\n"
    "\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "void main() {}\n"
    "/************************************************************************/\n"
    "\n"
    "#endif\n"
    ""
},
{.path = "data/shaders/volume.glsl", .size = 8877, .data =
    "/* Goxel 3D voxels editor\n"
    " *\n"
    " * copyright (c) 2015 Guillaume Chereau <guillaume@noctua-software.com>\n"
    " *\n"
    " * Goxel is free software: you can redistribute it and/or modify it under the\n"
    " * terms of the GNU General Public License as published by the Free Software\n"
    " * Foundation, either version 3 of the License, or (at your option) any later\n"
    " * version.\n"
    "\n"
    " * Goxel is distributed in the hope that it will be useful, but WITHOUT ANY\n"
    " * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS\n"
    " * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more\n"
    " * details.\n"
    "\n"
    " * You should have received a copy of the GNU General Public License along with\n"
    " * goxel.  If not, see <http://www.gnu.org/licenses/>.\n"
    " */\n"
    "\n"
    "// Some of the algos come from glTF Sampler, under Apache Licence V2.\n"
    "\n"
    "uniform highp mat4  u_model;\n"
    "uniform highp mat4  u_view;\n"
    "uniform highp mat4  u_proj;\n"
    "uniform lowp  float u_pos_scale;\n"
    "uniform highp vec3  u_camera;\n"
    "uniform highp float u_z_ofs; // Used for line rendering.\n"
    "\n"
    "// Light parameters\n"
    "uniform lowp    vec3  u_l_dir;\n"
    "uniform lowp    float u_l_int;\n"
    "uniform lowp    float u_l_amb; // Ambient light coef.\n"
    "\n"
    "// Material parameters\n"
    "uniform lowp float u_m_metallic;\n"
    "uniform lowp float u_m_roughness;\n"
    "uniform lowp float u_m_smoothness;\n"
    "uniform lowp vec4  u_m_base_color;\n"
    "uniform lowp vec3  u_m_emissive_factor;\n"
    "\n"
    "uniform mediump sampler2D u_normal_sampler;\n"
    "uniform lowp    float     u_normal_scale;\n"
    "\n"
    "#ifdef HAS_OCCLUSION_MAP\n"
    "uniform mediump sampler2D u_occlusion_tex;\n"
    "uniform mediump float     u_occlusion_strength;\n"
    "#endif\n"
    "\n"
    "#ifdef SHADOW\n"
    "uniform highp   mat4      u_shadow_mvp;\n"
    "uniform mediump sampler2D u_shadow_tex;\n"
    "uniform mediump float     u_shadow_strength;\n"
    "varying mediump vec4      v_shadow_coord;\n"
    "#endif\n"
    "\n"
    "\n"
    "varying highp   vec3 v_Position;\n"
    "varying lowp    vec4 v_color;\n"
    "varying mediump vec2 v_occlusion_uv;\n"
    "varying mediump vec2 v_UVCoord1;\n"
    "varying mediump vec3 v_gradient;\n"
    "\n"
    "#ifdef HAS_TANGENTS\n"
    "varying mediump mat3 v_TBN;\n"
    "#else\n"
    "varying mediump vec3 v_Normal;\n"
    "#endif\n"
    "\n"
    "\n"
    "const mediump float M_PI = 3.141592653589793;\n"
    "\n"
    "/*\n"
    " * Function: F_Schlick.\n"
    " * Compute Fresnel (specular).\n"
    " *\n"
    " * Optimized variant (presented by Epic at SIGGRAPH '13)\n"
    " * https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf\n"
    " */\n"
    "mediump vec3 F_Schlick(mediump vec3 f0, mediump float LdotH)\n"
    "{\n"
    "    mediump float fresnel = exp2((-5.55473 * LdotH - 6.98316) * LdotH);\n"
    "    return (1.0 - f0) * fresnel + f0;\n"
    "}\n"
    "\n"
    "/*\n"
    " * Function: V_SmithGGXCorrelatedFast\n"
    " * Compute Geometic occlusion.\n"
    " *\n"
    " * Fast approximation from\n"
    " * https://google.github.io/filament/Filament.html#materialsystem/standardmodel\n"
    " */\n"
    "mediump float V_GGX(mediump float NdotL, mediump float NdotV,\n"
    "                    mediump float alpha)\n"
    "{\n"
    "    mediump float a = alpha;\n"
    "    mediump float GGXV = NdotL * (NdotV * (1.0 - a) + a);\n"
    "    mediump float GGXL = NdotV * (NdotL * (1.0 - a) + a);\n"
    "    return 0.5 / (GGXV + GGXL);\n"
    "}\n"
    "\n"
    "/*\n"
    " * Function: D_GGX\n"
    " * Microfacet distribution\n"
    " */\n"
    "mediump float D_GGX(mediump float NdotH, mediump float alpha)\n"
    "{\n"
    "    mediump float a2 = alpha * alpha;\n"
    "    mediump float f = (NdotH * a2 - NdotH) * NdotH + 1.0;\n"
    "    return a2 / (M_PI * f * f);\n"
    "}\n"
    "\n"
    "mediump vec3 compute_light(mediump vec3 L,\n"
    "                           mediump float light_intensity,\n"
    "                           mediump float light_ambient,\n"
    "                           mediump vec3 base_color,\n"
    "                           mediump float metallic,\n"
    "                           mediump float roughness,\n"
    "                           mediump vec3 N, mediump vec3 V)\n"
    "{\n"
    "    mediump vec3 H = normalize(L + V);\n"
    "\n"
    "    mediump float NdotL = clamp(dot(N, L), 0.0, 1.0);\n"
    "    mediump float NdotV = clamp(dot(N, V), 0.0, 1.0);\n"
    "    mediump float NdotH = clamp(dot(N, H), 0.0, 1.0);\n"
    "    mediump float LdotH = clamp(dot(L, H), 0.0, 1.0);\n"
    "    mediump float VdotH = clamp(dot(V, H), 0.0, 1.0);\n"
    "\n"
    "    mediump float a_roughness = roughness * roughness;\n"
    "    // Schlick GGX model, as used by glTF2.\n"
    "    mediump vec3 f0 = vec3(0.04);\n"
    "    mediump vec3 diffuse_color = base_color * (vec3(1.0) - f0) * (1.0 - metallic);\n"
    "    mediump vec3 specular_color = mix(f0, base_color, metallic);\n"
    "    mediump vec3  F   = F_Schlick(specular_color, LdotH);\n"
    "    mediump float Vis = V_GGX(NdotL, NdotV, a_roughness);\n"
    "    mediump float D   = D_GGX(NdotH, a_roughness);\n"
    "    // Calculation of analytical lighting contribution\n"
    "    mediump vec3 diffuseContrib = (1.0 - F) * (diffuse_color / M_PI);\n"
    "    mediump vec3 specContrib = F * (Vis * D);\n"
    "    mediump vec3 shade = NdotL * (diffuseContrib + specContrib);\n"
    "    shade = max(shade, vec3(0.0));\n"
    "    return light_intensity * shade + light_ambient * base_color;\n"
    "}\n"
    "\n"
    "mediump vec3 getNormal()\n"
    "{\n"
    "    mediump vec3 ret;\n"
    "#ifdef HAS_TANGENTS\n"
    "    mediump mat3 tbn = v_TBN;\n"
    "    mediump vec3 n = texture2D(u_normal_sampler, v_UVCoord1).rgb;\n"
    "    n = tbn * ((2.0 * n - 1.0) * vec3(u_normal_scale, u_normal_scale, 1.0));\n"
    "    ret = normalize(n);\n"
    "#else\n"
    "    ret = normalize(v_Normal);\n"
    "#endif\n"
    "\n"
    "#ifdef SMOOTHNESS\n"
    "    ret = normalize(mix(ret, normalize(v_gradient), u_m_smoothness));\n"
    "#endif\n"
    "    return ret;\n"
    "}\n"
    "\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "/************************************************************************/\n"
    "attribute highp   vec3 a_pos;\n"
    "attribute mediump vec3 a_normal;\n"
    "attribute mediump vec3 a_tangent;\n"
    "attribute mediump vec3 a_gradient;\n"
    "attribute lowp    vec4 a_color;\n"
    "attribute mediump vec2 a_occlusion_uv;\n"
    "attribute mediump vec2 a_bump_uv;   // bump tex base coordinates [0,255]\n"
    "attribute mediump vec2 a_uv;        // uv coordinates [0,1]\n"
    "\n"
    "// Must match the value in goxel.h\n"
    "#define VOXEL_TEXTURE_SIZE 8.0\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec4 pos = u_model * vec4(a_pos * u_pos_scale, 1.0);\n"
    "    v_Position = vec3(pos.xyz) / pos.w;\n"
    "\n"
    "    v_color = a_color.rgba * a_color.rgba; // srgb to linear (fast).\n"
    "    v_occlusion_uv = (a_occlusion_uv + 0.5) / (16.0 * VOXEL_TEXTURE_SIZE);\n"
    "    gl_Position = u_proj * u_view * vec4(v_Position, 1.0);\n"
    "    gl_Position.z += u_z_ofs;\n"
    "\n"
    "#ifdef SHADOW\n"
    "    v_shadow_coord = u_shadow_mvp * vec4(v_Position, 1.0);\n"
    "#endif\n"
    "\n"
    "#ifdef HAS_TANGENTS\n"
    "    mediump vec4 tangent = vec4(normalize(a_tangent), 1.0);\n"
    "    mediump vec3 normalW = normalize(a_normal);\n"
    "    mediump vec3 tangentW = normalize(vec3(u_model * vec4(tangent.xyz, 0.0)));\n"
    "    mediump vec3 bitangentW = cross(normalW, tangentW) * tangent.w;\n"
    "    v_TBN = mat3(tangentW, bitangentW, normalW);\n"
    "#else\n"
    "    v_Normal = normalize(a_normal);\n"
    "#endif\n"
    "\n"
    "    v_gradient = a_gradient;\n"
    "    v_UVCoord1 = (a_bump_uv + 0.5 + a_uv * 15.0) / 256.0;\n"
    "\n"
    "#ifdef VERTEX_LIGHTNING\n"
    "    mediump vec3 N = getNormal();\n"
    "    v_color.rgb = compute_light(normalize(u_l_dir), u_l_int, u_l_amb,\n"
    "                                (v_color * u_m_base_color).rgb,\n"
    "                                u_m_metallic, u_m_roughness, N,\n"
    "                                normalize(u_camera - v_Position));\n"
    "#endif\n"
    "}\n"
    "\n"
    "#endif\n"
    "\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "\n"
    "\n"
    "/************************************************************************/\n"
    "vec3 toneMap(vec3 color)\n"
    "{\n"
    "    // color *= u_exposure;\n"
    "    return sqrt(color); // Gamma correction.\n"
    "}\n"
    "\n"
    "void main()\n"
    "{\n"
    "\n"
    "#ifdef ONLY_EDGES\n"
    "    mediump vec3 n = 2.0 * texture2D(u_normal_sampler, v_UVCoord1).rgb - 1.0;\n"
    "    if (n.z > 0.75)\n"
    "        discard;\n"
    "#endif\n"
    "\n"
    "    float metallic = u_m_metallic;\n"
    "    float roughness = u_m_roughness;\n"
    "    vec4 base_color = u_m_base_color * v_color;\n"
    "\n"
    "#ifdef MATERIAL_UNLIT\n"
    "    gl_FragColor = vec4(sqrt(base_color.rgb), base_color.a);\n"
    "    return;\n"
    "#endif\n"
    "\n"
    "    vec3 N = getNormal();\n"
    "    vec3 V = normalize(u_camera - v_Position);\n"
    "    vec3 L = normalize(u_l_dir);\n"
    "\n"
    "#ifndef VERTEX_LIGHTNING\n"
    "    vec3 color = compute_light(L, u_l_int, u_l_amb, base_color.rgb,\n"
    "                               metallic, roughness,\n"
    "                               N, V);\n"
    "#else\n"
    "    vec3 color = v_color.rgb;\n"
    "#endif\n"
    "\n"
    "    // Shadow map.\n"
    "#ifdef SHADOW\n"
    "    float NdotL = clamp(dot(N, L), 0.0, 1.0);\n"
    "    lowp vec2 PS[4]; // Poisson offsets used for the shadow map.\n"
    "    float visibility = 1.0;\n"
    "    mediump vec4 shadow_coord = v_shadow_coord / v_shadow_coord.w;\n"
    "    lowp float bias = 0.005 * tan(acos(clamp(NdotL, 0.0, 1.0)));\n"
    "    bias = clamp(bias, 0.0015, 0.015);\n"
    "    shadow_coord.z -= bias;\n"
    "    PS[0] = vec2(-0.94201624, -0.39906216) / 1024.0;\n"
    "    PS[1] = vec2(+0.94558609, -0.76890725) / 1024.0;\n"
    "    PS[2] = vec2(-0.09418410, -0.92938870) / 1024.0;\n"
    "    PS[3] = vec2(+0.34495938, +0.29387760) / 1024.0;\n"
    "    for (int i = 0; i < 4; i++)\n"
    "        if (texture2D(u_shadow_tex, v_shadow_coord.xy +\n"
    "           PS[i]).z < shadow_coord.z) visibility -= 0.2;\n"
    "    if (NdotL <= 0.0) visibility = 0.5;\n"
    "    float shade = mix(1.0, visibility, u_shadow_strength);\n"
    "    color *= shade;\n"
    "#endif // SHADOW\n"
    "\n"
    "#ifdef HAS_OCCLUSION_MAP\n"
    "    lowp float ao;\n"
    "    ao = texture2D(u_occlusion_tex, v_occlusion_uv).r;\n"
    "    color = mix(color, color * ao, u_occlusion_strength);\n"
    "#endif\n"
    "\n"
    "    color += u_m_emissive_factor;\n"
    "\n"
    "    gl_FragColor = vec4(toneMap(color), 1.0);\n"
    "}\n"
    "\n"
    "#endif\n"
    ""
},



