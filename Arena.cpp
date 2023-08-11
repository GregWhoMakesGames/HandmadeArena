// Ryan Fleury - Exercise 1
#include "Arena.h"

Arena* ArenaAlloc(uint64_t cap)
{
	Arena* arena = new Arena;
	arena->Size = cap;
	arena->Memory = new uint8_t[cap];
	return arena;
}

void ArenaRelease(Arena* arena)
{
	if (arena)
	{
		if (arena->Memory)
		{
			delete[] arena->Memory;
		}
		delete arena;
	}
}

void ArenaSetAutoAlign(Arena* arena, uint64_t align)
{

}


uint64_t ArenaPos(Arena* arena)
{
	return 0;
}


void* ArenaPushNoZero(Arena* arena, uint64_t size)
{

}

void* ArenaPushAligner(Arena* arena, uint64_t alignment)
{

}

void* ArenaPush(Arena* arena, uint64_t size)
{

}


void ArenaPopTo(Arena* arena, uint64_t pos)
{

}

void ArenaPop(Arena* arena, uint64_t size)
{

}

void ArenaClear(Arena* arena)
{

}
