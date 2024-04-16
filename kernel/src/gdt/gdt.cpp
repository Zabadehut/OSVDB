#include "gdt.h"

__attribute__((aligned(0x1000)))
GDT DefaultGDT = {
    {0, 0, 0, 0x00, 0x00, 0},
    {0, 0, 0, 0x9a, 0xa0, 0},
    {0, 0, 0, 0x92, 0xa0, 0},
    {0, 0, 0, 0x00, 0x00, 0},
    {0, 0, 0, 0x9a, 0xa0, 0},
    {0, 0, 0, 0x92, 0xa0, 0},
};

void CreateGDTEntry(uint16_t Limit0, uint16_t Base0, uint8_t Base1, uint8_t AccessByte, uint8_t Limit1_Flags, uint8_t Base2){
    GDTEntry newEntry;
    newEntry.Limit0 = Limit0;
    newEntry.Base0 = Base0;
    newEntry.Base1 = Base1;
    newEntry.AccessByte = AccessByte;
    newEntry.Limit1_Flags = Limit1_Flags;
    newEntry.Base2 = Base2;
}