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

  void update() override;

 private:
  C64*  machine_ { nullptr };
  bool  debug_   { false };
  bool  loram_   { true };
  bool  hiram_   { true };
  bool  charen_  { true };
};

#endif
