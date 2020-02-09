#ifndef C64_CIA_H
#define C64_CIA_H

#include <iostream>
#include <cassert>

class C64;

using uchar  = unsigned char;
using ushort = unsigned short;

class C64_CIA {
 public:
  C64_CIA(C64 *c64, int id);

  virtual ~C64_CIA() { }

  //---

  bool isDebug() const { return debug_; }
  void setDebug(bool b) { debug_ = b; }

  //---

  uchar getByte(ushort addr) const;
  void setByte(ushort addr, uchar c);

  //---

  void tick(ushort n);

  //---

  virtual uchar getKeyColumns(uchar) { return 0xFF; }

  //---

  ushort gpuMem1() const { return gpuMem1_; }
  ushort gpuMem2() const { return gpuMem2_; }

  ushort charMem1() const { return charMem1_; }
  ushort charMem2() const { return charMem2_; }

 public:
  // CIA #1 Registers (0xDC00 - 0xDC0F)
  // Note: must be contiguos

  // CIAPRA : Data Port Register A (0xDC00)
  //
  // Bit 0:  Select to read keyboard column 0
  //         Read joystick 2 up direction
  // Bit 1:  Select to read keyboard column 1
  //         Read joystick 2 down direction
  // Bit 2:  Select to read keyboard column 2
  //         Read joystick 2 left direction
  //         Read paddle 1 fire button
  // Bit 3:  Select to read keyboard column 3
  //         Read joystick 2 right direction
  //         Read paddle 2 fire button
  // Bit 4:  Select to read keyboard column 4
  //         Read joystick 2 fire button
  // Bit 5:  Select to read keyboard column 5
  // Bit 6:  Select to read keyboard column 6
  //         Select to read paddles on Port A or B
  // Bit 7:  Select to read keyboard column 7
  //         Select to read paddles on Port A or B
  uchar CIAPRA { 0xFF };

  // (CIAPRB) Data Port Register B (0xDC01)
  //
  // Bit 0:  Read keyboard row 0
  //         Read joystick 1 up direction
  // Bit 1:  Read keyboard row 1
  //         Read joystick 1 down direction
  // Bit 2:  Read keyboard row 2
  //         Read joystick 1 left direction
  //         Read paddle 1 fire button
  // Bit 3:  Read keyboard row 3
  //         Read joystick 1 right direction
  //         Read paddle 2 fire button
  // Bit 4:  Read keyboard row 4
  //         Read joystick 1 fire button
  // Bit 5:  Read keyboard row 5
  // Bit 6:  Read keyboard row 6
  //         Toggle or pulse data output for Timer A
  // Bit 7:  Read keyboard row 7
  //         Toggle or pulse data output for Timer B
  uchar CIAPRB { 0x00 };

  // CIDDRA : Data Direction Register A (0xDC02)
  // Each bit selects corresponding bit of Data Port A for input or output (0=input, 1=output)
  // Default is 0xFF (all outputs)
  uchar CIDDRA { 0xFF };

  // CIDDRB : Data Direction Register B (0xDC03)
  // Each bit selects corresponding bit of Data Port B for input or output (0=input, 1=output)
  // Default is 0x00 (all inputs)
  uchar CIDDRB { 0x00 };

  uchar TIMALO { 0x95 }; // 0xDC04 (Timer A Low/High)
  uchar TIMAHI { 0x42 }; // 0xDC05
  uchar TIMBLO { 0x00 }; // 0xDC06 (Timer B Low/High)
  uchar TIMBHI { 0x00 }; // 0xDC07
  uchar TODTEN { 0x00 }; // 0xDC08 (Time of Day Clock - TOD)
  uchar TODSEC { 0x00 }; // 0xDC09
  uchar TODMIN { 0x00 }; // 0xDC0A
  uchar TODHRS { 0x00 }; // 0xDC0B
  uchar CIASDR { 0x00 }; // 0xDC0C
  uchar CIAICR { 0x00 }; // 0xDC0D
  uchar CIACRA { 0x00 }; // 0xDC0E
  uchar CIACRB { 0x00 }; // 0xDC0F

  // CIA #1 Register Images ($DC10-$DCFF)
  // every 16-byte area in this 256-byte block is a mirror of every other
  uchar dummy[240];

 private:
  C64 *c64_ { nullptr };
  int  id_  { 0 };

  struct Timer {
    ushort latch       { 0 };     // reset value
    ushort count       { 0 };     // current value
    bool   enabled     { false }; // is enabled (signals)
    bool   zeroed      { false }; // went to zero
    bool   outputB     { false }; // output on port B
    bool   toggleB     { false }; // toggle port B
    bool   oneShot     { false }; // one shot timer
    bool   countCycles { false }; // Timer A input mode
                                  //  true  = count microprocessor cycles
                                  //  false = count user port signals
    uchar  inputMode   { 0 };     // Timer B input mode
                                  //  0 = Count microprocessor cycles
                                  //  1 = Count signals on CNT line at pin 4 of User Port
                                  //  2 = Count each time that Timer A counts down to 0
                                  //  3 = Count Timer A 0's when CNT pulses are also present
  };

  struct TOD {
    bool enabled { false };
    bool alarm   { false };
    bool use50   { false };
    bool latched { false };
  };

  mutable Timer timerA_;
  mutable Timer timerB_;
  mutable TOD   todTimer_;

  //---

  // Memory select (CIA #2)
  uchar  gpuBank_  { 0 };
  ushort gpuMem1_  { 0x0000 };
  ushort gpuMem2_  { 0x3FFF };
  ushort charMem1_ { 0x1000 };
  ushort charMem2_ { 0x1FFF };

  bool debug_     { false };
  bool enableIRQ_ { true };
};

#endif
