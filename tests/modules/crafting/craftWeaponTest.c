//*****************************************************************************
// Copyright (c) 2018 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/tests/framework/testFixture.c";

object Player;
object Selector;

/////////////////////////////////////////////////////////////////////////////
void Init()
{
    ignoreList += ({ "SetUpSkills", "SetUpInventory", "SetUpResearch",
        "CraftSword", "PopulateSwordData", "getMaterialsOnHand", "__inline_lib_tests_modules_crafting_craftWeaponTest_c_179_0000" });
}

/////////////////////////////////////////////////////////////////////////////
void SetUpSkills()
{
    Player->Wis(50);
    Player->Str(50);
    Player->Int(50);
    Player->addSkillPoints(500);
    Player->advanceSkill("blacksmithing", 20);
    Player->advanceSkill("metal crafting", 10);
    Player->advanceSkill("weapon smithing", 10);
    Player->advanceSkill("chemistry", 10);
    Player->advanceSkill("physics", 10);
    Player->advanceSkill("leatherworking", 20);
    Player->advanceSkill("carpentry", 10);
    Player->advanceSkill("wood crafting", 10);
    Player->advanceSkill("gem crafting", 20);
    Player->advanceSkill("sculpture", 15);
}

/////////////////////////////////////////////////////////////////////////////
void SetUpInventory()
{
    object material = clone_object("/lib/instances/items/materials/metal/admantite.c");
    material->set("quantity", 5);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/admantite.c");
    material->set("quantity", 6);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/steel.c");
    material->set("quantity", 10);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/iron.c");
    material->set("quantity", 3);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/iron.c");
    material->set("quantity", 5);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/wood/koa.c");
    material->set("quantity", 5);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/leather/pegasus-leather.c");
    material->set("quantity", 5);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/gold.c");
    material->set("quantity", 3);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/platinum.c");
    material->set("quantity", 3);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/metal/galvorn.c");
    material->set("quantity", 3);
    move_object(material, Player);

    material = clone_object("/lib/instances/items/materials/crystal/ruby.c");
    material->set("quantity", 5);
    move_object(material, Player);
}

/////////////////////////////////////////////////////////////////////////////
void SetUpResearch()
{
    Player->addResearchPoints(20);
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftCommonMetal.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftGems.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftRareGems.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftUncommonMetal.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftAlloy.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftRareMetal.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftPreciousMetal.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftMythicMetal.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftLeather.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftExoticLeather.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftCommonWood.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftUncommonWood.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/materials/craftRareWood.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/weapons/craftWeapons.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/weapons/swords/craftBasicSwords.c"));
    ExpectTrue(Player->initiateResearch("lib/instances/research/crafting/weapons/swords/craftLongSwords.c"));
}

/////////////////////////////////////////////////////////////////////////////
void CraftSword()
{
    // This method navigates through the crafting menus to generate an
    // appropriate sword for this test.
    command("1", Player);
    command("1", Player);
    command("1", Player);
    command("6", Player);
    command("25", Player);
    command("2", Player);
    command("11", Player);
    command("1", Player);
    command("25", Player);
    command("2", Player);
    command("15", Player);
    command("25", Player);
    command("3", Player);
    command("9", Player);
    command("1", Player);
    command("12", Player);
    command("2", Player);
    command("16", Player);
    command("3", Player);
    command("23", Player);
    command("11", Player);
    command("4", Player);
    command("13", Player);
    command("2", Player);
    command("35", Player);
    command("1", Player);
    command("25", Player);
    command("27", Player);
}

