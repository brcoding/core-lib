//*****************************************************************************
// Copyright (c) 2018 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************

private object Player = 0;

private string *selectors = ({
    "/lib/modules/creation/genderSelector.c",
    "/lib/modules/creation/raceSelector.c",
    "/lib/modules/creation/subraceSelector.c",
    "/lib/modules/creation/hairSelector.c",
    "/lib/modules/creation/eyeSelector.c",
    "/lib/modules/creation/attributeSelector.c",
    "/lib/modules/creation/skillsSelector.c",
    "/lib/modules/creation/traitSelector.c"
});

/////////////////////////////////////////////////////////////////////////////
private nomask void movePlayerToStart(object player)
{
    object startingLocation = 0;
    catch (startingLocation = load_object(player->savedLocation()));

    if (startingLocation)
    {
        move_object(player, startingLocation);
    }
    else
    {
        move_object(player, "/room/city/central_park.c");
        tell_object(player, "Doh! The room you were last in during your "
            "previous session is broken.\nYou have been moved to a different "
            "location.\n");
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask void onRestoreSucceeded(object caller)
{
    caller->unregisterEvent(this_object());
    caller->updateLoginTime();
    movePlayerToStart(caller);
    destruct(this_object());
}

/////////////////////////////////////////////////////////////////////////////
private nomask void initiateSelector()
{
    if (sizeof(selectors) && Player)
    {
        string selector = selectors[0];
        selectors -= ({ selector });

        object selectorObj = clone_object(selector);
        move_object(selectorObj, Player);
        selectorObj->registerEvent(this_object());
        selectorObj->initiateSelector(Player);
    }
    else if (Player)
    {
        object backgroundDictionary = 
            load_object("/lib/dictionaries/backgroundDictionary.c");

        Player->hitPoints(Player->maxHitPoints());
        Player->spellPoints(Player->maxSpellPoints());
        Player->staminaPoints(Player->maxStaminaPoints());
        Player->save();
        tell_object(Player, format("\x1b[0;32;1mCharacter creation is now complete"
            " and you have been moved to your starting location.\x1b[0m "
            "\x1b[0;32mIf you need additional information to get started or for "
            "getting around in the game, you can use the 'help' command. Enjoy "
            "your time here and don't hesitate to contact any of the game "
            "administrators with your questions or comments.\n\x1b[0m\n", 78));

        backgroundDictionary->initiateBackground(Player);
        destruct(this_object());
    }
    else
    {
        destruct(this_object());
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask void onRestoreFailed(object caller)
{
    Player = caller;
    Player->hitPoints(30);
    Player->spellPoints(30);
    Player->staminaPoints(30);

    initiateSelector();
}

/////////////////////////////////////////////////////////////////////////////
public nomask void onSelectorCompleted(object caller)
{
    caller->cleanUp();
    initiateSelector();
}
