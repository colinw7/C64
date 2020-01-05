#include <C64.h>
#include <C6502.h>

#include <basic.h>
#include <characters.h>
#include <kernel.h>

#include <cassert>

enum Colors {
  BLACK,
  WHITE,
  RED,
  CYAN,  // LIGHT BLUE-GREEN
  PURPLE,
  GREEN,
  BLUE,
  YELLOW,
  ORANGE,
  BROWN,
  LIGHT_RED,
  DARK_GRAY,
  MEDIUM_GRAY,
  LIGHT_GREEN,
  LIGHT_BLUE,
  LIGHT_GRAY,
};


class C64_6502 : public C6502 {
 public:
  C64_6502(C64 *machine) :
   C6502(), machine_(machine) {
  }

 ~C64_6502() { }

  uchar getByte(ushort addr) const {
    if      (addr >= 0xA000 && addr < 0xC000) {
      if (loram_)
        return basic_data[addr - 0xA000]; // 8K Basic ROM
    }
    else if (addr >= 0xD000 && addr < 0xDFFF) {
      if (! charen_)
        return characters_data[addr - 0xD000]; // 4K Character ROM
      else {
        if (addr == 0xD018)
          return machine_->screenLine();
      }
    }
    else if (addr >= 0xE000 && addr < 0xFFFF) {
      if (hiram_)
        return kernel_data[addr - 0xE000]; // 8K Kernel ROM
    }

    return C6502::getByte(addr);
  }

  void setByte(ushort addr, uchar c) {
    if       (addr == 0x0001) {
      loram_  = (c & 0x01);
      hiram_  = (c & 0x02);
      charen_ = (c & 0x04);
    }
    else if (addr == 0xD018) {
      machine_->setRasterCompareInterruptValue(c); // low 8 bits
    }

    C6502::setByte(addr, c);
  }

  void memset(ushort addr, const uchar *data, ushort len) {
    C6502::memset(addr, data, len);
  }

 private:
  C64*  machine_ { nullptr };
  bool  loram_   { false };
  bool  hiram_   { false };
  bool  charen_  { false };
};

// 8K BASIC Interpreter ROM
// 8K Operating System Kernal ROM
// 4K Character Generator ROM
// Sound Interface Device (SID)
// 6566 Video Interface Controller (VIC-II)
// two 6526 Complex Interface adapter chips

