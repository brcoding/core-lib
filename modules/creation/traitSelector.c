//*****************************************************************************
// Copyright (c) 2017 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/modules/creation/baseSelector";

private int TotalPoints;
private int TestTaken = 0;
private string *UndoDetails = ({ });
private object SubselectorObj;

/////////////////////////////////////////////////////////////////////////////
public nomask void reset(int arg)
{
    if(!arg)
    {
        Description = "From this menu, you can choose your character's traits";
        Data = ([
            "1":([
                "name": "Take Personality Test",
                "type": "personality",
                "description": "This option takes you through a series of questions that\n"
                    "are used to identify your character's personality.\n"
            ]),
            "2":([
                "name": "Educational Traits",
                    "type" : "educational",
                "description": "Educational traits are learned traits - those that\n"
                    "have been cultivated both through formal learning as well as\n"
                    "those uncovered as a result of either success or failure to learn.\n"
            ]),
            "3":([
                "name": "Genetic Traits",
                    "type" : "genetic",
                    "description": "Positive traits are those traits that provide you with additional\n"
                    "starting abilities and/or bonuses to your character's skills,\n"
                    "attributes, or abilities.\n"
            ])
        ]);
    }
}

/////////////////////////////////////////////////////////////////////////////
protected nomask void setUpUserForSelection()
{
    object racialDictionary = load_object("/lib/dictionaries/racialDictionary.c");

    TotalPoints = racialDictionary->backgroundTraitPoints(User->Race());
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string displayDetails(string choice)
{
    string ret = "";

    if ((Data[choice]["type"] == "personality") && TestTaken)
    {
        ret = "[0;34;1m  (Completed)[0m";
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string additionalInstructions()
{
    string ret = "";
    if (TotalPoints > 0)
    {
        ret += sprintf("You have %d trait points left to assign.\n", TotalPoints);
    }
    if (!TestTaken)
    {
        ret += "You have not yet taken the personality test.\n";
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask int processSelection(string selection)
{
    int ret = -1;
    if (User)
    {
        ret = (TotalPoints == 0 && TestTaken);
        if (!ret)
        {
            if (TestTaken && (Data[selection]["type"] == "personality"))
            {
                tell_object(User, "You have already taken the personality test.\n");
            }
            else
            {
                string selector = sprintf("/lib/modules/creation/%sTraitSelector.c",
                    lower_case(Data[selection]["type"]));

                SubselectorObj = clone_object(selector);
                move_object(SubselectorObj, User);
                SubselectorObj->registerEvent(this_object());
                SubselectorObj->initiateSelector(User);
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask void onSelectorCompleted(object caller)
{
    if (caller->selection())
    {
        if (stringp(caller->selection()))
        {
            UndoDetails += ({ caller->selection() });
        }
        TotalPoints -= caller->cost();
        TestTaken = caller->testTaken();
    }
    caller->cleanUp();

    if (TotalPoints || !TestTaken)
    {
        tell_object(User, displayMessage());
    }
    else
    {
        notify("onSelectorCompleted");
    }
}

/////////////////////////////////////////////////////////////////////////////
protected nomask int suppressMenuDisplay()
{
    return objectp(SubselectorObj);
}

/////////////////////////////////////////////////////////////////////////////
protected nomask void undoSelection(string selection)
{
    if (User && sizeof(UndoDetails))
    {
        string traitToRemove = UndoDetails[sizeof(UndoDetails) - 1];

        if (sizeof(UndoDetails) > 1)
        {
            UndoDetails = UndoDetails[0..(sizeof(UndoDetails) - 2)];
        }
        else
        {
            UndoDetails = ({});
        }
        User->removeTrait(traitToRemove);
        TotalPoints += load_object("/lib/dictionaries/traitsDictionary.c")->
            traitObject(traitToRemove)->query("cost");
    }
}
