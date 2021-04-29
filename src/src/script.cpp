/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "Main.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Ped player;

bool debugOn = false;
bool invincible = false;


void Initialize()
{
	player = PLAYER::PLAYER_PED_ID();
}

void main()
{
	WAIT(500);
	Initialize();
	
	while (true)
	{
		player = PLAYER::PLAYER_PED_ID();
		try
		{
			//updateUI();
		}
		catch (...)
		{
			log("Something wrong happened");
			std::exception_ptr ex = std::current_exception();
			try 
			{
				if (ex)
				{
					rethrow_exception(ex);
				}
				else
				{
					log("No exception captured.");
				}
			}
			catch (const exception& e)
			{
				showSubtitle(e.what());
				//log(e.what());
			}
		}


		if (debugOn)
		{
			debug(GAMEPLAY::GET_WIND_SPEED());
			GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(player));
			GAMEPLAY::SET_WIND_SPEED(20);
			WAIT(7000);
			GAMEPLAY::SET_WIND_SPEED(4);

			//PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), 1);

			//DECISIONEVENT::REMOVE_ALL_SHOCKING_EVENTS(0);
			//DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();

			Vector3 pos = playerPos();

			//Hash weap;
			//WEAPON::GET_CURRENT_PED_WEAPON(player, &weap, 0, 0, 0);
			//if (weap == GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat") && !PED::IS_PED_RELOADING(player))
			//{
			//	int ammo;
			//	//WEAPON::GET_AMMO_IN_CLIP(player, GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat"), &ammo);
			//	int* i = new int;
			//	*i = 0;
			//	WEAPON::_0x678F00858980F516(player, (Any*)&ammo, (Any*)i);
			//	debug(ammo);
			//	//debug(WEAPON::GET_AMMO_IN_PED_WEAPON(player, GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat")));
			//}


			

			//debug(DECISIONEVENT::IS_SHOCKING_EVENT_IN_SPHERE(0x93B7032F, pos.x, pos.y, pos.z, 60));
			//debug(DECISIONEVENT::IS_SHOCKING_EVENT_IN_SPHERE(1811873798, pos.x, pos.y, pos.z, 60));

			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(player, &weaponHash, 0, 0, 0);
			if (weaponHash != GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED")) {
				Entity e;
				if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &e) /*&& distanceBetweenEntities(player, e) < 20*/) {
					if (IsKeyJustUp(VK_KEY_Z)) {
						int bone;
						PED::GET_PED_LAST_DAMAGE_BONE(e, &bone);
						PED::_0xFFD54D9FE71B966A(e, 2, 26043, -.5, -.05, 0, ENTITY::GET_ENTITY_HEADING(e), 5000, -1, 1);
					}
				}
				else
				{
				}
			}
			else
			{
				Entity targetEntity;
				if (PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity))
				{
					if (IsKeyJustUp(VK_KEY_Z)) {
					}
				}
				else
				{

				}
			}

			if (PED::IS_PED_ON_MOUNT(player))
			{

				ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_MOUNT(player), 1);
			}


			//PURSUIT::CLEAR_CURRENT_PURSUIT();
			//PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			//PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), 0);

			if (IsKeyJustUp(VK_KEY_X))
			{
				playAmbientSpeech(player, "RE_ES_EMR_V1_ACCEPT_P");
			}

			if (IsKeyJustUp(VK_F1))
			{
				invincible = !invincible;
				if (invincible) {
					showSubtitle("invincible ON");
				}
				else
				{
					showSubtitle("invincible OFF");

				}
				ENTITY::SET_ENTITY_INVINCIBLE(player, invincible);
			}

			if (IsKeyJustUp(VK_KEY_Z))
			{
				Ped ped = createPed("g_m_o_uniexconfeds_01", playerPos() + getForwardVector(player) * rndInt(5, 10), 180);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				//ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
			}


			if (IsKeyJustUp(VK_F3))
			{
				AI::CLEAR_PED_TASKS(player, 1, 1);
			}

			if (IsKeyJustUp(VK_KEY_K))
			{
				showSubtitle("3");
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(createPed("g_m_o_uniexconfeds_01", playerPos() + getForwardVector(player) * rndInt(5, 10), 180), true);
				PLAYER::_0xD04AD186CE8BB129(PLAYER::PLAYER_ID(), GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat"), 3);
				WAIT(10000);
				showSubtitle("5");
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(createPed("g_m_o_uniexconfeds_01", playerPos() + getForwardVector(player) * rndInt(5, 10), 180), true);
				PLAYER::_0xD04AD186CE8BB129(PLAYER::PLAYER_ID(), GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat"), 5);
				WAIT(10000);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(createPed("g_m_o_uniexconfeds_01", playerPos() + getForwardVector(player) * rndInt(5, 10), 180), true);
				showSubtitle("100");
				PLAYER::_0xD04AD186CE8BB129(PLAYER::PLAYER_ID(), GAMEPLAY::GET_HASH_KEY("weapon_revolver_lemat"), 100);
			}
		}

		if (true && IsKeyJustUp(VK_F2))
		{
			setDebugMode(!isDebugMode());
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}

void debug(const char* text) {
	UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text), 0, 0);
}

void debug(string text) {
	debug(text.c_str());
}

void debug(Vector3 pos) {
	stringstream str;
	str << pos.x << ", " << pos.y << ", " << pos.z;
	debug(str.str());
}

void debug(float f) {
	debug(to_string(f));
}

void debug(int n) {
	debug(to_string(n));
}

void debug(bool b) {
	debug(to_string(b));
}

void logPlayerPos()
{
	Vector3 playerPos = entityPos(player);
	float ground;
	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &ground, false);
	std::stringstream output;
	output << "\n"
		<< playerPos.x << ", " << playerPos.y << ", " << playerPos.z << "\n"
		<< playerPos.x << ", " << playerPos.y << ", " << ground << "\n"
		<< "heading: " << ENTITY::GET_ENTITY_HEADING(player);

	log(output.str().c_str());
	showSubtitle(to_string(getGroundPos(playerPos)));
}

bool isDebugMode()
{
	return debugOn;
}

void setDebugMode(bool toggle)
{
	debugOn = toggle;
	if (debugOn)
	{
		showSubtitle("Debug tools ON");
	}
	else
	{
		showSubtitle("Debug tools OFF");
	}
}