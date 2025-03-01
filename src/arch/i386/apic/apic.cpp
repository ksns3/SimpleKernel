
// This file is a part of Simple-XX/SimpleKernel
// (https://github.com/Simple-XX/SimpleKernel).
//
// apic.cpp for Simple-XX/SimpleKernel.

#include "assert.h"
#include "intr.h"
#include "cpu.hpp"
#include "apic.h"

// TODO: 完善
// TODO: 加入内核

IO APIC::io;

APIC::APIC(void) {
    return;
}

APIC::~APIC(void) {
    return;
}

bool APIC::init(void) {
    CPU::CPUID cpuid;
    if (cpuid.xapic() == true) {
        io.info("support APIC&xAPIC\n");
    }
    if (cpuid.x2apic() == true) {
        io.info("support x2APIC\n");
    }
    uint64_t msr = CPU::READ_MSR(CPU::IA32_APIC_BASE);
    // 开启 xAPIC 与 x2APIC
    msr |= (CPU::IA32_APIC_BASE_GLOBAL_ENABLE_BIT |
            CPU::IA32_APIC_BASE_X2APIC_ENABLE_BIT);
    CPU::WRITE_MSR(CPU::IA32_APIC_BASE, msr);
    // 设置 SIVR
    msr = CPU::READ_MSR(CPU::IA32_X2APIX_SIVR);
    msr |= (CPU::IA32_X2APIX_SIVR_APIC_ENABLE_BIT |
            CPU::IA32_X2APIX_SIVR_EOI_ENABLE_BIT);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_SIVR, msr);

    // 屏蔽所有 LVT
    msr = 0;
    msr |= CPU::IA32_X2APIX_LVT_MASK_BIT;
    CPU::WRITE_MSR(CPU::IA32_X2APIX_CMCI, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_TIMER, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_THERMAL, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_PMI, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_LINT0, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_LINT1, msr);
    CPU::WRITE_MSR(CPU::IA32_X2APIX_LVT_ERROR, msr);

    // 关闭 8259A
    io.outb(0x21, 0xff);
    io.outb(0xa1, 0xff);
    io.info("apic init\n");
    return true;
}