C64::
C64()
{
  cpu_ = new C64_6502(this);

  // BASIC Working Storage (0x0 - 0x8F)

  cpu_->setByte(0x00, 0xEF  ); // D6510 (6510 On-Chip I/O DATA Direction Register)
  cpu_->setByte(0x01, 0x07  ); // R6510
  cpu_->setByte(0x02, 0x00  );
  cpu_->setWord(0x03, 0xB1AA); // ADRAY1
  cpu_->setWord(0x05, 0xB391); // ADRAY2
  cpu_->setByte(0x07, 0x00  ); // CHARAC
  cpu_->setByte(0x08, 0x00  ); // ENDCHR
  cpu_->setByte(0x09, 0x00  ); // TRMPOS
  cpu_->setByte(0x0A, 0x00  ); // VERCK
  cpu_->setByte(0x0B, 0x00  ); // COUNT
  cpu_->setByte(0x0C, 0x00  ); // DIMFLG
  cpu_->setByte(0x0D, 0x00  ); // VALTYP
  cpu_->setByte(0x0E, 0x00  ); // INTFLG
  cpu_->setByte(0x0F, 0x00  ); // GARBFL
  cpu_->setByte(0x10, 0x00  ); // SUBFLG
  cpu_->setByte(0x11, 0x00  ); // INPFLG
  cpu_->setByte(0x12, 0x00  ); // TANSGN
  cpu_->setByte(0x13, 0x00  ); // CHANNL
  cpu_->setWord(0x14, 0x0000); // LINNUM
  cpu_->setByte(0x16, 0x00  ); // TEMPPT
  cpu_->setWord(0x17, 0x0000); // LASTPT
  cpu_->setByte(0x19, 0x00  ); // TEMPST (0x19 - 0x21)
  cpu_->setByte(0x22, 0x00  ); // INDEX (0x22 - 0x25)
  cpu_->setByte(0x26, 0x00  ); // RESHO (0x26 - 0x2A)
  cpu_->setWord(0x2B, 0x0801); // TXTTAB
  cpu_->setWord(0x2D, 0x0000); // VARTAB
  cpu_->setWord(0x2F, 0x0000); // ARYTAB
  cpu_->setWord(0x31, 0x0000); // STREND
  cpu_->setWord(0x33, 0x0000); // FREETOP
  cpu_->setWord(0x35, 0x0000); // FRESPC
  cpu_->setWord(0x37, 0x0000); // MEMSIZ
  cpu_->setWord(0x39, 0x0000); // CURLIN
  cpu_->setWord(0x3B, 0x0000); // OLDLIN
  cpu_->setWord(0x3D, 0x0000); // OLDTXT
  cpu_->setWord(0x3F, 0x0000); // DATLIN
  cpu_->setWord(0x41, 0x0000); // DATPTR
  cpu_->setWord(0x43, 0x0000); // INPPTR
  cpu_->setWord(0x45, 0x0000); // VARNAM
  cpu_->setWord(0x47, 0x0000); // VARPNT
  cpu_->setWord(0x49, 0x0000); // FORPNT
  cpu_->setWord(0x4B, 0x0000); // OPPTR
  cpu_->setByte(0x4D, 0x00  ); // OPMASK
  cpu_->setWord(0x4E, 0x0000); // DEFPNT
  cpu_->setByte(0x50, 0x00  ); // DSCPNT (0x50 - 0x52)
  cpu_->setByte(0x53, 0x00  ); // FOUR6
  cpu_->setByte(0x54, 0x00  ); // JMPER (0x54 - 0x56)
  cpu_->setByte(0x57, 0x00  ); //       (0x57 - 0x60)
  cpu_->setByte(0x61, 0x00  ); // FAC1 (0x61 - 0x66)
  cpu_->setByte(0x67, 0x00  ); // SGNFLG
  cpu_->setByte(0x68, 0x00  ); // BITS
  cpu_->setByte(0x69, 0x00  ); // FAC2 (0x69 - 0x6E) ARGEXP, ARGHO, ARGSGN
  cpu_->setByte(0x6F, 0x00  ); // ARISGN
  cpu_->setByte(0x70, 0x00  ); // FACOV
  cpu_->setWord(0x71, 0x0000); // FBUFPT
  cpu_->setByte(0x73, 0x00  ); // CHRGET (0x73 - 0x8A)
  cpu_->setByte(0x8B, 0x00  ); // RNDX (0x8B - 0x8F)

  cpu_->setByte(0x90, 0x00  ); // STATUS
  cpu_->setByte(0x91, 0x00  ); // STKEY
  cpu_->setByte(0x92, 0x00  ); // SVXT
  cpu_->setByte(0x93, 0x00  ); // VERCK
  cpu_->setByte(0x94, 0x00  ); // C3PO
  cpu_->setByte(0x95, 0x00  ); // BSOUR
  cpu_->setByte(0x96, 0x00  ); // SYNO
  cpu_->setByte(0x97, 0x00  ); // XSAV
  cpu_->setByte(0x98, 0x00  ); // LDTND
  cpu_->setByte(0x99, 0x00  ); // DFLTN
  cpu_->setByte(0x9A, 0x00  ); // DFLTO
  cpu_->setByte(0x9B, 0x00  ); // PRTY
  cpu_->setByte(0x9C, 0x00  ); // DPSW
  cpu_->setByte(0x9D, 0x00  ); // MSGFLG
  cpu_->setByte(0x9E, 0x00  ); // PTR1
  cpu_->setByte(0x9F, 0x00  ); // PTR2
  cpu_->setByte(0xA0, 0x00  ); // TIME (0xA0 - 0xA2)
  cpu_->setByte(0xA3, 0x00  ); //      (0xA3 - 0xA4)
  cpu_->setByte(0xA5, 0x00  ); // CNTDN
  cpu_->setByte(0xA6, 0x00  ); // BUFPNT
  cpu_->setByte(0xA7, 0x00  ); // INBIT
  cpu_->setByte(0xA8, 0x00  ); // BITCI
  cpu_->setByte(0xA9, 0x00  ); // RINONE
  cpu_->setByte(0xAA, 0x00  ); // RIDATA
  cpu_->setByte(0xAB, 0x00  ); // RIPRTY
  cpu_->setByte(0xAC, 0x00  ); // SAL (0xAC - 0xAD)
  cpu_->setByte(0xAE, 0x00  ); // EAL (0xAE - 0xAF)
  cpu_->setByte(0xB0, 0x00  ); // CMP0 (0xB0 - 0xB1)
  cpu_->setByte(0xB2, 0x00  ); // TAPE1 (0xB2 - 0xB3)
  cpu_->setByte(0xB4, 0x00  ); // BITTS
  cpu_->setByte(0xB5, 0x00  ); // NXTBIT
  cpu_->setByte(0xB6, 0x00  ); // RODATA
  cpu_->setByte(0xB7, 0x00  ); // FNLEN
  cpu_->setByte(0xB8, 0x00  ); // LA
  cpu_->setByte(0xB9, 0x00  ); // SA
  cpu_->setByte(0xBA, 0x00  ); // FA
  cpu_->setByte(0xBB, 0x00  ); // FNADR (0xBB - 0xBC)
  cpu_->setByte(0xBD, 0x00  ); // ROPRTY
  cpu_->setByte(0xBE, 0x00  ); // FSBLK
  cpu_->setByte(0xBF, 0x00  ); // MYCH
  cpu_->setByte(0xC0, 0x00  ); // CAS1
  cpu_->setByte(0xC1, 0x00  ); // STAL (0xC1 - 0xC2)
  cpu_->setByte(0xC5, 0x00  ); // LSTX
  cpu_->setByte(0xC6, 0x00  ); // NDX
  cpu_->setByte(0xC7, 0x00  ); // RVS
  cpu_->setByte(0xC8, 0x00  ); // INDX
  cpu_->setByte(0xC9, 0x00  ); // LXSP (0xCA - 0xCA)
  cpu_->setByte(0xCB, 0x00  ); // SFDX
  cpu_->setByte(0xCC, 0x00  ); // BLNSW
  cpu_->setByte(0xCD, 0x00  ); // BLNCT
  cpu_->setByte(0xCE, 0x00  ); // GDBLN
  cpu_->setByte(0xCF, 0x00  ); // BLNON
  cpu_->setByte(0xD0, 0x00  ); // CRSW
  cpu_->setByte(0xD1, 0x00  ); // PNT (0xD1 - 0xD2)
  cpu_->setByte(0xD3, 0x00  ); // PNTR
  cpu_->setByte(0xD4, 0x00  ); // QTSW
  cpu_->setByte(0xD5, 0x00  ); // LNMX
  cpu_->setByte(0xD6, 0x00  ); // TBLX
  cpu_->setByte(0xD7, 0x00  );
  cpu_->setByte(0xD8, 0x00  ); // INSRT
  cpu_->setByte(0xD9, 0x00  ); // LDTB1 (0xD9 - 0xF2)
  cpu_->setByte(0xF3, 0x00  ); // USER (0xF2 - 0xF3)
  cpu_->setByte(0xF5, 0x00  ); // KEYTAB (0xF6 - 0xF7)
  cpu_->setByte(0xF7, 0x00  ); // RIBUF (0xF7 - 0xF8)
  cpu_->setByte(0xF9, 0x00  ); // ROBUF (0xF7 - 0xF8)
  cpu_->setByte(0xFB, 0x00  ); // FREEZP (0xFB - 0xFE)
  cpu_->setByte(0xFF, 0x00  ); // BASZPT

  cpu_->setByte(0x100, 0x00); // Stack Area (0x100 - 0x1FF)

  // VIC-II chip registers (47 of 64)
  cpu_->setByte(0xD000, 0x00); // Spite Pos (0xD000 - 0xD010)
  cpu_->setByte(0xD011, 0x9B); // SCROLY (high bit of raster compare, 25 row)
  cpu_->setByte(0xD012, 0x00); // RASTER
  cpu_->setByte(0xD013, 0x00); // LPENX
  cpu_->setByte(0xD014, 0x00); // LPENY
  cpu_->setByte(0xD015, 0x00); // SPENA
  cpu_->setByte(0xD016, 0x08); // SCROLX
  cpu_->setByte(0xD017, 0x00); // YXPAND
  cpu_->setByte(0xD018, 0x44); // VMCSB
  cpu_->setByte(0xD019, 0x15); // VICIRQ
  cpu_->setByte(0xD01A, 0x00); // IRQMASK
  cpu_->setByte(0xD01B, 0x00); // SPBGPR
  cpu_->setByte(0xD01C, 0x00); // SPMC
  cpu_->setByte(0xD01D, 0x00); // XXPAND
  cpu_->setByte(0xD01E, 0x00); // SPSPCL
  cpu_->setByte(0xD01F, 0x00); // SPBGCL
  cpu_->setByte(0xD020, 0x0E); // EXTCOL
  cpu_->setByte(0xD021, 0x06); // BGCOL0
  cpu_->setByte(0xD022, 0x01); // BGCOL1
  cpu_->setByte(0xD023, 0x02); // BGCOL2
  cpu_->setByte(0xD024, 0x03); // BGCOL3
  cpu_->setByte(0xD025, 0x00); // SPMC0
  cpu_->setByte(0xD025, 0x00); // SPMC0
  cpu_->setByte(0xD027, 0x01); // SP0COL
  cpu_->setByte(0xD028, 0x02); // SP1COL
  cpu_->setByte(0xD029, 0x03); // SP2COL
  cpu_->setByte(0xD02A, 0x04); // SP3COL
  cpu_->setByte(0xD02B, 0x05); // SP4COL
  cpu_->setByte(0xD02C, 0x06); // SP5COL
  cpu_->setByte(0xD02D, 0x07); // SP6COL
  cpu_->setByte(0xD02E, 0x0C); // SP7COL
  cpu_->setByte(0xD02F, 0x00); // Location Range: (0xD02F - 0xD03F)

  // Sound Interface Device (SID) Registers
  cpu_->setByte(0xD040, 0x00); // // (0xD400 - 0xD41C)

  cpu_->setByte(0xD419, 0x00); // POTX
  cpu_->setByte(0xD41A, 0x00); // POTY
  cpu_->setByte(0xD41B, 0x00); // RANDOM

  cpu_->setByte(0xD800, 0x0); // Color RAM (0xD800 - 0xDBFF) (Fixed)
}

