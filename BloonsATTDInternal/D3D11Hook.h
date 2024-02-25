#pragma once
#include "windows.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <MinHook.h>
#pragma comment(lib, "libMinHook.x64.lib")

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);

namespace d11
{
  void getPresentPtr(present* ptr);
  bool hookPresent(present pPresentTarget, present* pDetour, present* pPresent);
  bool unhookPresent();
}
