//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
inherit "/lib/commands/baseCommand.c";

/////////////////////////////////////////////////////////////////////////////
public nomask void reset(int arg)
{
    if (!arg)
    {
        CommandType = "Wizard";
        addCommandTemplate("cp [-r] [##Target##] [##Destination##]");
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask int execute(string command, object initiator)
{
    int ret = 0;

    if (canExecuteCommand(command) && initiator->hasExecuteAccess("cp"))
    {
        string source = regreplace(command, "^cp ([^ ]+) .*", "\\1");
        string destination = regreplace(command, "^cp [^ ]+ (.*)", "\\1");

        string sourcePath = initiator->hasReadAccess(source);
        string destinationPath = initiator->hasWriteAccess(destination);
        
        if (sourcePath && destinationPath)
        {
            if (file_size(sourcePath) != -1)
            {
                ret = (copy_file(sourcePath, destinationPath) == 0);
            }
            else
            {
                tell_object(initiator, format(sprintf("The file '%s' does not exist.",
                    sourcePath), 78));
            }
        }
        else if(!initiator->hasReadAccess(source))
        {
            tell_object(initiator, format(sprintf(
                "You do not have read access to '%s'", source || "???"), 78));
        }
        else if (!initiator->hasWriteAccess(destination))
        {
            tell_object(initiator, format(sprintf(
                "You do not have write access to '%s'", destination || "???"), 78));
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
protected string synopsis(string displayCommand)
{
    return "Copy a file.";
}

/////////////////////////////////////////////////////////////////////////////
protected string description(string displayCommand)
{
    return format("The cp command will copy the source file to the destination "
        "file provided that the user has read access to the source file "
        "and write access to the destination location.", 78);
}

/////////////////////////////////////////////////////////////////////////////
protected string notes(string displayCommand)
{
    return "See also: mv and rm";
}
