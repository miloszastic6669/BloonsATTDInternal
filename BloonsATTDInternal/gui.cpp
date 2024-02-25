#include "gui.h"



std::string toHex(unsigned int value) {
  std::stringstream ss;
  ss << std::hex << std::uppercase << value; // Convert to hexadecimal format
  return ss.str(); // Return the hexadecimal representation as a string
}

std::vector<std::string> orbsStrings;
void getOrbStrings(std::vector<std::string>* strings)
{
  strings->erase(strings->begin(), strings->end());
  std::string str;
  str = "Common: " + std::to_string(*(int*)offsets::commonOrb);
  strings->push_back(str);
  
  str = "Uncommon: " + std::to_string(*(int*)offsets::uncommonOrb);
  strings->push_back(str);

  str = "Rare: " + std::to_string(*(int*)offsets::rareOrb);
  strings->push_back(str);
  
  str = "Super Rare: " + std::to_string(*(int*)offsets::superRareOrb);
  strings->push_back(str);

  str = "Epic: " + std::to_string(*(int*)offsets::epicOrb);
  strings->push_back(str);
}

void gui::Draw()
{
  const ImGuiViewport* mainViewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(mainViewport->WorkPos.x + 100, mainViewport->WorkPos.y + 50), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(600, 500));
  ImGui::Begin("Trainer Main", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
  ImGui::Text("Current Orbs:");
   
  getOrbStrings(&orbsStrings);
  for(auto i : orbsStrings)
  {
    ImGui::Text(i.c_str());
  }

  ImGui::Text("In-game Hacks:");
  ImGui::Checkbox("Money Hack", &hacks::money);
  hacks::moneyHack();
  ImGui::Checkbox("Health Hack", &hacks::health);
  hacks::healthHack();
  
  ImGui::Text("Currency Hacks:");
  ImGui::Checkbox("Cosmic Essence Hack", &hacks::essence);
  hacks::essenceHack();
  ImGui::Checkbox("Martian Crystals Hack", &hacks::crystal);
  hacks::crystalHack();
  ImGui::Checkbox("Martial Deal Hack(Buy items multiple times)", &hacks::martianBuy);
  hacks::martianBuyHack();
  ImGui::SliderInt("Cosmic Essence", &hacks::essenceAdd, 5, 1000, "%d", ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic);
  if(ImGui::Button(std::format("Add {} Cosmic Essence", hacks::essenceAdd).c_str()))
  {
    hacks::RemoveGenericTowerXpCurrency((__int64)offsets::cosmicEssencePtr, (__int64)-hacks::essenceAdd);
  }
  ImGui::SliderInt("Wish Orb Shards", &hacks::wishOrbShardsAdd, 10, 1000000, "%d", ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic);
  if(ImGui::Button(std::format("Add {} Wish Orb Shards", hacks::wishOrbShardsAdd).c_str()))
  {
    hacks::AddWishOrbShards((__int64)offsets::wishOrbShardsPtr, (__int64)hacks::wishOrbShardsAdd);
  }
  ImGui::Text(std::format("Max XP You can set: {}", hacks::MaxXPFromCap).c_str());
  ImGui::SliderInt("Player XP", &(hacks::playerXpSet), 10, hacks::MaxXPFromCap, "%d", ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic);
  if(ImGui::Button(std::format("Set Player XP to {}", hacks::playerXpSet).c_str()))
  {
    hacks::CryptVarInt32_Set(offsets::playerXpPtr, hacks::playerXpSet);
  }
  ImGui::SliderInt("Gems", &(hacks::gemsSet), 0, 50000, "%d", ImGuiSliderFlags_::ImGuiSliderFlags_Logarithmic);
  if (ImGui::Button(std::format("Set Gems to {}", hacks::gemsSet).c_str()))
  {
    hacks::CryptVarInt32_Set(offsets::gemsPtr, hacks::gemsSet);
  }

  



  ImGui::End();
}
