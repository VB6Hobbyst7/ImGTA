#pragma once
#include <string>

int GetSwitchAnimDictName(int iParam0, std::string & sParam1, std::string & sParam2, std::string & sParam3)
{
	switch (iParam0)
	{
	case 11:
		sParam1 = "SWITCH@FRANKLIN@STRIPCLUB";
		sParam2 = "002113_02_FRAS_15_STRIPCLUB_IDLE";
		sParam3 = "002113_02_FRAS_15_STRIPCLUB_EXIT";
		return 1;
		
	case 124:
		sParam1 = "SWITCH@MICHAEL@WASH_FACE";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 234:
		sParam1 = "SWITCH@TREVOR@ON_TOILET";
		sParam2 = "trev_on_toilet_loop";
		sParam3 = "trev_on_toilet_exit";
		return 1;
		
	case 316:
		sParam1 = "SWITCH@TREVOR@JERKING_OFF";
		sParam2 = "trev_jerking_off_loop";
		sParam3 = "trev_jerking_off_exit";
		return 1;
		
	case 77:
		sParam1 = "SWITCH@MICHAEL@BEDROOM";
		sParam2 = "BED_LOOP_Michael";
		sParam3 = "BED_EXIT_Michael";
		return 1;
		
	case 78:
		sParam1 = "SWITCH@MICHAEL@BEDROOM2";
		sParam2 = "BED_LOOP_Michael";
		sParam3 = "BED_EXIT_Michael";
		return 1;
		
	case 79:
		sParam1 = "SAFE@MICHAEL@IG_3";
		sParam2 = "BASE_MICHAEL";
		sParam3 = "EXIT_MICHAEL";
		return 1;
		
	case 80:
		sParam1 = "SWITCH@MICHAEL@SITTING";
		sParam2 = "IDLE";
		sParam3 = "EXIT_FORWARD";
		return 1;
		
	case 82:
		sParam1 = "SWITCH@MICHAEL@WAKES_UP_SCREAMING";
		sParam2 = "001671_02_MICS2_1_WAKES_UP_SCREAMING_IDLE";
		sParam3 = "001671_02_MICS2_1_WAKES_UP_SCREAMING_EXIT";
		return 1;
		
	case 84:
		sParam1 = "SAVECountryside@";
		sParam2 = "M_Sleep_Loop_countryside";
		sParam3 = "M_GetOut_countryside";
		return 1;
		
	case 83:
		sParam1 = "SWITCH@MICHAEL@WAKES_UP_SCARED";
		sParam2 = "001672_02_MICS2_1_WAKES_UP_SCARED_IDLE";
		sParam3 = "001672_02_MICS2_1_WAKES_UP_SCARED_EXIT";
		return 1;
		
	case 85:
		sParam1 = "SWITCH@MICHAEL@WATCHING_TV";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 291:
		sParam1 = "SWITCH@TREVOR@WATCHING_TV";
		sParam2 = "LOOP";
		sParam3 = "EXIT";
		return 1;
		
	case 128:
		sParam1 = "SWITCH@MICHAEL@SITTING";
		sParam2 = "IDLE";
		sParam3 = "EXIT_FORWARD";
		return 1;
		
	case 86:
		sParam1 = "SWITCH@MICHAEL@ON_SOFA";
		sParam2 = "BASE_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 87:
	case 88:
	case 184:
	case 185:
		sParam1 = "SWITCH@MICHAEL@SUNLOUNGER";
		sParam2 = "SunLounger_Idle";
		sParam3 = "SunLounger_GetUp";
		return 1;
		
	case 89:
	case 90:
		sParam1 = "SWITCH@MICHAEL@SLEEP_IN_CAR";
		sParam2 = "BASE_MICHAEL";
		sParam3 = "SLEEP_IN_CAR_MICHAEL";
		return 1;
		
	case 127:
		sParam1 = "SWITCH@MICHAEL@SLEEP_IN_CAR";
		sParam2 = "BASE_PREMIER_MICHAEL";
		sParam3 = "SLEEP_IN_CAR_PREMIER_MICHAEL";
		return 1;
		
	case 91:
	case 92:
	case 93:
	case 104:
	case 81:
	case 126:
		sParam1 = "SWITCH@MICHAEL@SMOKING2";
		sParam2 = "LOOP";
		sParam3 = "EXIT";
		return 1;
		
	case 94:
		sParam1 = "SWITCH@MICHAEL@CAFE";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 95:
		sParam1 = "SWITCH@MICHAEL@EXIT_RESTAURANT";
		sParam2 = "mic_exit_restaurant_loop";
		sParam3 = "mic_exit_restaurant_exit";
		return 1;
		
	case 134:
		sParam1 = "SWITCH@MICHAEL@DRUNK_BAR";
		sParam2 = "Drunk_Idle_PED";
		sParam3 = "Drunk_Exit_PED";
		return 1;
		
	case 108:
	case 109:
		sParam1 = "SWITCH@MICHAEL@PARKBENCH_SMOKE_RANGER";
		sParam2 = "parkbench_smoke_ranger_loop";
		sParam3 = "parkbench_smoke_ranger_exit";
		return 1;
		
	case 112:
	case 113:
	case 123:
		sParam1 = "SWITCH@MICHAEL@SITTING_ON_CAR_BONNET";
		sParam2 = "sitting_on_car_bonnet_loop";
		sParam3 = "sitting_on_car_bonnet_exit";
		return 1;
		
	case 41:
	case 135:
	case 136:
	case 137:
	case 138:
	case 139:
		sParam1 = "SWITCH@MICHAEL@SITTING_ON_CAR_PREMIERE";
		sParam2 = "SITTING_ON_CAR_PREMIERE_LOOP_PLAYER";
		sParam3 = "SITTING_ON_CAR_PREMIERE_EXIT_PLAYER";
		return 1;
		
	case 114:
		sParam1 = "SWITCH@MICHAEL@PHARMACY";
		sParam2 = "mics1_ig_11_loop";
		sParam3 = "mics1_ig_11_exit";
		return 1;
		
	case 105:
		sParam1 = "SWITCH@MICHAEL@STUCKINTRAFFIC";
		sParam2 = "";
		sParam3 = "StuckInTraffic_Aggitated";
		return 1;
		
	case 106:
		sParam1 = "SWITCH@MICHAEL@STUCKINTRAFFIC";
		sParam2 = "";
		sParam3 = "StuckInTraffic_HitWheel";
		return 1;
		
	case 107:
		sParam1 = "SWITCH@MICHAEL@STUCKINTRAFFIC";
		sParam2 = "";
		sParam3 = "StuckInTraffic_HitHorn";
		return 1;
		
	case 98:
		sParam1 = "SWITCH@MICHAEL@AMANDA_EXITS_CAR";
		sParam2 = "000606_02_MICS1_5_AMANDA_EXITS_CAR_IDLE_MIC";
		sParam3 = "000606_02_MICS1_5_AMANDA_EXITS_CAR_EXIT_MIC";
		return 1;
		
	case 170:
		sParam1 = "SWITCH@MICHAEL@OPENS_DOOR_FOR_AMA";
		sParam2 = "001895_02_MICS3_17_OPENS_DOOR_FOR_AMA_IDLE_MIC";
		sParam3 = "001895_02_MICS3_17_OPENS_DOOR_FOR_AMA_EXIT_MIC";
		return 1;
		
	case 171:
		sParam1 = "SWITCH@MICHAEL@DROPPING_OFF_JMY";
		sParam2 = "001839_02_MICS3_20_DROPPING_OFF_JMY_IDLE_MIC";
		sParam3 = "001839_02_MICS3_20_DROPPING_OFF_JMY_EXIT_MIC";
		return 1;
		
	case 172:
		sParam1 = "SWITCH@MICHAEL@TRACY_EXITS_CAR";
		sParam2 = "001840_01_MICS3_IG_21_TRACY_EXITS_CAR_IDLE_MIC";
		sParam3 = "001840_01_MICS3_IG_21_TRACY_EXITS_CAR_MIC";
		return 1;
		
	case 103:
		sParam1 = "SWITCH@MICHAEL@PIER";
		sParam2 = "pier_lean_smoke_idle";
		sParam3 = "pier_lean_smoke_outro";
		return 1;
		
	case 121:
		sParam1 = "SWITCH@MICHAEL@MARINA";
		sParam2 = "loop";
		sParam3 = "exit";
		return 1;
		
	case 122:
		sParam1 = "SWITCH@MICHAEL@ARGUE_WITH_AMANDA";
		sParam2 = "argue_with_amanda_loop_michael";
		sParam3 = "argue_with_amanda_exit_michael";
		return 1;
		
	case 125:
		sParam1 = "SWITCH@MICHAEL@WALK_AND_TALK";
		sParam2 = "";
		sParam3 = "Im_A_Married_Man_Michael";
		return 1;
		
	case 115:
	case 116:
	case 117:
	case 97:
	case 162:
		sParam1 = "SWITCH@MICHAEL@CAFE";
		sParam2 = "Cafe_Idle_PED";
		sParam3 = "Cafe_Exit_PED";
		return 1;
		
	case 110:
	case 111:
	case 131:
	case 132:
		sParam1 = "SWITCH@MICHAEL@BENCH";
		sParam2 = "bench_on_phone_idle";
		sParam3 = "EXIT_FORWARD";
		return 1;
		
	case 129:
		sParam1 = "SWITCH@MICHAEL@ON_CLUBCHAIR";
		sParam2 = "Switch_ON_CLUBCHAIR_BASE";
		sParam3 = "Switch_ON_CLUBCHAIR";
		return 1;
		
	case 130:
		sParam1 = "SAFE@MICHAEL@IG_5";
		sParam2 = "BASE_MICHAEL";
		sParam3 = "EXIT_1_MICHAEL";
		return 1;
		
	case 150:
		sParam1 = "SWITCH@MICHAEL@RONEX_IG_5_P2";
		sParam2 = "BASE_MICHAEL";
		sParam3 = "RONEX_IG5_P2_MICHAEL";
		return 1;
		
	case 151:
		sParam1 = "SWITCH@MICHAEL@RESTAURANT";
		sParam2 = "001510_02_GC_MICS3_IG_1_BASE_MICHAEL";
		sParam3 = "001510_02_GC_MICS3_IG_1_EXIT_MICHAEL";
		return 1;
		
	case 152:
		sParam1 = "SWITCH@MICHAEL@LOUNGE_CHAIRS";
		sParam2 = "001523_01_MICS3_9_LOUNGE_CHAIRS_IDLE_MIC";
		sParam3 = "001523_01_MICS3_9_LOUNGE_CHAIRS_EXIT_MIC";
		return 1;
		
	case 153:
		sParam1 = "SWITCH@MICHAEL@GOODBYE_TO_SOLOMAN";
		sParam2 = "001400_01_MICS3_5_BYE_TO_SOLOMAN_IDLE";
		sParam3 = "001400_01_MICS3_5_BYE_TO_SOLOMAN_EXIT";
		return 1;
		
	case 154:
		sParam1 = "SWITCH@MICHAEL@GOODBYE_TO_SOLOMAN";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 155:
		sParam1 = "SWITCH@MICHAEL@AMA_TENNIS";
		sParam2 = "001833_01_MICS3_18_AMA_TENNIS_IDLE_MIC";
		sParam3 = "001833_01_MICS3_18_AMA_TENNIS_EXIT_MIC";
		return 1;
		
	case 156:
		sParam1 = "SWITCH@MICHAEL@AROUND_THE_TABLE_SELFISH";
		sParam2 = "AROUND_THE_TABLE_SELFISH_BASE_Michael";
		sParam3 = "AROUND_THE_TABLE_SELFISH_Michael";
		return 1;
		
	case 157:
		sParam1 = "SWITCH@MICHAEL@REJECTED_ENTRY";
		sParam2 = "001396_01_MICS3_6_REJECTED_ENTRY_IDLE_MIC";
		sParam3 = "001396_01_MICS3_6_REJECTED_ENTRY_EXIT_MIC";
		return 1;
		
	case 159:
		sParam1 = "SWITCH@MICHAEL@EXITS_BARBER";
		sParam2 = "001406_01_MICS3_7_EXITS_BARBER_IDLE";
		sParam3 = "001406_01_MICS3_7_EXITS_BARBER_EXIT";
		return 1;
		
	case 160:
		sParam1 = "SWITCH@MICHAEL@EXITS_FANCYSHOP";
		sParam2 = "001405_01_MICS3_8_EXITS_FANCYSHOP_IDLE";
		sParam3 = "001405_01_MICS3_8_EXITS_FANCYSHOP_EXIT";
		return 1;
		
	case 161:
		sParam1 = "SWITCH@MICHAEL@SMOKING";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 163:
		sParam1 = "SWITCH@MICHAEL@GETS_READY";
		sParam2 = "001520_02_MICS3_14_GETS_READY_IDLE_MIC";
		sParam3 = "001520_02_MICS3_14_GETS_READY_EXIT_MIC";
		return 1;
		
	case 164:
		sParam1 = "SWITCH@MICHAEL@READS_SCRIPT";
		sParam2 = "001404_01_MICS3_16_READS_SCRIPT_IDLE";
		sParam3 = "001404_01_MICS3_16_READS_SCRIPT_EXIT";
		return 1;
		
	case 165:
		sParam1 = "SWITCH@MICHAEL@BAR_EMPLOYEE_CONVO";
		sParam2 = "001387_03_MICS3_2_BAR_EMPLOYEE_CONVO_IDLE_MIC";
		sParam3 = "001387_03_MICS3_2_BAR_EMPLOYEE_CONVO_EXIT_MIC";
		return 1;
		
	case 158:
		sParam1 = "SWITCH@MICHAEL@PROSTITUTE";
		sParam2 = "BASE_MICHAEL";
		sParam3 = "EXIT_MICHAEL";
		return 1;
		
	case 166:
		sParam1 = "SWITCH@MICHAEL@TALKS_TO_GUARD";
		sParam2 = "001393_02_MICS3_3_TALKS_TO_GUARD_IDLE_MIC";
		sParam3 = "001393_02_MICS3_3_TALKS_TO_GUARD_EXIT_MIC";
		return 1;
		
	case 167:
		sParam1 = "SWITCH@MICHAEL@ON_SET_W_JMY";
		sParam2 = "";
		sParam3 = "001513_03_GC_MICS3_IG_4_ON_SET_W_JMY_EXIT_MIC";
		return 1;
		
	case 168:
		sParam1 = "SWITCH@MICHAEL@TV_W_KIDS";
		sParam2 = "001520_02_MICS3_14_TV_W_KIDS_IDLE_MIC";
		sParam3 = "001520_02_MICS3_14_TV_W_KIDS_EXIT_MIC";
		return 1;
		
	case 173:
		sParam1 = "SWITCH@MICHAEL@BIKING_WITH_JIMMY";
		sParam2 = "LOOP_Michael";
		sParam3 = "EXIT_Michael";
		return 1;
		
	case 169:
		sParam1 = "SWITCH@MICHAEL@GAMING_W_JMY";
		sParam2 = "001518_02_MICS3_11_GAMING_W_JMY_IDLE_MIC";
		sParam3 = "001518_02_MICS3_11_GAMING_W_JMY_EXIT_MIC";
		return 1;
			}
	switch (iParam0)
	{
	case 186:
		sParam1 = "SWITCH@FRANKLIN@CLEANING_APT";
		sParam2 = "001918_01_FRAS_V2_1_CLEANING_APT_IDLE";
		sParam3 = "001918_01_FRAS_V2_1_CLEANING_APT_EXIT";
		return 1;
		
	case 187:
		sParam1 = "SWITCH@FRANKLIN@ON_CELL";
		sParam2 = "001914_01_FRAS_V2_2_ON_CELL_IDLE";
		sParam3 = "001914_01_FRAS_V2_2_ON_CELL_EXIT";
		return 1;
		
	case 188:
		sParam1 = "SWITCH@FRANKLIN@SNACKING";
		sParam2 = "001922_01_FRAS_V2_3_SNACKING_IDLE";
		sParam3 = "001922_01_FRAS_V2_3_SNACKING_EXIT";
		return 1;
		
	case 189:
		sParam1 = "SWITCH@FRANKLIN@ON_LAPTOP";
		sParam2 = "001927_01_FRAS_V2_4_ON_LAPTOP_IDLE";
		sParam3 = "001927_01_FRAS_V2_4_ON_LAPTOP_EXIT";
		return 1;
		
	case 190:
		sParam1 = "SWITCH@FRANKLIN@IRONING";
		sParam2 = "001947_01_GC_FRAS_V2_IG_6_BASE";
		sParam3 = "001947_01_GC_FRAS_V2_IG_6_EXIT";
		return 1;
		
	case 191:
		sParam1 = "SWITCH@FRANKLIN@WATCHING_TV";
		sParam2 = "001915_01_FRAS_V2_8_WATCHING_TV_IDLE";
		sParam3 = "001915_01_FRAS_V2_8_WATCHING_TV_EXIT";
		return 1;
		
	case 175:
	case 176:
		sParam1 = "SWITCH@FRANKLIN@BED";
		sParam2 = "Sleep_LOOP";
		sParam3 = "Sleep_GetUp_RubEyes";
		return 1;
		
	case 177:
		sParam1 = "SWITCH@FRANKLIN@NAPPING";
		sParam2 = "002333_01_FRAS_V2_10_NAPPING_IDLE";
		sParam3 = "002333_01_FRAS_V2_10_NAPPING_EXIT";
		return 1;
		
	case 178:
		sParam1 = "SWITCH@FRANKLIN@GETTING_READY";
		sParam2 = "002334_02_FRAS_V2_11_GETTING_DRESSED_IDLE";
		sParam3 = "002334_02_FRAS_V2_11_GETTING_DRESSED_EXIT";
		return 1;
		
	case 179:
	case 180:
		sParam1 = "SWITCH@FRANKLIN@BED";
		sParam2 = "Bed_Reading_LOOP";
		sParam3 = "Bed_Reading_GetUp";
		return 1;
		
	case 181:
	case 182:
	case 183:
		sParam1 = "SWITCH@FRANKLIN@PRESS_UPS";
		sParam2 = "PressUps_LOOP";
		sParam3 = "PressUps_OUT";
		return 1;
		
	case 192:
		sParam1 = "SWITCH@FRANKLIN@002110_04_MAGD_3_WEED_EXCHANGE";
		sParam2 = "002110_04_MAGD_3_WEED_EXCHANGE_SHOPKEEPER";
		sParam3 = "002110_04_MAGD_3_WEED_EXCHANGE_FRANKLIN";
		return 1;
		
	case 193:
		sParam1 = "SWITCH@FRANKLIN@DISPENSARY";
		sParam2 = "exit_dispensary_idle";
		sParam3 = "exit_dispensary_outro_ped";
		return 1;
		
	case 194:
		sParam1 = "SWITCH@FRANKLIN@DISPENSARY";
		sParam2 = "exit_dispensary_idle";
		sParam3 = "exit_dispensary_outro";
		return 1;
		
	case 195:
		sParam1 = "SWITCH@FRANKLIN@DISPENSARY";
		sParam2 = "exit_dispensary_idle";
		sParam3 = "exit_dispensary_outro";
		return 1;
		
	case 198:
		sParam1 = "SWITCH@FRANKLIN@GARBAGE";
		sParam2 = "Garbage_Idle_PLYR";
		sParam3 = "Garbage_Toss_PLYR";
		return 1;
		
	case 199:
		sParam1 = "SWITCH@FRANKLIN@GARBAGE_B";
		sParam2 = "Garbage_Idle_PLYR";
		sParam3 = "Garbage_Toss_PLYR";
		return 1;
		
	case 200:
		sParam1 = "SWITCH@FRANKLIN@THROW_CUP";
		sParam2 = "throw_cup_loop";
		sParam3 = "throw_cup_exit";
		return 1;
		
	case 201:
		sParam1 = "SWITCH@FRANKLIN@HIT_CUP_HAND";
		sParam2 = "hit_cup_hand_loop";
		sParam3 = "hit_cup_hand_exit";
		return 1;
		
	case 202:
		sParam1 = "SWITCH@FRANKLIN@GYM";
		sParam2 = "001942_02_GC_FRAS_IG_5_BASE";
		sParam3 = "001942_02_GC_FRAS_IG_5_EXIT";
		return 1;
		
	case 203:
	case 206:
	case 207:
		sParam1 = "SWITCH@FRANKLIN@PLAYS_W_DOG";
		sParam2 = "001916_01_FRAS_V2_9_PLAYS_W_DOG_IDLE";
		sParam3 = "001916_01_FRAS_V2_9_PLAYS_W_DOG_EXIT";
		return 1;
		
	case 204:
	case 205:
		sParam1 = "SWITCH@FRANKLIN@PLAYS_W_DOG";
		sParam2 = "001916_01_FRAS_V2_9_PLAYS_W_DOG_IDLE";
		sParam3 = "001916_01_FRAS_V2_9_PLAYS_W_DOG_EXIT";
		return 1;
		
	case 211:
	case 213:
	case 216:
	case 217:
		sParam1 = "SWITCH@FRANKLIN@ADMIRE_MOTORCYCLE";
		sParam2 = "BASE_FRANKLIN";
		sParam3 = "EXIT_FRANKLIN";
		return 1;
		
	case 212:
	case 214:
		sParam1 = "SWITCH@FRANKLIN@CLEANING_CAR";
		sParam2 = "001946_01_GC_FRAS_V2_IG_5_BASE";
		sParam3 = "001946_01_GC_FRAS_V2_IG_5_EXIT";
		return 1;
		
	case 196:
		sParam1 = "SWITCH@FRANKLIN@TANISHA_ARGUE";
		sParam2 = "BASE_Franklin";
		sParam3 = "Tanisha_Argue_Franklin";
		return 1;
		
	case 197:
		sParam1 = "SWITCH@FRANKLIN@WALK_AROUND_HOUSE";
		sParam2 = "IDLE_FRANKLIN";
		sParam3 = "EXIT_FRANKLIN";
		return 1;
		
	case 215:
		sParam1 = "SWITCH@FRANKLIN@BYE_TAXI";
		sParam2 = "001938_01_FRAS_V2_7_BYE_TAXI_IDLE_FRA";
		sParam3 = "001938_01_FRAS_V2_7_BYE_TAXI_EXIT_FRA";
		return 1;
		
	case 221:
		sParam1 = "SWITCH@FRANKLIN@PICKUP_LINE";
		sParam2 = "base_Franklin";
		sParam3 = "switch_P1_Franklin";
		return 1;
		
	case 222:
		sParam1 = "SWITCH@FRANKLIN@CHOPSHOP";
		sParam2 = "BASE";
		sParam3 = "CheckShoe";
		return 1;
		
	case 223:
		sParam1 = "SWITCH@FRANKLIN@CHOPSHOP";
		sParam2 = "BASE";
		sParam3 = "WipeHands";
		return 1;
		
	case 224:
		sParam1 = "SWITCH@FRANKLIN@CHOPSHOP";
		sParam2 = "BASE";
		sParam3 = "WipeRight";
		return 1;
		
	case 226:
	case 227:
	case 230:
		sParam1 = "SWITCH@FRANKLIN@EXIT_BUILDING";
		sParam2 = "loop";
		sParam3 = "switch_01";
		return 1;
		
	case 228:
	case 229:
		sParam1 = "SWITCH@FRANKLIN@EXIT_BUILDING";
		sParam2 = "loop";
		sParam3 = "switch_02";
		return 1;
		
	case 218:
		sParam1 = "SWITCH@FRANKLIN@GANG_TAUNT_P1";
		sParam2 = "gang_taunt_loop_franklin";
		sParam3 = "gang_taunt_exit_franklin";
		return 1;
		
	case 219:
		sParam1 = "SWITCH@FRANKLIN@GANG_TAUNT_P3";
		sParam2 = "gang_taunt_with_lamar_loop_frank";
		sParam3 = "gang_taunt_with_lamar_exit_frank";
		return 1;
		
	case 220:
		sParam1 = "SWITCH@FRANKLIN@GANG_TAUNT_P5";
		sParam2 = "fras_ig_6_p5_loop_frank";
		sParam3 = "fras_ig_6_p5_exit_frank";
		return 1;
		
	case 225:
		sParam1 = "SWITCH@FRANKLIN@GANG_TAUNT_P3";
		sParam2 = "fras_ig_10_p3_loop_frank";
		sParam3 = "fras_ig_10_p3_exit_frank";
		return 1;
		
	case 232:
	case 233:
		sParam1 = "missheist_agency2aig_9";
		sParam2 = "Franklin_call_Michael_IDLE_PLAYER";
		sParam3 = "Franklin_call_Michael_EXIT_PLAYER";
		return 1;
		
	case 235:
		sParam1 = "SWITCH@TREVOR@MOCKS_LAPDANCE";
		sParam2 = "001443_01_TRVS_28_IDLE_TRV";
		sParam3 = "001443_01_TRVS_28_EXIT_TRV";
		return 1;
		
	case 236:
		sParam1 = "SWITCH@TREVOR@BAR";
		sParam2 = "LOOP_Trevor";
		sParam3 = "EXIT_Trevor";
		return 1;
		
	case 237:
		sParam1 = "SWITCH@TREVOR@CHASE_STRIPPERS";
		sParam2 = "LOOP_Trevor";
		sParam3 = "EXIT_Trevor";
		return 1;
		
	case 238:
		sParam1 = "SWITCH@TREVOR@STRIPCLUB";
		sParam2 = "trev_leave_stripclub_idle";
		sParam3 = "trev_leave_stripclub_outro";
		return 1;
		
	case 239:
		sParam1 = "SWITCH@TREVOR@ESCORTED_OUT";
		sParam2 = "001215_02_TRVS_12_ESCORTED_OUT_IDLE_TRV";
		sParam3 = "001215_02_TRVS_12_ESCORTED_OUT_EXIT_TRV";
		return 1;
		
	case 273:
	case 274:
		sParam1 = "SWITCH@TREVOR@PUKING_INTO_FOUNTAIN";
		sParam2 = "trev_fountain_puke_loop";
		sParam3 = "trev_fountain_puke_exit";
		return 1;
		
	case 245:
	case 40:
		sParam1 = "SWITCH@TREVOR@TREV_SMOKING_METH";
		sParam2 = "TREV_SMOKING_METH_LOOP";
		sParam3 = "TREV_SMOKING_METH_EXIT";
		return 1;
		
	case 315:
		sParam1 = "SWITCH@TREVOR@HEAD_IN_SINK";
		sParam2 = "trev_sink_idle";
		sParam3 = "trev_sink_exit";
		return 1;
		
	case 250:
	case 251:
	case 252:
	case 253:
		sParam1 = "SWITCH@TREVOR@AT_THE_DOCKS";
		sParam2 = "001209_01_TRVS_3_AT_THE_DOCKS_IDLE";
		sParam3 = "001209_01_TRVS_3_AT_THE_DOCKS_EXIT";
		return 1;
		
	case 262:
		sParam1 = "SWITCH@TREVOR@KO_NEIGHBOUR";
		sParam2 = "001500_03_TRVS_19_KO_NEIGHBOUR_LOOP_TRV";
		sParam3 = "001500_03_TRVS_19_KO_NEIGHBOUR_EXIT_TRV";
		return 1;
		
	case 243:
		sParam1 = "SWITCH@TREVOR@GARBAGE_FOOD";
		sParam2 = "LOOP_Trevor";
		sParam3 = "EXIT_Trevor";
		return 1;
		
	case 244:
		sParam1 = "SWITCH@TREVOR@THROW_FOOD";
		sParam2 = "LOOP_Trevor";
		sParam3 = "EXIT_Trevor";
		return 1;
		
	case 271:
	case 272:
	case 265:
	case 266:
	case 267:
	case 268:
	case 269:
	case 270:
	case 279:
	case 240:
	case 241:
	case 242:
		sParam1 = "SWITCH@TREVOR@SLOUCHED_GET_UP";
		sParam2 = "TREV_SLOUCHED_GET_UP_IDLE";
		sParam3 = "TREV_SLOUCHED_GET_UP_EXIT";
		return 1;
		
	case 280:
		sParam1 = "SWITCH@TREVOR@NAKED_ISLAND";
		sParam2 = "loop";
		sParam3 = "exit";
		return 1;
		
	case 246:
		sParam1 = "SWITCH@TREVOR@PUSHES_BODYBUILDER";
		sParam2 = "001426_03_TRVS_5_PUSHES_BODYBUILDER_IDLE_TRV";
		sParam3 = "001426_03_TRVS_5_PUSHES_BODYBUILDER_EXIT_TRV";
		return 1;
		
	case 286:
		sParam1 = "SWITCH@TREVOR@RUDE_AT_CAFE";
		sParam2 = "001218_03_TRVS_23_RUDE_AT_CAFE_IDLE_TRV";
		sParam3 = "001218_03_TRVS_23_RUDE_AT_CAFE_EXIT_TRV";
		return 1;
		
	case 247:
		sParam1 = "SWITCH@TREVOR@ANNOYS_SUNBATHERS";
		sParam2 = "trev_annoys_sunbathers_loop_trevor";
		sParam3 = "trev_annoys_sunbathers_exit_trevor";
		return 1;
		
	case 263:
		sParam1 = "SWITCH@TREVOR@SCARES_TRAMP";
		sParam2 = "TREV_SCARES_TRAMP_IDLE_TREVOR";
		sParam3 = "TREV_SCARES_TRAMP_EXIT_TREVOR";
		return 1;
		
	case 278:
		sParam1 = "SWITCH@TREVOR@NAKED_ON_BRIDGE";
		sParam2 = "002055_01_TRVS_17_NAKED_ON_BRIDGE_IDLE";
		sParam3 = "002055_01_TRVS_17_NAKED_ON_BRIDGE_EXIT";
		return 1;
		
	case 264:
		sParam1 = "SWITCH@TREVOR@DUMPSTER";
		sParam2 = "002002_01_TRVS_14_DUMPSTER_IDLE";
		sParam3 = "002002_01_TRVS_14_DUMPSTER_EXIT";
		return 1;
		
	case 255:
		sParam1 = "SWITCH@TREVOR@FUNERAL_HOME";
		sParam2 = "trvs_ig_11_loop";
		sParam3 = "trvs_ig_11_exit";
		return 1;
		
	case 285:
		sParam1 = "SWITCH@TREVOR@BRIDGE";
		sParam2 = "HOLD_LOOP_trevor";
		sParam3 = "THROW_EXIT_trevor";
		return 1;
		
	case 259:
		sParam1 = "SWITCH@TREVOR@YELLS_AT_DOORMAN";
		sParam2 = "001430_01_TRVS_21_YELLS_AT_DOORMAN_IDLE_TRV";
		sParam3 = "001430_01_TRVS_21_YELLS_AT_DOORMAN_EXIT_TRV";
		return 1;
		
	case 248:
		sParam1 = "SWITCH@TREVOR@BLOCK_CAMERA";
		sParam2 = "001220_03_GC_TRVS_IG_7_BASE_TREVOR";
		sParam3 = "001220_03_GC_TRVS_IG_7_EXIT_TREVOR";
		return 1;
		
	case 249:
		sParam1 = "SWITCH@TREVOR@GUITAR_BEATDOWN";
		sParam2 = "001370_02_TRVS_8_GUITAR_BEATDOWN_IDLE_TRV";
		sParam3 = "001370_02_TRVS_8_GUITAR_BEATDOWN_EXIT_TRV";
		return 1;
		
	case 254:
		sParam1 = "SWITCH@TREVOR@LINGERIE_SHOP";
		sParam2 = "trev_exit_lingerie_shop_idle";
		sParam3 = "trev_exit_lingerie_shop_outro";
		return 1;
		
	case 287:
		sParam1 = "SWITCH@TREVOR@RAND_TEMPLE";
		sParam2 = "";
		sParam3 = "TAI_CHI_Trevor";
		return 1;
		
	case 288:
		sParam1 = "SWITCH@TREVOR@UNDER_PIER";
		sParam2 = "LOOP_Trevor";
		sParam3 = "EXIT_Trevor";
		return 1;
		
	case 289:
		sParam1 = "SWITCH@TREVOR@DRUNK_HOWLING";
		sParam2 = "loop";
		sParam3 = "exit";
		return 1;
		
	case 290:
		sParam1 = "SWITCH@TREVOR@DRUNK_HOWLING_SC";
		sParam2 = "loop";
		sParam3 = "exit";
		return 1;
		
	case 292:
	case 295:
		sParam1 = "SWITCH@TREVOR@BED";
		sParam2 = "Bed_Sleep_TREVOR";
		sParam3 = "Bed_GetUp_1_TREVOR";
		return 1;
		
	case 293:
	case 294:
		sParam1 = "SWITCH@TREVOR@BED";
		sParam2 = "Bed_Sleep_TREVOR";
		sParam3 = "Bed_GetUp_2_TREVOR";
		return 1;
		
	case 299:
		sParam1 = "SWITCH@TREVOR@FLOYD_CRYING";
		sParam2 = "Console_LOOP_TREVOR";
		sParam3 = "Console_Wasnt_Fun_TREVOR";
		return 1;
		
	case 300:
	case 301:
	case 302:
	case 303:
		sParam1 = "SWITCH@TREVOR@FLOYD_CRYING";
		sParam2 = "Console_LOOP_TREVOR";
		sParam3 = "Console_Get_Along_TREVOR";
		return 1;
		
	case 296:
		sParam1 = "SWITCH@TREVOR@BEAR_IN_FLOYDS_FACE";
		sParam2 = "bear_in_floyds_face_loop_trev";
		sParam3 = "bear_in_floyds_face_exit_trev";
		return 1;
		
	case 297:
		sParam1 = "SWITCH@TREVOR@BEAR_FLOYDS_FACE_SMELL";
		sParam2 = "bear_floyds_face_smell_loop_trev";
		sParam3 = "bear_floyds_face_smell_exit_trev";
		return 1;
		
	case 298:
		sParam1 = "SWITCH@TREVOR@PINEAPPLE";
		sParam2 = "Pineapple_LOOP_TREVOR";
		sParam3 = "Pineapple_EXIT_TREVOR";
		return 1;
		
	case 304:
		sParam1 = "SWITCH@MICHAEL@SMOKING2";
		sParam2 = "LOOP";
		sParam3 = "EXIT";
		return 1;
		
	case 305:
		sParam1 = "AMB@WORLD_HUMAN_SMOKING@MALE@MALE_A@IDLE_A";
		sParam2 = "IDLE_A";
		sParam3 = "IDLE_A";
		return 1;

	case 310:
		sParam1 = "SWITCH@TREVOR@DIGGING";
		sParam2 = "001433_01_TRVS_26_DIGGING_IDLE";
		sParam3 = "001433_01_TRVS_26_DIGGING_EXIT";
		return 1;
		
	case 311:
		sParam1 = "SWITCH@TREVOR@FLUSHES_FOOT";
		sParam2 = "002057_03_TRVS_27_FLUSHES_FOOT_IDLE";
		sParam3 = "002057_03_TRVS_27_FLUSHES_FOOT_EXIT";
		return 1;
			}
	sParam1 = "NULL";
	sParam2 = "NULL";
	sParam3 = "NULL";
	return 0;
}