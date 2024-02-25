#pragma once
#include "offsets.h"




namespace offsets
{
  uintptr_t commonOrb = 0;
  uintptr_t uncommonOrb = 0;
  uintptr_t rareOrb = 0;
  uintptr_t superRareOrb = 0;
  uintptr_t epicOrb = 0;

  uintptr_t dynamicCommonOrb = 0x1d84f58;        // will be changed immediately after the object is constructed
  uintptr_t dynamicCashOpCode = 0x611c54;        // change to mulsd from addsd for much more money
  uintptr_t dynamicHealthOpCode = 0x614465;      // nop the call to disable the health decreasing
  uintptr_t dynamicEssenceOpCode = 0x33d8c3;     // nop the call to disable the cosmic essence from decrementing
  uintptr_t dynamicCrystalOpCode = 0x3d7e1c;     // change call to mov eax,04234584 for a lot of shards when going into martian games
  uintptr_t dynamicMartialDealOpCode = 0x3b1f72; // nop the call so you can buy stuff over and over again

  uintptr_t cosmicEssencePtr = 0x1d84f58; // pass this address to RemoveGenericTowerXPCurrency(__int64 cosmicEssencePtr, __int64 value)
  uintptr_t wishOrbShardsPtr = 0x1db49e8; // pass this address to AddWishOrbShards(__int64 shardsPtr, __int64 amount)
  uintptr_t playerXpPtr = 0x1dd7728; //pass this address to CryptVarInt32_Set(__int64 ptr, __int64 value) to set playerXP
  uintptr_t gemsPtr = 0x1d84f58; //pass this address to CryptVarInt32_Set(__int64 ptr, __int64 value) to set gems

  const std::vector<unsigned int> commonOrbOffsets = { 0x68,0xc60,0x30,0x18,0x18,0x2c };
  const std::vector<unsigned int> currencyPtrOffsets = { 0x68, 0xb60 };
  const std::vector<unsigned int> wishOrbShardsOffsets = { 0xb8,0x38,0xa0,0x18,0x40,0x0 };
  const std::vector<unsigned int> playerXPOffsets = { 0xb8,0x18,0xa0, 0x100,0x20, 0x0 };
  const std::vector<unsigned int> gemPtrOffsets = {0x68, 0xc60, 0x18, 0x0};


  void resolveAll(uintptr_t base)
  {
    commonOrb = mem::FindDMAAddy(dynamicCommonOrb + base, commonOrbOffsets);
    uncommonOrb = commonOrb + 0x10;
    rareOrb = commonOrb + 0x20;
    superRareOrb = commonOrb + 0x30;
    epicOrb = commonOrb + 0x40;

    dynamicCashOpCode += (uintptr_t)base;
    dynamicHealthOpCode += (uintptr_t)base;
    dynamicEssenceOpCode += (uintptr_t)base;
    dynamicCrystalOpCode += (uintptr_t)base;
    dynamicMartialDealOpCode += (uintptr_t)base;

    cosmicEssencePtr = mem::FindDMAAddy(cosmicEssencePtr + base, currencyPtrOffsets);
    hacks::RemoveGenericTowerXpCurrency = reinterpret_cast<RemoveGenericTowerXpCurrency_>(base + 0x3DD890);
    wishOrbShardsPtr = mem::FindDMAAddy(wishOrbShardsPtr + base, wishOrbShardsOffsets);
    hacks::AddWishOrbShards = reinterpret_cast<AddWishOrbShards_>(base + 0x3D8580);
    playerXpPtr = mem::FindDMAAddy(playerXpPtr + base, playerXPOffsets);
    hacks::CryptVarInt32_Set = reinterpret_cast<CryptVarInt32_Set_>(base + 0x13AAE10);
    hacks::GetMaxXPFromCap = reinterpret_cast<GetMaxXPFromCap_>(base + 0x51E530);
    gemsPtr = mem::FindDMAAddy(gemsPtr + base, gemPtrOffsets);


    hacks::MaxXPFromCap = hacks::GetMaxXPFromCap(0);

  }
}