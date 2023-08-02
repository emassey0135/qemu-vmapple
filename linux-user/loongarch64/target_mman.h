/*
 * arch/loongarch/include/asm/processor.h:
 * TASK_UNMAPPED_BASE         PAGE_ALIGN(TASK_SIZE / 3)
 * TASK_SIZE64                0x1UL << (... ? VA_BITS : ...)
 */
#define TASK_UNMAPPED_BASE \
    TARGET_PAGE_ALIGN((1ull << TARGET_VIRT_ADDR_SPACE_BITS) / 3)

#include "../generic/target_mman.h"
