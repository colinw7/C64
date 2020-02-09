#include <C64_VICII.h>
#include <C64_6502.h>
#include <C64.h>
#include <C6502.h>
#include <iostream>

C64_VICII::
C64_VICII(C64 *c64) :
 c64_(c64)
{
  for (int i = 0; i < 17; ++i)
    unused[i] = 0xFF;
}

uchar
C64_VICII::
getByte(ushort addr) const
{
  assert(addr < 0x400);

  ushort addr1 = addr & 0x3F;

  if (addr1 > 0x2E) return 0xFF;

  std::cerr << "VICII::getByte " << std::hex << (0xD000 | addr) << "\n";

  if (addr1 == 0x12) return rasterLine();

  return (&SP0X_)[addr1];
}

void
C64_VICII::
setByte(ushort addr, uchar c)
{
  assert(addr < 0x400);

  ushort addr1 = addr & 0x3F;

  if (addr1 > 0x2E) return;

  std::cerr << "VICII::setByte " << std::hex << (0xD000 | addr) << " " <<
               std::hex << int(c) << "\n";

  (&SP0X_)[addr1] = c;
}

void
C64_VICII::
drawScreen()
{
  auto cpu = c64_->getCPU();

//bool vscroll = fineScrollY();
//bool hscroll = fineScrollX();

  // 25 Lines by 40 Columns
  uchar ny = textRows();
  uchar nx = textColumns();

//bool noblank        = noBlankBackground();
  bool bitmapGraphics = isBitmapGraphics();
//bool extendedColor  = isExtendedColor();
//bool videoReset     = videoReset();

//uchar CI2PRA  = cpu->getByte(0xDD00);
//uchar VICBank = (3 - (CI2PRA & 0x3));

  if (! bitmapGraphics) {
    uchar  videoMatrixOffset = this->videoMatrixOffset();
    ushort videoMatrixData   = cpu->gpuMem1() + videoMatrixOffset*0x400; // (0x400 == 1024)

    drawCharBorder();

    int ch = 8; // pixels

    int i = 0;

    for (int y = 0; y < ny; ++y) {
      for (int y1 = 0; y1 <= ch; ++y1)
        setRasterLine(y*ch + y1);

      for (int x = 0; x < nx; ++x, ++i, ++videoMatrixData) {
        uchar c = cpu->getByte(videoMatrixData);

        drawChar(x, y, i, c);
      }
    }
  }
  else {
    bool multicolor = isMultiColor();

    uchar  textCharDotOffset = this->textCharDotOffset();
    ushort textCharDotData   = cpu->gpuMem1() + textCharDotOffset*0x400; // (0x400 == 1024)

    if (! multicolor) {
      int w = 40; // 40 bytes, 320 pixels
      int h = 200;

      for (int y = 0; y < h; ++y) {
        setRasterLine(y);

        int ix = 0;

        for (int x = 0; x < w; ++x) {
          uchar c = cpu->getByte(textCharDotData++);

          for (int i = 0; i < 8; ++i, ++ix) {
            bool b = (c & (1 << i));

            uchar pc = (! b ? BGCOL0 : BGCOL1);

            drawPixel(x + ix, y, pc);
          }
        }
      }
    }
    else {
      uchar  videoMatrixOffset = this->videoMatrixOffset();
      ushort videoMatrixData   = cpu->gpuMem1() + videoMatrixOffset*0x400; // (0x400 == 1024)

      int w = 20; // 20 bytes, 160 pixels
      int h = 200;

      for (int y = 0; y < h; ++y) {
        int ix = 0;

        for (int x = 0; x < w; ++x, ++textCharDotData) {
          uchar tc = cpu->getByte(textCharDotData++);
          uchar vc = cpu->getByte(videoMatrixData++);

          for (int i = 0; i < 4; ++i, ++ix) {
            bool b0 = (tc & (1 << (i*2    )));
            bool b1 = (tc & (1 << (i*2 + 1)));

            uchar pc;

            if      (! b0 && ! b1) pc = BGCOL0;
            else if (  b0 && ! b1) pc = (vc & 0x0F);
            else if (! b0 &&   b1) pc = (vc & 0xF0) >> 4;
            else                   pc = BGCOL1;

            drawPixel(x + ix, y, pc);
          }
        }
      }
    }
  }

  //---

  drawSprites();

  //---

  setRasterLine(0);
}

