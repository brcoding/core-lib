//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
#include "/lib/dictionaries/regions/building-layouts.h"
#include "/lib/dictionaries/regions/floor-plans.h"
#include "/lib/dictionaries/regions/region-types.h"
#include "/lib/dictionaries/regions/settlements.h"
#include "/lib/modules/secure/regions.h"

private string FeaturePrefix = "/lib/environment/features/";

private mapping WeightedFeatures = ([]);
private mapping WeightedEncounters = ([]);

private string *availableDirections = ({ "north", "south", "east", "west",
    "northwest", "northeast", "southwest", "southeast" });

private string *buildingColors = ({ "wood building", "stone building" });

/////////////////////////////////////////////////////////////////////////////
public nomask int isValidRegionType(string type)
{
    return member(RegionTypes, type);
}

/////////////////////////////////////////////////////////////////////////////
public nomask int isValidRegion(object region)
{
    int ret = 0;
    if (objectp(region) &&
        member(inherit_list(region), "lib/environment/region.c") > -1)
    {
        ret = isValidRegionType(region->regionType());
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask mapping setTerrain(mapping room, mapping roomInput)
{
    if (member(roomInput, "terrain"))
    {
        room["terrain"] = roomInput["terrain"];
    }
    else
    {
        room["interior"] = roomInput["interior"];
    }
    return room;
}

/////////////////////////////////////////////////////////////////////////////
private nomask mapping setExits(mapping room, mapping data, object region)
{
    room["exits"] = ([]);
    room["buildings"] = ([]);

    foreach(string direction in m_indices(data["exits"]))
    {
        if (member(data, "buildings") && member(data["buildings"], direction))
        {
            object building = load_object(data["buildings"][direction]);
            if(building)
            {
                object interior = building->generateInterior(
                    direction, data["x"], data["y"]);

                room["buildings"][direction] = ([
                    "exit to": direction,
                    "building": data["buildings"][direction],
                    "region": interior,
                    "entry point": interior ? 
                        interior->getEntryCoordinates() : "0x0",
                ]);
            }
        }
        else
        {
            room["exits"][direction] = ([
                "exit to": data["exits"][direction],
                "path type": "/lib/environment/features/paths/path.c",
                "region": region
            ]);
        }
    }
    return room;
}


/////////////////////////////////////////////////////////////////////////////
private nomask void createWeightedFeatureList(string featureType,
    mapping features)
{
    WeightedFeatures[featureType] = ({});

    foreach(string feature in m_indices(features))
    {
        for (int i = 0; i < features[feature]; i++)
        {
            WeightedFeatures[featureType] += ({ feature });
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask void createWeightedEncounterList(string regionType,
    mapping encounters)
{
    WeightedEncounters[regionType] = ({});

    foreach(string encounter in m_indices(encounters))
    {
        for (int i = 0; i < encounters[encounter]; i++)
        {
            WeightedEncounters[regionType] += ({ encounter });
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask mapping generateElements(string regionType, mapping items)
{
    mapping ret = ([]);

    if (sizeof(items))
    {
        int numFeatures = 1 + random(3);
        string direction = availableDirections[random(sizeof(availableDirections))];

        for (int i = 0; i < numFeatures; i++)
        {
            string featureType = m_indices(items)[random(sizeof(items))];

            if (!member(WeightedFeatures, featureType))
            {
                createWeightedFeatureList(featureType, items[featureType]);
            }
            string feature = sprintf("%s%s/%s.c", FeaturePrefix, featureType,
                WeightedFeatures[featureType][
                random(sizeof(WeightedFeatures[featureType]))]);

            if (!member(ret, feature))
            {
                ret[feature] = ({});
            }

            if (member(ret[feature], direction) < 0)
            {
                ret[feature] += ({ direction });
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string *generateEncounters(string regionType, mapping encounters)
{
    string *ret = ({});

    object personaDictionary =
        load_object("/lib/dictionaries/personaDictionary.c");

    mapping personas = personaDictionary->personaBlueprints();

    if (sizeof(encounters))
    {
        if (!member(WeightedEncounters, regionType))
        {
            createWeightedEncounterList(regionType, encounters);
        }

        int possibleEncounters = 3 + random(5);
        for (int i = 0; i < possibleEncounters; i++)
        {
            ret += ({ WeightedEncounters[regionType]
                [random(sizeof(WeightedEncounters[regionType]))] });
        }
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping generateRoomData(object region, mapping data)
{
    mapping ret = 0;

    if (isValidRegion(region))
    {
        ret = ([]);
        mapping roomInput = RegionTypes[region->regionType()] + ([]);

        if (member(data, "terrain") || member(data, "interior"))
        {
            setTerrain(ret, data);
        }
        else
        {
            setTerrain(ret, roomInput);
        }
        setExits(ret, data, region);

        string regionType = region->regionType();

        ret["features"] = generateElements(regionType,
            RegionTypes[regionType]["potential features"]);

        ret["items"] = generateElements(regionType,
            RegionTypes[regionType]["potential items"]);

        ret["room objects"] = ([]);

        ret["creatures"] = (data["room type"] == "room") ?
            generateEncounters(regionType, 
                RegionTypes[regionType]["potential encounters"]) : ([]);

        foreach(string creature in ret["creatures"])
        {
            ret["room objects"][creature] = ([
                "type": "creature",
                "state": "default",
                "is random": 1,
                "probability": 100 / sizeof(ret["creatures"]),
                "quantity": 1
            ]);
        }
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping loadRegion(string enterFrom, string location)
{
    return loadRegionData(enterFrom, location);
}

/////////////////////////////////////////////////////////////////////////////
public nomask void saveRegion(object region)
{
    if (objectp(region) &&
        (member(inherit_list(region), "lib/environment/region.c") > -1))
    {
        saveRegionData(region->regionName(),
            region->regionType(),
            region->xDimension(),
            region->yDimension(),
            region->entryPoint(),
            region->entryDirection(),
            region->rooms() + region->decorators());
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask int canConstructSettlement(object region)
{
    string type = region->regionType();
    int chance = region->settlementChance();

    return region && member(RegionTypes, type) &&
        member(RegionTypes[type], "settlement chance") &&
        (random(100) < ((chance != -1) ? chance :
            RegionTypes[type]["settlement chance"]));
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping constructSettlement(string type)
{
    mapping ret = 0;

    if (member(RegionTypes, type))
    {
        int size = RegionTypes[type]["settlement size"];
        mapping possibleSettlements = filter(Settlements,
            (: $2["size"] <= $3 :), size);

        ret = possibleSettlements[m_indices(possibleSettlements)
            [random(sizeof(possibleSettlements))]];
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping getBuildingLayout(string size)
{
    mapping ret = 0;
    if (member(BuildingLayouts, size))
    {
        mapping possibleBuildings = BuildingLayouts[size];
        string *layouts = m_indices(possibleBuildings);
        string type = layouts[random(sizeof(layouts))];
        ret = possibleBuildings[type] + ([]);

        ret["color"] = buildingColors[random(sizeof(buildingColors))];
        ret["class"] = "building";
        ret["type"] = type;
        ret["size"] = size;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask mapping getMapDecorator(string class, string size, string type,
    string color)
{
    mapping ret = 0;

    switch (class)
    {
        case "building":
        {
            if (member(BuildingLayouts, size) &&
                member(BuildingLayouts[size], type))
            {
                ret = BuildingLayouts[size][type] + ([]);
                break;
            }
        }
    }

    if (ret)
    {
        ret["color"] = color;
        ret["class"] = class;
        ret["type"] = type;
        ret["size"] = size;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string getBuildingEntrance(string building)
{
    return building;
}
