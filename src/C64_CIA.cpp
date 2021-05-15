#include <C64_CIA.h>
#include <C64.h>
#include <C64_6502.h>

C64_CIA::
C64_CIA(C64 *c64, int id) :
 c64_(c64), id_(id)
{
  assert(c64_);

  assert(id_ == 1 || id_ == 2);

  enableIRQ_ = true;

  if (getenv("C64_DISABLE_IRQ"))
    enableIRQ_ = false;

  if (getenv("C64_CIA_DEBUG"))
    debug_ = true;
}

uchar
C64_CIA::
getByte(ushort addr) const
{
  assert(addr < 0xFF);

  ushort addr1 = addr & 0x0F;

  if      (id_ == 1) { // CIA #1
    auto debugRet1 = [&](uchar c) {
      if (isDebug())
        std::cerr << "CIA #1::getByte " << std::hex << (0xDC00 | addr) << " " <<
                     std::hex << int(c) << "\n";
      return c;
    };

    if      (addr1 == 0x00) { // CIAPRA
    }
    else if (addr1 == 0x01) { // CIAPRB
    }
    else if (addr1 == 0x02) { // CIDDRA
    }
    else if (addr1 == 0x03) { // CIDDRB
    }
    else if (addr1 == 0x04) { // TIMALO
      return debugRet1(timerA_.count & 0x00FF);
    }
    else if (addr1 == 0x05) { // TIMAHI
      return debugRet1((timerA_.count & 0xFF00) >> 8);
    }
    else if (addr1 == 0x06) { // TIMBLO
      return debugRet1(timerB_.count & 0x00FF);
    }
    else if (addr1 == 0x07) { // TIMBHI
      return debugRet1((timerB_.count & 0xFF00) >> 8);
    }
    else if (addr1 == 0x08) { // TODTEN
      // TODO
      todTimer_.latched = false;
    }
    else if (addr1 == 0x09) { // TODSEC
      // TODO
    }
    else if (addr1 == 0x0A) { // TODMIN
      // TODO
    }
    else if (addr1 == 0x0B) { // TODHRS
      // TODO
      todTimer_.latched = true;
    }
    else if (addr1 == 0x0C) { // CIASDR
      // TODO
    }
    else if (addr1 == 0x0D) { // CIAICR
      uchar c = 0x00;

      // clear on read
      if (timerA_.zeroed) { c |= 0x01; timerA_.zeroed = false; }
      if (timerB_.zeroed) { c |= 0x02; timerB_.zeroed = false; }

      if (todTimer_.alarm ) { c |= 0x04; todTimer_.alarm  = false; }
    //if (SSRData_ .finish) { c |= 0x08; SSRData_ .finish = false; }
    //if (flagLine_.signal) { c |= 0x10; flagLine_.signal = false; }

    //if (c) c |= 0x80; // signal bit is set ?

      return debugRet1(c);
    }
    else if (addr1 == 0x0E) { // CIACRA
    }
    else if (addr1 == 0x0F) { // CIACRB
    }

    return debugRet1((&CIAPRA)[addr1]);
  }
  else if (id_ == 2) { // CIA #2
    auto debugRet2 = [&](uchar c) {
      if (isDebug())
        std::cerr << "CIA #2::getByte " << std::hex << (0xDD00 | addr) << " " <<
                     std::hex << int(c) << "\n";
      return c;
    };

    if      (addr1 == 0x00) { // CI2PRA
    }
    else if (addr1 == 0x01) { // CI2PRB
    }
    else if (addr1 == 0x02) { // C2DDRA
    }
    else if (addr1 == 0x03) { // C2DDRB
    }
    else if (addr1 == 0x04) { // TI2ALO
      return debugRet2(timerA_.count & 0xFF);
    }
    else if (addr1 == 0x05) { // TI2AHI
      return debugRet2((timerA_.count & 0xFF00) >> 8);
    }
    else if (addr1 == 0x06) { // TI2BLO
      return debugRet2(timerB_.count & 0xFF);
    }
    else if (addr1 == 0x07) { // TI2BHI
      return debugRet2((timerB_.count & 0xFF00) >> 8);
    }
    else if (addr1 == 0x08) { // TO2TEN
      // TODO
      todTimer_.latched = false;
    }
    else if (addr1 == 0x09) { // TO2SEC
      // TODO
    }
    else if (addr1 == 0x0A) { // TO2MIN
      // TODO
    }
    else if (addr1 == 0x0B) { // TO2HRS
      // TODO
      todTimer_.latched = true;
    }
    else if (addr1 == 0x0C) { // CI2SDR
      // TODO
    }
    else if (addr1 == 0x0D) { // CI2ICR
      uchar c = 0x00;

      // clear on read
      if (timerA_.zeroed) { c |= 0x01; timerA_.zeroed = false; }
      if (timerB_.zeroed) { c |= 0x02; timerB_.zeroed = false; }

      if (todTimer_.alarm ) { c |= 0x04; todTimer_.alarm  = false; }
    //if (SSRData_ .finish) { c |= 0x08; SSRData_ .finish = false; }
    //if (flagLine_.signal) { c |= 0x10; flagLine_.signal = false; }

    //if (c) c |= 0x80; // signal bit is set ?

      return debugRet2(c);
    }
    else if (addr1 == 0x0E) { // CI2CRA
    }
    else if (addr1 == 0x0F) { // CI2CRB
    }

    return debugRet2((&CIAPRA)[addr1]);
  }
  else {
    return 0x00;
  }
}

