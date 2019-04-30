//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/modules/traits/baseTrait.c";

/////////////////////////////////////////////////////////////////////////////
public void reset(int arg)
{
    if (!arg)
    {
        addSpecification("type", "personality");
        addSpecification("name", "irritable");
        addSpecification("description", "You're cranky. There are a lot of "
            "things that annoy you. Most of them talk.");
        addSpecification("root", "harsh");
        addSpecification("opposing root", "kind");
        addSpecification("opinion", -5);
        addSpecification("opposing opinion", -5);
        "baseTrait"::reset(arg);
    }
}
