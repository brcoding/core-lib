//*****************************************************************************
// Copyright (c) 2020 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/modules/research/persistedActiveResearchItem.c";

protected string WeaponType = "ERROR";
protected string WeaponSkill = "unarmed";

/////////////////////////////////////////////////////////////////////////////
protected void Setup()
{
}

/////////////////////////////////////////////////////////////////////////////
public void reset(int arg)
{
    if (!arg)
    {
        persistedActiveResearchItem::reset(arg);
        addSpecification("name", "Bloodswarm");
        addSpecification("source", "Scion of Dhuras Guild");
        addSpecification("description", "This research provides the user with the "
            "knowledge of the bloodswarm technique. By means of this, the "
            "Scion is able to use their weapon as a conduit for emitting a "
            "powerful negative energy storm that harries a foe.");
        Setup();

        addPrerequisite(sprintf("guilds/scion/paths/%s/root.c", WeaponType),
            (["type":"research"]));
        addPrerequisite(sprintf("guilds/scion/paths/%s/blood/enervating-barrier.c", WeaponType),
            (["type":"research"]));
        addPrerequisite("level",
            (["type":"level",
                "guild": "Scion of Dhuras",
                "value": 33
            ]));

        addSpecification("modifiers", ({ 
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/blood/malefic-barrier.c", WeaponType),
                "name" : "Malefic Barrier",
                "formula" : "additive",
                "base value" : 2,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/blood/corrupting-barrier.c", WeaponType),
                "name" : "Corrupting Barrier",
                "formula" : "additive",
                "base value" : 2,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/blood/nefarious-barrier.c", WeaponType),
                "name" : "Nefarious Barrier",
                "formula" : "additive",
                "base value" : 5,
                "rate": 1.0
            ]),
            ([
                "type":"skill",
                "name" : WeaponSkill,
                "formula" : "additive",
                "rate" : 1.05
            ]),
            ([
                "type":"skill",
                "name" : "blood",
                "formula" : "additive",
                "rate" : 1.10
            ]),
            ([
                "type":"skill",
                "name" : "spellcraft",
                "formula" : "logarithmic",
                "rate" : 1.10
            ]),
            ([
                "type":"level",
                "name" : "level",
                "formula" : "logarithmic",
                "rate" : 1.10
            ]),
            ([
                "type":"attribute",
                "name" : "intelligence",
                "formula" : "additive",
                "rate" : 1.05
            ]) 
        }));

        addSpecification("scope", "targeted");
        addSpecification("research type", "points");
        addSpecification("research cost", 1);
        addSpecification("cooldown", 240);
        addSpecification("spell point cost", 175);
        addSpecification("duration", 90);
        addSpecification("event handler", "bloodswarmEvent");
        addSpecification("command template", "bloodswarm [at ##Target##]");
        addSpecification("penalty to resist undead", 50);
        addSpecification("penalty to resist physical", 25);
        addSpecification("apply enfeebled", 1);
        addSpecification("apply slow", 1);

        addSpecification("use ability message", "A wave of garish negative energy erupts "
            "from ##InitiatorPossessive::Name## ##InitiatorWeapon## and engulfs "
            "##TargetName##.");
    }
}
