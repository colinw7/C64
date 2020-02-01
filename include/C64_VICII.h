#ifndef C64_VICII_H
#define C64_VICII_H

#include <cassert>

class C64;

using uchar  = unsigned char;
using ushort = unsigned short;

class C64_VICII {
 public:
  C64_VICII(C64 *c64);

  virtual ~C64_VICII() { }

  //---

  uchar getByte(ushort addr) const;
  void setByte(ushort addr, uchar c);

  //---

  void drawScreen();

  void drawCharBorder();

  void drawChar(int x, int y, int i, uchar c);

  void drawSprites();
  void drawSprite(int s, uchar addr, bool doubleWidth, bool doubleHeight, bool multiColor);

  virtual void fillScreen(uchar c);

  virtual void drawPixel(int x, int y, uchar c);

  //---

  // VIC-II Chip Registers (0xD000 - 0xD02E)
  // Note: must be contiguos

 public:
  // Sprite Pos (0xD000 - 0xD010)
  uchar spriteX(uchar i) {
    assert(i < 8);
    uchar x = (&SP0X_)[i*2];
    if (MSIGX_ & (1 << i)) x += 256;
    return x;
  }

  uchar spriteY(uchar i) { assert(i < 8); return (&SP0Y_)[i*2]; }

 private:
  uchar SP0X_ { 0x00 }; // 0xD000
  uchar SP0Y_ { 0x00 };

 public:
  uchar SP1X_ { 0x00 };
  uchar SP1Y_ { 0x00 };
  uchar SP2X_ { 0x00 };
  uchar SP2Y_ { 0x00 };
  uchar SP3X_ { 0x00 };
  uchar SP3Y_ { 0x00 };
  uchar SP4X_ { 0x00 };
  uchar SP4Y_ { 0x00 };
  uchar SP5X_ { 0x00 };
  uchar SP5Y_ { 0x00 };
  uchar SP6X_ { 0x00 };
  uchar SP6Y_ { 0x00 };
  uchar SP7X_ { 0x00 };
  uchar SP7Y_ { 0x00 };

 private:
  uchar MSIGX_ { 0x00 }; // 0xD010 (Most Significant Bits of Sprites 0-7 Horizontal Position)

 public:
  // Vertical Fine Scrolling and Control Register
  //  Bits 0-2: Fine scroll display vertically by X scan lines (0-7)
  //  Bit  3:   Select a 24-row or 25-row text display (1=25 rows, 0=24 rows)
  //  Bit  4:   Blank the entire screen to the same color as the background (0=blank)
  //  Bit  5:   Enable bitmap graphics mode (1=enable)
  //  Bit  6:   Enable extended color text mode (1=enable)
  //  Bit  7:   High bit (Bit 8) of raster compare register at 53266 ($D012)
  uchar fineScrollY() { return (SCROLY_ & 0x7); }
  uchar textRows() const { return (SCROLY_ & 0x08 ? 25 : 24); }
  bool noBlankBackground() const { return (SCROLY_ & 0x10); }
  bool isBitmapGraphics() const { return (SCROLY_ & 0x20); }
  bool isExtendedColor() const { return (SCROLY_ & 0x40); }

 private:
  uchar SCROLY_ { 0x9B }; // 0xD011

 public:
  // Read:  Current Raster Scan Line
  // Write: Line to Compare for Raster IRQ
  uchar RASTER_ { 0x37 }; // 0xD012

 public:
  // Light Pen Position
  uchar LPENX { 0x00 }; // 0xD013
  uchar LPENY { 0x00 }; // 0xD014

  // Sprite Enable Register
  uchar SPENA { 0x00 }; // 0xD015

 public:
  // Horizontal Fine Scrolling and Control Register
  //  Bits 0-2: Fine scroll display horizontally by X dot positions (0-7)
  //  Bit  3:   Select a 38-column or 40-column text display (1=40 columns, 0=38 columns)
  //  Bit  4:   Enable multicolor text or multicolor bitmap mode (1=multicolor on, 0=multicolor off)
  //  Bit  5:   Video chip reset (0=normal operations, 1=video completely off)
  //  Bits 6-7: Unused

  uchar fineScrollX() { return (SCROLX_ & 0x7); }
  uchar textColumns() const { return (SCROLX_ & 0x08 ? 40 : 38); }
  bool isMultiColor() const { return (SCROLX_ & 0x10); }
  bool videoReset() const { return (SCROLX_ & 0x20); }

 private:
  uchar SCROLX_ { 0x08 }; // 0xD016

 public:
  // Sprite Vertical Expansion Register (Bit per sprite)
  bool isDoubleHeightSprite(uchar i) const { assert(i < 8); return (YXPAND_ & (1 << i)); }

 private:
  uchar YXPAND_ { 0x00 }; // 0xD017

