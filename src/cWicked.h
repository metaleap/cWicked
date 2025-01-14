#pragma once


#ifdef __cplusplus
extern "C" {
#endif
/// C-only API:



const char* wi_version_getVersionString();
const char* wi_version_getCreditsString();
int wi_version_getMajor();
int wi_version_getMinor();
int wi_version_getRevision();

void wi_arguments_parse(int argc, char** argv);

void wi_renderer_setShaderPath(char* path);
void wi_renderer_setShaderSourcePath(char* path);



// typedef struct SwigObj_wi_Application wi_Application;
// void wi_Application_infoDisplay(wi_Application* wiApp, bool active, bool watermark, bool fpsInfo, bool deviceName, bool resolution, bool logicalSize,
//                                 bool colorSpace, bool heapAllocCounter, bool pipelineCount, bool pipelineCreation, bool vramUsage, int size,
//                                 bool colorGradingHelper);




///
#ifdef __cplusplus
} // extern "C"
#endif
