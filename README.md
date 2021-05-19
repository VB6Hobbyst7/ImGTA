This mod helps you debug GTA V scripts by watching and interacting with internal global variables.<br />

Mod menu:
![Mod Menu](https://github.com/Rayope/ImGTA/blob/master/Images/InGameMenu.jpg?raw=true)
![Mod Menu Detail](https://github.com/Rayope/ImGTA/blob/master/Images/InGameMenuDetail.jpg?raw=true)

Mod in game displays:
![Mod Menu](https://github.com/Rayope/ImGTA/blob/master/Images/InGameDisplay.jpg?raw=true)

List of all modules:
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
* Global watcch
  * Watch address (int, float, string, vector, bitfield)
  * Watch address in game
* Handle helper
  * List nearby pedestrians id
  * List nearby vehicles id
  * Show pedestrians and vehicles in game (id, life)
  * Entity list of variables (type, health, injured, model, position, is mission entity)
* Lua console
  * Haven't looked at it but it should be able to call natives...
* Area
  * Draw box in game
  * Check if ped in angled are
  * Check if ped in area
  * Check if ped at coord
* Mission (in development)
  * Mission state (failed/skipped/restarted...)
  * Mission death name (the name written in scripts)
  * Mission list of variables (in development)
* Player switch (in development)
  * Switch variables (in progress, type, state)
  * Player switch locations list of variables
* Synchronized Scene
  * Synchronized scene (loop, set phase, set rate, set hold last frame)
  * List running synchronized scene
