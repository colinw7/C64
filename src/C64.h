#ifndef C64_H
#define C64_H

using uchar  = unsigned char;
using ushort = unsigned short;

class C64_6502;

class C64 {
 public:
  C64();

  ushort screenLine() const { return screenLine_; }

  void setRasterCompareInterruptValue(ushort s) { rasterCompareInterruptValue_ = s; }

 private:
  void drawScreen();
  void drawChar(int x, int y, int i, uchar c);
  void drawSprite(int s, uchar addr, bool doubleHeight);
  void drawPixel(int x, int y);

 private:
  C64_6502* cpu_                         { nullptr };
  ushort    screenLine_                  { 0 };
  ushort    rasterCompareInterruptValue_ { 0 };
};

#endif
