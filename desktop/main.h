#pragma once

#include "BasicRenderer.h"
#include "cstr.h"
#include "IO.h"
#include "math.h"
#include "memory.h"
#include "panic.h"
#include "pci.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/PageTableManager.h"
#include "paging/paging.h"
#include "userinput/kbScancodeTranslation.h"
#include "userinput/keyboard.h"
#include "userinput/mouse.h"
#include "AHCI/ahci.h"
#include "BSL/string.h"
#include "memory/heap.h"
#include "memory/dynamics.h"
#include "memory/standardHeap.h"
#include "handlers/keyboard.h"
#include "handlers/mouse.h"


void startDesktop(AHCI::device disk);