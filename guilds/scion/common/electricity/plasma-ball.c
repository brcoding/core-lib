//*****************************************************************************
// Copyright (c) 2020 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/modules/research/instantaneousActiveResearchItem.c";

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
        instantaneousActiveResearchItem::reset(arg);
        addSpecification("name", "Plasma Ball");
        addSpecification("source", "Scion of Dhuras Guild");
        addSpecification("description", "This research provides the user with the "
            "knowledge of the plasma ball technique. By means of this, the "
            "Scion is able to use their weapon as a conduit for emitting a ball "
            "of plasma at a foe.");
        Setup();

        addPrerequisite(sprintf("guilds/scion/paths/%s/root.c", WeaponType),
            (["type":"research"]));
        addPrerequisite(sprintf("guilds/scion/paths/%s/electricity/lightning-blast.c", WeaponType),
            (["type":"research"]));
        addPrerequisite("level",
            (["type":"level",
                "guild": "Scion of Dhuras",
                "value": 29
            ]));

        addSpecification("scope", "targeted");
        addSpecification("research type", "points");
        addSpecification("research cost", 1);
        addSpecification("spell point cost", 200);

        addSpecification("damage hit points", ({ ([
                "probability":90,
                "base damage" : 100,
                "range" : 200
            ]),
            ([
                "probability":10,
                "base damage" : 200,
                "range" : 500
            ])
        }));
        addSpecification("damage spell points", ({ ([
                "probability":90,
                "base damage" : 50,
                "range" : 100
            ]),
            ([
                "probability": 10,
                "base damage": 100,
                "range" : 200
            ])
        }));

        addSpecification("damage type", "electricity");

        addSpecification("modifiers", ({ 
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/electricity/static-charge.c", WeaponType),
                "name" : "Static Charge",
                "formula" : "additive",
                "base value" : 10,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/electricity/electrostatic-induction.c", WeaponType),
                "name" : "Electrostatic Induction",
                "formula" : "additive",
                "base value" : 10,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/electricity/ionization.c", WeaponType),
                "name" : "Ionization",
                "formula" : "additive",
                "base value" : 10,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/electricity/enhanced-discharge.c", WeaponType),
                "name" : "Enhanced Discharge",
                "formula" : "additive",
                "base value" : 20,
                "rate": 1.0
            ]),
            ([
                "type":"research",
                "research item": sprintf("guilds/scion/paths/%s/electricity/plasma-eruption.c", WeaponType),
                "name" : "Plasma Eruption",
                "formula" : "additive",
                "base value" : 30,
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
                "name" : "elemental air",
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

        addSpecification("cooldown", 100);
        addSpecification("event handler", "plasmaBallEvent");
        addSpecification("command template", "plasma ball [at ##Target##]");
        addSpecification("use ability message",  "A large, churning ball "
            "of plasma erupts from ##InitiatorPossessive::Name## "
            "##InitiatorWeapon## and flies into ##TargetName##.");
    }
}
