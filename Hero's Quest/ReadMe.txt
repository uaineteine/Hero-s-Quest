========================================================================
    CONSOLE APPLICATION : Hero's Quest Project Overview
========================================================================

AppWizard has created this Hero's Quest application for you.

This file contains a summary of what you will find in each of the files that
make up your Hero's Quest application.


Hero's Quest.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Hero's Quest.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Hero's Quest.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Hero's Quest.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

Please see class diagram PDF in folder of Hero Quest.

I introduced a delay function which will use windows libraries to pause the console for a 
certain time or unix libraries depending on the OS (theortically)
See the delay void(s).

The game works by taking the charater class and constructing an item, player and monster 
class by inheriting its members. Therefore all these classes inherit a name and status points
for attack, defence, health, etc. The attacks and damages in the classes are self contained
by using pointers requiriing no external top level alteration to the classes member data.

For extra functionality the prize money was given a use to buy player items and buffs. Some are 
constant, others are consumable items during the fight. The player class contains a vector of 
items, and the ability to purchase them from the top levelclass. Additionally the player has
levels that go up as the fights go on, allowing them to choose a skill to increase.

The main function code is broken up into respective voids:

Initialise()
-Before the game begins it sets the values for the monster and items arrays,and then asks for the
player information.

The game is then looped and prints the game 'scren' via PrintGameScreen()
-This void takes the current monster you are fighting, the player and prints out their stats and
health bars on the top of the screen. Both the player and monster have their health bars made from
the function GetHealthBar(float current, float max) which returns a 10 character long bar.
Like so: [::::::  ]

Each round in the loop asks the player if they want to use an item, or attack the enemy monster.
If they want to consume an item:
-ConsumeItem()
--They go through the selection of an item from a printed list and then that item is consumed from the
--class level and the pointer to the item on the player's vector is erased.

If they want to attack:
-If the monster's health goes below zero, the player won the round. This triggers the PlayerWinsFight()
-void.
--This void adds the prize money from the monster 'value' and also will level up the player.

Once the player wins a round then they can GoShopping()
-This will print the shopping list and let a player choose an item/ or items to buy. It will not allow
a player to buy multiple items, and will state if they have it already in the list. (including consumables).

If a monster dies and it is the last monster, the player wins with a victory screen.
If he dies, well... You get a very bad oh no.

Most fields of the classes are strictly private with public functions to retrieve or set their
values. This and the introduction of pointers made managing memory far more efficient and less
likely to result in errors, making all alterations to variables done in a private manner.

/////////////////////////////////////////////////////////////////////////////
