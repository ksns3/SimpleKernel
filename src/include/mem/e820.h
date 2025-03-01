
// This file is a part of Simple-XX/SimpleKernel
// (https://github.com/Simple-XX/SimpleKernel).
//
// e820.h for Simple-XX/SimpleKernel.

#ifndef _E820_H_
#define _E820_H_

#include "stddef.h"
#include "stdint.h"

static constexpr const uint32_t E820_MAX      = 8;
static constexpr const uint32_t E820_RAM      = 1;
static constexpr const uint32_t E820_RESERVED = 2;
static constexpr const uint32_t E820_ACPI     = 3;
static constexpr const uint32_t E820_NVS      = 4;
static constexpr const uint32_t E820_UNUSABLE = 5;

typedef struct e820entry {
    // 数据类型由位数决定
    uint8_t *addr;
    size_t   length;
    uint32_t type;
} __attribute__((packed)) e820entry_t;

typedef struct e820map {
    uint32_t    nr_map;
    e820entry_t map[E820_MAX];
} e820map_t;

#endif /* _E820_H_ */