void
C64_CIA::
setByte(ushort addr, uchar c)
{
  assert(addr < 0xFF);

  ushort addr1 = addr & 0x0F;

  if      (id_ == 1) { // CIA #1
    if (isDebug())
      std::cerr << "CIA #1::setByte " << std::hex << (0xDC00 | addr) << " " <<
                   std::hex << int(c) << "\n";

    if      (addr1 == 0x00) { // CIAPRA
      if (isDebug()) {
        if (CIDDRA != 0xFF || CIDDRB != 0x00)
          std::cerr << "CIDDRA or CIDDRB non-standard value\n";
      }

      uchar c1 = getKeyColumns(c);

      CIAPRB = c1;
    }
    else if (addr1 == 0x01) { // CIAPRB
      //uchar c1 = getKeyRows(c);

      //CIAPRA = c1;
    }
    else if (addr1 == 0x03) { // C2DDRB
    }
    else if (addr1 == 0x04) { // TIMALO
      timerA_.latch = (timerA_.latch & 0xFF00) | c;
    }
    else if (addr1 == 0x05) { // TIMAHI
      timerA_.latch = (timerA_.latch & 0x00FF) | (c << 8);
    }
    else if (addr1 == 0x06) { // TIMBLO
      timerB_.latch = (timerB_.latch & 0xFF00) | c;
    }
    else if (addr1 == 0x07) { // TIMBHI
      timerB_.latch = (timerB_.latch & 0x00FF) | (c << 8);
    }
    else if (addr1 == 0x08) { // TODTEN
      // TODO
    }
    else if (addr1 == 0x09) { // TODSEC
      // TODO
    }
    else if (addr1 == 0x0A) { // TODMIN
      // TODO
    }
    else if (addr1 == 0x0B) { // TODHRS
      // TODO
    }
    else if (addr1 == 0x0C) { // CIASDR
      // TODO
    }
    else if (addr1 == 0x0D) { // CIAICR
      bool setOrClear = (c & 0x80);

      if (c & 0x01) timerA_.enabled = setOrClear;
      if (c & 0x02) timerB_.enabled = setOrClear;

      if (c & 0x04) todTimer_.enabled = setOrClear;
    //if (c & 0x08) SSRData_ .enabled = setOrClear;
    //if (c & 0x10) flagLine_.enabled = setOrClear;
    }
    else if (addr1 == 0x0E) { // CIACRA
      timerA_.enabled = (c & 0x01);
      timerA_.outputB = (c & 0x02);
      timerA_.toggleB = (c & 0x04);
      timerA_.oneShot = (c & 0x08);

      if (c & 0x10)
        timerA_.count = timerA_.latch;

      timerA_.countCycles = ! (c & 0x20);
    //timerA_.serialOut   = (c & 0x40);

      todTimer_.use50 = (c & 0x80);
    }
    else if (addr1 == 0x0F) { // CIACRB
      timerB_.enabled = (c & 0x01);
      timerB_.outputB = (c & 0x02);
      timerB_.toggleB = (c & 0x04);
      timerB_.oneShot = (c & 0x08);

      if (c & 0x10)
        timerB_.count = timerB_.latch;

      timerB_.inputMode = (c & 0x60) >> 5;

      todTimer_.alarm = (c & 0x80);
    }

    (&CIAPRA)[addr1] = c;
  }
  else if (id_ == 2) { // CIA #2
    if (isDebug()) {
      std::cerr << "CIA #2::setByte " << std::hex << (0xDD00 | addr) << " " <<
                   std::hex << int(c) << "\n";
    }

    if      (addr1 == 0x00) { // CI2PRA
      gpuBank_ = 3 - (c & 0x03);

      gpuMem1_ = gpuBank_*0x4000;
      gpuMem2_ = gpuMem1_ + 0x3FFF;

      charMem1_ = gpuMem1_  + 0x1000;
      charMem2_ = charMem1_ + 0x0FFF;
    }
    else if (addr1 == 0x01) { // CI2PRB
    }
    else if (addr1 == 0x02) { // C2DDRA
    }
    else if (addr1 == 0x03) { // C2DDRB
    }
    else if (addr1 == 0x04) { // TI2ALO
      timerA_.latch = (timerA_.latch & 0xFF00) | c;
    }
    else if (addr1 == 0x05) { // TI2AHI
      timerA_.latch = (timerA_.latch & 0x00FF) | (c << 8);
    }
    else if (addr1 == 0x06) { // TI2BLO
      timerB_.latch = (timerB_.latch & 0xFF00) | c;
    }
    else if (addr1 == 0x07) { // TI2BHI
      timerB_.latch = (timerB_.latch & 0x00FF) | (c << 8);
    }
    else if (addr1 == 0x08) { // TO2TEN
      // TODO
    }
    else if (addr1 == 0x09) { // TO2SEC
      // TODO
    }
    else if (addr1 == 0x0A) { // TO2MIN
      // TODO
    }
    else if (addr1 == 0x0B) { // TO2HRS
      // TODO
    }
    else if (addr1 == 0x0C) { // CI2SDR
      // TODO
    }
    else if (addr1 == 0x0D) { // CI2ICR
      bool setOrClear = (c & 0x80);

      if (c & 0x01) timerA_.enabled = setOrClear;
      if (c & 0x02) timerB_.enabled = setOrClear;

      if (c & 0x04) todTimer_.enabled = setOrClear;
    //if (c & 0x08) SSRData_ .enabled = setOrClear;
    //if (c & 0x10) flagLine_.enabled = setOrClear;
    }
    else if (addr1 == 0x0E) { // CI2CRA
      timerA_.enabled = (c & 0x01);
      timerA_.outputB = (c & 0x02);
      timerA_.toggleB = (c & 0x04);
      timerA_.oneShot = (c & 0x08);

      if (c & 0x10)
        timerA_.count = timerA_.latch;

      timerA_.countCycles = ! (c & 0x20);
    //timerA_.serialOut   = (c & 0x40);

      todTimer_.use50 = (c & 0x80);
    }
    else if (addr1 == 0x0F) { // CI2CRB
      timerB_.enabled = (c & 0x01);
      timerB_.outputB = (c & 0x02);
      timerB_.toggleB = (c & 0x04);
      timerB_.oneShot = (c & 0x08);

      if (c & 0x10)
        timerB_.count = timerB_.latch;

      timerB_.inputMode = (c & 0x60) >> 5;

      todTimer_.alarm = (c & 0x80);
    }

    (&CIAPRA)[addr1] = c;
  }
  else {
    assert(false);
  }
}

