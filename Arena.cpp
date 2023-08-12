// Ryan Fleury - Exercise 1
#include <stdlib.h>
#include <string.h>
#include "Arena.h"

Arena* ArenaAlloc(const uint32_t capacity, const bool isHead)
{
	Arena* arena = (Arena*) malloc(sizeof(Arena) + capacity);
	arena->IsHead = isHead;
	arena->Capacity = capacity;
	arena->Position = 0;
	arena->Memory = arena + sizeof(Arena);
	arena->Next = nullptr;
	return arena;
}

void ArenaRelease(Arena* arena)
{
	if (!arena)
	{
		return;
	}

	if (arena->Next != nullptr)
	{
		ArenaRelease(arena->Next);
	}

	free(arena);
}

uint32_t ArenaPos(const Arena* arena)
{
	if (!arena || !arena->IsHead)
	{
		return 0;
	}

	return arena->Position;
}

Arena* GetArenaByPosition(const Arena* arena, const uint32_t position)
{
	if (!arena && !arena->IsHead)
	{
		return nullptr;
	}

	const Arena* currentArena = arena;
	const uint32_t capacity = arena->Capacity;
	uint32_t currentPosition = position;
	while (currentPosition > capacity)
	{
		if (arena->Next == nullptr)
		{
			return nullptr;
		}

		currentArena = arena->Next;
		currentPosition -= capacity;
	}

	return (Arena*) currentArena;
}

void ArenaPushNoZero(Arena* arena, uint32_t size)
{
	if (!arena)
	{
		return;
	}

	if (!arena->IsHead)
	{
		return;
	}

	Arena* currentArena = arena;
	uint32_t currentPosition = arena->Position;
	uint32_t capacity = arena->Capacity;

	while (currentPosition > capacity)
	{
		currentPosition -= capacity;
		arena = arena->Next;

		if (arena == nullptr)
		{
			return;
		}
	}

	uint32_t nextPosition = currentPosition + size;
	if (nextPosition > capacity)
	{
		currentArena->Next = ArenaAlloc(capacity, false);
		currentArena = currentArena->Next;
		nextPosition = nextPosition % capacity;
	}

	currentArena->Position = nextPosition;
}

void ArenaPushAligner(Arena* arena, const uint32_t alignment)
{
	if (!arena)
	{
		return;
	}

	if (alignment == 0)
	{
		return;
	}

	uint32_t padding = alignment - (arena->Position % alignment);
	arena->Position += padding;
}

void ArenaPush(Arena* arena, const uint32_t size)
{
	if (!arena)
	{
		return;
	}

	if (size + arena->Position > arena->Capacity)
	{
		return;
	}

	memset(arena->Memory + arena->Position, 0, size);
	arena->Position += size;
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
