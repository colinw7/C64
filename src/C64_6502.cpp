#include <C64_6502.h>
#include <C64.h>
#include <C64_VICII.h>
#include <C64_CIA.h>
#include <C6502.h>

#include <basic.h>
#include <characters.h>
#include <kernel.h>

C64_6502::
C64_6502(C64 *machine) :
 C6502(), machine_(machine)
{
}

C64_6502::
~C64_6502()
{
}

uchar
C64_6502::
getByte(ushort addr) const
{
  if (isDebugger()) {
    if      (addr >= charMem1_ && addr <= charMem2_) {
      return characters_data[addr - charMem1_]; // 4K Character ROM
    }
    else if (addr >= 0xA000 && addr < 0xC000) {
      if (loram_)
        return basic_data[addr - 0xA000]; // 8K Basic ROM
    }
    else if (addr >= 0xD000 && addr < 0xDFFF) {
      if (! charen_)
        return characters_data[addr - 0xD000]; // 4K Character ROM
    }
    else if (addr >= 0xE000 && addr < 0xFFFF) {
      if (hiram_)
        return kernel_data[addr - 0xE000]; // 8K Kernel ROM
    }

    return C6502::getByte(addr);
  }

  //---

  if      (addr == 0x0001) {
    if (debug_)
      std::cerr << "Read: R6510\n";
  }
  else if (addr >= charMem1_ && addr <= charMem2_) {
    return characters_data[addr - charMem1_]; // 4K Character ROM
  }
  else if (addr >= 0xA000 && addr < 0xC000) {
    if (loram_)
      return basic_data[addr - 0xA000]; // 8K Basic ROM
  }
  else if (addr >= 0xD000 && addr < 0xDFFF) {
    if (! charen_) {
      return characters_data[addr - 0xD000]; // 4K Character ROM
    }
    else if (addr >= 0xDC00 && addr < 0xDD00) {
      return machine_->getCIA1()->getByte(addr - 0xDC00);
    }
    else if (addr >= 0xDD00 && addr < 0xDE00) {
      return machine_->getCIA2()->getByte(addr - 0xDD00);
    }
    else {
      if      (addr >= 0xD000 && addr < 0xD400) {
        return machine_->getGPU()->getByte(addr - 0xD000);
      }
    }
  }
  else if (addr >= 0xE000 && addr < 0xFFFF) {
    if (hiram_)
      return kernel_data[addr - 0xE000]; // 8K Kernel ROM
  }

  return C6502::getByte(addr);
}

void
C64_6502::
setByte(ushort addr, uchar c)
{
  if      (addr == 0x0000) {
    if (debug_)
      std::cerr << "Write: D6510 = " << (int) c << "\n";
  }
  else if (addr == 0x0001) {
    if (debug_)
      std::cerr << "Write: R6510 = " << (int) c << "\n";

    loram_  = (c & 0x01); // Selects ROM or RAM at ($A000). 1=BASIC , 0=RAM
    hiram_  = (c & 0x02); // Selects ROM or RAM at ($E000). 1=Kernal, 0=RAM
    charen_ = (c & 0x04); // Selects character ROM or I/O devices. 1=I/O, 0=ROM
  }
  else if (addr >= 0xD000 && addr < 0xDFFF) {
    if (! charen_) {
      // 4K Character ROM is mapped in
    }
    else {
      if      (addr >= 0xD000 && addr < 0xD400) {
      //if (addr == 0xD018)
      //  machine_->getGPU()->setRasterCompareInterruptValue(c); // low 8 bits

        machine_->getGPU()->setByte(addr - 0xD000, c);
      }
      else if (addr >= 0xDC00 && addr < 0xDD00) {
        machine_->getCIA1()->setByte(addr - 0xDC00, c);
      }
      else if (addr >= 0xDD00 && addr < 0xDE00) {
        machine_->getCIA2()->setByte(addr - 0xDD00, c);

        gpuMem1_ = machine_->getCIA2()->gpuMem1();
        gpuMem2_ = machine_->getCIA2()->gpuMem2();

        charMem1_ = machine_->getCIA2()->charMem1();
        charMem2_ = machine_->getCIA2()->charMem2();
      }
    }
  }

  C6502::setByte(addr, c);
}

void
C64_6502::
memset(ushort addr, const uchar *data, ushort len)
{
  C6502::memset(addr, data, len);
}

void
C64_6502::
tick(uchar n)
{
  machine_->getCIA1()->tick(n);
}

bool
C64_6502::
isScreen(ushort addr, ushort len) const
{
  return machine_->getGPU()->isScreen(addr, len);
}