 public:
  uchar textCharDotOffset() const { return (VMCSB_ & 0x0E); }
  uchar videoMatrixOffset() const { return (VMCSB_ & 0xF0) >> 4; }

 private:
  // VIC-II Chip Memory Control Register
  // Bit  0  : Unused
  // Bits 1-3: Text character dot-data base address within VIC-II address space
  // Bits 4-7: Video matrix base address within VIC-II address space
  uchar VMCSB_ { 0x14 }; // 0xD018

 public:
  // VIC Interrupt Flag Register
  //  Bit 0:    Is the Raster Compare a possible source of an IRQ?  (1=yes)
  //  Bit 1:    Is a collision between a sprite and the normal graphics display
  //            a possible source of an IRQ?  (1=yes)
  //  Bit 2:    Is a collision between two sprites a possible source of an IRQ?  (1=yes)
  //  Bit 3:    Is the light pen trigger a possible source of an IRQ?  (1=yes)
  //  Bits 4-6: Not used
  //  Bit 7:    Is there any VIC-II chip IRQ source which could cause an IRQ?  (1=yes)
  uchar VICIRQ  { 0x0F }; // 0xD019

 public:
  // IRQ Mask Register
  //  Bit 0:    Enable Raster Compare IRQ (1=interrupt enabled)
  //  Bit 1:    Enable IRQ to occur when sprite collides with display of normal
  //            graphics data (1=interrupt enabled)
  //  Bit 2:    Enable IRQ to occur when two sprites collide (1=interrupt enabled)
  //  Bit 3:    Enable light pen to trigger an IRQ (1=interrupt enabled)
  //  Bits 4-7: Not used
  bool isRasterCompareIRQ  () const { return (IRQMASK_ & 0x01); }
  bool isSpriteCollisionIRQ() const { return (IRQMASK_ & 0x02); }
  bool isSpriteSpriteIRQ   () const { return (IRQMASK_ & 0x04); }
  bool isLightPenIRQ       () const { return (IRQMASK_ & 0x08); }

 private:
  uchar IRQMASK_ { 0x00 }; // 0xD01A

 public:
  // Sprite to Foreground Display Priority Register (bit per sprite)
  bool isSpriteBehind(uchar i) const { assert(i < 8); return (SPBGPR_ & (1 << i)); }

 private:
  uchar SPBGPR_ { 0x00 }; // 0xD01B

 public:
  // Sprite Multicolor Registers (bit per sprite)
  bool isSpriteMulticolor(uchar i) const { assert(i < 8); return (SPMC_ & (1 << i)); }

 private:
  uchar SPMC_ { 0x00 }; // 0xD01C

 public:
  // Sprite Horizontal Expansion Register (bit per sprite)
  bool isSpriteDoubleWidth(uchar i) const { assert(i < 8); return (XXPAND_ & (1 << i)); }

 private:
  uchar XXPAND_ { 0x00 }; // 0xD01D

 public:
  // Sprite to Sprite Collision Register (bit per sprite)
  uchar SPSPCL  { 0x00 }; // 0xD01E

  // Sprite to Foreground Collision Register (bit per sprite)
  uchar SPBGCL  { 0x00 }; // 0xD01F

  // Border Color Register
  uchar EXTCOL  { 0x0E }; // 0xD020

  // Background colors
  uchar BGCOL0  { 0x06 }; // 0xD021
  uchar BGCOL1  { 0x01 }; // 0xD022
  uchar BGCOL2  { 0x02 }; // 0xD023
  uchar BGCOL3  { 0x03 }; // 0xD024

  // Sprite Multicolor Registers
  uchar SPMC0   { 0x04 }; // 0xD025
  uchar SPMC1   { 0x00 }; // 0xD026

  // Sprite Colors
  uchar SP0COL  { 0x01 }; // 0xD027
  uchar SP1COL  { 0x02 }; // 0xD028
  uchar SP2COL  { 0x03 }; // 0xD029
  uchar SP3COL  { 0x04 }; // 0xD02A
  uchar SP4COL  { 0x05 }; // 0xD02B
  uchar SP5COL  { 0x06 }; // 0xD02C
  uchar SP6COL  { 0x07 }; // 0xD02D
  uchar SP7COL  { 0x4C }; // 0xD02E

  uchar spriteCol(uchar i) { assert(i < 8); return (&SP0COL)[i]; }

  uchar unused[17]; // 0xD02F - 0xD03F (always 0xFF)

  uchar regimg[960]; // 0xD040 - 0xD3FF (mirror of bottom 64 * 15)

  //---

 private:
  // extra (internal) variable

  C64 *c64_ { nullptr };

 public:
  // current raster line
  uchar rasterLine() const { return rasterLine_; }
  void setRasterLine(uchar l) { rasterLine_ = l; }

 private:
  uchar rasterLine_ { 0 };
};

#endif
