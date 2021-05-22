# ImGTA
This mod helps you debug GTA V scripts by watching and interacting with internal local and global variables.<br />
Some of the functionalities are only available to GTA V build version 372 (online 1.27) because they use global addresses directly and these are dependent on version.<br />
As the information based on globals is reverse engineered, it is sometimes without useful description or it can be wrongly described. Please let us know if you have any correction.

# Mod menu (V1.0)
![Mod Menu](https://github.com/Rayope/ImGTA/blob/master/Images/InGameMenu.jpg?raw=true)
![Mod Menu Detail](https://github.com/Rayope/ImGTA/blob/master/Images/InGameMenuDetail.jpg?raw=true)

# Mod in-game displays (V1.0)
Note:
* It shows nearby animals as well (e.g., Ped 24834)<br />
* The nearby pedestrians and vehicles that are not in the field of view have their information displayed on the sides
![Mod Menu](https://github.com/Rayope/ImGTA/blob/master/Images/InGameDisplay.jpg?raw=true)

# List of all modules
* Cheats (main menu):
  * Player modifications (heal, kill, teleport, add weapon)
  * Vehicle (repair, destroy)
  * World (spawn vehicle)
  * HUD (font sizes)
  * Player debug variables (handle, position, health, armour, speed, speed vector, game time)
* Audio
  * Conversation (restart, stop, pause, skip to next line, start preloaded conversation)
  * Audio scenes (start, set variable, stop)
  * Music events (prepare, trigger, cancel)
  * Audio list of variables ((new) name/source of current conversation)
* Cutscene
  * Cutscene (request (new list with names), list loaded cutscene, unload, start, stop, set variable)
  * Cutscene list of variables
* Scripts
  * List running scripts (name, handle)
  * Start script
* Memory watcher
  * Variable types (int, float, string, vector, bitfield)
  * Watch local (script) variable from index
  * Watch global variable from index
  * Watch addresses in game
* Handle helper
  * List nearby pedestrians id
  * List nearby vehicles id
  * Show pedestrians and vehicles in game (id, life)
  * Entity list of variables (type, health, injured, model, position, is mission entity)
* Lua console
  * Can call all natives directly within the game
* Area
  * Draw box in game
  * Check if ped in angled are
  * Check if ped in area
  * Check if ped at coord
* Mission (in development)
  * Mission state (failed/skipped/restarted...)
  * Mission death name (the name written in scripts)
  * Mission list of variables (mission list, available missions)
* Player switch (in development)
  * Switch variables (in progress, type, state)
  * Player switch locations list of variables
* Comms
  * A stub at the moment
* Synchronized Scene
  * Synchronized scene (loop, set phase, set rate, set hold last frame)
  * List running synchronized scene
