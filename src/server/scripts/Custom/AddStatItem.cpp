#include "ScriptMgr.h"
#include "Player.h"
#include "WorldSession.h"
#include "Unit.h"
#include <Configuration\Config.h>


class addstatitem : public ItemScript
{
public:
	addstatitem() : ItemScript("addstatitem") { }

    uint32 item_id = sConfigMgr->GetIntDefault("AddStatItem.ItemID", 55001);


	bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
	{
		if (player->IsInCombat() || player->IsInFlight())
		{
			player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, NULL);
			return true;
		}
		else
		{
            player->HandleStatFlatModifier(UNIT_MOD_STAT_STRENGTH, TOTAL_VALUE, 10, true);
            player->DestroyItemCount(item_id, 1, true);
		}
		return true;
	}
};

void AddSC_addstatitem()
{
	new addstatitem();
}