/////////////////////////////////////////////////////////////////////////////
void PopulateSwordData(object sword)
{
    sword->set("material", "admantite");
    sword->set("crafting materials", ([
        "blade": ([ "description": "a broad, flat, metal blade with parallel edges and a lenticular cross-section. The fuller is narrow and runs half of the length of the blade, ending in a rounded point.", 
                    "metal": "admantite", 
                    "type": "Type XIII",
                    "value": 110 
        ]), 
        "crossguard": ([ "crystal": "ruby", 
                    "description": "an ornate metal knuckleguard that has been sculpted to appear as though a dracolich with crystal eyes is protecting the user's hand.", 
                    "metal": "galvorn", 
                    "type": "Dracolich Form", 
                    "value": 325 
        ]), 
        "hilt": ([ "description": "a hilt of metal covered with a slightly ovular grip made out of wood and wrapped in spiraled metal wire.", 
                    "leather": "pegasus leather", 
                    "metal": "gold", 
                    "type": "Spiral Grip", "value": 15, 
                    "wood": "koa" 
        ]), 
        "pommel": ([ "crystal": "ruby", 
                    "description": "an exquisite metal pommel that has been intricately sculpted to resemble a dragon's talon. Clutched in its grip is a beautifully cut crystal.", 
                    "metal": "platinum", 
                    "type": "Dragon Talon", 
                    "value": 50
        ])
    ]));
    command("1", Player);
    command("25", Player);
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping getMaterialsOnHand()
{
    mapping ret = ([]);
    object *inventory = filter(deep_inventory(Player),
        (: (member(inherit_list($1), "lib/items/material.c") > -1) :));

    if (sizeof(inventory))
    {
        foreach(object item in inventory)
        {
            string type = item->query("class");
            string material = item->query("blueprint");
            if (!member(ret, type))
            {
                ret[type] = ([]);
            }
            if (!member(ret[type], material))
            {
                ret[type][material] = 0;
            }
            ret[type][material] += item->query("quantity");
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
void Setup()
{
    Selector = clone_object("/lib/modules/crafting/selectMaterialsSelector.c");
    Selector->setItem("long sword");
    Selector->setType("weapons");
    Selector->setSubType("swords");

    Player = clone_object("/lib/tests/support/services/mockPlayer.c");
    Player->Name("bob");
    Player->addCommands();

    SetUpSkills();
    SetUpResearch();
    SetUpInventory();
    move_object(Selector, Player);
    move_object(Player, "/lib/tests/support/environment/fakeEnvironment.c");
}

/////////////////////////////////////////////////////////////////////////////
void CleanUp()
{
    destruct(Player);
    destruct(Selector);
}

/////////////////////////////////////////////////////////////////////////////
void CraftSelectedOptionBecomesEnabledWhenAllCriteriaMet()
{
    Selector->initiateSelector(Player);
    ExpectSubStringMatch("31mCraft Selected Long sword",
        Player->caughtMessage());

    CraftSword();

    ExpectSubStringMatch("32mCraft Selected Long sword",
        Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void ChoosingCraftSelectedFailsWhenDisabled()
{
    Selector->initiateSelector(Player);
    string priorMessage = Player->caughtMessage();

    command("5", Player);
    ExpectEq(priorMessage, Player->caughtMessage());
}

/////////////////////////////////////////////////////////////////////////////
void CraftingASwordGeneratesTheCorrectItemAndReducesMaterials()
{
    Selector->initiateSelector(Player);

    ExpectFalse(present("long sword", Player));
    ExpectEq((["crystal": (["ruby": 5]),
        "leather": (["pegasus leather": 5]),
        "metal": (["admantite": 11, 
                   "galvorn": 3,
                   "gold": 3,
                   "iron": 8,
                   "platinum": 3,
                   "steel": 10 ]),
        "wood": (["koa": 5]) ]), getMaterialsOnHand());

    object sword = Player->itemBeingCrafted();
    ExpectTrue(sword, "Crafting item has been set");
    PopulateSwordData(sword);
    command("5", Player);

    ExpectFalse(Player->itemBeingCrafted(), "Crafting item has been reset");
    ExpectEq(sword, present("long sword", Player));

    ExpectEq((["crystal":(["ruby":2]),
        "leather" : (["pegasus leather":4]),
        "metal" : (["admantite":5,
            "galvorn" : 1,
            "gold" : 2,
            "iron" : 8,
            "platinum" : 2,
            "steel" : 10
        ]),
        "wood": (["koa":4])]), getMaterialsOnHand());
    ExpectEq(40, sword->query("craftsmanship"));
    ExpectEq(2, load_object("/lib/dictionaries/materialsDictionary.c")->getMaterialCraftsmanshipBonus(sword));
}

/////////////////////////////////////////////////////////////////////////////
void CraftingIsNotAffectedByNotApplicableLimitedByCraftingTypeResearch()
{
    ExpectTrue(Player->initiateResearch("lib/tests/support/research/limitedByCraftingResearch.c"));
    Selector->setItem("dagger");
    Selector->setType("weapons");
    Selector->setSubType("daggers");

    ExpectEq(10, Player->getSkill("weapon smithing"));
    Selector->initiateSelector(Player);

    object sword = Player->itemBeingCrafted();
    PopulateSwordData(sword);

    ExpectEq(10, Player->getSkill("weapon smithing"));
}