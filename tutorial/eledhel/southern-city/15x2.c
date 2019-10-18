//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/environment/environment.c";

/////////////////////////////////////////////////////////////////////////////
public void Setup()
{
    setTerrain("/lib/environment/terrain/city.c");
    addBuilding("/lib/environment/buildings/homes/large-limestone-house.c",
        "north");

    addExit("west", "/lib/tutorial/eledhel/southern-city/16x2.c");
    addExit("east", "/lib/tutorial/eledhel/southern-city/14x2.c");
}