void
C64::
drawScreen()
{
  // 25 Lines by 40 Columns

  uchar SCROLY = cpu_->getByte(0xD011); // SCROLY
  uchar SCROLX = cpu_->getByte(0xD016); // SCROLX

  bool vscroll = (SCROLY & 0x07);
  bool hscroll = (SCROLX & 0x07);

  uchar ny = (SCROLY & 0x08 ? 25 : 24);
  uchar nx = (SCROLX & 0x08 ? 40 : 38);

  bool noblank        = (SCROLY & 0x10);
  bool bitmapGraphics = (SCROLY & 0x20);
  bool extendedColor  = (SCROLY & 0x40);
  bool multicolor     = (SCROLX & 0x10);
  bool videoReset     = (SCROLX & 0x20);

  uchar VMCSB = cpu_->getByte(0xD018); // VMCSB

  uchar textCharDotOffset = (VMCSB & 0x0E) >> 1;
  uchar videoMatrixBase   = (VMCSB & 0xF0) >> 4;

  uchar IRQMASK = cpu_->getByte(0xD01A); // IRQMASK

  // IRQ addr at 0x314
  bool rasterCompareIRQ   = (IRQMASK & 0x01);
  bool spriteCollisionIRQ = (IRQMASK & 0x02);
  bool spriteSpriteIRQ    = (IRQMASK & 0x04);
  bool lightPenIRQ        = (IRQMASK & 0x08);

  ushort textCharDotData = textCharDotOffset*0x0400;

  ushort addr1 = textCharDotData;

  if (! bitmapGraphics) {
    int i = 0;

    for (int y = 0; y < ny; ++y) {
      for (int x = 0; x < nx; ++x, ++i, ++addr1) {
        drawChar(x, y, i, cpu_->getByte(addr1));
      }
    }
  }
  else {
  }

  uchar SPENA  = cpu_->getByte(0xD015);
  uchar YXPAND = cpu_->getByte(0xD017);
  uchar SPBGPR = cpu_->getByte(0xD01B);
  uchar SPMC   = cpu_->getByte(0xD01C);
  uchar XXPAND = cpu_->getByte(0xD01D);

  ushort addr2 = addr1 + 0x3F8;

  for (int s = 0; s < 8; ++s, ++addr2) {
    if (SPENA & (1 << s)) {
      bool doubleHeight = (YXPAND & (1 << s));
      bool behind       = (SPBGPR & (1 << s));
      bool multicolor   = (SPMC   & (1 << s));
      bool doubleWidth  = (XXPAND & (1 << s));

      ushort saddr = 64*cpu_->getByte(addr2);

      drawSprite(s, saddr, doubleHeight);
    }
  }
}

void
C64::
drawChar(int x, int y, int i, uchar c)
{
  uchar  color    = cpu_->getWord(0xD800 + i) & 0x0F;
  ushort charRom  = cpu_->getWord(0xC000 + i*32);
//ushort charRom  = characters_data[i*32];

  for (int cy = 0; cy < 16; ++cy, ++y) {
    for (int cx = 0; cx < 2; ++cx, ++charRom) {
      ushort c1 = cpu_->getByte(charRom + c);

      for (int i = 0; i < 8; ++i) {
        bool b = (c1 & (1 << i));

        if (b)
          drawPixel(x, y);
      }
    }
  }
}

void
C64::
drawSprite(int s, uchar addr, bool doubleHeight)
{
  // Sprite: width=24, height=21

  uchar x = cpu_->getByte(0xD000 + 2*s    );
  uchar y = cpu_->getByte(0xD000 + 2*s + 1);

  ushort epos = cpu_->getByte(0xD010 + s);

  if (epos & (1 << s))
    x += 256;

  assert(x > 0 && y > 0 && (addr + doubleHeight) > 0);
}

void
C64::
drawPixel(int x, int y)
{
  assert(x + y > 0);
}
