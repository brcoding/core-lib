//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
#ifndef stoneKeepComponents_h
#define stoneKeepComponents_h

private mapping StoneKeepComponents = ([
    "Simple Square Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 15,
            "spearman": 25,
            "light infantry": 25,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1
        ]),
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Tall Square Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 15,
            "knight": 5,
            "spearman": 40,
            "light infantry": 40,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 200,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 300,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Large Square Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 20,
            "knight": 10,
            "spearman": 35,
            "swordsman": 35,
        ]),
        "henchmen": ([
            "seneschal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1,
            "scholar": 1,
            "magic user": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 8]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 8]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 500,
            "wood": 25,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 350,
        "structure": 400,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Simple Round Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 15,
            "spearman": 25,
            "light infantry": 25,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Tall Round Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 15,
            "knight": 5,
            "spearman": 40,
            "light infantry": 40,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 200,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 300,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Large Round Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 20,
            "knight": 10,
            "spearman": 35,
            "swordsman": 35,
        ]),
        "henchmen": ([
            "seneschal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1,
            "scholar": 1,
            "magic user": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 8]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 8]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 500,
            "wood": 25,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 350,
        "structure": 400,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Simple Hexagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 15,
            "spearman": 25,
            "light infantry": 25,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Tall Hexagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 15,
            "knight": 5,
            "spearman": 40,
            "light infantry": 40,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 200,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 300,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Large Hexagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 20,
            "knight": 10,
            "spearman": 35,
            "swordsman": 35,
        ]),
        "henchmen": ([
            "seneschal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1,
            "scholar": 1,
            "magic user": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 8]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 8]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 500,
            "wood": 25,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 350,
        "structure": 400,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Simple Octagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 15,
            "spearman": 25,
            "light infantry": 25,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Tall Octagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 15,
            "knight": 5,
            "spearman": 40,
            "light infantry": 40,
        ]),
        "henchmen": ([
            "senechal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 200,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 300,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Large Octagonal Stone Keep":([
        "class": "main stone keep",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 20,
            "knight": 10,
            "spearman": 35,
            "swordsman": 35,
        ]),
        "henchmen": ([
            "seneschal": 1,
            "advisor": 1,
            "diplomat": 1,
            "soldier": 1,
            "scholar": 1,
            "magic user": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 8]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 8]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 500,
            "wood": 25,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 350,
        "structure": 400,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Square Stone Tower":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
        ]),
        "structure": 150,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Round Stone Tower":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 150,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Hexagonal Stone Tower":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 150,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Octagonal Stone Tower":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "man-at-arms": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
        ]),
        "structure": 150,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Stone Bretasche":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 15,
            "knight": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
            "noble": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 10]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 10]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 250,
            "wood": 25,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 200,
        "structure": 200,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Stone Bergfriede": ([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "man-at-arms": 20,
            "knight": 10,
        ]),
        "henchmen": ([
            "soldier": 1,
            "scholar": 1,
            "noble": 1
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 15]),
            "carpentry": (["type":"skill", "value": 15]),
            "wood crafting": (["type":"skill", "value": 8]),
            "engineering": (["type":"skill", "value": 15]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 350,
            "wood": 50,
            "metal": 15,
            "textile": 10,
        ]),
        "added duration": 350,
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Stone Observatory":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "knight": 3,
        ]),
        "henchmen": ([
            "administrator": 1,
            "magic user": 1,
            "scholar": 2,
            "scientist": 3
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 20]),
            "carpentry": (["type":"skill", "value": 20]),
            "wood crafting": (["type":"skill", "value": 10]),
            "engineering": (["type":"skill", "value": 15]),
            "sewing": (["type":"skill", "value": 5]),
        ]),
        "building materials": ([
            "stone": 400,
            "wood": 60,
            "metal": 35,
            "textile": 15,
        ]),
        "added duration": 500,
        "structure": 350,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Magi Stone Tower":([
        "class": "central stone tower",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
        ]),
        "henchmen": ([
            "magic user": 8
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 20]),
            "carpentry": (["type":"skill", "value": 20]),
            "spellcraft": (["type":"skill", "value": 20]),
            "wood crafting": (["type":"skill", "value": 10]),
            "engineering": (["type":"skill", "value": 15]),
            "sewing": (["type":"skill", "value": 5]),
        ]),
        "building materials": ([
            "stone": 400,
            "wood": 50,
            "metal": 35,
            "textile": 15,
        ]),
        "material scarcity": ([
            "stone": "uncommon",
            "wood": "rare",
            "metal": "very rare",
            "textile": "uncommon"
        ]),
        "added duration": 500,
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Simple Stone Battlement":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1,
        "default units": ([
            "archer": 20,
        ]),
        "structure": 150,
        "defend ground attack": 6,
        "defend air attack": 1,
    ]),
    "Stone Parapet":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "archer": 25,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 100,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 200,
        "defend ground attack": 6,
        "defend air attack": 2,
    ]),
    "Crenelated Stone Parapet":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "archer": 25,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 8]),
            "carpentry": (["type":"skill", "value": 8]),
            "wood crafting": (["type":"skill", "value": 6]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 100,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 225,
        "structure": 225,
        "defend ground attack": 6,
        "defend air attack": 3,
    ]),
    "Enbrasured Stone Parapet":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "archer": 30,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 10]),
            "carpentry": (["type":"skill", "value": 10]),
            "wood crafting": (["type":"skill", "value": 8]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 100,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 300,
        "structure": 250,
        "defend ground attack": 6,
        "defend air attack": 4,
    ]),
    "Machicolationed Stone Battlement":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "archer": 25,
            "bombadier": 5,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 15]),
            "carpentry": (["type":"skill", "value": 15]),
            "wood crafting": (["type":"skill", "value": 10]),
            "engineering": (["type":"skill", "value": 10]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 100,
            "wood": 25,
            "metal": 25,
            "textile": 5,
        ]),
        "added duration": 400,
        "structure": 275,
        "defend ground attack": 6,
        "defend air attack": 4,
        "air attack": 2,
    ]),
    "Crossbow Stone Parapet":([
        "class": "stone battlement",
        "description": "",
        "experience modifier": 1.1,
        "default units": ([
            "crossbowman": 20,
            "auxiliary" : 5,
        ]),
        "building prerequisites": ([
            "stonemasonry": (["type":"skill", "value": 5]),
            "carpentry": (["type":"skill", "value": 5]),
            "wood crafting": (["type":"skill", "value": 5]),
            "engineering": (["type":"skill", "value": 5]),
            "sewing": (["type":"skill", "value": 2]),
        ]),
        "building materials": ([
            "stone": 100,
            "wood": 25,
            "metal": 5,
            "textile": 5,
        ]),
        "added duration": 200,
        "structure": 200,
        "defend ground attack": 6,
        "defend air attack": 2,
    ]),
]);

#endif
