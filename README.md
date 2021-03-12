# 7DRL 2021
To check out the 7DRL challenge, go to <https://7drl.com/>, or for the 2021 challenge <https://itch.io/jam/7drl-challenge-2021>.

![Screenshot of the Main Menu](https://github.com/andrewgasson/roguelike-7drl-2021/blob/master/Document/Screenshot/Day4MainMenu.png)

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
