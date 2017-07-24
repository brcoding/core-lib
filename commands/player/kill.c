//*****************************************************************************
// Copyright (c) 2017 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/commands/baseCommand.c";

/////////////////////////////////////////////////////////////////////////////
public nomask void init()
{
    addCommandTemplate("kill ##Target##");
}

/////////////////////////////////////////////////////////////////////////////
public nomask int execute(string command, object initiator)
{
    int ret = 0;

    object target = getTarget(initiator, command);

    if (target && canExecuteCommand(command) && !initiator->spellAction() &&
        (target->onKillList() && !target->isRealizationOf("player")) ||
        (target->isRealizationOf("player") && initiator->isRealizationOf("player") &&
            target->onKillList() && initiator->onKillList()))
    {
        ret = 1;
        initiator->attack(target);
        initiator->spellAction(1);
        tell_object(initiator, sprintf("You attack %s.\n", target->Name()));
        say(sprintf("%s attacks %s.\n", initiator->Name(), target->Name()));
    }
    return ret;
}