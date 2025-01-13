%module test
%nspace;

%{
#include "../pch/wi_pch.h"
%}

%include "../.wi/WickedEngine/wiVersion.h"
%include "../.wi/WickedEngine/wiApplication.h"
%include "../.wi/WickedEngine/wiArchive.h"
%include "../.wi/WickedEngine/wiAudio.h"
%include "../.wi/WickedEngine/wiBVH.h"
%include "../.wi/WickedEngine/wiColor.h"
%include "../.wi/WickedEngine/wiConfig.h"
%include "../.wi/WickedEngine/wiEventHandler.h"
%include "../.wi/WickedEngine/wiFadeManager.h"
%include "../.wi/WickedEngine/wiFFTGenerator.h"
%include "../.wi/WickedEngine/wiGPUBVH.h"
%include "../.wi/WickedEngine/wiGraphicsDevice_Vulkan.h"
%include "../.wi/WickedEngine/wiHelper.h"
%include "../.wi/WickedEngine/wiInitializer.h"
%include "../.wi/WickedEngine/wiJobSystem.h"
%include "../.wi/WickedEngine/wiLoadingScreen.h"
%include "../.wi/WickedEngine/wiLocalization.h"
%include "../.wi/WickedEngine/wiLuna.h"
%include "../.wi/WickedEngine/wiNetwork.h"
%include "../.wi/WickedEngine/wiOcean.h"
%include "../.wi/WickedEngine/wiProfiler.h"
%include "../.wi/WickedEngine/wiRandom.h"
%include "../.wi/WickedEngine/wiRectPacker.h"
%include "../.wi/WickedEngine/wiRenderPath.h"
%include "../.wi/WickedEngine/wiRenderPath2D.h"
%include "../.wi/WickedEngine/wiRenderPath3D_PathTracing.h"
%include "../.wi/WickedEngine/wiScene_Decl.h"
%include "../.wi/WickedEngine/wiShaderCompiler.h"
%include "../.wi/WickedEngine/wiSpinLock.h"
%include "../.wi/WickedEngine/wiSprite.h"
%include "../.wi/WickedEngine/wiSpriteFont.h"
%include "../.wi/WickedEngine/wiTimer.h"
%include "../.wi/WickedEngine/wiTrailRenderer.h"
%include "../.wi/WickedEngine/wiUnorderedMap.h"
%include "../.wi/WickedEngine/wiUnorderedSet.h"
%include "../.wi/WickedEngine/wiVector.h"
%include "../.wi/WickedEngine/wiVideo.h"
%include "../.wi/WickedEngine/wiXInput.h"

// %ignore "";
// %rename("%s") wi;
// %rename("%s") wi::renderer;
// %rename("%s") wi::renderer::SetShaderSourcePath;
// %rename("%s") SetShaderSourcePath;
// %include "../.wi/WickedEngine/wiRenderer.h"
// %rename("%s") "";



namespace wi::renderer {
	void SetShaderSourcePath(char* dirPath);
	void SetShaderPath(char* dirPath);
}

namespace wi::arguments {
  void Parse(int argc, char *argv[]);
}



%{

namespace wi::version {
	long GetVersion() {
		return 0;
	}
}

const char* wi_renderer_GetShaderSourcePath() {
  return wi::renderer::GetShaderSourcePath().c_str();
}

const char* wi_renderer_GetShaderPath() {
  return wi::renderer::GetShaderPath().c_str();
}

#ifdef __cplusplus
extern "C" {
#endif
SWIGEXPORTC void wi_Application_infoDisplay(SwigObj* wiApp, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize, bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int textSize, bool colorGradingHelper) {
  wi::Application *app = (wi::Application *) wiApp;
  app->infoDisplay.active = active;
  app->infoDisplay.colorspace = colorSpace;
  app->infoDisplay.device_name = deviceName;
  app->infoDisplay.fpsinfo = fpsInfo;
  app->infoDisplay.heap_allocation_counter = heapAllocCounter;
  app->infoDisplay.logical_size = logicalSize;
  app->infoDisplay.pipeline_count = pipelineCount;
  app->infoDisplay.pipeline_creation = pipelineCreation;
  app->infoDisplay.resolution = resolution;
  app->infoDisplay.vram_usage = vramUsage;
  app->infoDisplay.watermark = watermark;
  app->infoDisplay.size = textSize;
  app->infoDisplay.colorgrading_helper = colorGradingHelper;
}
#ifdef __cplusplus
}
#endif

%}
