# ifndef _SHADER_HPP_
# define _SHADER_HPP_
#define STRINGIFY(A)  #A

#include <shader/SHADER_VERTEX_MVP.h>
#include <shader/SHADER_FRAGMENT_TEXTURE.h>
#include <shader/SHADER_OUTLINE.h>
#include <shader/SHADER_SKYBOX.h>
#include <shader/SHADER_FRAGMENT_NORMAL.h>

extern const char * g_shader_vertex_mvp;
extern const char * g_shader_frag_diffuse;
extern const char * g_shader_vert_outline;
extern const char * g_shader_frag_outline;
extern const char * g_shader_vert_skybox;
extern const char * g_shader_frag_skybox;
extern const char * g_shader_vertex_normal;
extern const char * g_shader_frag_normal;

#endif