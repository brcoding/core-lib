//*****************************************************************************
// Copyright (c) 2020 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
virtual inherit "/lib/items/material.c";

/////////////////////////////////////////////////////////////////////////////
public void reset(int arg) 
{
    if (!arg) 
    {
        set("name", "Cashmere");
        set("short", "Cashmere");
        set("aliases", ({ "cloth", "textile", "cashmere" }));
        set("blueprint", "cashmere");
    }
}
