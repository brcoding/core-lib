//*****************************************************************************
// Copyright (c) 2019 - Allen Cummings, RealmsMUD, All rights reserved. See
//                      the accompanying LICENSE file for details.
//*****************************************************************************
#ifndef castleBuildings_h
#define castleBuildings_h

private mapping CastleBuildings = ([
    "unbuilt moat":([
        "type": "moat",
        "dimensions": "17x15",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;9m",
                "24-bit": "\x1b[0;38;2;200;0;0m"
            ]),
        ]),
        "components":([
            "MMM": ([
                "ascii": "   ",
                "unicode": "   ",
            ]),
            "WSM": ([
                "ascii": "   ",
                "unicode": "   ",
            ]),
            "ESM": ([
                "ascii": "   ",
                "unicode": "   ",
            ]),
        ]),
    ]),

    "simple moat":([
        "type": "moat",
        "dimensions": "17x15",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;44;30m",
                "8-bit": "\x1b[0;48;5;20;38;5;14m",
                "3-bit": "\x1b[0;48;2;0;0;180;38;2;0,190,255m",
            ]),
        ]),
        "components":([
            "MMM": ([
                "ascii": "~~~",
                "unicode": "\xe2\x96\x91\xe2\x96\x91\xe2\x96\x91",
            ]),
            "WSM": ([
                "ascii": "  ~",
                "unicode": " \xe2\x96\x91\xe2\x96\x91",
            ]),
            "ESM": ([
                "ascii": "~  ",
                "unicode": "\xe2\x96\x91\xe2\x96\x91 ",
            ]),
        ]),
    ]),

    "unbuilt northwest castle building":([
        "type": "northwest castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;1m",
                "24-bit": "\x1b[0;38;2;128;0;0m"
            ]),
        ]),
        "components":([
            "NC1": ([
                "ascii": ".?.",
                "unicode": "\xe2\x94\x8a\xe2\x81\x87\xe2\x94\x8a",
            ]),
            "NC2": ([
                "ascii": "...",
                "unicode": "\xe2\x94\x94\xe2\x94\x88\xe2\x94\x98",
            ]),
        ]),
    ]),

    "unbuilt northeast castle building":([
        "type": "northeast castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;1m",
                "24-bit": "\x1b[0;38;2;128;0;0m"
            ]),
        ]),
        "components":([
            "NC3": ([
                "ascii": ".?.",
                "unicode": "\xe2\x94\x8a\xe2\x81\x87\xe2\x94\x8a",
            ]),
            "NC4": ([
                "ascii": "...",
                "unicode": "\xe2\x94\x94\xe2\x94\x88\xe2\x94\x98",
            ]),
        ]),
    ]),

    "unbuilt first western castle building":([
        "type": "first western castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;9m",
                "24-bit": "\x1b[0;38;2;200;0;0m"
            ]),
        ]),
        "components":([
            "WC1": ([
                "ascii": ".. ",
                "unicode": "\xe2\x94\x88\xe2\x94\x90 ",
            ]),
            "WC2": ([
                "ascii": "?. ",
                "unicode": "\xe2\x81\x87\xe2\x94\x8a ",
            ]),
            "WC3": ([
                "ascii": ".. ",
                "unicode": "\xe2\x94\x88\xe2\x94\x98 ",
            ]),
        ]),
    ]),

    "unbuilt second western castle building":([
        "type": "second western castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;9m",
                "24-bit": "\x1b[0;38;2;200;0;0m"
            ]),
        ]),
        "components":([
            "WC4": ([
                "ascii": ".. ",
                "unicode": "\xe2\x94\x88\xe2\x94\x90 ",
            ]),
            "WC5": ([
                "ascii": "?. ",
                "unicode": "\xe2\x81\x87\xe2\x94\x8a ",
            ]),
            "WC6": ([
                "ascii": ".. ",
                "unicode": "\xe2\x94\x88\xe2\x94\x98 ",
            ]),
        ]),
    ]),

    "unbuilt first eastern castle building":([
        "type": "first eastern castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;9m",
                "24-bit": "\x1b[0;38;2;200;0;0m"
            ]),
        ]),
        "components":([
            "EC1": ([
                "ascii": " ..",
                "unicode": " \xe2\x94\x8c\xe2\x94\x88",
            ]),
            "EC2": ([
                "ascii": " .?",
                "unicode": " \xe2\x94\x8a\xe2\x81\x87",
            ]),
            "EC3": ([
                "ascii": " ..",
                "unicode": " \xe2\x94\x94\xe2\x94\x88",
            ]),
        ]),
    ]),

    "unbuilt second eastern castle building":([
        "type": "second eastern castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;9m",
                "24-bit": "\x1b[0;38;2;200;0;0m"
            ]),
        ]),
        "components":([
            "EC4": ([
                "ascii": " ..",
                "unicode": " \xe2\x94\x8c\xe2\x94\x88",
            ]),
            "EC5": ([
                "ascii": " .?",
                "unicode": " \xe2\x94\x8a\xe2\x81\x87",
            ]),
            "EC6": ([
                "ascii": " ..",
                "unicode": " \xe2\x94\x94\xe2\x94\x88",
            ]),
        ]),
    ]),

    "unbuilt southwest castle building":([
        "type": "southwest castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;1m",
                "24-bit": "\x1b[0;38;2;128;0;0m"
            ]),
        ]),
        "components":([
            "SC1": ([
                "ascii": "...",
                "unicode": "\xe2\x94\x8c\xe2\x94\x88\xe2\x94\x90",
            ]),
            "SC2": ([
                "ascii": ".?.",
                "unicode": "\xe2\x94\x8a\xe2\x81\x87\xe2\x94\x8a",
            ]),
        ]),
    ]),

    "unbuilt southeast castle building":([
        "type": "southeast castle building",
        "dimensions": "2x1",
        "description": "",
        "colors": ([
            "default":([
                "3-bit": "\x1b[0;31m",
                "8-bit": "\x1b[0;38;5;1m",
                "24-bit": "\x1b[0;38;2;128;0;0m"
            ]),
        ]),
        "components":([
            "SC3": ([
                "ascii": "...",
                "unicode": "\xe2\x94\x8c\xe2\x94\x88\xe2\x94\x90",
            ]),
            "SC4": ([
                "ascii": ".?.",
                "unicode": "\xe2\x94\x8a\xe2\x81\x87\xe2\x94\x8a",
            ]),
        ]),
    ]),
]);

#endif
