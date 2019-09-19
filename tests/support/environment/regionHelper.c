//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/environment/region.c";

private int roomCount = 5;

/////////////////////////////////////////////////////////////////////////////
public int *EntryLocation()
{
    return entry + ({});
}

/////////////////////////////////////////////////////////////////////////////
public int generatedRoomCount()
{
    return sizeof(filter(rooms, (: $1["room type"] != "path" :)));
}

/////////////////////////////////////////////////////////////////////////////
public mapping *rooms()
{
    return rooms + ({});
}

/////////////////////////////////////////////////////////////////////////////
public void setRoomCount(int value)
{
    roomCount = value;
}

/////////////////////////////////////////////////////////////////////////////
protected int getRoomCount()
{
    return roomCount;
}

/////////////////////////////////////////////////////////////////////////////
public mapping addTestRoom(int x, int y, mapping data)
{
    if (!sizeof(grid))
    {
        createEmptyGrid(MaxX, MaxY);
    }
    grid[x][y] = data;
    generateRoomDetails(data);

    return data;
}