//---

void
C64_CIA::
tick(ushort n)
{
  if (id_ != 1)
    return;

  //----

  auto handleBZero = [&]() {
    CIAICR |= 0x02; // Set bit 1

    if (timerB_.enabled) {
      if (isDebug())
        std::cerr << "B NMI\n";

      //c64_->getCPU()->resetNMI();
    }

    if (timerB_.outputB) {
      if (timerB_.toggleB) {
        // toggle bit 7
      }
      else {
        // pulse bit 7 ?
      }
    }

    timerB_.count = timerB_.latch;

    if (timerB_.oneShot)
      timerB_.enabled = false;
  };

  auto handleAZero = [&]() {
    CIAICR |= 0x01; // Set bit 0

    if (timerA_.enabled) {
      if (! c64_->getCPU()->Iflag()) {
        if (isDebug())
          std::cerr << "A IRQ " <<  std::hex << c64_->getCPU()->PC() << "\n";

        if (enableIRQ_)
          c64_->getCPU()->resetIRQ();
      }
    }

    if (timerA_.outputB) {
      // set bit 6 of port B
    }

    if (timerB_.inputMode == 2) {
      ++timerB_.count;

      if (timerB_.count == 0) {
        timerB_.zeroed = true;

        handleBZero();
      }
    }

    timerA_.count = timerA_.latch;

    if (timerA_.oneShot)
      timerA_.enabled = false;
  };

  //----

  if (timerA_.countCycles) {
    // microprocessor machine cycles = 1,022,730 cycles per second
    // See line 8560 of mapping-c64.txt

    if (timerA_.count > 0 && timerA_.count <= n) {
      timerA_.zeroed = true;

      handleAZero();
    }
    else {
      timerA_.count -= n;
    }
  }
  else { // count signals on CNT line at pin 4 of User Port
    // TODO
  }

  //---

  if      (timerB_.inputMode == 0) { // count cycles
    if (timerB_.count > 0 && timerB_.count <= n) {
      timerB_.zeroed = true;

      handleBZero();
    }
    else {
      timerB_.count -= n;
    }
  }
  else if (timerB_.inputMode == 1) { // count signals on CNT line at pin 4 of User Port
    // TODO
  }
  else if (timerB_.inputMode == 2) { // Count each time that Timer A counts down to 0
    // Handled by A timer
  }
  else if (timerB_.inputMode == 3) { // Count Timer A 0's when CNT pulses are also present
    // TODO
  }
}
