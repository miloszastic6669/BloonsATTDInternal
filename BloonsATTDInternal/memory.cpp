#include "memory.h"


void mem::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
  DWORD oldprotect;
  VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
  memcpy(dst, src, size);
  VirtualProtect(dst, size, oldprotect, &oldprotect);
 }

void mem::Nop(BYTE* dst, unsigned int size)
{
  DWORD oldprotect;
  VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
  memset(dst, 0x90, size);
  VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t mem::FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
  uintptr_t addr = ptr;
  for (auto i : offsets)
  {
    addr = *(uintptr_t*)addr;
    addr += i;
  }
  return addr;
}
