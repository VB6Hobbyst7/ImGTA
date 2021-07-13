// Made from https://www.se7ensins.com/forums/threads/ref-gta-v-vehicle-hashes-list-2.1615439/
#pragma once
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, std::vector<std::string>> vehicle_names = {
	{"bicycle", {"bmx", "cruiser", "fixter", "scorcher", "tribike", "tribike2", "tribike3"}},
	{"boat", {"dinghy", "dinghy2", "dinghy3", "dinghy4", "jetmax", "marquis", "predator", "seashark", "seashark2", "seashark3", "speeder", "speeder2", "squalo", "submersible", "submersible2", "suntrap", "toro", "toro2", "tropic", "tropic2", "tug"}},
	{"commercial", {"cerberus", "cerberus2", "cerberus3", "hauler2", "mule4", "phantom3", "pounder2", "terbyte"}},
	{"compact", {"blista", "brioso", "dilettante", "dilettante2", "issi2", "issi3", "issi4", "issi5", "issi6", "panto", "prairie", "rhapsody"}},
	{"coupe", {"cogcabrio", "exemplar", "f620", "faction", "faction2", "felon", "felon2", "jackal", "sentinel", "sentinel2", "windsor", "windsor2", "zion", "zion2"}},
	{"emergency", {"ambulance", "barracks", "barracks2", "barracks3", "crusader", "fbi", "fbi2", "firetruk", "lguard", "pbus", "police", "police2", "police3", "police4", "policeb", "policeold1", "policeold2", "policet", "pranger", "rhino", "riot", "riot2", "sheriff", "sheriff2"}},
	{"helicopter", {"akula", "annihilator", "blimp", "blimp2", "buzzard", "buzzard2", "cargobob", "cargobob2", "cargobob3", "cargobob4", "frogger", "frogger2", "havok", "hunter", "maverick", "polmav", "savage", "seasparrow", "skylift", "supervolito", "supervolito2", "swift", "swift2", "valkyrie", "valkyrie2", "volatus"}},
	{"military", {"apc", "barrage", "chernobog", "halftrack", "khanjali", "scarab", "scarab2", "scarab3", "thruster", "trailersmall2", "vigilante"}},
	{"motorcycle", {"akuma", "avarus", "bagger", "bati", "bati2", "bf400", "carbonrs", "chimera", "cliffhanger", "daemon", "daemon2", "deathbike", "deathbike2", "deathbike3", "defiler", "diablous", "diablous2", "double", "enduro", "esskey", "faggio", "faggio2", "faggio3", "faggion", "fcr", "fcr2", "gargoyle", "hakuchou", "hakuchou2", "hexer", "innovation", "lectro", "manchez", "nemesis", "nightblade", "oppressor", "oppressor2", "pcj", "ratbike", "rrocket", "ruffian", "sanchez", "sanchez2", "sanctus", "shotaro", "sovereign", "thrust", "vader", "vindicator", "vortex", "wolfsbane", "zombiea", "zombieb"}},
	{"muscle", {"blade", "btype2", "buccaneer", "buccaneer2", "chino", "chino2", "clique", "deviant", "dominator", "dominator2", "dominator3", "dominator4", "dominator5", "dominator6", "dukes", "dukes2", "ellie", "faction3", "gauntlet", "gauntlet2", "gauntlet3", "gauntlet4", "hermes", "hotknife", "hustler", "impaler", "impaler2", "impaler3", "impaler4", "imperator", "imperator2", "imperator3", "minivan2", "nightshade", "peyote2", "phoenix", "picador", "ruiner", "sabregt", "sabregt2", "slamvan", "slamvan2", "slamvan3", "slamvan4", "slamvan5", "slamvan6", "stalion", "stalion2", "tampa", "tampa2", "tampa3", "tornado5", "tornado6", "tulip", "vamos", "vigero", "virgo", "virgo2", "virgo3", "voodoo", "voodoo2", "yosemite"}},
	{"offroad", {"bfinjection", "bifta", "blazer", "blazer2", "blazer3", "blazer4", "blazer5", "bodhi2", "brawler", "bruiser", "bruiser2", "bruiser3", "brutus", "brutus2", "brutus3", "caracara", "caracara2", "dloader", "dubsta3", "dune", "dune2", "dune3", "dune4", "dune5", "freecrawler", "guardian", "hellion", "insurgent", "insurgent2", "insurgent3", "kalahari", "kamacho", "marshall", "menacer", "mesa3", "monster", "monster3", "monster4", "monster5", "nightshark", "rancherxl", "rancherxl2", "rcbandito", "rebel", "rebel2", "riata", "sandking", "sandking2", "technical", "technical2", "technical3", "trophytruck", "trophytruck2"}},
	{"pickup", {"bison", "bison2", "bison3", "bobcatxl", "contender", "ratloader", "ratloader2", "sadler", "sadler2"}},
	{"plane", {"alphaz1", "avenger", "avenger2", "besra", "blimp3", "bombushka", "cargoplane", "cuban800", "dodo", "duster", "howard", "hydra", "jet", "lazer", "luxor", "luxor2", "mammatus", "microlight", "miljet", "mogul", "molotok", "nimbus", "nokota", "pyro", "rogue", "seabreeze", "shamal", "starling", "strikeforce", "stunt", "titan", "tula", "velum", "velum2", "vestra", "volatol"}},
	{"sedan", {"asea", "asea2", "asterope", "cog55", "cog552", "cognoscenti", "cognoscenti2", "emperor", "emperor2", "emperor3", "fugitive", "glendale", "ingot", "intruder", "limo2", "oracle", "oracle2", "premier", "primo", "primo2", "regina", "romero", "schafter2", "schafter3", "schafter4", "schafter5", "schafter6", "stafford", "stanier", "stratum", "stretch", "superd", "surge", "tailgater", "taxi", "warrener", "washington"}},
	{"service", {"airbus", "airtug", "brickade", "bulldozer", "bus", "cablecar", "caddy", "caddy2", "coach", "forklift", "mower", "pbus2", "rentalbus", "ripley", "tourbus", "tractor", "tractor2", "tractor3", "trash", "trash2", "utillitruck", "utillitruck2", "utillitruck3"}},
	{"sport", {"alpha", "banshee", "bestiagts", "blista2", "blista3", "buffalo", "buffalo2", "buffalo3", "carbonizzare", "comet2", "comet3", "comet4", "comet5", "coquette", "drafter", "elegy", "elegy2", "feltzer2", "flashgt", "furoregt", "fusilade", "futo", "gb200", "hotring", "infernus2", "issi7", "italigto", "jester", "jester2", "jugular", "khamelion", "kuruma", "kuruma2", "locust", "lynx", "mamba", "massacro", "massacro2", "neo", "neon", "ninef", "ninef2", "omnis", "paragon", "paragon2", "pariah", "penumbra", "raiden", "rapidgt", "rapidgt2", "raptor", "revolter", "ruiner2", "ruiner3", "ruston", "schlagen", "schwarzer", "sentinel3", "seven70", "specter", "specter2", "streiter", "sultan", "surano", "tropos", "verlierer2", "zr380", "zr3802", "zr3803"}},
	{"sportsclassic", {"ardent", "btype", "btype3", "casco", "cheburek", "cheetah2", "coquette2", "coquette3", "deluxo", "dynasty", "fagaloa", "feltzer3", "gt500", "jb700", "jester3", "lurcher", "manana", "michelli", "monroe", "nebula", "peyote", "pigalle", "rapidgt3", "retinue", "savestra", "stinger", "stingergt", "stromberg", "swinger", "torero", "tornado", "tornado2", "tornado3", "tornado4", "viseris", "z190", "zion3", "ztype"}},
	{"supercar", {"adder", "autarch", "banshee2", "bullet", "cheetah", "cyclone", "deveste", "emerus", "entity2", "entityxf", "fmj", "gp1", "infernus", "italigtb", "italigtb2", "krieger", "le7b", "nero", "nero2", "osiris", "penetrator", "pfister811", "prototipo", "reaper", "s80", "sc1", "scramjet", "sheava", "sultanrs", "t20", "taipan", "tempesta", "tezeract", "thrax", "turismo2", "turismor", "tyrant", "tyrus", "vacca", "vagner", "visione", "voltic", "voltic2", "wastelander", "xa21", "zentorno", "zorrusso"}},
	{"suv", {"baller", "baller2", "baller3", "baller4", "baller5", "baller6", "bjxl", "cavalcade", "cavalcade2", "dubsta", "dubsta2", "fq2", "granger", "gresley", "habanero", "huntley", "landstalker", "mesa", "mesa2", "novak", "patriot", "patriot2", "radi", "rocoto", "seminole", "serrano", "toros", "xls", "xls2"}},
	{"trailer", {"armytanker", "armytrailer", "armytrailer2", "baletrailer", "boattrailer", "docktrailer", "freighttrailer", "graintrailer", "proptrailer", "raketrailer", "tanker", "tanker2", "tr2", "tr3", "tr4", "trailerlogs", "trailers", "trailers2", "trailers3", "trailersmall", "trflat", "tvtrailer"}},
	{"train", {"freight", "freightcar", "freightcont1", "freightcont2", "freightgrain", "metrotrain", "tankercar"}},
	{"truck", {"benson", "biff", "boxville", "boxville2", "boxville3", "boxville4", "boxville5", "cutter", "docktug", "dump", "flatbed", "handler", "hauler", "mixer", "mixer2", "mule", "mule2", "mule3", "packer", "phantom", "phantom2", "pounder", "rallytruck", "rubble", "scrap", "stockade", "stockade3", "tiptruck", "tiptruck2", "towtruck", "towtruck2"}},
	{"utility", {"caddy3", "trailerlarge", "trailers4"}},
	{"van", {"burrito", "burrito2", "burrito3", "burrito4", "burrito5", "camper", "gburrito", "gburrito2", "journey", "minivan", "moonbeam", "moonbeam2", "paradise", "pony", "pony2", "rumpo", "rumpo2", "rumpo3", "speedo", "speedo2", "speedo4", "surfer", "surfer2", "taco", "youga", "youga2"}}
};