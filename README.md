# ImGTA
This mod helps you debug GTA V scripts by watching and interacting with internal local and global variables.<br />
Some of the functionalities are only available to GTA V build version 372 (online 1.27) because they use global addresses directly and these are dependent on version.<br />
As the information based on globals is reverse engineered, it is sometimes without useful description or it can be wrongly described. Please let us know if you have any correction.

# Mod menu (V1.2)
![Mod Menu Detail](https://github.com/Rayope/ImGTA/blob/master/Images/InGameMenuDetail.jpg?raw=true)

# Mod in-game displays (V1.2)
![Mod Menu](https://github.com/Rayope/ImGTA/blob/master/Images/InGameHUD.jpg?raw=true)
Notes:
* It shows nearby animals as well<br />

# List of all modules (V1.2)
* Cheats (main menu):
  * Player modifications (heal, kill, teleport, add weapon)
  * Vehicle (repair, destroy)
  * World (spawn vehicle)
  * HUD (font sizes/color, km/h - m/s, show available inputs)
  * Player debug variables (handle, position, health, armour, speed, speed vector, game time)
* Audio
  * Conversation (restart, stop, pause, skip to next line, start preloaded conversation)
  * Audio scenes (start, set variable, stop)
  * Music events (prepare, trigger, cancel)
  * Audio list of variables (name/source of current conversation)
* Cutscene
  * Cutscene (request (list with names), unload, start, stop, set variable, set thread owner)
  * Cutscene list of variables for the currently loaded one
* Scripts
  * List running scripts (name, handle)
  * Display in game
  * Pin a script to the top of display
  * Order scripts by name/handle
  * Start/Terminate script
  * Loading screen (toggle)
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
  * Call all natives directly within the game
  * Autocompletion for natives
  * Command history
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
* Comms (in development)
  * A stub at the moment
* Synchronized Scene
  * Synchronized scene (loop, set phase, set rate, set hold last frame)
  * List running synchronized scene
* User settings

# Instructions for developers
ScriptHookV
* You must download ScriptHookV SDK [here](http://www.dev-c.com/gtav/scripthookv/)
* Extract the archive in Libraries/ScriptHookV_SDK
	After extracting, you should have at least these two folders: Libraries/ScriptHookV_SDK/inc and Libraries/ScriptHookV_SDK/lib
* Then you need to update (replace) Libraries/ScriptHookV_SDK/inc/natives.h with the updated one provided in Libraries/UpdatedNatives/natives.h


# Indirect contributors
Thank you to everyone that indirectly contributed to this mod's functionalities:
* GTA V Speedruns discord members (https://www.speedrun.com/gtav):  All its coding community and special mentions to: Parik, Gogsi123, Justice
* Script research: https://github.com/drunderscore/GTA-Research
* Native DB 1: http://www.dev-c.com/nativedb/
* Native DB 2: https://alloc8or.re/gta5/nativedb/