void
C64_VICII::
drawCharBorder()
{
  fillScreen(EXTCOL);
}

void
C64_VICII::
drawChar(int x, int y, int i, uchar c)
{
  auto cpu = c64_->getCPU();

  // characters are 8x8 (8 bytes)

  bool multicolor    = isMultiColor();
  bool extendedColor = isExtendedColor();

  uchar  textCharDotOffset = this->textCharDotOffset();
  ushort textCharDotData   = cpu->gpuMem1() + textCharDotOffset*0x400; // (0x400 == 1024)

  ushort charRom = textCharDotData + c*8;
//ushort charRom = cpu->getWord(0xC000) + c*8;
//ushort charRom = characters_data[c*8];

  int cw = 1; // bytes
  int ch = 8; // pixels

  int iy = y*8;

  if      (! multicolor && ! extendedColor) {
    uchar fgColor = cpu->getWord(0xD800 + i) & 0x0F;

    for (int cy = 0; cy < ch; ++cy, ++iy) {
      int ix = x*8;

      for (int cx = 0; cx < cw; ++cx, ++charRom) {
        uchar c1 = cpu->getByte(charRom);

        for (int i = 7; i >= 0; --i, ++ix) {
          bool b = (c1 & (1 << i));

          uchar pc = (! b ? BGCOL0 : fgColor);

          drawPixel(ix, iy, pc);
        }
      }
    }
  }
  else if (multicolor) {
    uchar colorChar = cpu->getWord(0xD800 + i);

    uchar fgColor   = colorChar & 0x07;
    bool  multiChar = colorChar & 0x08;

    for (int cy = 0; cy < ch; ++cy, ++iy) {
      int ix = x*8;

      for (int cx = 0; cx < cw; ++cx, ++charRom) {
        uchar c1 = cpu->getByte(charRom);

        for (int i = 3; i >= 0; --i, ++ix) {
          if (multiChar) {
            bool b0 = (c1 & (1 << (i*2    )));
            bool b1 = (c1 & (1 << (i*2 + 1)));

            uchar pc;

            if      (! b0 && ! b1) pc = BGCOL0;
            else if (  b0 && ! b1) pc = BGCOL1;
            else if (! b0 &&   b1) pc = BGCOL2;
            else                   pc = fgColor;

            drawPixel(ix    , iy, pc);
            drawPixel(ix + 1, iy, pc);
          }
          else {
            bool b = (c1 & (1 << i));

            uchar pc = (! b ? BGCOL0 : fgColor);

            drawPixel(ix, iy, pc);
          }
        }
      }
    }
  }
  else if (extendedColor) {
    for (int cy = 0; cy < ch; ++cy, ++iy) {
      int ix = x*8;

      for (int cx = 0; cx < cw; ++cx, ++charRom) {
        uchar c1 = cpu->getByte(charRom);

        uchar pc;

        if      (c1 <  64) pc = BGCOL0;
        else if (c1 < 128) pc = BGCOL1;
        else if (c1 < 192) pc = BGCOL2;
        else               pc = BGCOL3;

        c1 &= 0x3F;

        for (int i = 7; i >= 0; --i, ++ix) {
          bool b = (c1 & (1 << i));

          if (b)
            drawPixel(ix, iy, pc);
        }
      }
    }
  }
}

void
C64_VICII::
drawSprites()
{
  auto cpu = c64_->getCPU();

  // 8 Sprites, 24x21 (64 bytes)

  uchar  textCharDotOffset = this->textCharDotOffset();
  ushort textCharDotData   = cpu->gpuMem1() + textCharDotOffset*0x400; // (0x400 == 1024)

  ushort spriteAddr = textCharDotData + 0x3F8;

  for (int s = 0; s < 8; ++s, ++spriteAddr) {
    if (SPENA & (1 << s)) {
      bool doubleHeight = isDoubleHeightSprite(s);
//    bool behind       = isSpriteBehind(s);
      bool multicolor   = isSpriteMulticolor(s);
      bool doubleWidth  = isSpriteDoubleWidth(s);

      ushort saddr = 64*cpu->getByte(spriteAddr);

      drawSprite(s, saddr, doubleWidth, doubleHeight, multicolor);
    }
  }
}

