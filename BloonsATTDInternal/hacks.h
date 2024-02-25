#pragma once
#include "offsets.h"
#include "memory.h"

typedef int32_t (__fastcall* RemoveGenericTowerXpCurrency_)(__int64 currencyPtr, __int64 amount);
typedef __int64 (__fastcall* AddWishOrbShards_)(__int64 shardsPtr, __int64 amount);
typedef __int64(__fastcall* CryptVarInt32_Set_)(__int64 ptr, __int64 value);
typedef int32_t(__stdcall* GetMaxXPFromCap_)(__int64 cock);

namespace hacks
{
  enum Orbs
  {
    Common,
    Uncommon,
    Rare,
    SuperRare,
    Epic
  };

  extern bool money;
  extern bool health;
  extern bool essence;
  extern bool crystal;
  extern bool martianBuy;

  extern int essenceAdd;
  extern int wishOrbShardsAdd;
  extern int wishOrbsAdd;
  extern int playerXpSet;
  extern long int MaxXPFromCap;
  extern int gemsSet;
  

  void addOrb(Orbs orb, int value);
  void moneyHack();
  void healthHack();
  void essenceHack();
  void crystalHack();
  void martianBuyHack();

  extern RemoveGenericTowerXpCurrency_ RemoveGenericTowerXpCurrency; //cosmicEssencePtr is the first 
  extern AddWishOrbShards_ AddWishOrbShards;
  extern CryptVarInt32_Set_ CryptVarInt32_Set;
  extern GetMaxXPFromCap_ GetMaxXPFromCap;
}

