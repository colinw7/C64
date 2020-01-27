#ifndef C64_6502_H
#define C64_6502_H

#include <C6502.h>

class C64;

class C64_6502 : public C6502 {
 public:
  C64_6502(C64 *machine);
 ~C64_6502();

  uchar getByte(ushort addr) const override;
  void setByte(ushort addr, uchar c) override;

  void memset(ushort addr, const uchar *data, ushort len) override;

  bool isScreen(ushort pos, ushort len) const override;

  ushort gpuMem() const { return gpuMem1_; }

  ushort charMem() const { return charMem1_; }

 private:
  C64*   machine_  { nullptr };
  bool   debug_    { false };
  bool   loram_    { true };
  bool   hiram_    { true };
  bool   charen_   { true };
  uchar  gpuBank_  { 0 };
  ushort gpuMem1_  { 0x0000 };
  ushort gpuMem2_  { 0x3FFF };
  ushort charMem1_ { 0x1000 };
  ushort charMem2_ { 0x1FFF };
};

#endif
