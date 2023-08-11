// Ryan Fleury - Exercise 1
#include <stdlib.h>
#include <string.h>
#include "Arena.h"

Arena* ArenaAlloc(const uint32_t capacity)
{
	Arena* arena = (Arena*) malloc(sizeof(Arena) + capacity);
	arena->Capacity = capacity;
	arena->Position = 0;
	arena->Memory = arena + sizeof(Arena);
	return arena;
}

void ArenaRelease(Arena* arena)
{
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

	if (arena->Position + size > arena->Capacity)
	{
		return nullptr;
	}

	arena->Position += size;
	return arena->Memory + arena->Position;
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

	uint32_t padding = alignment - (arena->Position % alignment);
	arena->Position += padding;
	return arena->Memory + arena->Position;
}

void* ArenaPush(Arena* arena, const uint32_t size)
{
	if (!arena)
	{
		return nullptr;
	}

	if (size + arena->Position > arena->Capacity)
	{
		return nullptr;
	}

	memset(arena->Memory + arena->Position, 0, size);
	arena->Position += size;

	return arena->Memory + arena->Position;
}

void* ArenaPopTo(Arena* arena, const uint32_t pos)
{
	if (!arena)
	{
		return nullptr;
	}

	if (arena->Position <= pos)
	{
		return nullptr;
	}

	arena->Position = pos;
	return arena->Memory + arena->Position;
}

void* ArenaPop(Arena* arena, const uint32_t size)
{
	if (!arena)
	{
		return nullptr;
	}

	const uint32_t usedSize = arena->Position;
	if (size > usedSize)
	{
		return nullptr;
	}

	arena->Position -= size;
	return arena->Memory + arena->Position;
}

void ArenaClear(Arena* arena)
{
	if (!arena)
	{
		return;
	}

	arena->Position = 0;
}
