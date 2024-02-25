#include "windows.h"
#include <iostream>
#include <chrono>
#include <thread>

#include "vendor/ImGui/imgui.h"
#include "vendor/ImGui/backends/imgui_impl_win32.h"
#include "vendor/ImGui/backends/imgui_impl_dx11.h"

#include "D3D11Hook.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <MinHook.h>
#pragma comment(lib, "libMinHook.x64.lib")

#include "offsets.h"
#include "memory.h"
#include "hacks.h"
#include "gui.h"




HINSTANCE DllHandle;
//definitions
DWORD __stdcall EjectThread(LPVOID lpParameter);
void mainHack(const HMODULE instance);

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    return true;

  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

present pPresent; // original function ptr after 
present pPresentTarget; //original function ptr BEFORE hook

bool firstTime = true;
HWND window = NULL;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;

bool gShowGUI = true;
bool showPointers = false;

std::vector<std::string> pointerStrings; 




static long __stdcall detourPresent(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags)
{
  if (firstTime) {
    if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
    {
      pDevice->GetImmediateContext(&pContext);
      DXGI_SWAP_CHAIN_DESC sd;
      pSwapChain->GetDesc(&sd);
      window = sd.OutputWindow;
      ID3D11Texture2D* pBackBuffer;
      pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
      pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
      pBackBuffer->Release();
      oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
      ImGui::CreateContext();
      ImGuiIO& io = ImGui::GetIO();
      io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
      ImGui_ImplWin32_Init(window);
      ImGui_ImplDX11_Init(pDevice, pContext);
      firstTime = false;
    }
    else
      return pPresent(pSwapChain, syncInterval, flags);
  }
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();

  //ImGui::ShowDemoWindow();
  
  
  
  if(gShowGUI)
  {
    gui::Draw();
  }

  ImGui::EndFrame();
  ImGui::Render();

  pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  return pPresent(pSwapChain, syncInterval, flags);
}

void mainHack(const HMODULE instance)
{
  d11::getPresentPtr(&pPresentTarget);
  if (pPresentTarget == nullptr)
  {
    CreateThread(0, 0, EjectThread, 0, 0, 0);
    return;
  }

  bool hookResult = d11::hookPresent(pPresentTarget, (present*)detourPresent, &pPresent);

  uintptr_t gameAssemblyBase = reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll"));
  offsets::resolveAll(gameAssemblyBase);
  //getPointerStrings(&pointerStrings);

  while (!GetAsyncKeyState(VK_END))
  {
    if (GetAsyncKeyState(VK_HOME) & 1)
      gShowGUI = !gShowGUI;
  }
  
  bool unhook = d11::unhookPresent();

  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
  if (pContext) { pContext->Release(); pContext = NULL; }
  if (pDevice) { pDevice->Release(); pDevice = NULL; }
  SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));

  CreateThread(0, 0, EjectThread, 0, 0, 0);
  return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    DllHandle = hModule;
    DisableThreadLibraryCalls(hModule);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainHack, hModule, 0, 0);
  }

  return TRUE;
}

DWORD __stdcall EjectThread(LPVOID lpParameter)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  FreeLibraryAndExitThread(DllHandle, 0);
  return 0;
}