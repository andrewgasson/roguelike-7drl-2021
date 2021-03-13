# 7DRL 2021
To check out the 7DRL challenge, go to <https://7drl.com/>, or for the 2021 challenge <https://itch.io/jam/7drl-challenge-2021>.

![Screenshot of the Main Menu](https://github.com/andrewgasson/roguelike-7drl-2021/blob/main/Document/Screenshot/Day4MainMenu.png)
![Screenshot of the Game](https://github.com/andrewgasson/roguelike-7drl-2021/blob/main/Document/Screenshot/Day6Game.png)

## Goal
Create a simple Roguelike inspired by the original Rogue and OD&D using Raylib. This will include procedural dungeons, combat, and loot, and if time allows for it, magic, archery, and shops.

## Log
### Day 1 (2021/03/8)
The objective of the day was to implement a basic terminal with player creature movement, rendering, and collisions. This was achieved.

### Day 2 (2021/03/9)
The objective of the day was to implement a view system that handles both GUI and game control. This also included drawing functions for the terminal. This was mostly achieved. The view and view-controller system was implemented. However, the terminal drawing tools are unfinished, which means views such as the prompts are also incomplete. The game and its associated default game view still runs.

### Day 3 (2021/03/10)
The objective of the day was to finish implementing the terminal draw functions and, subsequently, the bool prompt. Once finished, the goal was to create a simple dungeon layout generator. This was achieved. The dungeon generator, though identical to previous behaviour, is now organised in a reasonable location, separate from the game module, and prepared for generation. Additionally, a new input system has been added that can account for holding down keys with pulse triggers, and the potential for key rebindings.

### Day 4 (2021/03/11)
The objective of the day was to implement the message prompt, and expand the dungeon generator. This was mostly achieved. The prompts are complete (though text area doesn't wrap single words to the next line), and the process of adding the features necessary for the dungeon have begun (so far, terrain and doors). The protagonist can now also gain experience and level up.

### Day 5 (2021/03/12)
The objective of the day was to continue implementing features for the dungeon. This was achieved. Now items, inventories, and containers exist. Additionally, sprites now render based on a their layer, and subsequent layer's priority. This fixed the issue where the door was rendered above the player. A new main menu design was also added, which decided the game's theme: vampires.

### Day 6 (2021/03/13)
The objective of the day was to get as much gameplay in as possible. Unfortunately, this was not achieved. Added the ability to pick up items, which are shown in a new inventory view, fixed up bugs with input, and started work on the actor module (turn-based system), but this did not get finished. This game still compiles, but there's no real improvement over the last day.

### Day 7 (2021/03/14)
Because the challenge was started fairly early in the day, there is no time to make any real improvements, so this day was skipped.

## Insight
The real aim of this project was to see how useful, and what problems I would face, using a relation, static memory pool, inline function as namespace, collection-oriented architecture. Surprisingly, I think it scales quite well. It's especially easy, for example, to add behaviours to the creature once modules are set up and their API deicded. The downfall is that modules take some extra thinking since you need to worry about an entire collection's behaviour, rather than just the single instance. Overkill for a 7DRL (at least when starting entirely from scratch), but definitely useful for larger projects.

A lot more progress was made this year than the previous year. I believe that a year focused on finalising common modules means that a much larger Roguelike could come together quickly within the 7 days. GUI utility functions would be especially useful.