void
C64_VICII::
drawSprite(int s, uchar addr, bool doubleWidth, bool doubleHeight, bool multicolor)
{
  auto cpu = c64_->getCPU();

  // Sprite: width=24, height=21

  // TODO: collision

  uchar x = spriteX(s);
  uchar y = spriteY(s);

  uchar pc = spriteCol(s); // SP<n>COL

  uchar pc1 = SPMC0;
  uchar pc2 = SPMC1;

  assert(x > 0 && y > 0 && (addr + doubleHeight) > 0);

  for (int iy = 0; iy < 21; ++iy) {
    for (int ix = 0; ix < 3; ++ix, ++addr) {
      uchar c = cpu->getByte(addr);

      if (! multicolor) {
        for (int i = 0; i < 8; ++i) {
          bool b = (c & (1 << i));

          if (b) {
            if      (! doubleWidth && ! doubleHeight) {
              drawPixel(x + ix + i, y + iy, pc);
            }
            else if (  doubleWidth && ! doubleHeight) {
              drawPixel(x + 2*ix     + i, y + iy    , pc);
              drawPixel(x + 2*ix + 1 + i, y + iy + 1, pc);
            }
            else if (! doubleWidth &&   doubleHeight) {
              drawPixel(x + ix + i, y + 2*iy    , pc);
              drawPixel(x + ix + i, y + 2*iy + 1, pc);
            }
            else {
              drawPixel(x + 2*ix     + i, y + 2*iy    , pc);
              drawPixel(x + 2*ix + 1 + i, y + 2*iy    , pc);
              drawPixel(x + 2*ix     + i, y + 2*iy + 1, pc);
              drawPixel(x + 2*ix + 1 + i, y + 2*iy + 1, pc);
            }
          }
        }
      }
      else {
        for (int i = 0; i < 4; ++i) {
          bool b0 = (c & (1 << (i*2    )));
          bool b1 = (c & (1 << (i*2 + 1)));

          if (b0 || b1) {
            uchar pc12;

            if      (  b0 && ! b1)
              pc12 = pc;
            else if (! b0 &&   b1)
              pc12 = pc1;
            else
              pc12 = pc2;

            if (doubleHeight) {
              drawPixel(x + ix + i, y + 2*iy    , pc12);
              drawPixel(x + ix + i, y + 2*iy + 1, pc12);
            }
            else
              drawPixel(x + ix + i, y + iy, pc12);
          }
        }
      }
    }
  }
}

void
C64_VICII::
fillScreen(uchar)
{
}

void
C64_VICII::
drawPixel(int x, int y, uchar c)
{
  assert(x + y + c > 0);
}

bool
C64_VICII::
isScreen(ushort addr, ushort len) const
{
  auto cpu = c64_->getCPU();

  ushort addr1 = addr;
  ushort addr2 = addr1 + len - 1;

  auto rangesOverlap = [&](ushort r1, ushort r2) {
    return ! (addr2 < r1 || addr1 > r2);
  };

  if (rangesOverlap(0xD000, 0xD400)) return true;

  uchar  videoMatrixOffset = this->videoMatrixOffset();
  ushort videoMatrixData1  = cpu->gpuMem1() + videoMatrixOffset*0x400; // (0x400 == 1024)
  ushort videoMatrixData2  = videoMatrixData1 + 0x1FFF;

  if (rangesOverlap(videoMatrixData1, videoMatrixData2)) return true;

  uchar  textCharDotOffset = this->textCharDotOffset();
  ushort textCharDotData1  = cpu->gpuMem1() + textCharDotOffset*0x400; // (0x400 == 1024)
  ushort textCharDotData2  = textCharDotData1 + 0x1FFF;

  if (rangesOverlap(textCharDotData1, textCharDotData2)) return true;

  return false;
}
