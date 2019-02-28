//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/tests/framework/testFixture.c";
#include "/lib/include/inventory.h"

object Player;
string *Slots = ({ "Primary Weapon", "Equipped Offhand", "Worn Armor", "Worn Helmet",
    "Worn Gloves", "Worn Boots", "Worn Cloak", "Worn Amulet", "Worn Belt",
    "Worn Arm Greaves", "Worn Leg Greaves", "Worn Bracers", "Worn First Ring",
    "Worn Second Ring" });

string Bar = "\x1b[0;31m+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\x1b[0m";
string EquippedItem = "\x1b[0;31m| \x1b[0m\x1b[0;36m%s:%s\x1b[0m\x1b[0;%sm%s\x1b[0m%s\n";
string nothingEquipped = "\x1b[0;31m| \x1b[0m\x1b[0;36m%s:%s\x1b[0m\x1b[0;30;1mnothing\x1b[0m\n";
string UnequippedItem = "\x1b[0;31m| \x1b[0m\x1b[0;37;1m%s\x1b[0m%s\n";

/////////////////////////////////////////////////////////////////////////////
varargs string BuildInventoryString(mapping equipped, string *unequipped, int verbose)
{
    string ret = "";
    
    string showVerbose = verbose ? "   " : "";

    if(sizeof(equipped))
    {
        ret += Bar;
        foreach(string slot in Slots)
        {
            string spacing = (sizeof(slot) >= 14) ? "\t" : "\t\t";

            if(member(equipped, slot))
            {
                ret += sprintf(EquippedItem, slot, spacing, equipped[slot]["type"], equipped[slot]["data"], showVerbose);
            }
            else
            {
                ret += sprintf(nothingEquipped, slot, spacing);
            }

            if(slot == "Equipped Offhand")
            {
                ret += Bar;
            }
        }
        ret += Bar;
    }

    if(sizeof(unequipped))
    {
        foreach(string item in unequipped)
        {
            ret += sprintf(UnequippedItem, item, showVerbose);
        }

        ret += Bar;
    }

    ret += sprintf("\x1b[0;31m| \x1b[0;36mYou currently have \x1b[0;32m%d\x1b[0;36m in cash on hand.\n", Player->Money());
    ret += Bar;

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
void Init()
{
    ignoreList += ({ "BuildInventoryString" });
}

/////////////////////////////////////////////////////////////////////////////
void Setup()
{
    Player = clone_object("/lib/tests/support/services/mockPlayer.c");
    Player->Name("bob");
    Player->addCommands();
    move_object(Player, "/lib/tests/support/environment/fakeEnvironment.c");
}

/////////////////////////////////////////////////////////////////////////////
void CleanUp()
{
    destruct(Player);
}

/////////////////////////////////////////////////////////////////////////////
void CanExecuteInventoryCommand()
{
    ExpectTrue(Player->executeCommand("inventory"));
}

/////////////////////////////////////////////////////////////////////////////
void CanExecuteInvenCommand()
{
    ExpectTrue(Player->executeCommand("inven"));
}

/////////////////////////////////////////////////////////////////////////////
void CanExecuteICommand()
{
    ExpectTrue(Player->executeCommand("i"));
}

/////////////////////////////////////////////////////////////////////////////
void ExecuteRegexpIsNotGreedy()
{
    ExpectFalse(Player->executeCommand("invent"));
    ExpectFalse(Player->executeCommand("in"));
    ExpectFalse(Player->executeCommand("inventoryy"));
    ExpectFalse(Player->executeCommand("hi"));
    ExpectFalse(Player->executeCommand("sgjdfsdfginvent"));
    ExpectFalse(Player->executeCommand("blarginventory"));
}

/////////////////////////////////////////////////////////////////////////////
void ExecuteRegexpFailsIfInvalidFlagsPassed()
{
    ExpectFalse(Player->executeCommand("inventory -t bob"));
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsSparselyPopulatedList()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"37;1", "data" : "Sword of Blah"])]);

    object armor = clone_object("/lib/items/armor");
    armor->set("name", "blarg");
    armor->set("short", "Equipment of equippedness");
    armor->set("equipment locations", Gloves | Armor | ArmGreaves | LegGreaves | Boots);
    move_object(armor, Player);
    armor->equip("blarg");
    items["Worn Armor"] = (["type":"37;1", "data" : "Equipment of equippedness"]);
    items["Worn Gloves"] = (["type":"37;1", "data" : "Equipment of equippedness"]);
    items["Worn Boots"] = (["type":"37;1", "data" : "Equipment of equippedness"]);
    items["Worn Arm Greaves"] = (["type":"37;1", "data" : "Equipment of equippedness"]);
    items["Worn Leg Greaves"] = (["type":"37;1", "data" : "Equipment of equippedness"]);

    armor = clone_object("/lib/items/armor");
    armor->set("name", "f");
    armor->set("short", "Some junk");
    armor->set("equipment locations", Gloves | Armor | ArmGreaves | LegGreaves | Boots);
    move_object(armor, Player);
    string *unequipped = ({ "Some junk" });

    ExpectTrue(Player->executeCommand("inventory"));
    ExpectEq(BuildInventoryString(items, unequipped), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsWellCraftedItemsInGreen()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("weapon type", "long sword");
    weapon->set("craftsmanship", 20);
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"32", "data" : "Sword of Blah"])]);

    ExpectTrue(Player->executeCommand("inventory"));
    ExpectEq(BuildInventoryString(items), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsMasterworkItemsInBoldGreen()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("weapon type", "long sword");
    weapon->set("craftsmanship", 50);
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"32;1", "data" : "Sword of Blah"])]);

    ExpectTrue(Player->executeCommand("inventory"));
    ExpectEq(BuildInventoryString(items), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsMagicItemsInMagenta()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("weapon type", "long sword");
    weapon->set("bonus attack", 1);
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"35", "data" : "Sword of Blah"])]);

    ExpectTrue(Player->executeCommand("inventory"));
    ExpectEq(BuildInventoryString(items), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsPowerfulMagicItemsInBoldMagenta()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("weapon type", "long sword");
    weapon->set("bonus attack", 5);
    weapon->set("bonus damage", 5);
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"35;1", "data" : "Sword of Blah"])]);

    ExpectTrue(Player->executeCommand("inventory"));
    ExpectEq(BuildInventoryString(items), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void CanExecuteVerboseInventory()
{
    object weapon = clone_object("/lib/items/weapon");
    weapon->set("name", "blah");
    weapon->set("short", "Sword of Blah");
    weapon->set("weapon type", "long sword");
    weapon->set("bonus attack", 5);
    weapon->set("bonus damage", 5);
    weapon->set("equipment locations", OnehandedWeapon);
    move_object(weapon, Player);
    weapon->equip("blah");
    mapping items = (["Primary Weapon":(["type":"35;1", "data" : "Sword of Blah"])]);

    ExpectTrue(Player->executeCommand("inventory -v"));
    ExpectEq(BuildInventoryString(items, 0, 1), Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void InventoryShowsCorrectAmountOfMoney()
{
    Player->addMoney(123456);
    ExpectTrue(Player->executeCommand("inventory"));
    ExpectSubStringMatch("123456", Player->caughtMessage());
    ExpectEq(BuildInventoryString(([])), Player->caughtMessage());
}