#pragma once
#include <stdio.h>
#include <vector>
#include "hacks.h"
#include "memory.h"



namespace offsets
{
  extern uintptr_t commonOrb;
  extern uintptr_t uncommonOrb;
  extern uintptr_t rareOrb;
  extern uintptr_t superRareOrb;
  extern uintptr_t epicOrb;

  extern uintptr_t dynamicCommonOrb;         // will be changed immediately after the object is constructed
  extern uintptr_t dynamicCashOpCode;        // change to mulsd from movaps for much more money
  extern uintptr_t dynamicHealthOpCode;      // nop the call to disable the health decreasing
  extern uintptr_t dynamicEssenceOpCode;     // nop the call to disable the cosmic essence from decrementing
  extern uintptr_t dynamicCrystalOpCode;     // change call to mov eax,04234584 for a lot of shards when going into martian games
  extern uintptr_t dynamicMartialDealOpCode; // nop the call so you can buy stuff over and over again

  extern uintptr_t cosmicEssencePtr; 
  extern uintptr_t wishOrbShardsPtr;
  extern uintptr_t playerXpPtr;
  extern uintptr_t gemsPtr;

  void resolveAll(uintptr_t base);
}

