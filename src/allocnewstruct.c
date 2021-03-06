#include "types.h"
#include "battle_structs.h"
#include "new_battle_struct.h"
#include "battle_locations.h"
#include "defines.h"

u32 malloc_and_clear(u16 size);

void alloc_new_struct()
{
    u32 *ptr;
    ptr=(u32 *)(&battle_stuff_ptr);
    *ptr=malloc_and_clear(0x2A4);
    ptr=(u32 *)(&new_battlestruct);
    *ptr=malloc_and_clear(sizeof(struct new_battle_struct));
    for (u8 i = 0; i < 4; i++)
    {
        new_battlestruct.ptr->bank_affecting[i].type3 = TYPE_EGG;
    }
}

void free(u32 address);

void free_new_struct()
{
    u32 *ptr;
    ptr=(u32 *)(&battle_stuff_ptr);
    free(*ptr);
    *ptr=0;
    ptr=(u32 *)(&new_battlestruct);
    free(*ptr);
    *ptr=0;
}
