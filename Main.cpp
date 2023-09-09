#include <iostream>
#include "Arena.h"

void SystemTests()
{
	std::cout << "Running Arena system tests" << std::endl;
	uint32_t sizeOfUInt32 = sizeof(uint32_t);
	if (sizeOfUInt32 != 4)
	{
		std::cout << "Warning: uint32 is not size 4 on this platform. Tests may not behave well." << std::endl;
	}
}

struct PlayerCharacter
{
	uint32_t health;
	uint32_t mana;
	uint8_t items[8];
};

void ArenaBasicTests()
{
	std::cout << "Running Arena basic tests" << std::endl;

	Arena* arena = ArenaAlloc(16);

	PlayerCharacter* player = (PlayerCharacter*) ArenaPush(arena, sizeof(PlayerCharacter));
	uint32_t position = ArenaPos(arena);

	if (position != 16)
	{
		std::cout << "Position invalid. Expected: 16. Actual: " << position << std::endl;
	}

	player->health = 100;
	player->mana = 20;
	player->items[0] = 5;
	player->items[1] = 12;
	player->items[2] = 7;

	ArenaRelease(arena);

}

int main() {

	SystemTests();

	ArenaBasicTests();
}
