#include "hacks.h"



namespace hacks
{
  bool money = false;
  bool moneyLast = false;
  
  bool health = false;
  bool healthLast = false;
  
  bool essence = false;
  bool essenceLast = false;
  
  bool crystal = false;
  bool crystalLast = false;
  
  bool martianBuy = false;
  bool martianBuyLast = false;

  int essenceAdd = 10;
  int wishOrbShardsAdd = 100;
  int wishOrbsAdd = 10;
  int playerXpSet = 1000;
  long int MaxXPFromCap = 20000;
  int gemsSet = 10;

  void addOrb(Orbs orb, int value)
  {
    *((int*)(offsets::commonOrb + 0x10 * orb)) += value;
  }

  void moneyHack()
  {
    if(money && !moneyLast)
    {
      mem::Patch((BYTE*)offsets::dynamicCashOpCode, (BYTE*)"\xF2\x0F\x59", 3);
      moneyLast = true;
    }
    else if(!money && moneyLast)
    {
      mem::Patch((BYTE*)offsets::dynamicCashOpCode, (BYTE*)"\xF2\x0F\x58", 3);
      moneyLast = false;
    }
  }

  void healthHack()
  {
    if(health && !healthLast)
    {
      mem::Nop((BYTE*)offsets::dynamicHealthOpCode, 5);
      healthLast = true;
    }
    else if(!health && healthLast)
    {
      mem::Patch((BYTE*)offsets::dynamicHealthOpCode, (BYTE*)"\xe8\x96\x76\xd9\x00", 5);
      healthLast = false;
    }
  }

  void essenceHack()
  {
    if(essence && !essenceLast)
    {
      mem::Nop((BYTE*)offsets::dynamicEssenceOpCode, 5);
      essenceLast = true;
    }
    else if(!essence && essenceLast)
    {
      mem::Patch((BYTE*)offsets::dynamicEssenceOpCode, (BYTE*)"\xe8\xc8\xff\x09\x00", 5);
      essenceLast = false;
    }

  }

  void crystalHack()
  {
    if (crystal && !crystalLast)
    {
      mem::Patch((BYTE*)offsets::dynamicCrystalOpCode, (BYTE*)"\xb8\x84\x45\x23\x04", 5);
      crystalLast = true;
    }
    else if (!crystal && crystalLast)
    {
      mem::Patch((BYTE*)offsets::dynamicCrystalOpCode, (BYTE*)"\xe8\xcf\x29\xfd\x00", 5);
      crystalLast = false;
    }
  }

  void martianBuyHack()
  {
    if (martianBuy && !martianBuyLast)
    {
      mem::Nop((BYTE*)offsets::dynamicMartialDealOpCode, 5);
      martianBuyLast = true;
    }
    else if (!martianBuy && martianBuyLast)
    {
      mem::Patch((BYTE*)offsets::dynamicMartialDealOpCode, (BYTE*)"\xe8\x69\xc2\x02\x00", 5);
      martianBuyLast = false;
    }
  }
  RemoveGenericTowerXpCurrency_ RemoveGenericTowerXpCurrency = nullptr; //cosmicEssencePtr is the first
  AddWishOrbShards_ AddWishOrbShards = nullptr;
  CryptVarInt32_Set_ CryptVarInt32_Set = nullptr;
  GetMaxXPFromCap_ GetMaxXPFromCap = nullptr;
  
}
