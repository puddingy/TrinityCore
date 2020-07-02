#include "ScriptMgr.h"
#include "Player.h"
#include "WorldSession.h"

// Original code by kazzyx from AC-Web
uint32 ITEM_ID = 55000;
uint8 MAX_LVL = 80;

class levelupitem : public ItemScript
{
public:
	levelupitem() : ItemScript("levelupitem") { }

	bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
	{
		if (player->IsInCombat() || player->IsInFlight())
		{
			player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, NULL);
			return true;
		}
		if (player->GetLevel() >= MAX_LVL)
		{
			player->GetSession()->SendNotification("You already reached the maximum level.");
			return true;
		}
		else
		{
			int32 oldlevel = player->GetLevel();
			int32 newLevel = oldlevel + 1;

			player->GiveLevel(newLevel);
			player->InitTalentForLevel();
			player->SetUInt32Value(PLAYER_XP, 0);
			player->DestroyItemCount(ITEM_ID, 1, true);
		}
		return true;
	}
};

void AddSC_levelupitem()
{
	new levelupitem();
}