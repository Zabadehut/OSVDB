#pragma once
#include <stdint.h>

// Enum for EFI_MEMORY_DESCRIPTOR types.
enum EFIMemoryType {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType // Always keep this after the last item, it represents the total number of types.
};

// Memory descriptor structure
struct EFI_MEMORY_DESCRIPTOR {
    EFIMemoryType type; // Memory type.
    void* physAddr;     // Physical address.
    void* virtAddr;     // Virtual address.
    uint64_t numPages;  // Number of pages.
    uint64_t attribs;   // Attributes.
};

extern const char* EFI_MEMORY_TYPE_STRINGS[EfiMaxMemoryType];