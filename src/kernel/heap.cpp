
// This file is a part of Simple-XX/SimpleKernel
// (https://github.com/Simple-XX/SimpleKernel).
//
// heap.cpp for Simple-XX/SimpleKernel.

#include "cpu.hpp"
#include "heap.h"

IO HEAP::io;

HEAP::HEAP(void) : name("SLAB"), manage(SLAB()) {
    return;
}

HEAP::~HEAP(void) {
    return;
}

int32_t HEAP::init(void) {
    manage_init();
    io.printf("heap_init\n");
    return 0;
}

int32_t HEAP::manage_init(void) {
    manage.init(COMMON::KERNEL_END_4K, HEAP_SIZE);
    return 0;
}

void *HEAP::malloc(size_t byte) {
    return manage.alloc(byte);
}

void HEAP::free(void *addr) {
    manage.free(addr);
    return;
}

size_t HEAP::get_total(void) {
    return manage.get_total();
}

size_t HEAP::get_block(void) {
    return manage.get_block();
}

size_t HEAP::get_free(void) {
    return manage.get_free();
}
