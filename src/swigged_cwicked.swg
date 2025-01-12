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

namespace wi::arguments {
  void Parse(int argc, char *argv[]);
}

%{
namespace wi::version {
	long GetVersion() {
		return 0;
	}
}
%}
