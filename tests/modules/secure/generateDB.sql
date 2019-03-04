drop view if exists basicPlayerData;
##
drop view if exists researchChoicesView;
##
drop view if exists traitsView;
##
drop procedure if exists saveBiologicalInformation;
##
drop procedure if exists saveCombatInformation;
##
drop procedure if exists saveMaterialAttributes;
##
drop procedure if exists saveMaterialAttribute;
##
drop procedure if exists saveGuild;
##
drop procedure if exists saveQuest;
##
drop procedure if exists saveSkills;
##
drop procedure if exists saveTraits;
##
drop procedure if exists saveTemporaryTraits;
##
drop procedure if exists saveResearch;
##
drop procedure if exists pruneResearchChoices;
##
drop procedure if exists saveResearchChoiceOption;
##
drop procedure if exists saveOpenResearchTrees;
##
drop procedure if exists pruneInventory;
##
drop procedure if exists saveInventoryItem;
##
drop procedure if exists saveFaction;
##
drop procedure if exists saveCombatStatistics;
##
drop procedure if exists saveCombatStatisticsForRace;
##
drop procedure if exists saveWizardLevel;
##
drop procedure if exists saveOpinionOfCharacter;
##
drop procedure if exists saveCharacterState;
##
drop procedure if exists saveSetting;
##
drop procedure if exists saveBlockedUser;
##
drop procedure if exists updateLoginTime;
##
drop function if exists saveBasicPlayerInformation;
##
drop function if exists saveResearchChoice;
##
drop table if exists settings;
##
drop table if exists blockedUsers;
##
drop table if exists opinions;
##
drop table if exists characterStates;
##
drop table if exists biological;
##
drop table if exists combatStatisticsForRace;
##
drop table if exists combatStatistics;
##
drop table if exists guilds;
##
drop table if exists materialAttributes;
##
drop table if exists openResearchTrees;
##
drop table if exists playerCombatData;
##
drop table if exists quests;
##
drop table if exists research;
##
drop table if exists researchChoiceItems;
##
drop table if exists researchChoices;
##
drop table if exists skills;
##
drop table if exists wizards;
##
drop table if exists wizardTypes;
##
drop table if exists timedtraits;
##
drop table if exists traits;
##
drop table if exists temporaryTraits;
##
drop table if exists inventory;
##
drop table if exists factions;
##
drop table if exists players;
##
drop table if exists environment;
##
CREATE TABLE `environment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `currentTime` int(11) NOT NULL DEFAULT '0',
  `currentDay` int(11) NOT NULL DEFAULT '0',
  `currentYear` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
INSERT INTO environment (currentTime, currentDay, currentYear) values (660, 92, 2942);
##
CREATE TABLE `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(40) NOT NULL,
  `race` varchar(20) NOT NULL,
  `age` bigint unsigned NOT NULL,
  `gender` tinyint unsigned NOT NULL DEFAULT '0',
  `ghost` tinyint unsigned NOT NULL DEFAULT '0',
  `strength` int(11) NOT NULL DEFAULT '0',
  `intelligence` int(11) NOT NULL DEFAULT '0',
  `dexterity` int(11) NOT NULL DEFAULT '0',
  `wisdom` int(11) NOT NULL DEFAULT '0',
  `constitution` int(11) NOT NULL DEFAULT '0',
  `charisma` int(11) NOT NULL DEFAULT '0',
  `invisible` tinyint NOT NULL DEFAULT '0',
  `whenCreated` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `LastLogin` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `location` varchar(200) NOT NULL,
  `attributePoints` smallint NOT NULL DEFAULT '0',
  `skillPoints` smallint NOT NULL DEFAULT '0',
  `researchPoints` smallint NOT NULL DEFAULT '0',
  `unassignedExperience` bigint DEFAULT NULL,
  `playerMoney` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `biological` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `intoxicated` smallint NOT NULL DEFAULT '0',
  `stuffed` smallint NOT NULL DEFAULT '0',
  `drugged` smallint NOT NULL DEFAULT '0',
  `soaked` smallint NOT NULL DEFAULT '0',
  `headache` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `playerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `combatStatistics` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(40) NOT NULL,
  `level` int(11) NOT NULL,
  `foeKey` varchar(200) DEFAULT NULL,
  `timesKilled` int(11) DEFAULT NULL,
  `playerid` int(11) NOT NULL,
  `isNemesis` tinyint NOT NULL DEFAULT '0',
  `isBestKill` tinyint NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `combatStatisticsplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `combatStatisticsForRace` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `race` varchar(20) NOT NULL,
  `timesKilled` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `combatStatisticsForRaceplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `guilds` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `name` varchar(40) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  `experience` bigint NOT NULL DEFAULT '0',
  `rank` varchar(45) DEFAULT NULL,
  `title` varchar(45) DEFAULT NULL,
  `pretitle` varchar(45) DEFAULT NULL,
  `leftGuild` bigint DEFAULT NULL,
  `anathema` bigint DEFAULT NULL,
  `rankAdvancedAt` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `guildsplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `materialAttributes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `type` varchar(40) NOT NULL,
  `value` varchar(80) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `materialAttributesplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `openResearchTrees` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `researchTree` varchar(200) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `openResearchTreesplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `playerCombatData` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `hitPoints` int(11) NOT NULL,
  `maxHitPoints` int(11) NOT NULL,
  `spellPoints` int(11) NOT NULL,
  `maxSpellPoints` int(11) NOT NULL,
  `staminaPoints` int(11) NOT NULL,
  `maxStaminaPoints` int(11) NOT NULL,
  `wimpy` smallint NOT NULL DEFAULT '0',
  `onKillList` tinyint NOT NULL DEFAULT '0',
  `timeToHealHP` smallint NOT NULL DEFAULT '0',
  `timeToHealSP` smallint NOT NULL DEFAULT '0',
  `timeToHealST` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `playerCombatDataplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `quests` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `path` varchar(200) NOT NULL,
  `name` varchar(45) NOT NULL,
  `state` varchar(45) NOT NULL,
  `statesCompleted` varchar(256) DEFAULT NULL,
  `isActive` tinyint NOT NULL DEFAULT '0',
  `isCompleted` tinyint NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `questsplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `research` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `path` varchar(200) NOT NULL,
  `whenResearchBegan` bigint NOT NULL DEFAULT '0',
  `whenResearchComplete` bigint DEFAULT NULL,
  `timeSpentLearning` int(11) DEFAULT NULL,
  `researchComplete` tinyint NOT NULL DEFAULT '0',
  `timeToCompleteLearning` int(11) DEFAULT NULL,
  `cooldown` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `researchplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `researchChoices` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `name` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `researchChoicesplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `researchChoiceItems` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `researchChoiceId` int(11) NOT NULL,
  `selectionNumber` varchar(5) NOT NULL,
  `type` varchar(15) NOT NULL,
  `name` varchar(45) NOT NULL,
  `description` varchar(256) NOT NULL,
  `key` varchar(200) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `researchChoiceId_idx` (`researchChoiceId`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
##
CREATE TABLE `wizardTypes` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;
##
insert into wizardTypes (type) values ('apprentice'), ('wizard'),
('creator'), ('highwizard'),('senior'),('admin'),('elder'),('sage'),
('archwizard'),('demigod'),('god'),('owner'),('emeritus');
##
CREATE TABLE `wizards` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `typeId` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `playerid_idx` (`playerId`),
  KEY `typeid_idx` (`typeId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `skills` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `name` varchar(45) NOT NULL,
  `value` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `skillsplayerid_idx` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `temporaryTraits` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `traitList` varchar(512) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `temptraitsplayerid_idx` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `traits` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `path` varchar(200) NOT NULL,
  `name` varchar(45) NOT NULL,
  `added` bigint NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `traits_playerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `timedtraits` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `traitid` int(11) NOT NULL,
  `endTime` int(11) NOT NULL,
  `expireMessage` varchar(256) DEFAULT NULL,
  `triggeringResearch` varchar(200) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `timed_traitsid` FOREIGN KEY (`traitid`) REFERENCES `traits` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `factions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `path` varchar(200) NOT NULL,
  `disposition` varchar(20) NOT NULL,
  `reputation` int(11) NOT NULL,
  `lastInteraction` int(11) NOT NULL,
  `lastReputation` int(11) NOT NULL,
  `numberOfInteractions` int(11) NOT NULL,
  `dispositionTime` bigint NOT NULL,
  `isMember` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `factions_playerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `inventory` (
  `playerid` int(11) NOT NULL,
  `fileName` varchar(200) NOT NULL,
  `data` blob NOT NULL,
  `isEquipped` tinyint NOT NULL DEFAULT '0',
  KEY `inventory_playerid_idx` (`playerid`),
  CONSTRAINT `inventory_playerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `opinions` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `targetKey` varchar(200) NOT NULL,
  `opinion` int(11) NOT NULL DEFAULT '0',
  `lastInteraction` bigint DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `opinions_playerid_idx` (`playerId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `characterStates` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `targetKey` varchar(200) NOT NULL,
  `state` varchar(80) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `characterStates_playerid_idx` (`playerId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;
##
CREATE TABLE `settings` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `setting` varchar(20) NOT NULL,
  `value` varchar(20) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `settingsplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE TABLE `blockedUsers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerid` int(11) NOT NULL,
  `blockedPlayerId` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  CONSTRAINT `blockingplayerid` FOREIGN KEY (`playerid`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `blockedplayersid` FOREIGN KEY (`blockedPlayerId`) REFERENCES `players` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
##
CREATE VIEW `basicPlayerData` AS select `players`.`name` AS `name`,
                                        `players`.`race` AS `race`,
                                        `players`.`age` AS `age`,
                                        `players`.`gender` AS `gender`,
                                        `players`.`ghost` AS `ghost`,
                                        `players`.`strength` AS `strength`,
                                        `players`.`intelligence` AS `intelligence`,
                                        `players`.`dexterity` AS `dexterity`,
                                        `players`.`wisdom` AS `wisdom`,
                                        `players`.`constitution` AS `constitution`,
                                        `players`.`charisma` AS `charisma`,
                                        `players`.`invisible` AS `invisible`,
                                        `biological`.`intoxicated` AS `intoxicated`,
                                        `biological`.`stuffed` AS `stuffed`,
                                        `biological`.`drugged` AS `drugged`,
                                        `biological`.`soaked` AS `soaked`,
                                        `biological`.`headache` AS `headache`,
                                        `playerCombatData`.`hitPoints` AS `hitPoints`,
                                        `playerCombatData`.`maxHitPoints` AS `maxHitPoints`,
                                        `playerCombatData`.`spellPoints` AS `spellPoints`,
                                        `playerCombatData`.`maxSpellPoints` AS `maxSpellPoints`,
                                        `playerCombatData`.`staminaPoints` AS `staminaPoints`,
                                        `playerCombatData`.`maxStaminaPoints` AS `maxStaminaPoints`,
                                        `playerCombatData`.`wimpy` AS `wimpy`,
                                        `playerCombatData`.`onKillList` AS `onKillList`,
                                        `playerCombatData`.`timeToHealHP` AS `timeToHealHP`,
                                        `playerCombatData`.`timeToHealSP` AS `timeToHealSP`,
                                        `playerCombatData`.`timeToHealST` AS `timeToHealST`,
                                        `players`.`whenCreated` AS `whenCreated`,
                                        `players`.`LastLogin` AS `LastLogin`,
                                        `players`.`location` AS `location`,
                                        `players`.`attributePoints` AS `availableAttributePoints`,
                                        `players`.`skillPoints` AS `availableSkillPoints`,
                                        `players`.`researchPoints` AS `availableResearchPoints`,
                                        `players`.`unassignedExperience` AS `unassignedExperience`,
                                        `players`.`playerMoney` AS `playerMoney`,
                                        `players`.`id` AS `playerId` 
                               from ((`players` 
                               join `biological` on((`players`.`id` = `biological`.`playerid`))) 
                               join `playerCombatData` on((`players`.`id` = `playerCombatData`.`playerid`)));
##
CREATE VIEW `researchChoicesView` AS select `researchChoices`.`playerId` AS `playerId`,
                                            `researchChoices`.`name` AS `Choice`,
                                            `researchChoiceItems`.`selectionNumber` AS `selectionNumber`,
                                            `researchChoiceItems`.`type` AS `type`,
                                            `researchChoiceItems`.`name` AS `name`,
                                            `researchChoiceItems`.`description` AS `description`,
                                            `researchChoiceItems`.`key` AS `key` 
                                     from (`researchChoices` 
                                     join `researchChoiceItems` on((`researchChoices`.`id` = `researchChoiceItems`.`researchChoiceId`)));
##
CREATE VIEW `traitsView` AS select `traits`.`playerid` AS `playerid`,
                                   `traits`.`path` AS `path`,
                                   `traits`.`name` AS `name`,
                                   `traits`.`added` AS `added`,
                                   `timedtraits`.`endTime` AS `endTime`,
                                   `timedtraits`.`expireMessage` AS `expireMessage`,
                                   `timedtraits`.`triggeringResearch` AS `triggeringResearch` 
                            from (`traits` 
                            left join `timedtraits` on((`traits`.`id` = `timedtraits`.`traitid`)));
##
CREATE FUNCTION `saveBasicPlayerInformation`(p_name varchar(40),
p_race varchar(20), p_age int, p_gender int, p_ghost int, p_strength int,
p_intelligence int, p_dexterity int, p_wisdom int, p_constitution int,
p_charisma int, p_invisible int, p_attributes int, p_skill int,
p_research int, p_unassigned int, p_location varchar(200), p_money int) RETURNS int(11)
BEGIN
	declare pid int;
    
    select id into pid
    from players where name = p_name;
    
    if pid is not null then
		update players set race = p_race,
						   age = p_age,
                           gender = p_gender,
                           ghost = p_ghost,
                           strength = p_strength,
                           intelligence = p_intelligence,
                           dexterity = p_dexterity,
                           wisdom = p_wisdom,
                           constitution = p_constitution,
                           charisma = p_charisma,
                           invisible = p_invisible,
                           attributePoints = p_attributes,
                           skillPoints = p_skill,
                           researchPoints = p_research,
                           unassignedExperience = p_unassigned,
                           location = p_location,
                           playerMoney = p_money,
                           LastLogin = now()
		where id = pid;
	else
		insert into players (name, race, age, gender, ghost, strength,
        intelligence, dexterity, wisdom, constitution, charisma, invisible,
        attributePoints, skillPoints, researchPoints, unassignedExperience, 
        whenCreated, LastLogin, location, playerMoney)
        values (p_name, p_race, p_age, p_gender, p_ghost, p_strength, 
        p_intelligence, p_dexterity, p_wisdom, p_constitution, p_charisma, 
        p_invisible, p_attributes, p_skill, p_research, p_unassigned, now(), now(), p_location, p_money);
    
        select id into pid from players where name = p_name;
    end if;
RETURN pid;
END;
##

CREATE PROCEDURE `saveBiologicalInformation`(p_playerid int, p_intoxicated int,
p_stuffed int, p_drugged int, p_soaked int, p_headache int)
BEGIN
	declare pid int;
    
    select id into pid
    from biological where playerid = p_playerid;
    
    if pid is not null then
		update biological set intoxicated = p_intoxicated,
						      stuffed = p_stuffed,
						      drugged = p_drugged,
						      soaked = p_soaked,
						      headache = p_headache
		where id = pid;
	else
		insert into biological (playerid, intoxicated, stuffed, drugged, soaked, headache)
        values (p_playerid, p_intoxicated, p_stuffed, p_drugged, p_soaked, p_headache);
    end if;
END;
##
CREATE PROCEDURE `saveCombatInformation`(p_playerid int, p_hp int,
p_maxhp int, p_sp int, p_maxsp int, p_st int, p_maxst int, p_wimpy int,
p_killList int, p_healhp int, p_healsp int, p_healst int)
BEGIN
	declare pid int;
 
    select id into pid
    from playerCombatData where playerid = p_playerid;
    
    if pid is not null then
		update playerCombatData set hitPoints = p_hp,
						      maxHitPoints = p_maxhp,
						      spellPoints = p_sp,
						      maxSpellPoints = p_maxsp,
						      staminaPoints = p_st,
						      maxStaminaPoints = p_maxst,
						      wimpy = p_wimpy,
						      onKillList = p_killList,
						      timeToHealHP = p_healhp,
						      timeToHealSP = p_healsp,
						      timeToHealST = p_healst
		where id = pid;
	else
		insert into playerCombatData (playerid,
									  hitPoints,
									  maxHitPoints,
									  spellPoints,
									  maxSpellPoints,
									  staminaPoints,
									  maxStaminaPoints,
									  wimpy,
									  onKillList,
									  timeToHealHP,
									  timeToHealSP,
									  timeToHealST)
        values (p_playerid, p_hp, p_maxhp, p_sp, p_maxsp, p_st, p_maxst,
				p_wimpy, p_killList, p_healhp, p_healsp, p_healst);
    end if;
END;
##
CREATE PROCEDURE `saveMaterialAttribute`(p_playerid int, p_type varchar(45), p_value varchar(256))
BEGIN
	declare materialId int;
    
    select id into materialId
    from materialAttributes
    where playerid = p_playerid and type = p_type;
    
    if materialId is not null then
		update materialAttributes set value = p_value where id = materialId;
	else
		insert into materialAttributes (playerid, type, value)
        values (p_playerid, p_type, p_value);
    end if;
END;
##
CREATE PROCEDURE `saveMaterialAttributes`(p_playerid int, p_title varchar(256),
p_pretitle varchar(256), p_msgin varchar(256), p_msgout varchar(256),
p_magicalin varchar(256), p_magicalout varchar(256), p_home varchar(256),
p_clone varchar(256), p_short varchar(256), p_long varchar(256))
BEGIN
    if p_title <> '' then
	    call saveMaterialAttribute(p_playerid, 'title', p_title);
    end if;
    if p_pretitle <> '' then
	    call saveMaterialAttribute(p_playerid, 'pretitle', p_pretitle);
    end if;
    if p_msgin <> '' then
	    call saveMaterialAttribute(p_playerid, 'messageIn', p_msgin);
    end if;
    if p_msgout <> '' then
	    call saveMaterialAttribute(p_playerid, 'messageOut', p_msgout);
    end if;
    if p_magicalIn <> '' then
	    call saveMaterialAttribute(p_playerid, 'magicalMessageIn', p_magicalIn);
    end if;
    if p_magicalOut <> '' then
	    call saveMaterialAttribute(p_playerid, 'magicalMessageOut', p_magicalOut);
    end if;
    if p_home <> '' then
	    call saveMaterialAttribute(p_playerid, 'messageHome', p_home);
    end if;
    if p_clone <> '' then
	    call saveMaterialAttribute(p_playerid, 'messageClone', p_clone);
    end if;
    if p_short <> '' then
	    call saveMaterialAttribute(p_playerid, 'shortDescription', p_short);
    end if;
    if p_long <> '' then
    	call saveMaterialAttribute(p_playerid, 'longDescription', p_long);
    end if;
END;
##
CREATE PROCEDURE `saveGuild`(p_playerid int, p_guild varchar(40), p_title varchar(45), 
p_pretitle varchar(45), p_rank varchar(45), p_level int, p_experience int, p_leftGuild int,
p_anathema int, p_rankAdvancedAt int)
BEGIN
	declare guildId int;
 
    select id into guildId
    from guilds where playerid = p_playerid and name = p_guild;
    
    if guildId is not null then
		update guilds set title = p_title,
						  pretitle = p_pretitle,
                          rank = p_rank,
                          level = p_level,
                          experience = p_experience,
                          leftGuild = p_leftGuild,
                          anathema = p_anathema,
                          rankAdvancedAt = p_rankAdvancedAt
		where id = guildId;
	else
		insert into guilds (playerid,
									  name,
									  title,
									  pretitle,
                                      rank,
                                      level,
									  experience,
                                      leftGuild,
								      anathema,
                                      rankAdvancedAt)
        values (p_playerid, p_guild, p_title, p_pretitle, p_rank, p_level,
                p_experience, p_leftGuild, p_anathema, p_rankAdvancedAt);
    end if;
END;
##
CREATE PROCEDURE `saveQuest` (p_playerid int, p_quest varchar(200), p_name varchar(45), 
p_state varchar(45), p_statesCompleted varchar(45), p_active int, p_completed int)
BEGIN
	declare questId int;
 
    select id into questId
    from quests where playerid = p_playerid and path = p_quest;
    
    if questId is not null then
		update quests set name = p_name,
                          state = p_state,
						  statesCompleted = p_statesCompleted,
                          isActive = p_active,
                          isCompleted = p_completed
		where id = questId;
	else
		insert into quests (playerid, path, name, state, statesCompleted, isActive, isCompleted)
        values (p_playerid, p_quest, p_name, p_state, p_statesCompleted, p_active, p_completed);
    end if;
END;
##
CREATE PROCEDURE `saveResearch`(p_playerid int, p_path varchar(200), p_began int, 
p_whenCompleted int, p_timeSpent int, p_completed int, p_timeToComplete int, 
p_cooldown int)
BEGIN
	declare researchId int;
 
    select id into researchId
    from research where playerid = p_playerid and path = p_path;
    
    if researchId is not null then
		update research set whenResearchBegan = p_began,
						  whenResearchComplete = p_whenCompleted,
                          timeSpentLearning = p_timeSpent,
                          researchComplete = p_completed,
                          timeToCompleteLearning = p_timeToComplete,
                          cooldown = p_cooldown
		where id = researchId;
	else
		insert into research (playerid, path, whenResearchBegan, whenResearchComplete, 
        timeSpentLearning, researchComplete, timeToCompleteLearning, cooldown)
        values (p_playerid, p_path, p_began, p_whenCompleted, p_timeSpent, p_completed,
        p_timeToComplete, p_cooldown);
    end if;
END;
##
CREATE PROCEDURE `pruneResearchChoices` (p_playerid int)
BEGIN
	delete from researchChoiceItems
    where researchChoiceId in (select id from researchChoices where playerid = p_playerid);
    
    delete from researchChoices where playerid = p_playerid;
END;
##
CREATE FUNCTION `saveResearchChoice` (p_playerid int, p_name varchar(45))
RETURNS INTEGER
BEGIN
	declare choiceId int;
    
    insert into researchChoices (playerid, name) values (p_playerId, p_name);
    
    select id into choiceId
    from researchChoices
    where playerId = p_playerid and name = p_name;
    
RETURN choiceId;
END;
##
CREATE PROCEDURE `saveResearchChoiceOption` (p_choiceId int, p_selection varchar(5),
p_type varchar(15), p_name varchar(45), p_description varchar(256), p_key varchar(200))
BEGIN
	insert into researchChoiceItems 
    (researchChoiceId, selectionNumber, type, name, description, researchChoiceItems.key)
    values (p_choiceId, p_selection, p_type, p_name, p_description, p_key);
END;
##
CREATE PROCEDURE `saveOpenResearchTrees` (p_playerid int, p_path varchar(200))
BEGIN
	declare researchId int;
 
    select id into researchId
    from openResearchTrees where playerid = p_playerid and researchTree = p_path;
    
    if researchId is null then
		insert into openResearchTrees (playerId, researchTree)
        values (p_playerid, p_path);
    end if;
END;
##
CREATE PROCEDURE `saveSkills` (p_playerid int, p_name varchar(45), 
p_value int)
BEGIN
	declare skillId int;
 
    select id into skillId
    from skills where playerid = p_playerid and name = p_name;
    
    if skillId is not null then
		update skills set value = p_value
		where id = skillId;
	else
		insert into skills (playerid, name, value)
        values (p_playerid, p_name, p_value);
    end if;
END;
##
CREATE PROCEDURE `saveTraits` (p_playerid int, p_path varchar(200), 
p_name varchar(45), p_added int, p_end int, p_expire varchar(256),
p_trigger varchar(200))
BEGIN
	declare tid int;
 
    select id into tid
    from traits where playerid = p_playerid and path = p_path;
    
    if tid is not null then
		update traits set name = p_name,
                          added = p_added
		where id = tid;

        if p_end is not null and p_end <> 0 then 
            update timedtraits set endTime = p_end,
                              expireMessage = p_expire,
                              triggeringResearch = p_trigger
            where traitid = tid;
        end if;
	else
		insert into traits (playerid, path, name, added)
        values (p_playerid, p_path, p_name, p_added);

        if p_end is not null and p_end <> 0 then
            select id into tid
            from traits where playerid = p_playerid and path = p_path;

   		    insert into timedtraits (traitid, endTime, expireMessage, triggeringResearch)
            values (tid, p_end, p_expire, p_trigger);
        end if;
    end if;
END;
##
CREATE PROCEDURE `saveTemporaryTraits` (p_playerid int, p_traits varchar(512))
BEGIN
	declare playerId int;
 
    select id into playerId
    from temporaryTraits where playerid = p_playerid;
    
    if playerId is not null then
		update temporaryTraits set traitList = p_traits
		where id = playerId;
	else
		insert into temporaryTraits (playerid, traitList)
        values (p_playerid, p_traits);
    end if;
END;
##
CREATE PROCEDURE `pruneInventory` (p_playerid int)
BEGIN
    delete from inventory where playerid = p_playerid;
END;
##
CREATE PROCEDURE `saveInventoryItem` (p_playerid int,
p_filename varchar(200), p_data blob, p_equipped int)
BEGIN
    insert into inventory (playerid,filename,data,isEquipped) 
        values (p_playerid,p_filename,p_data,p_equipped);
END;
##
CREATE PROCEDURE `saveFaction` (p_playerid int, p_path varchar(200), 
p_disposition varchar(20), p_reputation int, p_lastInteraction int, 
p_lastReputation int, p_numInteractions int, p_dispositionTime int, p_isMember tinyint)
BEGIN
 	declare factionId int;

    select id into factionId
    from factions where playerid = p_playerid and path = p_path;
    
    if factionId is not null then
		update factions set disposition = p_disposition,
                            reputation = p_reputation,
                            lastInteraction = p_lastInteraction,
                            lastReputation = p_lastReputation,
                            numberOfInteractions = p_numInteractions,
                            dispositionTime = p_dispositionTime,
                            isMember = p_isMember
		where id = factionId;
	else
		insert into factions (playerid, path, disposition, reputation, lastInteraction, lastReputation, numberOfInteractions, dispositionTime, isMember)
        values (p_playerid, p_path, p_disposition, p_reputation, p_lastInteraction, p_lastReputation, p_numInteractions, p_dispositionTime, p_isMember);
    end if;
END;
##
CREATE PROCEDURE `saveCombatStatistics` (p_playerName varchar(40),
p_key varchar(200), p_name varchar(40), p_level int)
BEGIN	
	declare lPlayerId int;
    declare statId int;
    declare timesPreviouslyKilled int;
    
    select id into lPlayerId
    from players where name = p_playerName;

    if(lPlayerId is not null) then
    
		select id, timesKilled into statId, timesPreviouslyKilled
		from combatStatistics
		where (playerid = lPlayerId) AND (foeKey = p_key);
		
        if(statId is not null) then
			update combatStatistics
			set timesKilled = timesPreviouslyKilled + 1
            where id = statId;
		else
            insert into combatStatistics
            (name, level, foeKey, timesKilled, playerId)
            values (p_name, p_level, p_key, 1, lPlayerId);           
        end if;
        
        update combatStatistics
        set isNemesis = 0, isBestKill = 0
        where playerid = lPlayerId;
        
        -- Stupid MySQL can handle this as an embedded query???
        select id into statId 
        from combatStatistics
		where playerId = lPlayerId
		order by timesKilled desc, level desc
		limit 1;

        update combatStatistics
        set isNemesis = 1
        where id = statId;
 
        select id into statId
        from combatStatistics
		where playerId = lPlayerId
		order by level desc, timesKilled desc
		limit 1;

        update combatStatistics
        set isBestKill = 1
        where id = statId;
                    
    end if;
END;
##
CREATE PROCEDURE `saveCombatStatisticsForRace` 
(p_playerName varchar(40), p_race varchar(20))
BEGIN	
	declare lPlayerId int;
    declare statId int;
    
    select id into lPlayerId
    from players where name = p_playerName;

    if(lPlayerId is not null) then
		select id into statId
		from combatStatisticsForRace
		where (playerid = lPlayerId) AND (race = p_race);
		
        if(statId is not null) then
			update combatStatisticsForRace
			set timesKilled = timesKilled + 1
            where id = statId;
		else
            insert into combatStatisticsForRace
            (playerid, race, timesKilled)
            values (lPlayerId, p_race, 1);           
        end if;
    end if;
END;
##
CREATE PROCEDURE `saveWizardLevel`(p_playerid int, p_level varchar(20))
BEGIN
	declare levelId int;
    declare wizardId int;
    
    select id into levelId
    from wizardTypes where type = p_level;
    
    if levelId is not null then
		select id into wizardId
		from wizards where playerId = p_playerId;
		
		if wizardId is not null then
			update wizards set typeId = levelId
            where id = wizardId;
		else
			insert into wizards (playerId, typeId) values (p_playerId, levelId);
		end if;
    end if;    
END;
##
CREATE PROCEDURE `saveOpinionOfCharacter`(p_playerName varchar(40),
p_targetKey varchar(200), p_opinion int, p_lastInteraction bigint)
BEGIN
    declare lplayerId int;
    declare opinionId int;

    select id into lplayerId
    from players where name = p_playerName;
    
    if lplayerId is not null then
		select id into opinionId
		from opinions where playerId = lplayerId and targetKey = p_targetKey;
		
		if opinionId is not null then
			update opinions set opinion = p_opinion,
                                lastInteraction = p_lastInteraction
            where id = opinionId;
		else
			insert into opinions (playerId, targetKey, opinion, lastInteraction) 
            values (lplayerId, p_targetKey, p_opinion, p_lastInteraction);
		end if;
    end if;    
END;
##
CREATE PROCEDURE `saveCharacterState`(p_playerName varchar(40),
p_targetKey varchar(200), p_state varchar(80))
BEGIN
    declare lplayerId int;
    declare stateId int;

    select id into lplayerId
    from players where name = p_playerName;
    
    if lplayerId is not null then
		select id into stateId
		from characterStates 
        where playerId = lplayerId and targetKey = p_targetKey;
		
		if stateId is not null then
			update characterStates set state = p_state
            where id = stateId;
		else
			insert into characterStates (playerId, targetKey, state) 
            values (lplayerId, p_targetKey, p_state);
		end if;
    end if;    
END;
##
CREATE PROCEDURE `updateLoginTime` (p_playerName varchar(40))
BEGIN
    update players set LastLogin = now() where name = p_playerName;
END;
##
CREATE PROCEDURE `saveSetting`(p_playerName varchar(40),
p_setting varchar(20), p_value varchar(20))
BEGIN
    declare lplayerId int;
    declare lSettingId int;

    select id into lplayerId
    from players where name = p_playerName;
    
    if lplayerId is not null then
		select id into lSettingId
		from settings 
        where playerId = lplayerId and setting = p_setting;
		
		if lSettingId is not null then
			update settings set value = p_value
            where id = lSettingId;
		else
			insert into settings (playerId, setting, value) 
            values (lplayerId, p_setting, p_value);
		end if;
    end if;    
END;
##
CREATE PROCEDURE `saveBlockedUser`(p_playerName varchar(40),
p_blockedPlayer varchar(40), actionType varchar(10))
BEGIN
    declare lplayerId int;
    declare lBlockedId int;
    declare lBlockId int;

    select id into lplayerId
    from players where name = p_playerName;
    
    select id into lBlockedId
    from players where name = p_blockedPlayer;

    if lplayerId is not null and lBlockedId is not null then
		select id into lBlockId
		from blockedUsers 
        where playerId = lplayerId and blockedPlayerId = lBlockedId;
		
		if lBlockId is null and actionType = 'block' then
			insert into blockedUsers (playerId, blockedPlayerId) 
            values (lplayerId, lBlockedId);
		elseif lBlockId is not null and actionType = 'unblock' then
			delete from blockedUsers where id = lBlockId;
        end if;
    end if;    
END;
##
insert into players (id,name,race,age,gender) values (1,'maeglin','high elf',1,1);
##
insert into wizards (playerid,typeid) values (1, (select id from wizardTypes where type='owner'));
##
insert into players (id,name,race,age,gender) values (2,'sonja','high elf',1,2);
##
insert into wizards (playerid,typeid) values (2, (select id from wizardTypes where type='owner'));
