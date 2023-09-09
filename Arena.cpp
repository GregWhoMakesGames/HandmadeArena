// Ryan Fleury - Exercise 1
#include <stdlib.h>
#include <string.h>
#include "Arena.h"

Arena* ArenaAlloc(const uint32_t capacity, const bool isHead)
{
	uint32_t bytesAllocated = sizeof(Arena) + capacity;
	Arena* arena = (Arena*) malloc(sizeof(Arena) + capacity);
	arena->Capacity = capacity;
	arena->Position = 0;
	arena->Memory = (void*) (((uint32_t) arena) + sizeof(Arena));
	return arena;
}

void ArenaRelease(Arena* arena)
{
	if (!arena)
	{
		return;
	}

	free(arena);
}

uint32_t ArenaPos(const Arena* arena)
{
	if (!arena)
	{
		return 0;
	}

	return arena->Position;
}

void* ArenaPushNoZero(Arena* arena, uint32_t size)
{
	if (!arena)
	{
		return nullptr;
	}

	if ((size + arena->Position) > arena->Capacity)
	{
		return nullptr;
	}

	void* destination = arena->Memory + arena->Position;
	arena->Position += size;
	return destination;
}

void* ArenaPushAligner(Arena* arena, const uint32_t alignment)
{
	if (!arena)
	{
		return nullptr;
	}

	if (alignment == 0)
	{
		return nullptr;
	}

	void* destination = arena->Memory + arena->Position;

	uint32_t padding = alignment - (arena->Position % alignment);
	arena->Position += padding;
	return destination;
}

void* ArenaPush(Arena* arena, const uint32_t size)
{
	if (!arena)
	{
		return nullptr;
	}

	if ((size + arena->Position) > arena->Capacity)
	{
		return nullptr;
	}

	void* destination = (void*) (((uint32_t) arena->Memory) + arena->Position);
	memset(destination, 0, size);
	arena->Position += size;
	return destination;
}

bool ArenaPopTo(Arena* arena, const uint32_t pos)
{
	if (!arena)
	{
		return false;
	}

	if (arena->Position <= pos)
	{
		return false;
	}

	arena->Position = pos;
	return true;
}

bool ArenaPop(Arena* arena, const uint32_t size)
{
	if (!arena)
	{
		return false;
	}

	const uint32_t usedSize = arena->Position;
	if (size > usedSize)
	{
		return false;
	}

	arena->Position -= size;
	return true;
}

void ArenaClear(Arena* arena)
{
	if (!arena)
	{
		return;
	}

	arena->Position = 0;
}
