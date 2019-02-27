//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************

protected mapping descriptionData = ([ ]);
protected int isLegacy = 0;
protected int LightLevelWhenDetailsVisible = 6;

protected int suppressAction = 0; 
private string elementName = 0;
private string State = "default";

/////////////////////////////////////////////////////////////////////////////
protected object environmentDictionary()
{
    return load_object("/lib/dictionaries/environmentDictionary.c");
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs string Name(string newName)
{
    if (newName && stringp(newName))
    {
        elementName = newName;
    }
    return elementName;
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs string currentState(string newState)
{
    if (newState && stringp(newState))
    {
        State = newState;
    }
    return State;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string *aliases(string state)
{
    if (!state)
    {
        state = currentState();
    }

    string *ret = ({ elementName });
    if (member(descriptionData[state], "aliases"))
    {
        ret += descriptionData[state]["aliases"];
    }
    return m_indices(mkmapping(ret - ({ 0 })));
}

/////////////////////////////////////////////////////////////////////////////
public nomask string *states()
{
    return m_indices(descriptionData) + ({});
}

/////////////////////////////////////////////////////////////////////////////
public string Type()
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
public void Setup()
{
}

/////////////////////////////////////////////////////////////////////////////
public nomask void reset(int arg)
{
    if (!arg)
    {
        if (!elementName)
        {
            Setup();
        }

        if (environmentDictionary() && stringp(elementName) &&
            !environmentDictionary()->isValidEnvironmentItem(elementName))
        {
            environmentDictionary()->registerElement(program_name(this_object()));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask string parseSeasonDescription(string message, mapping data)
{
    string ret = message;
    string season = environmentDictionary()->season();
    if (member(data, season) && environmentDictionary()->ambientLight() > 5)
    {
        ret += data[season][random(sizeof(data[season]))];
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string parseTimeOfDayDetails(string message, mapping data)
{
    string ret = message;
    string season = environmentDictionary()->season();
    string timeOfDay = environmentDictionary()->timeOfDay();
    if (member(data, timeOfDay) && member(data[timeOfDay], season))
    {
        ret += data[timeOfDay][season][random(sizeof(data[timeOfDay][season]))];
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string parseWeatherDetails(string message, mapping data)
{
    return message;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask void suppressEntryMessage()
{
    suppressAction = 1;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int displayActionText()
{
    return !suppressAction;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string parseEntryAction(string message, mapping data)
{
    return !displayActionText() ? message : environmentDictionary()->getEntryMessage() + " " +
        message + ".";
}

/////////////////////////////////////////////////////////////////////////////
private nomask string parseAdjectives(string message, mapping data)
{
    string ret = message;

    if (member(data, "adjectives") && sizeof(data["adjectives"]) &&
        sizeof(regexp(({ message}), "##Adjective##")))
    {
        ret = regreplace(ret, "##Adjective##( *)", 
            (environmentDictionary()->ambientLight() > 5) ?
            data["adjectives"][random(sizeof(data["adjectives"]))] + "\\1" : "", 1);
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected int displayWeatherDetails()
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
protected int displayEntryMessage()
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs string parseTemplate(string template, mapping data)
{
    string ret = parseSeasonDescription(template, data);
    ret = parseTimeOfDayDetails(ret, data);

    if (displayWeatherDetails())
    {
        ret = parseWeatherDetails(ret, data);
    }
    if (displayEntryMessage())
    {
        ret = parseEntryAction(ret, data);
    }
    ret = parseAdjectives(ret, data);
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs string description(string state)
{
    string ret = 0;

    if (!state)
    {
        state = currentState();
    }

    if (member(descriptionData, state) && member(descriptionData[state],
        "template"))
    {
        ret = parseTemplate(descriptionData[state]["template"], descriptionData[state]);
    }
    else if (member(descriptionData, "default") && 
        member(descriptionData["default"], "template"))
    {
        ret = parseTemplate(descriptionData["default"]["template"],
            descriptionData["default"]);
    }

    if (displayActionText() && !ret)
    {
        raise_error(sprintf("ERROR in baseFeature.c: The description for "
            "the %s state does not exist.\n", state));
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string long(int brief)
{
    string ret = 0;
    string state = currentState();

    string introText = isLegacy ? "" : "You see ";
    if (member(descriptionData, state) && member(descriptionData[state],
        "item template"))
    {
        ret = introText +
            parseTemplate(descriptionData[state]["item template"],
                descriptionData[state]) + ".\n";
    }
    else if (member(descriptionData, "default") && 
        member(descriptionData["default"], "item template"))
    {
        ret = introText +
            parseTemplate(descriptionData["default"]["item template"],
                descriptionData["default"]) + ".\n";
    }

    if (!ret)
    {
        raise_error(sprintf("ERROR in baseFeature.c: The item details for "
            "the %s state does not exist.\n", state));
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addAdjectives(string *list, string state)
{
    if (!state)
    {
        state = "default";
    }

    if (!member(descriptionData, state))
    {
        descriptionData[state] = ([]);
    }
    descriptionData[state]["adjectives"] = list;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addDescriptionTemplate(string template, string state)
{
    if (!state)
    {
        state = "default";
    }

    if (!member(descriptionData, state))
    {
        descriptionData[state] = ([]);
    }
    descriptionData[state]["template"] = template;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addItemTemplate(string template, string state)
{
    if (!state)
    {
        state = "default";
    }

    if (!member(descriptionData, state))
    {
        descriptionData[state] = ([]);
    }
    descriptionData[state]["item template"] = template;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addAlias(string alias, string state)
{
    if (!state)
    {
        state = "default";
    }

    if (!member(descriptionData, state))
    {
        descriptionData[state] = ([]);
    }
    if (!member(descriptionData[state], "aliases"))
    {
        descriptionData[state]["aliases"] = ({ });
    }
    descriptionData[state]["aliases"] = 
        m_indices(mkmapping(descriptionData[state]["aliases"] + ({ alias })));
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addSeasonDescription(string season, string *list, string state)
{
    if (environmentDictionary()->isValidSeason(season))
    {
        if (!state)
        {
            state = "default";
        }

        if (!member(descriptionData, state))
        {
            descriptionData[state] = ([]);
        }
        descriptionData[state][season] = list;
    }
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addTimeOfDayDescription(string period, string *list, string state, string season)
{
    if (environmentDictionary()->isValidTimeOfDay(period))
    {
        if (!state)
        {
            state = "default";
        }

        if (!member(descriptionData, state))
        {
            descriptionData[state] = ([]);
        }
        if (!member(descriptionData[state], period))
        {
            descriptionData[state][period] = ([]);
        }
        if (environmentDictionary()->isValidSeason(season))
        {
            descriptionData[state][period][season] = list;
        }
        else
        {
            foreach(string item in environmentDictionary()->seasons())
            {
                descriptionData[state][period][item] = list;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask varargs mapping setSourceOfLightBySeason(int magnitude, string season)
{
    mapping data = ([]);
    if (environmentDictionary()->isValidSeason(season))
    {
        data[season] = magnitude;
    }
    else
    {
        foreach(string item in environmentDictionary()->seasons())
        {
            data[item] = magnitude;
        }
    }
    return data;
}

/////////////////////////////////////////////////////////////////////////////
private nomask varargs mapping setSourceOfLightByTime(int magnitude, string period, string season)
{
    mapping data = ([]);
    if (environmentDictionary()->isValidTimeOfDay(period))
    {
        data[period] = setSourceOfLightBySeason(magnitude, season);
    }
    else
    {
        foreach(string timeOfDay in environmentDictionary()->timesOfDay())
        {
            data[timeOfDay] = setSourceOfLightBySeason(magnitude, season);
        }
    }
    return data;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void lightLevelWhenVisible(int value)
{
    LightLevelWhenDetailsVisible = value;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void addSourceOfLight(int magnitude, string state, string period, string season)
{
    string *states = ({ });
    if (state && (state != ""))
    {
        states = ({ state });
    }
    else
    {
        states = states();

        if (!sizeof(states))
        {
            states = ({ "default" });
        }
    }
    if (!member(descriptionData, "light"))
    {
        descriptionData["light"] = ([]);
    }

    if (sizeof(states))
    {
        foreach(string stateItem in states)
        {
            descriptionData["light"][stateItem] = 
                setSourceOfLightByTime(magnitude, period, season);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs int isSourceOfLight(string state)
{
    int ret = 0;

    if (!state || (member(descriptionData, "light") &&
        !member(descriptionData["light"], state)))
    {
        state = "default";
    }

    string timeOfDay = environmentDictionary()->timeOfDay();
    string season = environmentDictionary()->season();

    if (member(descriptionData, "light") &&
        member(descriptionData["light"], state) &&
        member(descriptionData["light"][state], timeOfDay) &&
        member(descriptionData["light"][state][timeOfDay], season))
    {
        ret = descriptionData["light"][state][timeOfDay][season];
    }
    return ret;
}
