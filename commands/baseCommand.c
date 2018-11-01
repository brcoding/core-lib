//*****************************************************************************
// Copyright (c) 2018 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
#include <mtypes.h>

private string MaterialAttributes = "lib/modules/materialAttributes.c";
private string MessageParser = "/lib/core/messageParser.c";

protected string *commands = ({});
protected int SplitCommands;
protected string CommandType = "general";
protected object configuration = load_object("/lib/dictionaries/configurationDictionary.c");

/////////////////////////////////////////////////////////////////////////////
public nomask string *commandList()
{
    return commands + ({});
}

/////////////////////////////////////////////////////////////////////////////
private nomask string prepCommandRegExp(string command)
{
    string ret = regreplace(command, "\\] *\\[", ")*( ", 1);
    ret = regreplace(ret, " \\[(.+)\\]", "( \\1)\*", 1);

    return "^" + ret + "$";
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs string commandRegExp(string commandToParse)
{
    string ret = 0;

    if(sizeof(commands))
    {
        ret = "(";

        if (commandToParse && (member(commands, commandToParse) > -1))
        {
            ret += prepCommandRegExp(commandToParse);
        }
        else
        {
            foreach(string command in commands)
            {
                if (sizeof(ret) > 1)
                {
                    ret += "|";
                }
                ret += prepCommandRegExp(command);
            }
        }
        ret += ")";

        ret = regreplace(ret, "##(Target|Environment|Item|Value)##", ".+", 1);
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int canExecuteCommand(string passedCommand)
{
    int ret = 0;

    if(passedCommand && stringp(passedCommand))
    {
        string commandRegexp;
        if (SplitCommands)
        {
            foreach(string command in commands)
            {
                commandRegexp = commandRegExp(command);
                if (commandRegexp)
                {
                    ret = sizeof(regexp(({ passedCommand }), commandRegexp));
                    if (ret)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            commandRegexp = commandRegExp();

            if (commandRegexp)
            {
                ret = sizeof(regexp(({ passedCommand }), commandRegexp));
            }
        }
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string commandString(string passedCommand)
{
    string ret = 0;

    if(sizeof(commands))
    {
        foreach(string command in commands)
        {
            string commandRegexp = prepCommandRegExp(command);
            string commandCheck = regreplace(commandRegexp, "##(Target|Environment|Item|Value)##", ".+", 1);

            if (sizeof(regexp(({ passedCommand }), commandCheck)))
            {
                ret = regreplace(commandRegexp, "##(Target|Environment|Item|Value)##", "", 1);
                ret -= "$";
                break;
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask object getTarget(object owner, string command)
{
    object ret = 0;
    string template = commandString(command);

    if (command && stringp(command) && template && stringp(template) &&
        environment(owner))
    {
        string *targetId = regexplode(command, template);

        if (sizeof(targetId) == 3)
        {
            ret = present(targetId[2], environment(owner)) ||
                present(targetId[2], owner);

            if (!ret && environment(owner)->isEnvironmentalElement(targetId[2]))
            {
                ret = environment(owner)->getEnvironmentalElement(targetId[2]);
            }
            else if(!ret && (this_object()->query("scope") == "targeted") &&
                (targetId[2] == ""))
            {
                ret = owner;
            }
        }
    }

    if ((ret == owner) && this_object()->query("damage type") &&
        !this_object()->query("is beneficial"))
    {
        ret = owner->getTargetToAttack();
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string getTargetString(object owner, string command)
{
    string ret = 0;
    string template = commandString(command);

    if (command && stringp(command) && template && stringp(template))
    {
        string *targetId = regexplode(command, template);

        if (sizeof(targetId) == 3)
        {
            ret = targetId[2];
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public int execute(string command, object initiator)
{
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int addCommandTemplate(string command)
{
    int ret = 0;

    if (member(commands, command) == -1)
    {
        commands += ({ command });
        ret = 1;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string commandType()
{
    return CommandType;
}

/////////////////////////////////////////////////////////////////////////////
private nomask object messageParser()
{
    return load_object(MessageParser);
}

/////////////////////////////////////////////////////////////////////////////
private nomask int isValidLiving(object livingCheck)
{
    return (livingCheck && objectp(livingCheck) && 
            (member(inherit_list(livingCheck), MaterialAttributes) > -1));
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string formatText(string text, int colorInfo, object viewer)
{
    return color(viewer->query("term"), viewer, colorInfo, format(text, 78));
}

/////////////////////////////////////////////////////////////////////////////
protected nomask string parseTemplate(string template, string perspective,
                                    object initiator, object target)
{
    string message = template;
    // ##Infinitive::verb##
    // ##InitiatorName## - Initiator's name
    // ##InitiatorPossessive[::Name]## - Initiator possessive / your / Name's
    // ##InitiatorObjective## - Initiator's objective / you
    // ##InitiatorReflexive## - Initiator's reflexive pronoun / yourself
    // ##InitiatorSubjective## - Initiator's subjective pronoun / you
    // ##Target[NPOS]## - Target's (one of above 4)
    // ##HitDictionary## - random word from the hit dictionary (slash/slashes,
    //   chop/chops)
    // ##SimileDictionary## - random word from the simile dictionary

    // dictionary calls must be done first!
    int isSecondPerson = (perspective == "initiator");
    
    if(initiator && objectp(initiator))
    {
        message = messageParser()->parseSimileDictionary(message, initiator);
        message = messageParser()->parseVerbDictionary(message, 
            "HitDictionary", initiator);
            
        message = messageParser()->parseVerbs(message, isSecondPerson);
    }
    
    if(isValidLiving(initiator))
    {
        message = messageParser()->parseTargetInfo(message, "Initiator", 
            initiator, isSecondPerson);
    }

    if(isValidLiving(target))
    {    
        isSecondPerson = (perspective == "target");
        message = messageParser()->parseTargetInfo(message, "Target", 
            target, isSecondPerson);      
    }
    
    message = messageParser()->capitalizeSentences(message);
    return message;    
}

/////////////////////////////////////////////////////////////////////////////
protected nomask varargs void displayMessage(string message, object initiator,
    object target)
{
    // This annoying loop handles the fact that everyone has different
    // setting for color.
    if (environment(initiator))
    {
        foreach(object person in all_inventory(environment(initiator)))
        {
            if (person && objectp(person))// && interactive(person))
            {
                string parsedMessage;
                int colorInfo = C_EMOTES;
                if (person == initiator)
                {
                    parsedMessage = parseTemplate(message, "initiator", initiator,
                        target);
                }
                else if (person == target)
                {
                    parsedMessage = parseTemplate(message, "target",
                        initiator, target);
                }
                else
                {
                    parsedMessage = parseTemplate(message, "other",
                        initiator, target);
                }
                tell_object(person, formatText(parsedMessage, colorInfo,
                    person));
            }
        }
    }
} 

/////////////////////////////////////////////////////////////////////////////
protected nomask void displayMessageToSelf(string message, object initiator)
{
    if (initiator && objectp(initiator))
    {
        string parsedMessage;
        int colorInfo = C_EMOTES;

        parsedMessage = parseTemplate(message, "initiator", initiator,
            initiator);

        tell_object(initiator, formatText(message, colorInfo,
            initiator));
    }
}

/////////////////////////////////////////////////////////////////////////////
protected string flagInformation(string flag)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string usageDetails(string displayCommand)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string synopsis(string displayCommand)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string description(string displayCommand)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string options(string displayCommand)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string notes(string displayCommand)
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
protected string copyright()
{
    return "\x1b[0;36;1mCopyright\n\x1b[0;36m\tCopyright (C) 1991-2018 Allen "
        "Cummings. For additional licensing\n\tinformation, see "
        "http://realmsmud.org/license/ \x1b[0m\n";
}

/////////////////////////////////////////////////////////////////////////////
protected string wildcardMeaning()
{
    return "";
}

/////////////////////////////////////////////////////////////////////////////
public nomask string displayUsageDetails(string displayCommand,
    string colorConfiguration, int useUnicode)
{
    string ret = "";

    if (sizeof(commands))
    {
        string *commandText = ({});
        foreach(string command in commands)
        {
            string currentCommand = regreplace(command, "\\[\\.\\*\\]", wildcardMeaning(), 1);
            currentCommand = format(regreplace(currentCommand, "\\|", "", 1), 78);
            currentCommand = "\x1b[0;36m" + regreplace(currentCommand, "##([^#]+)##", "\x1b[0;33m<\\1>\x1b[0m\x1b[0;36m", 1) + "\x1b[0m";
            commandText += ({ regreplace(currentCommand, "\n", "\n\t\t", 1) });
        }
        ret = "\t" + implode(commandText, "\n\t");
    }

    return "\n\x1b[0;36;1mSyntax\n\x1b[0m" + ret + "\n\x1b[0m";
}

/////////////////////////////////////////////////////////////////////////////
public string displaySynopsis(string displayCommand,
    string colorConfiguration, int useUnicode)
{
    return format(sprintf("\x1b[0;36;1mSynopsis\n\x1b[0;36m\t%s - %s\n\x1b[0m", 
        displayCommand, synopsis(displayCommand)), 78);
}

/////////////////////////////////////////////////////////////////////////////
public string displayDescription(string displayCommand,
    string colorConfiguration, int useUnicode)
{
    return sprintf("\x1b[0;36;1mDescription\n\x1b[0;36m%s\n\x1b[0m\n",
        description(displayCommand));
}

/////////////////////////////////////////////////////////////////////////////
public string displayOptions(string displayCommand,
    string colorConfiguration, int useUnicode)
{
    string ret = "";
    if (sizeof(commands) && sizeof(regexp(({ commands[0] }), " [[]*-[a-zA-Z]")))
    {
        string commandBlueprint = regreplace(commands[0], "^([^-[]+ +)(.*)", "\\2");
        string *options = explode(commandBlueprint, " [") - ({ ".*]" });
        string *optionList = ({});
        foreach(string option in options)
        {
            string shorthand = "\x1b[0;36;1m" + regreplace(option, "\\[*(.+)\\([^)]+\\)([^]]*)[]]$", "\\1\\2") + "\x1b[0m";
            string verbose = "\x1b[0;36;1m" + regreplace(option, "\\[*(.+)\\(([^|]+)\\|\\)([^]]*)[]]$", "\\1\\2\\3") + "\x1b[0m";

            optionList += ({ "    " + regreplace(format(shorthand + ", " + verbose, 78),
                "##([^#]+)##", "\x1b[0;33m<\\1>\x1b[0m", 1) + "\x1b[0;36m\t" +
                regreplace(format(flagInformation(shorthand), 78), "\n", "\n\t", 1) + "\x1b[0m\n" });
        }
        ret = implode(optionList, "");
    }
    return "\x1b[0;36;1mOptions\n" + "\x1b[0m" + ((ret != "") ? ret : "\x1b[0;36m\tThis command does not have any options.\x1b[0m\n\n");
}

/////////////////////////////////////////////////////////////////////////////
public string displayNotes(string displayCommand,
    string colorConfiguration, int useUnicode)
{
    return format(sprintf("\x1b[0;36;1mNotes\n\x1b[0;36m\t%s\n\x1b[0m\n",
        notes(displayCommand)), 78) + copyright();
}
