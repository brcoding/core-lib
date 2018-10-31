//*****************************************************************************
// Copyright (c) 2018 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
virtual inherit "/lib/core/thing.c";

#include "/lib/include/inventory.h"
#include "/lib/include/itemFormatters.h"
#include "/lib/modules/secure/inventory.h"
private mapping inventoryCache = ([
    "totals": ([])
]);

/////////////////////////////////////////////////////////////////////////////
static nomask int isEquipment(object itemToCheck)
{
    int ret = 0;
    // In order to prevent people from doing what I deem to be "really bad
    // stuff" that might break "really important stuff", living things will
    // ONLY be able to be worn/wielded if they inherit equipment.  There
    // should be plenty of flexibility within equipment to do anything you
    // can dream up. This check is done here to remove the opportunity to
    // "cheat"
    if(itemToCheck && objectp(itemToCheck) &&
       ((member(inherit_list(itemToCheck), ArmorBlueprint) > -1) ||
        (member(inherit_list(itemToCheck), WeaponBlueprint) > -1)))
    {
        ret = 1;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask object materialsObject()
{
    return getDictionary("materials");
}

/////////////////////////////////////////////////////////////////////////////
public nomask int canEquip(object item)
{
    int ret = 1;
    string *dictionaries = ({ "guilds", "racial", "traits", "background" });
    
    foreach(string dictionary in dictionaries)
    {
        object dictionaryObject = getDictionary(dictionary);

        if(dictionaryObject && objectp(dictionaryObject) && isEquipment(item) &&
           function_exists("canUseEquipmentOfType", dictionaryObject) &&
           !dictionaryObject->canUseEquipmentOfType(this_object(), item))
        {
            ret = 0;
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
static nomask int isModifierItem(object itemToCheck)
{
    int ret = 0;
    // In order to prevent people from circumventing modifier limits, all
    // items that can affect skills, attributes, combat stats, etc MUST inherit
    // modifierObject
    if(itemToCheck && objectp(itemToCheck) &&
       (member(inherit_list(itemToCheck), ModifierBlueprint) > -1))
    {
        ret = 1;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int isEquipped(object itemToCheck)
{
    int ret = 0;
    
    if(isEquipment(itemToCheck) && member(itemRegistry, "equipped") &&
       mappingp(itemRegistry["equipped"]))
    {
        ret = (member(m_values(itemRegistry["equipped"]), itemToCheck) > -1);
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask object *equippedByMask(int mask)
{
    object *items = ({ });
    
    string *itemsToCheck = materialsObject()->slotsUsedByItemMask(mask);
    
    if(sizeof(itemsToCheck))
    {
        foreach(string item in itemsToCheck)
        {
            if(item && member(itemRegistry["equipped"], item) && 
                itemRegistry["equipped"][item] &&
                objectp(itemRegistry["equipped"][item]) &&
                (member(items, itemRegistry["equipped"][item]) < 0))
            {
                items += ({ itemRegistry["equipped"][item] });
            }
        }
    }
    return items + ({ });
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs int usingEquipmentOfType(string type, int location)
{
    int ret = 0;

    object *items = equippedByMask(AllWielded | AllWorn);
    if(sizeof(items) > 0)
    {
        foreach(object equipment in items)
        {
            ret ||= (equipment->query("weapon type") == type) ||
                (equipment->query("armor type") == type) ||
                (equipment->query("crafting tool") == type) ||
                (member(
                    materialsObject()->slotsUsedByItemMask(equipment->query("equipment locations")),
                    type) > -1);
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask object equipmentInSlot(string slot)
{
    object ret = 0;
    
    if(slot && stringp(slot) && member(itemRegistry, "equipped") &&
       mappingp(itemRegistry["equipped"]) &&
       member(itemRegistry["equipped"], slot) &&
       itemRegistry["equipped"][slot] && 
       objectp(itemRegistry["equipped"][slot]))
    {
        ret = itemRegistry["equipped"][slot];
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
static nomask void resetInventoryCache()
{
    inventoryCache = ([
        "totals":([])
    ]);
}

/////////////////////////////////////////////////////////////////////////////
private nomask int removeEquippedItemFromSlot(string slot)
{
    int ret = 0;
    
    if(equipmentInSlot(slot))
    {
        itemRegistry["equipped"][slot] = 0;
        ret = 1;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask int equipItemInSlot(string slot, object item)
{
    int ret = 0;
    
    if(slot && stringp(slot) && member(itemRegistry, "equipped") &&
       mappingp(itemRegistry["equipped"]) &&
       member(itemRegistry["equipped"], slot) &&
       !itemRegistry["equipped"][slot])
    {
        itemRegistry["equipped"][slot] = item;
        ret = 1;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask void inventoryEvent(string event)
{
    object eventObj = getService("events");
    if(eventObj && objectp(eventObj))
    {
        eventObj->notify(event);
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask void removeItemFromCache(object item)
{
    string key = object_name(item);
    if (member(inventoryCache, key))
    {
        string *valuesToModify = m_indices(inventoryCache[key]);
        if (sizeof(valuesToModify))
        {
            foreach(string valueToModify in valuesToModify)
            {
                if (member(inventoryCache[key], valueToModify) &&
                    member(inventoryCache, "totals"))
                {
                    inventoryCache["totals"][valueToModify] -=
                        inventoryCache[key][valueToModify];
                }
            }
        }
        m_delete(inventoryCache, key);
        
        getService("combat")->resetCombatCache();
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask int addValueToCache(object item, string bonus, int value)
{
    if (objectp(item))
    {
        string itemKey = object_name(item);

        if (!member(inventoryCache, itemKey))
        {
            inventoryCache[itemKey] = ([]);
        }
        if (!member(inventoryCache[itemKey], bonus))
        {
            inventoryCache[itemKey][bonus] = value;

            if (!member(inventoryCache["totals"], bonus))
            {
                inventoryCache["totals"][bonus] += value;
            }
            else
            {
                inventoryCache["totals"][bonus] += value;
            }
        }
    }
    return value;
}

/////////////////////////////////////////////////////////////////////////////
private nomask void setEnchantments(object item, string type, string formatter)
{
    mapping enchantments = item->query(type);
    if (sizeof(enchantments))
    {
        foreach(string enchantment in m_indices(enchantments))
        {
            addValueToCache(item, sprintf(formatter, type), enchantments[type]);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
private nomask varargs void addItemToCache(object item)
{
    string *bonuses = m_indices(inventoryCache["totals"]);
    foreach(string bonus in bonuses)
    {
        addValueToCache(item, bonus, item->query(bonus));
    }

    setEnchantments(item, "resistances", "resist %s");
    setEnchantments(item, "enchantments", "%s enchantment");

    if (item == equipmentInSlot("armor"))
    {
        string *defenseTypes = filter(m_indices(inventoryCache["totals"]),
            (: sizeof(regexp(({ $1 }), "material defense bonus")) :));
        getDictionary("attacks")->validAttackTypes();
        foreach(string defenseType in defenseTypes)
        {
            addValueToCache(item, defenseType,
                materialsObject()->getMaterialDefense(item,
                    regreplace(defenseType, "material defense bonus (.*)", "\\1")));
        }
    }

    if (member(({ equipmentInSlot("armor"), equipmentInSlot("wielded primary"),
        equipmentInSlot("wielded offhand") }), item) > -1)
    {
        addValueToCache(item, "material encumberance",
            materialsObject()->getMaterialEncumberance(item));
    }
    getService("combat")->resetCombatCache();
}

/////////////////////////////////////////////////////////////////////////////
public nomask void updateInventoryCache(object itemToUpdate, string element)
{
    string itemKey = object_name(itemToUpdate);
    if (objectp(itemToUpdate) && member(inventoryCache["totals"], element) &&
        member(inventoryCache, itemKey) &&
        member(inventoryCache[itemKey], element))
    {
        inventoryCache["totals"][element] -= inventoryCache[itemKey][element];
        inventoryCache[itemKey][element] = itemToUpdate->query(element);
        inventoryCache["totals"][element] += inventoryCache[itemKey][element];
    }
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs int unequip(object itemToUnequip, int silently)
{
    int ret = 0;
    if(isEquipment(itemToUnequip) && (itemToUnequip->canUnequip() || silently)
       && isEquipped(itemToUnequip))
    {
        int itemMask = itemToUnequip->query("equipment locations");
        if(itemToUnequip->query("offhand") && (itemMask != TwohandedWeapon))
        {
            itemMask = OffhandWeapon;
        }
        
        ret = itemToUnequip->canUnequip() || silently;
        
        string *slotsToUnequip = materialsObject()->slotsUsedByItemMask(itemMask);
        foreach(string slot in slotsToUnequip)
        {
            if(equipmentInSlot(slot) == itemToUnequip)
            {
                removeEquippedItemFromSlot(slot);
            }
        }
    }
    if(ret)
    {    
        inventoryEvent("onUnequip");
        if(itemToUnequip->query("register event handler"))
        {
            object events = getService("events");
            if(events)
            {
                events->unregisterEvent(itemToUnequip);
            }
        }
        removeItemFromCache(itemToUnequip);
        m_delete(inventoryCache["totals"], "enchantments");
    }    
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int equip(object itemToEquip)
{
    int ret = 0;

    if(isEquipment(itemToEquip) && canEquip(itemToEquip))
    {
        int itemMask = itemToEquip->query("equipment locations");
        if(itemToEquip->query("offhand") && (itemMask != TwohandedWeapon))
        {
            itemMask = OffhandWeapon;
        }
        
        if(itemMask)
        {
            int equipOK = 1;
            object *itemsToUnequip = equippedByMask(itemMask);
            foreach(object item in itemsToUnequip)
            {
                equipOK &&= unequip(item);
            }
                        
            string *slotsToEquip = materialsObject()->slotsUsedByItemMask(itemMask);
            
            if(equipOK && !itemToEquip->isEquipped())
            {
                ret = itemToEquip->canEquip(this_object());
                if(ret)
                {
                    foreach(string slot in slotsToEquip)
                    {
                        if(ret)
                        {
                            ret = equipItemInSlot(slot, itemToEquip);
                        }
                    }
                }    
            }
        }
    }
    if(ret)
    {
        m_delete(inventoryCache["totals"], "enchantments");
        addItemToCache(itemToEquip);

        if(itemToEquip->query("register event handler"))
        {
            object events = getService("events");
            if(events)
            {
                events->registerEvent(itemToEquip);
            }
        }
        inventoryEvent("onEquip");
    }  
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask int validModifier(string type, string modifier)
{
    int ret = 0;

    if (member(inventoryCache["totals"], modifier))
    {
        ret = 1;
    }
    else
    {
        string serviceName = "valid" + capitalize(type);
    
        if(function_exists(serviceName))
        {
            string *modifiers = call_other(this_object(), serviceName);
            
            if(modifiers && (member(modifiers, modifier) > -1))
            {
                ret = 1;
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask object *registeredInventoryObjects()
{
    object *ret = 0;
    
    if(itemRegistry && 
       member(itemRegistry, "guild objects") &&
       mappingp(itemRegistry["guild objects"]))
    {
        ret = m_values(itemRegistry["guild objects"]);
        if(sizeof(ret) && !objectp(ret[0]))
        {
            ret = 0;
        }
    }
    return ret + ({ });
}

/////////////////////////////////////////////////////////////////////////////
public nomask object registeredInventoryObject(string fullyQualifiedName)
{
    object ret = 0;
    if(itemRegistry && 
       member(itemRegistry, "guild objects") &&
       mappingp(itemRegistry["guild objects"]) &&
       member(itemRegistry["guild objects"], fullyQualifiedName))
    {
        ret = itemRegistry["guild objects"][fullyQualifiedName];
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int registerObjectAsInventory(object item)
{
    int ret = 0;
    if(isModifierItem(item) && itemRegistry && 
       member(itemRegistry, "guild objects") &&
       mappingp(itemRegistry["guild objects"]) &&
       (!member(itemRegistry["guild objects"], item->fullyQualifiedName()) ||
       !itemRegistry["guild objects"][item->fullyQualifiedName()]))
    {
        itemRegistry["guild objects"][item->fullyQualifiedName()] = item;
        ret = 1;
    }
    if(ret)
    {
        m_delete(inventoryCache["totals"], "enchantments");
        addItemToCache(item);

        if(item->query("register event handler"))
        {
            object events = getService("events");
            if(events)
            {
                events->registerEvent(item);
            }
        }
        inventoryEvent("onRegisterItem");
    }      
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int unregisterObjectAsInventory(object item)
{
    int ret = 0;
    if(isModifierItem(item) && itemRegistry && 
        member(itemRegistry, "guild objects") &&
        mappingp(itemRegistry["guild objects"]) &&
        member(itemRegistry["guild objects"], item->fullyQualifiedName()))
    {
        m_delete(itemRegistry["guild objects"], item->fullyQualifiedName());
        ret = 1;
    }
    if(ret)
    {
        inventoryEvent("onUnregisterItem");
        if(item->query("register event handler"))
        {
            object events = getService("events");
            if(events)
            {
                events->unregisterEvent(item);
            }
        }
        removeItemFromCache(item);
        m_delete(inventoryCache["totals"], "enchantments");
    }      
    return ret;
}
       
/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetModifier(string type, string modifier)
{
    int ret = 0;
 
    if(validModifier(type, modifier))
    {
        if (member(inventoryCache["totals"], modifier))
        {
            ret = inventoryCache["totals"][modifier];
        }
        else
        {
            object *equippedItems = equippedByMask(AllWorn | AllWielded) +
                registeredInventoryObjects();

            foreach(object item in equippedItems)
            {
                // Item in this array CAN be null
                if (item && objectp(item) && (isEquipment(item) || isModifierItem(item)))
                {
                    ret += addValueToCache(item, modifier, item->query(modifier));
                }
            }
        }
    }
    return ret;
}
    
/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryAttributeBonus(string attribute)
{
    return inventoryGetModifier("attributes", sprintf("bonus %s", attribute));
}
     
/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetArmorClass()
{
    return inventoryGetModifier("combatModifiers", "armor class");
}    

/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetDefenseBonus(string damageType)
{
    int ret = inventoryGetModifier("combatModifiers", "bonus defense");

    string resistBonus = sprintf("resist %s", damageType);
    string materialBonus = sprintf("material defense bonus %s", damageType);
    object armor = equipmentInSlot("armor");
    string armorKey = object_name(armor);
    if (armor)
    {
        if (member(inventoryCache[armorKey], materialBonus))
        {
            ret += inventoryCache[armorKey][materialBonus];
        }
        else
        {
            ret += addValueToCache(armor, materialBonus,
                materialsObject()->getMaterialDefense(armor, damageType));
        }
    }

    if (member(inventoryCache["totals"], "armor class") ||
        member(inventoryCache["totals"], resistBonus))
    {
        ret += inventoryCache["totals"]["armor class"] +
            inventoryCache["totals"][resistBonus];
    }
    else
    {
        object *equippedItems = equippedByMask(AllWorn | AllWielded) +
            registeredInventoryObjects();

        foreach(object item in equippedItems)
        {
            if (objectp(item))
            {
                mapping resistances = item->query("resistances");
                if (resistances && member(resistances, damageType))
                {
                    ret += addValueToCache(item, resistBonus, resistances[damageType]);
                }

                ret += addValueToCache(item, "armor class", item->query("armor class"));     
            }
        }
    }
         
    return ret;
}    

/////////////////////////////////////////////////////////////////////////////
private nomask int getSkillPenalty(object item)
{
    string itemKey = object_name(item);
    return member(inventoryCache[itemKey], "skill penalty") ?
        inventoryCache[itemKey]["skill penalty"] :
        addValueToCache(item, "skill penalty", item->query("skill penalty"));
}

/////////////////////////////////////////////////////////////////////////////
private nomask int getSkillModifier(object item, string skill)
{
    string itemKey = object_name(item);

    return member(inventoryCache[itemKey], "skill modifier") ?
        inventoryCache[itemKey]["skill modifier"] :
        addValueToCache(item, "skill modifier", 
            call_other(this_object(), "getSkillModifier", item->query(skill)));
}

/////////////////////////////////////////////////////////////////////////////
private nomask int encumberanceForObject(object item, string skill)
{
    int ret = 0;

    if (item && objectp(item))
    {
        string itemKey = object_name(item);

        if (member(inventoryCache, itemKey) &&
            member(inventoryCache[itemKey], "encumberance"))
        {
            ret = inventoryCache[itemKey]["encumberance"];
        }
        else
        {
            ret = addValueToCache(item, "encumberance", item->query("encumberance"));
        }

        ret += getSkillPenalty(item) - 
            call_other(this_object(), "getSkillModifier", item->query(skill)) +
            materialsObject()->getMaterialEncumberance(item);
    }

    return (ret > 0) ? ret : 0;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetEncumberance()
{
    // Only armor and weapon encumberance is used for this
    int ret = encumberanceForObject(equipmentInSlot("armor"), "armor type") +
        encumberanceForObject(equipmentInSlot("wielded primary"), "weapon type") +
        encumberanceForObject(equipmentInSlot("wielded offhand"), "weapon type"); 
    
    return (ret > 0) ? ret : 0;
}   
    
/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetDefendAttackBonus()
{
    int ret = inventoryGetModifier("bonusSkills", "bonus parry") +
              inventoryGetModifier("combatModifiers", "defense class") +
              inventoryGetModifier("combatModifiers", "bonus defense class") +
              inventoryGetModifier("bonusSkills", "bonus dodge");
              
    // Might want to make this allow a bonus for any offhand weapon. For now,
    // only shields give a bonus. IsEquipped does all of the needed
    // object checks (not null, is equipment, etc)
    object offhand = equipmentInSlot("wielded offhand");
    if(isEquipped(offhand))
    {
        string offhandKey = object_name(offhand);
        if (member(inventoryCache, offhandKey) && 
            member(inventoryCache[offhandKey], "material defend attack"))
        {
            ret += inventoryCache[offhandKey]["skill modifier"] +
                inventoryCache[offhandKey]["material defend attack"] -
                inventoryCache[offhandKey]["skill penalty"];
        }
        else
        {
            string weaponType = offhand->query("weapon type");
            if (weaponType == "shield")
            {
                ret += addValueToCache(offhand, "skill modifier",
                    call_other(this_object(), "getSkillModifier",
                        weaponType));
            }

            ret -= getSkillPenalty(offhand);

            ret += addValueToCache(offhand, "material defend attack",
                materialsObject()->getMaterialDefendAttack(offhand));
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetAttackBonus(object weapon)
{
    object offhand = equipmentInSlot("wielded offhand");
    int ret = (weapon != offhand) ? 
        inventoryGetModifier("combatModifiers", "bonus attack") : 0;

    if (isEquipped(weapon))
    {
        string weaponKey = object_name(weapon);

        if (member(inventoryCache[weaponKey], "weapon attack"))
        {
            ret += inventoryCache[weaponKey]["weapon attack"];
        }
        else
        {
            ret += addValueToCache(weapon, "weapon attack",
                weapon->query("weapon attack"));
        }

        ret += call_other(this_object(), "getSkillModifier", weapon->query("weapon type")) -
            getSkillPenalty(weapon) + materialsObject()->getMaterialAttack(weapon);

        if (offhand)
        {
            string weaponType = offhand->query("weapon type");
            if (weaponType != "shield")
            {
                ret += (((offhand == weapon) ? -10 : -5) + 
                    call_other(this_object(), "getSkillModifier", "dual wield"));
            }
        }
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int inventoryGetDamageBonus(object weapon, string damageType)
{
    int ret = (damageType == "physical") ?
        inventoryGetModifier("combatModifiers", "bonus damage") : 0;

    string skillToUse = 0;
    
    if(isEquipped(weapon))
    {
        string weaponKey = object_name(weapon);
        skillToUse = weapon->query("weapon type");

        if (damageType == "physical")
        {
            if (member(inventoryCache[weaponKey], "weapon class"))
            {
                ret += inventoryCache[weaponKey]["weapon class"];
            }
            else
            {
                ret += addValueToCache(weapon, "weapon attack",
                    weapon->query("weapon class"));
            }

            if (skillToUse)
            {
                ret += (call_other(this_object(), "getSkillModifier", skillToUse) / 2);
            }
        }

        ret += materialsObject()->getMaterialDamage(weapon, damageType) - 
            getSkillPenalty(weapon);
    }
    
    string enchantment = sprintf("%s enchantment", damageType);
    if (member(inventoryCache["totals"], enchantment))
    {
        ret += inventoryCache["totals"][enchantment];
    }
    else
    {
        object *equippedItems = equippedByMask(AllWorn) + ({ weapon }) +
            registeredInventoryObjects();

        foreach(object item in equippedItems)
        {
            if (objectp(item))
            {
                mapping enchantments = item->query("enchantments");
                if (enchantments && member(enchantments, damageType))
                {
                    ret += addValueToCache(item, enchantment, enchantments[damageType]);
                }
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string *getExtraDamageTypes(object weapon)
{
    string *types = ({});
    
    if(isEquipped(weapon))
    {
        types += ({ "physical" });
        if (member(inventoryCache["totals"], "enchantments"))
        {
            types += inventoryCache["totals"]["enchantments"];
        }
        else
        {
            object *equippedItems = equippedByMask(AllWorn) + ({ weapon }) +
                registeredInventoryObjects();

            foreach(object item in equippedItems)
            {
                if (objectp(item))
                {
                    mapping enchantments = item->query("enchantments");
                    if (sizeof(enchantments))
                    {
                        types += m_indices(enchantments);
                    }
                }
            }
        }

        string *extraDamages = materialsObject()->hasExtraAttackTypes(weapon);
        if(sizeof(extraDamages))
        {
            types += extraDamages;
        }

        types = m_indices(mkmapping(types));
        inventoryCache["totals"]["enchantments"] = types + ({});
    }
    return types;
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs int Money(int newMoney)
{
    // newMoney must be a positive number
    if(intp(newMoney) && (newMoney > 0))
    {
        money = newMoney;
    }
    return money;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int addMoney(int moneyToAdd)
{
    int ret = 0;
    if(intp(moneyToAdd))
    {
        ret = 1;
        money += moneyToAdd;
        if(money < 0)
        {
            money = 0;
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public varargs nomask object transferMoneyFrom(int moneyToDrop)
{
    object ret = 0;

    if (!moneyToDrop)
    {
        moneyToDrop = Money();
    }

    if(moneyToDrop && (Money() >= moneyToDrop))
    {
        ret = clone_object("/lib/items/money.c");
        if(ret)
        {
            move_object(ret, this_object());
            ret->set("value", moneyToDrop);
            addMoney(-moneyToDrop);
        }
    }
    return ret;
}    

/////////////////////////////////////////////////////////////////////////////
public varargs nomask int transferMoneyTo(object money, int amount)
{
    int ret = objectp(money) &&
        (member(inherit_list(money), "lib/items/money.c") > -1) &&
        (amount >= 0);

    if (ret)
    {
        if (amount == 0)
        {
            amount = money->query("value");
        }

        if (amount <= money->query("value"))
        {
            int newAmountOnObject = money->query("value") - amount;
            if (newAmountOnObject > 0)
            {
                money->set("value", newAmountOnObject);
            }
            else
            {
                destruct(money);
            }
            addMoney(amount);
        }
        else
        {
            ret = 0;
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int transferItemsTo(object destination)
{
    int ret = 0;
    
    if(destination && objectp(destination))
    {
        foreach(object item in equippedByMask(AllWielded | AllWorn))
        {
            if(item)
            {
                item->unequip(item->query("name"), Silently);
            }
        }
        
        foreach(object item in all_inventory())
        {
            if(item && objectp(item) && !item->drop(Silently))
            {
                ret += item->query("weight");
                move_object(item, destination);
            }
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int canCarry(object item)
{
    int ret = 0;
    int maxWeight = 0;
    int attemptedLoad = 0;
    object *items = all_inventory();
    if (objectp(item) && item->query("weight"))
    {
        if (objectp(item))
        {
            items += ({ item });
        }
        foreach(object itemInInventory in items)
        {
            attemptedLoad += itemInInventory->query("weight");
        }
    }
    object attributes = getService("attributes");
    if (attributes)
    {
        maxWeight = 2 * attributes->Str() + 20;
    }
    ret = maxWeight - attemptedLoad;
    return (maxWeight >= attemptedLoad) ? (ret + 1) : 0;
}

/////////////////////////////////////////////////////////////////////////////
public nomask int can_put_and_get()
{
    return 1;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string colorizeText(object item, int verbose)
{
    string ret = "";

    if (item && item->short())
    {
        string formatter = NormalEquipment;

        if (materialsObject())
        {
            ret = materialsObject()->applyMaterialQualityToText(item, 
                item->short(), this_object());
        }

        if (verbose)
        {
            string details = "   " + materialsObject()->getMaterialDetails(item);
            ret += details ? details : "";
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
private nomask string equipmentText(string item, int verbose)
{
    string ret = colorizeText(equipmentInSlot(item), verbose);
    if (ret == "")
    {
        ret = sprintf(BoldBlack, "nothing");
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask string inventoryDescription()
{
    string ret = "";

    object *userDescriptionItems = sort_array(
        filter(m_indices(mkmapping(
            registeredInventoryObjects() + all_inventory(this_object()))),
            (: return call_other($1, "query", "user description"); :)),
        (: return object_name($1) > object_name($2); :));

    object messageParser = load_object("/lib/core/messageParser.c");
    if(messageParser)
    {
        foreach(object userDescriptionItem in userDescriptionItems)
        {
            ret += messageParser->capitalizeSentences(
                messageParser->parseTargetInfo(
                userDescriptionItem->query("user description"),
                "User",
                this_object())) + "\n";
        }
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////
public nomask varargs string inventoryText(int verbose)
{
    string ret = "";

    object *equippedItems = equippedByMask(AllWielded | AllWorn);

    if (sizeof(equippedItems))
    {
        string eqFormatter = sprintf(Red, "| ") + Cyan + "%s\n";

        ret += sprintf(Red, "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        ret += sprintf(eqFormatter, "Primary Weapon:\t", equipmentText("wielded primary", verbose));
        ret += sprintf(eqFormatter, "Equipped Offhand:\t", equipmentText("wielded offhand", verbose));
        ret += sprintf(Red, "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        ret += sprintf(eqFormatter, "Worn Armor:\t\t", equipmentText("armor", verbose));
        ret += sprintf(eqFormatter, "Worn Helmet:\t\t", equipmentText("helmet", verbose));
        ret += sprintf(eqFormatter, "Worn Gloves:\t\t", equipmentText("gloves", verbose));
        ret += sprintf(eqFormatter, "Worn Boots:\t\t", equipmentText("boots", verbose));
        ret += sprintf(eqFormatter, "Worn Cloak:\t\t", equipmentText("cloak", verbose));
        ret += sprintf(eqFormatter, "Worn Amulet:\t\t", equipmentText("amulet", verbose));
        ret += sprintf(eqFormatter, "Worn Belt:\t\t", equipmentText("belt", verbose));
        ret += sprintf(eqFormatter, "Worn Arm Greaves:\t", equipmentText("arm greaves", verbose));
        ret += sprintf(eqFormatter, "Worn Leg Greaves:\t", equipmentText("leg greaves", verbose));
        ret += sprintf(eqFormatter, "Worn Bracers:\t\t", equipmentText("bracers", verbose));
        ret += sprintf(eqFormatter, "Worn First Ring:\t", equipmentText("ring 1", verbose));
        ret += sprintf(eqFormatter, "Worn Second Ring:\t", equipmentText("ring 2", verbose));
        ret += sprintf(Red, "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    }
    else if(sizeof(all_inventory(this_object())))
    {
        ret += sprintf(Red, "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    }

    object *allItems = filter(all_inventory(this_object()), 
        (: (member(inherit_list($1), "lib/items/modifierObject.c") < 0) :));
    int addFooter = 0;
    foreach(object equipment in allItems)
    {
        if ((member(equippedItems, equipment) == -1) && equipment->short())
        {
            ret += sprintf(Red, "| ") + colorizeText(equipment, verbose) + "\n";
            addFooter = 1;
        }
    }
    if (addFooter)
    {
        ret += sprintf(Red, "+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    }
    return ret;
}
