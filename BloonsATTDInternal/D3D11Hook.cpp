#include "windows.h"
#include "D3D11Hook.h"
#include <chrono>
#include <thread>
#include <iostream>

#define DEBUG_MODE


void d11::getPresentPtr(present* ptr)
{
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 1;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = GetForegroundWindow();
  sd.SampleDesc.Count = 1;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  IDXGISwapChain* swap_chain;
  ID3D11Device* device;

  const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
  HRESULT cock = D3D11CreateDeviceAndSwapChain(
    NULL,
    D3D_DRIVER_TYPE_HARDWARE,
    NULL,
    0,
    feature_levels,
    2,
    D3D11_SDK_VERSION,
    &sd,
    &swap_chain,
    &device,
    nullptr,
    nullptr);

  if (cock == S_OK)
  {
    void** p_vtable = *reinterpret_cast<void***>(swap_chain);
    swap_chain->Release();
    device->Release();
    *ptr = (present)p_vtable[8];
    return;
  }

#ifdef DEBUG_MODE
  std::cout << "D3D11CreateDeviceAndSwapChain didn't return S_OK!!\n";
  std::cout << "HRESULT = " << cock << "\n";
#endif // DEBUG_MODE

  return;
}

bool d11::hookPresent(present pPresentTarget, present* pDetour, present* pPresent)
{
  if (MH_Initialize() != MH_OK)
    return false;
  if (MH_CreateHook(reinterpret_cast<void**>(pPresentTarget), pDetour, reinterpret_cast<void**>(pPresent)) != MH_OK)
    return false;
  if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    return false;
  return true;


}

bool d11::unhookPresent()
{
  if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
    return false;
  if (MH_Uninitialize() != MH_OK)
    return false;
  return true;
}


