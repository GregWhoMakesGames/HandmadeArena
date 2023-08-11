// Ryan Fleury - Exercise 1

// Write an arena implementation for the API below.
// This arena should operate on a fixed-capacity buffer, and not grow at all.
// It can obtain this buffer via malloc or equivalent.
// If the arena runs out of space, panic.

//TODO macro where you pass in something it does a sizeOf<> before ArenaPush

#include <stdint.h>

struct Arena {
	uint8_t* Memory;
	uint64_t Size;
};

namespace Arenas {
	Arena* ArenaAlloc(uint64_t cap);
	void ArenaRelease(Arena* arena);
	void ArenaSetAutoAlign(Arena* arena, uint64_t align);

	uint64_t ArenaPos(Arena* arena);

	void* ArenaPushNoZero(Arena* arena, uint64_t size);
	void* ArenaPushAligner(Arena* arena, uint64_t alignment);
	void* ArenaPush(Arena* arena, uint64_t size);

	void ArenaPopTo(Arena* arena, uint64_t pos);
	void ArenaPop(Arena* arena, uint64_t size);
	void ArenaClear(Arena* arena);
}

//#define PushArrayNoZero(...)
//#define ...

//Examples:
//String8 PushStr8F(Arena* arena, char* fmt, ...);
//StrSplit
//StrJoin

//TokenizeResult{tokens, msgs}
//TokenizeResult TokenizeFromText(Arena, Text);
