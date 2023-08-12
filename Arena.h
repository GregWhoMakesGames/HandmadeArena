// Ryan Fleury - Exercise 1

// Write an arena implementation for the API below.
// This arena should operate on a fixed-capacity buffer, and not grow at all.
// It can obtain this buffer via malloc or equivalent.
// If the arena runs out of space, panic.

//TODO macro where you pass in something it does a sizeOf<> before ArenaPush

#include <stdint.h>

struct Arena {
	bool IsHead;
	uint32_t Capacity;
	uint32_t Position;
	void* Memory;
	Arena* Next;
};

Arena* ArenaAlloc(const uint32_t cap, const bool isHead);
void ArenaRelease(Arena* arena);
uint32_t ArenaPos(const Arena* arena);
Arena* GetArenaByPosition(Arena* arena, const uint32_t position);

void ArenaPushNoZero(Arena* arena, const uint32_t size);
void ArenaPushAligner(Arena* arena, const uint32_t alignment);
void ArenaPush(Arena* arena, const uint32_t size);

void* ArenaPopTo(Arena* arena, const uint32_t pos);
void* ArenaPop(Arena* arena, const uint32_t size);
void ArenaClear(Arena* arena);

//#define PushArrayNoZero(...)
//#define ...

//Examples:
//String8 PushStr8F(Arena* arena, char* fmt, ...);
//StrSplit
//StrJoin

//TokenizeResult{tokens, msgs}
//TokenizeResult TokenizeFromText(Arena, Text);
