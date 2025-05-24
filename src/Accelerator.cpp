#include "Accelerator.hpp"
#include "Utilities/General.hpp"
#include "Utilities/Logger.hpp"
#include "imgui.h"
#include <CL/cl.h>
#include <CL/cl2.hpp>
#include <CL/opencl.hpp>
#include <vector>

#if SDW_OS_LINUX
#	include <dlfcn.h>
// #	define LOAD_LIBRARY(path) dlopen(path, RTLD_LAZY)
#	define LOAD_LIBRARY(path) dlopen(path, RTLD_NOW)
#	define GET_FUNCTION(lib, name) dlsym(lib, name)
#	define FREE_LIBRARY(lib) dlclose(lib)
#	define GET_LOAD_ERROR() (dlerror() ? std::string(dlerror()) : "Unknown error")
	typedef void* LibHandle;
#elif SDW_OS_WINDOWS
#	define LOAD_LIBRARY(path) LoadLibrary(path)
#	define GET_FUNCTION(lib, name) GetProcAddress(lib, name)
#	define FREE_LIBRARY(lib) FreeLibrary(lib)
#	define GET_LOAD_ERROR() std::to_string(GetLastError())
	typedef HMODULE LibHandle;
#else
#	error "IDK what os"
#endif

static LibHandle cudaLibrary = nullptr;

static bool cudaAvailable = false;
static bool openclAvailable = false;

#if SDW_OS_LINUX
# define CUDA_LIB_NAME "libcuda.so"
#elif SDW_OS_WINDOWS
# define CUDA_LIB_NAME "nvcuda.dll"
#endif

Accelerator::Accelerator() {

	cudaAvailable = isCudaAvailable();
	openclAvailable = isOpenCLAvailable();

}

Accelerator::~Accelerator() { }

void Accelerator::onUpdate() {
	using namespace ImGui;

	if (!Begin("AHH")) {
		End();
		return;
	}

	Text("running on %s", Shadow::Utils::getOSName());
	Text("compiled on %s", Shadow::Utils::getCompilerName());

	SeparatorText("Acceleration Devices");
	TextColored(cudaAvailable ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), "Nvidia CUDA");
	TextColored(openclAvailable ? ImColor(0, 255, 0, 255) : ImColor(255, 0, 0, 255), "OpenCL");

	TextColored(ImColor(0, 255, 0, 255), "Software Accelerated");

	End();
}

bool Accelerator::isCudaAvailable() {

	cudaLibrary = LOAD_LIBRARY(CUDA_LIB_NAME);

	if (!cudaLibrary) return false;

	return true;
}

bool Accelerator::isOpenCLAvailable() {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	if (platforms.empty()) return false;

	PRINT("OpenCL using %s", platforms[0].getInfo<CL_PLATFORM_NAME>().c_str());

	return true;
}