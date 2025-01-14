#include "../pch/wi_pch.h"

#include "cWicked.h"



void wi_renderer_setShaderPath(char* path) {
  wi::renderer::SetShaderPath(std::string(path));
}

void wi_renderer_setShaderSourcePath(char* path) {
  wi::renderer::SetShaderSourcePath(std::string(path));
}
