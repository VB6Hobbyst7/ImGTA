#include "strangers_and_freaks_names.h"

#include <cstring>
// Functions taken GTA V decompiled scripts... For some reason the strangers and freaks data is not stored in Globals...

void GetStrangersAndFreaksArray(int iParam0, StrangersAndFreaksArray & uParam1)//Position - 0xD23
{
	switch (iParam0)
	{
	case 0:
		func_12(uParam1, "Abigail1", func_14(iParam0), 0, 0, 4, -1604.668f, 5239.1f, 3.01f, 66, "", 109, 0, "ambient_Diving", 0, 0, 1, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 1:
		func_12(uParam1, "Abigail2", func_14(iParam0), 0, 0, 4, -1592.84f, 5214.04f, 3.01f, 400, "", 110, 0, "", 0, 0, -1, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 2:
		func_12(uParam1, "Barry1", func_14(iParam0), 0, 1, 4, 190.26f, -956.35f, 29.63f, 381, "", 74, 0, "", 0, 1, -1, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 3:
		func_12(uParam1, "Barry2", func_14(iParam0), 0, 1, 4, 190.26f, -956.35f, 29.63f, 381, "", -1, 0, "", 0, 1, -1, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 4:
		func_12(uParam1, "Barry3", func_14(iParam0), 0, 1, 4, 414.0f, -761.0f, 29.0f, 381, "", -1, 0, "", 164, 1, -1, 0, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 5:
		func_12(uParam1, "Barry3A", func_14(iParam0), 1, 1, 0, 1199.27f, -1255.63f, 34.23f, 381, "BARSTASH", 84, 0, "", 166, 0, 7, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 6:
		func_12(uParam1, "Barry3C", func_14(iParam0), 3, 1, 0, -468.9f, -1713.06f, 18.21f, 381, "", 84, 0, "", 166, 0, 7, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 7:
		func_12(uParam1, "Barry4", func_14(iParam0), 0, 1, 4, 237.65f, -385.41f, 44.4f, 381, "", 85, 0, "postRC_Barry4", 0, 0, -1, 4, 2, 800, 2000, func_13(iParam0), 0, 0);
		break;

	case 8:
		func_12(uParam1, "Dreyfuss1", func_14(iParam0), 0, 2, 4, -1458.97f, 485.99f, 115.38f, 66, "LETTERS_HINT", 106, 0, "", 0, 0, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 9:
		func_12(uParam1, "Epsilon1", func_14(iParam0), 0, 3, 4, -1622.89f, 4204.87f, 83.3f, 66, "", 86, 0, "", 0, 1, 10, 4, 1, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 10:
		func_12(uParam1, "Epsilon2", func_14(iParam0), 0, 3, 4, 242.7f, 362.7f, 104.74f, 206, "", 87, 16, "", 0, 0, 11, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 11:
		func_12(uParam1, "Epsilon3", func_14(iParam0), 0, 3, 4, 1835.53f, 4705.86f, 38.1f, 206, "", 88, 16, "epsCars", 0, 0, 12, 4, 1, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 12:
		func_12(uParam1, "Epsilon4", func_14(iParam0), 0, 3, 4, 1826.13f, 4698.88f, 38.92f, 206, "", 90, 16, "postRC_Epsilon4", 0, 0, 13, 4, 1, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 13:
		func_12(uParam1, "Epsilon5", func_14(iParam0), 0, 3, 4, 637.02f, 119.7093f, 89.5f, 206, "", 89, 16, "epsRobes", 0, 0, 14, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 14:
		func_12(uParam1, "Epsilon6", func_14(iParam0), 0, 3, 4, -2892.93f, 3192.37f, 11.66f, 206, "", 93, 0, "", 0, 0, 15, 4, 1, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 15:
		func_12(uParam1, "Epsilon7", func_14(iParam0), 0, 3, 4, 524.43f, 3079.82f, 39.48f, 206, "", -1, 16, "epsDesert", 0, 0, 16, 4, 1, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 16:
		func_12(uParam1, "Epsilon8", func_14(iParam0), 0, 3, 4, -697.75f, 45.38f, 43.03f, 206, "", 94, 16, "epsilonTract", 0, 0, -1, 4, 1, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 17:
		func_12(uParam1, "Extreme1", func_14(iParam0), 0, 4, 4, -188.22f, 1296.1f, 302.86f, 66, "", -1, 0, "", 4, 1, 18, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 18:
		func_12(uParam1, "Extreme2", func_14(iParam0), 0, 4, 4, -954.19f, -2760.05f, 14.64f, 382, "", 96, 0, "", 171, 0, 19, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 19:
		func_12(uParam1, "Extreme3", func_14(iParam0), 0, 4, 4, -63.8f, -809.5f, 321.8f, 382, "", 97, 0, "", 0, 0, 20, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 20:
		func_12(uParam1, "Extreme4", func_14(iParam0), 0, 4, 4, 1731.41f, 96.96f, 170.39f, 382, "", 98, 16, "", 0, 0, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 21:
		func_12(uParam1, "Fanatic1", func_14(iParam0), 0, 5, 4, -1877.82f, -440.649f, 45.05f, 405, "", 74, 0, "", 0, 1, -1, 4, 1, 700, 2000, func_13(iParam0), 1, 0);
		break;

	case 22:
		func_12(uParam1, "Fanatic2", func_14(iParam0), 0, 5, 4, 809.66f, 1279.76f, 360.49f, 405, "", -1, 0, "", 0, 1, -1, 4, 4, 700, 2000, func_13(iParam0), 1, 0);
		break;

	case 23:
		func_12(uParam1, "Fanatic3", func_14(iParam0), 0, 5, 4, -915.6f, 6139.2f, 5.5f, 405, "", -1, 0, "", 0, 1, -1, 4, 2, 700, 2000, func_13(iParam0), 0, 1);
		break;

	case 24:
		func_12(uParam1, "Hao1", func_14(iParam0), 0, 6, 4, -72.29f, -1260.63f, 28.14f, 66, "", -1, 0, "controller_Races", 13, 1, -1, 4, 2, 2000, 500, func_13(iParam0), 0, 1);
		break;

	case 25:
		func_12(uParam1, "Hunting1", func_14(iParam0), 0, 7, 4, 1804.32f, 3931.33f, 32.82f, 66, "", -1, 0, "", 174, 1, 26, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 26:
		func_12(uParam1, "Hunting2", func_14(iParam0), 0, 7, 4, -684.17f, 5839.16f, 16.09f, 384, "", 99, 0, "", 7, 0, -1, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 27:
		func_12(uParam1, "Josh1", func_14(iParam0), 0, 8, 4, -1104.93f, 291.25f, 64.3f, 66, "", -1, 0, "forSaleSigns", 0, 1, 28, 4, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 28:
		func_12(uParam1, "Josh2", func_14(iParam0), 0, 8, 4, 565.39f, -1772.88f, 29.77f, 385, "", 105, 0, "", 0, 0, 29, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 29:
		func_12(uParam1, "Josh3", func_14(iParam0), 0, 8, 4, 565.39f, -1772.88f, 29.77f, 385, "", -1, 16, "", 0, 0, 30, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 30:
		func_12(uParam1, "Josh4", func_14(iParam0), 0, 8, 4, -1104.93f, 291.25f, 64.3f, 385, "", -1, 36, "", 0, 0, -1, 4, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 31:
		func_12(uParam1, "Maude1", func_14(iParam0), 0, 9, 4, 2726.1f, 4145.0f, 44.3f, 66, "", -1, 0, "BailBond_Launcher", 0, 1, -1, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 32:
		func_12(uParam1, "Minute1", func_14(iParam0), 0, 10, 4, 327.85f, 3405.7f, 35.73f, 66, "", -1, 0, "", 0, 1, 33, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 33:
		func_12(uParam1, "Minute2", func_14(iParam0), 0, 10, 4, 18.0f, 4527.0f, 105.0f, 386, "", -1, 10, "", 0, 0, 34, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 34:
		func_12(uParam1, "Minute3", func_14(iParam0), 0, 10, 4, -303.82f, 6211.29f, 31.05f, 386, "", -1, 10, "", 0, 0, -1, 4, 4, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 35:
		func_12(uParam1, "MrsPhilips1", func_14(iParam0), 0, 11, 4, 1972.59f, 3816.43f, 32.42f, 66, "", -1, 0, "ambient_MrsPhilips", 0, 1, -1, 4, 4, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 36:
		func_12(uParam1, "MrsPhilips2", func_14(iParam0), 0, 11, 4, 0.0f, 0.0f, 0.0f, -1, "", -1, 0, "", 0, 1, -1, 4, 4, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 37:
		func_12(uParam1, "Nigel1", func_14(iParam0), 0, 12, 4, -1097.16f, 790.01f, 164.52f, 66, "", -1, 0, "", 177, 1, -1, 1, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 38:
		func_12(uParam1, "Nigel1A", func_14(iParam0), 0, 12, 1, -558.65f, 284.49f, 90.86f, 149, "NIGITEMS", 100, 0, "", 0, 0, 42, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 39:
		func_12(uParam1, "Nigel1B", func_14(iParam0), 0, 12, 1, -1034.15f, 366.08f, 80.11f, 149, "", 100, 0, "", 0, 0, 42, 4, 4, 700, 2000, func_13(iParam0), 1, 1);
		break;

	case 40:
		func_12(uParam1, "Nigel1C", func_14(iParam0), 0, 12, 1, -623.91f, -266.17f, 37.76f, 149, "", 100, 0, "", 0, 0, 42, 4, 4, 700, 2000, func_13(iParam0), 1, 1);
		break;

	case 41:
		func_12(uParam1, "Nigel1D", func_14(iParam0), 0, 12, 1, -1096.85f, 67.68f, 52.95f, 149, "", 100, 0, "", 0, 0, 42, 4, 4, 700, 2000, func_13(iParam0), 1, 1);
		break;

	case 42:
		func_12(uParam1, "Nigel2", func_14(iParam0), 0, 12, 4, -1310.7f, -640.22f, 26.54f, 149, "", -1, 8, "", 0, 0, 43, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 43:
		func_12(uParam1, "Nigel3", func_14(iParam0), 0, 12, 4, -44.75f, -1288.67f, 28.21f, 149, "", -1, 16, "postRC_Nigel3", 0, 0, -1, 4, 4, 0, 2359, func_13(iParam0), 1, 1);
		break;

	case 44:
		func_12(uParam1, "Omega1", func_14(iParam0), 0, 13, 4, 2468.51f, 3437.39f, 49.9f, 66, "", -1, 0, "spaceshipParts", 0, 1, 45, 4, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 45:
		func_12(uParam1, "Omega2", func_14(iParam0), 0, 13, 4, 2319.44f, 2583.58f, 46.76f, 387, "", 107, 0, "", 0, 0, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 46:
		func_12(uParam1, "Paparazzo1", func_14(iParam0), 0, 14, 4, -149.75f, 285.81f, 93.67f, 66, "", -1, 0, "", 0, 1, 47, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 47:
		func_12(uParam1, "Paparazzo2", func_14(iParam0), 0, 14, 4, -70.71f, 301.43f, 106.79f, 389, "", -1, 8, "", 0, 0, 48, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 48:
		func_12(uParam1, "Paparazzo3", func_14(iParam0), 0, 14, 4, -257.22f, 292.85f, 90.63f, 389, "", -1, 8, "", 183, 1, -1, 2, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 49:
		func_12(uParam1, "Paparazzo3A", func_14(iParam0), 0, 14, 2, 305.52f, 157.19f, 102.94f, 389, "PAPPHOTO", 102, 0, "", 0, 0, 51, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 50:
		func_12(uParam1, "Paparazzo3B", func_14(iParam0), 0, 14, 2, 1040.96f, -534.42f, 60.17f, 389, "", 102, 0, "", 0, 0, 51, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 51:
		func_12(uParam1, "Paparazzo4", func_14(iParam0), 0, 14, 4, -484.2f, 229.68f, 82.21f, 389, "", -1, 8, "", 0, 1, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 52:
		func_12(uParam1, "Rampage1", func_14(iParam0), 0, 15, 4, 908.0f, 3643.7f, 32.2f, 66, "", -1, 0, "", 0, 1, 54, 4, 4, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 54:
		func_12(uParam1, "Rampage3", func_14(iParam0), 0, 15, 4, 465.1f, -1849.3f, 27.8f, 84, "", -1, 0, "", 0, 1, 55, 4, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 55:
		func_12(uParam1, "Rampage4", func_14(iParam0), 0, 15, 4, -161.0f, -1669.7f, 33.0f, 84, "", -1, 0, "", 0, 0, 56, 4, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 56:
		func_12(uParam1, "Rampage5", func_14(iParam0), 0, 15, 4, -1298.2f, 2504.14f, 21.09f, 84, "", -1, 0, "", 0, 0, 53, 4, 4, 0, 2359, func_13(iParam0), 0, 0);
		break;

	case 53:
		func_12(uParam1, "Rampage2", func_14(iParam0), 0, 15, 4, 1181.5f, -400.1f, 67.5f, 84, "", -1, 0, "rampage_controller", 0, 0, -1, 4, 4, 0, 2359, func_13(iParam0), 1, 0);
		break;

	case 57:
		func_12(uParam1, "TheLastOne", func_14(iParam0), 0, 16, 4, -1298.98f, 4640.16f, 105.67f, 66, "", 133, 1, "", 0, 1, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 58:
		func_12(uParam1, "Tonya1", func_14(iParam0), 0, 17, 4, -14.39f, -1472.69f, 29.58f, 66, "AM_H_RCFS", -1, 0, "ambient_TonyaCall", 24, 1, 59, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 59:
		func_12(uParam1, "Tonya2", func_14(iParam0), 0, 17, 4, -14.39f, -1472.69f, 29.58f, 388, "", -1, 48, "ambient_Tonya", 185, 0, 60, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 60:
		func_12(uParam1, "Tonya3", func_14(iParam0), 0, 17, 4, 0.0f, 0.0f, 0.0f, -1, "", -1, 0, "", 187, 0, 61, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 61:
		func_12(uParam1, "Tonya4", func_14(iParam0), 0, 17, 4, 0.0f, 0.0f, 0.0f, -1, "", -1, 0, "", 0, 0, 62, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	case 62:
		func_12(uParam1, "Tonya5", func_14(iParam0), 0, 17, 4, -14.39f, -1472.69f, 29.58f, 388, "", -1, 48, "", 0, 0, -1, 4, 2, 0, 2359, func_13(iParam0), 0, 1);
		break;

	default:
		break;
	}
}

void func_12(StrangersAndFreaksArray & uParam0, const char* sParam1, Char16Byte Param2, int iParam4, int iParam5, int iParam6, float Param7_x, float Param7_y, float Param7_z, int iParam10, const char* sParam11, int iParam12, int iParam13, const char *sParam14, int iParam15, int iParam16, int iParam17, int iParam18, int iParam19, int iParam20, int iParam21, int uParam22, int iParam23, int iParam24)//Position - 0x1EC2
{
	uParam0.f_4 = iParam5;
	strcpy_s(uParam0.f_0.str, sizeof(uParam0.f_0.str), sParam1);
	uParam0.f_1 = Param2;
	uParam0.f_3 = iParam4;
	uParam0.f_5 = iParam6;
	uParam0.f_6[0] = Param7_x;
	uParam0.f_6[0] = Param7_y; 
	uParam0.f_6[0] = Param7_z;
	uParam0.f_9 = iParam10;
	strcpy_s(uParam0.f_10.str, 16, sParam11);
	uParam0.f_14 = iParam12;
	uParam0.f_15 = iParam13;
	strcpy_s(uParam0.f_16.str, 24, sParam14);
	uParam0.f_22 = iParam15;
	uParam0.f_23 = iParam16;
	uParam0.f_24 = iParam17;
	uParam0.f_25 = iParam18;
	uParam0.f_26 = iParam19;
	uParam0.f_27 = iParam20;
	uParam0.f_28 = iParam21;
	uParam0.f_29 = uParam22;
	uParam0.f_30 = iParam23;
	uParam0.f_31 = iParam24;
}


int func_13(int iParam0)//Position - 0x1F53
{
	switch (iParam0)
	{
	case 0:
		return 0;
		break;

	case 1:
		return 0;
		break;

	case 2:
		return 1;
		break;

	case 3:
		return 1;
		break;

	case 4:
		return 0;
		break;

	case 5:
		return 1;
		break;

	case 6:
		return 1;
		break;

	case 7:
		return 0;
		break;

	case 8:
		return 1;
		break;

	case 9:
		return 0;
		break;

	case 10:
		return 0;
		break;

	case 11:
		return 0;
		break;

	case 12:
		return 1;
		break;

	case 13:
		return 0;
		break;

	case 14:
		return 1;
		break;

	case 15:
		return 0;
		break;

	case 16:
		return 1;
		break;

	case 17:
		return 1;
		break;

	case 18:
		return 1;
		break;

	case 19:
		return 1;
		break;

	case 20:
		return 1;
		break;

	case 21:
		return 1;
		break;

	case 22:
		return 1;
		break;

	case 23:
		return 1;
		break;

	case 24:
		return 1;
		break;

	case 25:
		return 1;
		break;

	case 26:
		return 1;
		break;

	case 27:
		return 0;
		break;

	case 28:
		return 1;
		break;

	case 29:
		return 1;
		break;

	case 30:
		return 1;
		break;

	case 31:
		return 0;
		break;

	case 32:
		return 1;
		break;

	case 33:
		return 1;
		break;

	case 34:
		return 1;
		break;

	case 35:
		return 0;
		break;

	case 36:
		return 0;
		break;

	case 37:
		return 0;
		break;

	case 38:
		return 1;
		break;

	case 39:
		return 1;
		break;

	case 40:
		return 1;
		break;

	case 41:
		return 1;
		break;

	case 42:
		return 1;
		break;

	case 43:
		return 1;
		break;

	case 44:
		return 0;
		break;

	case 45:
		return 0;
		break;

	case 46:
		return 1;
		break;

	case 47:
		return 1;
		break;

	case 48:
		return 0;
		break;

	case 49:
		return 1;
		break;

	case 50:
		return 1;
		break;

	case 51:
		return 1;
		break;

	case 52:
		return 1;
		break;

	case 54:
		return 1;
		break;

	case 55:
		return 1;
		break;

	case 56:
		return 1;
		break;

	case 53:
		return 1;
		break;

	case 57:
		return 1;
		break;

	case 58:
		return 1;
		break;

	case 59:
		return 1;
		break;

	case 60:
		return 1;
		break;

	case 61:
		return 1;
		break;

	case 62:
		return 1;
		break;

	default:
		break;
	}
	return 0;
}

Char16Byte func_14(int iParam0)//Position - 0x2299
{
	Char16Byte Var0;
	Char16Byte cVar2;

	strcpy_s(Var0.str, 8, "");
	cVar2 = func_15(iParam0);
	if (cVar2.str[0] == '\0')
	{
	}
	else
	{
		strcpy_s(Var0.str, 8, "RC_");
		strcat_s(Var0.str, sizeof(Var0.str), cVar2.str);
	}
	return Var0;
}

Char16Byte func_15(int iParam0)//Position - 0x22D0
{
	Char16Byte Var0;

	strcpy_s(Var0.str, 8, "");
	switch (iParam0)
	{
	case 0:
		strcpy_s(Var0.str, 8, "ABI1");
		break;

	case 1:
		strcpy_s(Var0.str, 8, "ABI2");
		break;

	case 2:
		strcpy_s(Var0.str, 8, "BA1");
		break;

	case 3:
		strcpy_s(Var0.str, 8, "BA2");
		break;

	case 4:
		strcpy_s(Var0.str, 8, "BA3");
		break;

	case 5:
		strcpy_s(Var0.str, 8, "BA3A");
		break;

	case 6:
		strcpy_s(Var0.str, 8, "BA3C");
		break;

	case 7:
		strcpy_s(Var0.str, 8, "BA4");
		break;

	case 8:
		strcpy_s(Var0.str, 8, "DRE1");
		break;

	case 9:
		strcpy_s(Var0.str, 8, "EPS1");
		break;

	case 10:
		strcpy_s(Var0.str, 8, "EPS2");
		break;

	case 11:
		strcpy_s(Var0.str, 8, "EPS3");
		break;

	case 12:
		strcpy_s(Var0.str, 8, "EPS4");
		break;

	case 13:
		strcpy_s(Var0.str, 8, "EPS5");
		break;

	case 14:
		strcpy_s(Var0.str, 8, "EPS6");
		break;

	case 15:
		strcpy_s(Var0.str, 8, "EPS7");
		break;

	case 16:
		strcpy_s(Var0.str, 8, "EPS8");
		break;

	case 17:
		strcpy_s(Var0.str, 8, "EXT1");
		break;

	case 18:
		strcpy_s(Var0.str, 8, "EXT2");
		break;

	case 19:
		strcpy_s(Var0.str, 8, "EXT3");
		break;

	case 20:
		strcpy_s(Var0.str, 8, "EXT4");
		break;

	case 21:
		strcpy_s(Var0.str, 8, "FAN1");
		break;

	case 22:
		strcpy_s(Var0.str, 8, "FAN2");
		break;

	case 23:
		strcpy_s(Var0.str, 8, "FAN3");
		break;

	case 24:
		strcpy_s(Var0.str, 8, "HAO1");
		break;

	case 25:
		strcpy_s(Var0.str, 8, "HUN1");
		break;

	case 26:
		strcpy_s(Var0.str, 8, "HUN2");
		break;

	case 27:
		strcpy_s(Var0.str, 8, "JOS1");
		break;

	case 28:
		strcpy_s(Var0.str, 8, "JOS2");
		break;

	case 29:
		strcpy_s(Var0.str, 8, "JOS3");
		break;

	case 30:
		strcpy_s(Var0.str, 8, "JOS4");
		break;

	case 31:
		strcpy_s(Var0.str, 8, "MAU1");
		break;

	case 32:
		strcpy_s(Var0.str, 8, "MIN1");
		break;

	case 33:
		strcpy_s(Var0.str, 8, "MIN2");
		break;

	case 34:
		strcpy_s(Var0.str, 8, "MIN3");
		break;

	case 35:
		strcpy_s(Var0.str, 8, "MRS1");
		break;

	case 36:
		strcpy_s(Var0.str, 8, "MRS2");
		break;

	case 37:
		strcpy_s(Var0.str, 8, "NI1");
		break;

	case 38:
		strcpy_s(Var0.str, 8, "NI1A");
		break;

	case 39:
		strcpy_s(Var0.str, 8, "NI1B");
		break;

	case 40:
		strcpy_s(Var0.str, 8, "NI1C");
		break;

	case 41:
		strcpy_s(Var0.str, 8, "NI1D");
		break;

	case 42:
		strcpy_s(Var0.str, 8, "NI2");
		break;

	case 43:
		strcpy_s(Var0.str, 8, "NI3");
		break;

	case 44:
		strcpy_s(Var0.str, 8, "OME1");
		break;

	case 45:
		strcpy_s(Var0.str, 8, "OME2");
		break;

	case 46:
		strcpy_s(Var0.str, 8, "PA1");
		break;

	case 47:
		strcpy_s(Var0.str, 8, "PA2");
		break;

	case 48:
		strcpy_s(Var0.str, 8, "PA3");
		break;

	case 49:
		strcpy_s(Var0.str, 8, "PA3A");
		break;

	case 50:
		strcpy_s(Var0.str, 8, "PA3B");
		break;

	case 51:
		strcpy_s(Var0.str, 8, "PA4");
		break;

	case 52:
		strcpy_s(Var0.str, 8, "RAM1");
		break;

	case 53:
		strcpy_s(Var0.str, 8, "RAM2");
		break;

	case 54:
		strcpy_s(Var0.str, 8, "RAM3");
		break;

	case 55:
		strcpy_s(Var0.str, 8, "RAM4");
		break;

	case 56:
		strcpy_s(Var0.str, 8, "RAM5");
		break;

	case 57:
		strcpy_s(Var0.str, 8, "SAS1");
		break;

	case 58:
		strcpy_s(Var0.str, 8, "TON1");
		break;

	case 59:
		strcpy_s(Var0.str, 8, "TON2");
		break;

	case 60:
		strcpy_s(Var0.str, 8, "TON3");
		break;

	case 61:
		strcpy_s(Var0.str, 8, "TON4");
		break;

	case 62:
		strcpy_s(Var0.str, 8, "TON5");
		break;

	default:
		break;
	}
	return Var0;
}