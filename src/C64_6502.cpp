#include <C64_6502.h>
#include <C64.h>
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
  if      (addr == 0x0001) {
    if (debug_)
      std::cerr << "Read: R6510\n";
  }
  else if (addr >= 0xA000 && addr < 0xC000) {
    if (loram_)
      return basic_data[addr - 0xA000]; // 8K Basic ROM
  }
  else if (addr >= 0xD000 && addr < 0xDFFF) {
    if (! charen_) {
      return characters_data[addr - 0xD000]; // 4K Character ROM
    }
    else {
      if      (addr == 0xD018) {
        return machine_->screenLine();
      }
      else if (addr == 0xDC04) {
        return machine_->timerA_.count & 0xFF;
      }
      else if (addr == 0xDC05) {
        return (machine_->timerA_.count & 0xFF00) >> 8;
      }
      else if (addr == 0xDC06) {
        return machine_->timerB_.count & 0xFF;
      }
      else if (addr == 0xDC07) {
        return (machine_->timerB_.count & 0xFF00) >> 8;
      }
      else if (addr == 0xDC0D) {
        uchar c = 0x00;

        // clear on read
        if (machine_->timerA_.zeroed) { c |= 0x01; machine_->timerA_.zeroed = false; }
        if (machine_->timerB_.zeroed) { c |= 0x02; machine_->timerB_.zeroed = false; }

      //if (todTimer_.alarm ) { c |= 0x04; todTimer_.alarm  = false; }
      //if (SSRData_ .finish) { c |= 0x08; SSRData_ .finish = false; }
      //if (flagLine_.signal) { c |= 0x10; flagLine_.signal = false; }

      //if (c) c |= 0x80; // signal bit is set ?

        return c;
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

    loram_  = (c & 0x01);
    hiram_  = (c & 0x02);
    charen_ = (c & 0x04);
  }
  else if (addr == 0xD018) {
    machine_->setRasterCompareInterruptValue(c); // low 8 bits
  }
  else if (addr == 0xDC00) {
    for (int i = 0; i < 8; ++i) {
      if (! (c & (1 << i)))
        machine_->loadKeyColumn(i);
    }
  }
  else if (addr == 0xDC04) {
    machine_->timerA_.latch = (machine_->timerA_.latch & 0xFF00) | c;
  }
  else if (addr == 0xDC05) {
    machine_->timerA_.latch = (machine_->timerA_.latch & 0x00FF) | (c >> 8);
  }
  else if (addr == 0xDC06) {
    machine_->timerB_.latch = (machine_->timerB_.latch & 0xFF00) | c;
  }
  else if (addr == 0xDC07) {
    machine_->timerB_.latch = (machine_->timerB_.latch & 0x00FF) | (c >> 8);
  }
  else if (addr == 0xDC0D) {
    bool setOrClear = (c & 0x80);

    if (c & 0x01) machine_->timerA_.enabled = setOrClear;
    if (c & 0x02) machine_->timerB_.enabled = setOrClear;

//    if (c & 0x04) todTimer_.enabled = setOrClear;
//    if (c & 0x08) SSRData_ .enabled = setOrClear;
//    if (c & 0x10) flagLine_.enabled = setOrClear;
  }
  else if (addr == 0xDC0E) {
    machine_->startTimerA(c & 0x01);

    machine_->timerA_.outputB = (c & 0x02);
    machine_->timerA_.toggleB = (c & 0x04);
    machine_->timerA_.oneShot = (c & 0x08);

  //if (c & 0x10) machine_->timerA_.counter = getWord(0xDD04);

    machine_->timerA_.countCycles = (c & 0x20);
//    machine_->timerA_.serialOut   = (c & 0x40);

//    todTimer_.use50 = (c & 0x80);
  }
  else if (addr == 0xDC0E) {
    machine_->startTimerB(c & 0x01);

    machine_->timerB_.outputB = (c & 0x02);
    machine_->timerB_.toggleB = (c & 0x04);
    machine_->timerB_.oneShot = (c & 0x08);

  //if (c & 0x10) machine_->timerB_.counter = getWord(0xDD06);

    machine_->timerB_.inputMode = (c & 0x60) >> 5;

//    todTimer_.alarm = (c & 0x80);
  }

  C6502::setByte(addr, c);
}

void
C64_6502::
memset(ushort addr, const uchar *data, ushort len)
{
  C6502::memset(addr, data, len);
}

bool
C64_6502::
isScreen(ushort, ushort) const
{
  return false;
}

void
C64_6502::
update()
{
  C6502::update();

  machine_->update();
}
