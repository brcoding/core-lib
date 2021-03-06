//*****************************************************************************
// Copyright (c) 2020 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/modules/traits/baseTrait.c";

/////////////////////////////////////////////////////////////////////////////
public void reset(int arg)
{
    if (!arg)
    {
        addSpecification("type", "personality");
        addSpecification("name", "disloyal");
        addSpecification("description", "You show a decided lack of devotion "
            "to others.");
        addSpecification("root", "disloyal");
        addSpecification("opposing root", "loyal");
        addSpecification("opinion", -15);
        addSpecification("opposing opinion", -15);
        "baseTrait"::reset(arg);
    }
}
