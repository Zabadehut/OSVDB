#include "memory.h"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize) {
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) return memorySizeBytes;
    uint64_t descSizeTimesI = mMapDescSize; // Add mMapDescSize after each iteration
    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + descSizeTimesI);
        memorySizeBytes += desc->numPages * 4096;
        descSizeTimesI += mMapDescSize;
    }
    return memorySizeBytes;
}

void memset(void* start, uint8_t value, uint64_t num) {
    for (uint64_t i = 0; i < num; i++){
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}

void* memcpy(void* dst, const void* src, uint16_t num) {
    uint8_t* u8Dst = (uint8_t*)dst;
    const uint8_t* u8Src = (const uint8_t*)src;
    while (num--)
        *u8Dst++ = *u8Src++;
    return dst;
}

int memcmp(const void* ptr1, const void* ptr2, uint16_t num) {
    const uint8_t* u8Ptr1 = (const uint8_t*)ptr1;
    const uint8_t* u8Ptr2 = (const uint8_t*)ptr2;
    while (num--)
        if (*u8Ptr1++ != *u8Ptr2++)
            return 1;
    return 0;
}