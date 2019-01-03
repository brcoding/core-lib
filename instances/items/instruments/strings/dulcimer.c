//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
virtual inherit "/lib/items/instrument.c";

/////////////////////////////////////////////////////////////////////////////
public void reset(int arg) 
{
    if (!arg) 
    {
        set("name", "Dulcimer");
        set("short", "Dulcimer");
        set("aliases", ({ "dulcimer", "strings", "instrument" }));
        set("blueprint", "dulcimer");
    }
}
