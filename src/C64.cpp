#include <C64.h>
#include <C64_6502.h>
#include <C64_VICII.h>

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

// 8K BASIC Interpreter ROM
// 8K Operating System Kernal ROM
// 4K Character Generator ROM
// Sound Interface Device (SID)
// 6566 Video Interface Controller (VIC-II)
// two 6526 Complex Interface adapter chips

C64::
C64()
{
}

void
C64::
init()
{
  if (! cpu_)
    cpu_ = new C64_6502(this);

  if (! gpu_)
    gpu_ = new C64_VICII(this);

  initMemory();

  // call 6502 reset vector
  cpu_->resetSystem();
}

void
C64::
initMemory()
{
  auto cpu = getCPU();

  // BASIC Working Storage (0x00 - 0x8F)

  cpu->setByte(0x00, 0xEF  ); // D6510 (6510 On-Chip I/O DATA Direction Register)
  cpu->setByte(0x01, 0x07  ); // R6510

  cpu->setByte(0x02, 0x00  );

  cpu->setWord(0x03, 0xB1AA); // ADRAY1
  cpu->setWord(0x05, 0xB391); // ADRAY2

  cpu->setByte(0x07, 0x00  ); // CHARAC
  cpu->setByte(0x08, 0x00  ); // ENDCHR
  cpu->setByte(0x09, 0x00  ); // TRMPOS
  cpu->setByte(0x0A, 0x00  ); // VERCK
  cpu->setByte(0x0B, 0x00  ); // COUNT
  cpu->setByte(0x0C, 0x00  ); // DIMFLG
  cpu->setByte(0x0D, 0x00  ); // VALTYP
  cpu->setByte(0x0E, 0x00  ); // INTFLG
  cpu->setByte(0x0F, 0x00  ); // GARBFL
  cpu->setByte(0x10, 0x00  ); // SUBFLG
  cpu->setByte(0x11, 0x00  ); // INPFLG
  cpu->setByte(0x12, 0x00  ); // TANSGN
  cpu->setByte(0x13, 0x00  ); // CHANNL
  cpu->setWord(0x14, 0x0000); // LINNUM
  cpu->setByte(0x16, 0x19  ); // TEMPPT
  cpu->setWord(0x17, 0x0016); // LASTPT
  cpu->setByte(0x19, 0x00  ); // TEMPST (0x19 - 0x21)
  cpu->setByte(0x22, 0x00  ); // INDEX (0x22 - 0x25)
  cpu->setByte(0x26, 0x00  ); // RESHO (0x26 - 0x2A)
  cpu->setWord(0x2B, 0x0801); // TXTTAB
  cpu->setWord(0x2D, 0x0000); // VARTAB
  cpu->setWord(0x2F, 0x0000); // ARYTAB
  cpu->setWord(0x31, 0x0000); // STREND
  cpu->setWord(0x33, 0xFFFF); // FREETOP
  cpu->setWord(0x35, 0x0000); // FRESPC
  cpu->setWord(0x37, 0x9FFF); // MEMSIZ
  cpu->setWord(0x39, 0x0000); // CURLIN
  cpu->setWord(0x3B, 0x0000); // OLDLIN
  cpu->setWord(0x3D, 0x0000); // OLDTXT
  cpu->setWord(0x3F, 0x0000); // DATLIN
  cpu->setWord(0x41, 0x0000); // DATPTR
  cpu->setWord(0x43, 0x0000); // INPPTR
  cpu->setWord(0x45, 0x0000); // VARNAM
  cpu->setWord(0x47, 0x0000); // VARPNT
  cpu->setWord(0x49, 0x0000); // FORPNT
  cpu->setWord(0x4B, 0x0000); // OPPTR
  cpu->setByte(0x4D, 0x00  ); // OPMASK
  cpu->setWord(0x4E, 0x0000); // DEFPNT
  cpu->setByte(0x50, 0x00  ); // DSCPNT (0x50 - 0x52)
  cpu->setByte(0x53, 0x00  ); // FOUR6
  cpu->setByte(0x54, 0x4C  ); // JMPER (0x54 - 0x56)
  cpu->setWord(0x55, 0x0000); //
  cpu->setByte(0x57, 0x00  ); //       (0x57 - 0x60)
  cpu->setByte(0x61, 0x00  ); // FAC1 (0x61 - 0x66)
  cpu->setByte(0x67, 0x00  ); // SGNFLG
  cpu->setByte(0x68, 0x00  ); // BITS
  cpu->setByte(0x69, 0x00  ); // FAC2 (0x69 - 0x6E) ARGEXP, ARGHO, ARGSGN
  cpu->setByte(0x6F, 0x00  ); // ARISGN
  cpu->setByte(0x70, 0x00  ); // FACOV
  cpu->setWord(0x71, 0x0000); // FBUFPT

  cpu->setByte(0x73, 0x00  ); // CHRGET (0x73 - 0x8A) Copied from 0xE3A2
  cpu->setByte(0x79, 0x00  ); // CHRGOT

//cpu->memset(0x73, &kernel_data[0x3A2], 0x17);

  cpu->setByte(0x8B, 0x80  ); // RNDX (0x8B - 0x8F)
  cpu->setByte(0x8C, 0x4F  );
  cpu->setByte(0x8D, 0xC7  );
  cpu->setByte(0x8E, 0x52  );
  cpu->setByte(0x8F, 0x58  );

  cpu->setByte(0x90, 0x00  ); // STATUS
  cpu->setByte(0x91, 0x00  ); // STKEY
  cpu->setByte(0x92, 0x00  ); // SVXT
  cpu->setByte(0x93, 0x00  ); // VERCK
  cpu->setByte(0x94, 0x00  ); // C3PO
  cpu->setByte(0x95, 0x00  ); // BSOUR
  cpu->setByte(0x96, 0x00  ); // SYNO
  cpu->setByte(0x97, 0x00  ); // XSAV
  cpu->setByte(0x98, 0x00  ); // LDTND
  cpu->setByte(0x99, 0x00  ); // DFLTN (Default Input : 0 Keyboard)
  cpu->setByte(0x9A, 0x03  ); // DFLTO (Default Output : 3 Screen)
  cpu->setByte(0x9B, 0x00  ); // PRTY
  cpu->setByte(0x9C, 0x00  ); // DPSW
  cpu->setByte(0x9D, 0x00  ); // MSGFLG
  cpu->setByte(0x9E, 0x00  ); // PTR1
  cpu->setByte(0x9F, 0x00  ); // PTR2
  cpu->setByte(0xA0, 0x00  ); // TIME (0xA0 - 0xA2)
  cpu->setByte(0xA3, 0x00  ); //      (0xA3 - 0xA4)
  cpu->setByte(0xA5, 0x00  ); // CNTDN
  cpu->setByte(0xA6, 0x00  ); // BUFPNT
  cpu->setByte(0xA7, 0x00  ); // INBIT
  cpu->setByte(0xA8, 0x00  ); // BITCI
  cpu->setByte(0xA9, 0x00  ); // RINONE
  cpu->setByte(0xAA, 0x00  ); // RIDATA
  cpu->setByte(0xAB, 0x00  ); // RIPRTY
  cpu->setByte(0xAC, 0x00  ); // SAL (0xAC - 0xAD)
  cpu->setByte(0xAE, 0x00  ); // EAL (0xAE - 0xAF)
  cpu->setByte(0xB0, 0x00  ); // CMP0 (0xB0 - 0xB1)
  cpu->setByte(0xB2, 0x00  ); // TAPE1 (0xB2 - 0xB3)
  cpu->setByte(0xB4, 0x00  ); // BITTS
  cpu->setByte(0xB5, 0x00  ); // NXTBIT
  cpu->setByte(0xB6, 0x00  ); // RODATA
  cpu->setByte(0xB7, 0x00  ); // FNLEN
  cpu->setByte(0xB8, 0x00  ); // LA
  cpu->setByte(0xB9, 0x00  ); // SA
  cpu->setByte(0xBA, 0x00  ); // FA (Current Device Number)
  cpu->setByte(0xBB, 0x00  ); // FNADR (0xBB - 0xBC)
  cpu->setByte(0xBD, 0x00  ); // ROPRTY
  cpu->setByte(0xBE, 0x00  ); // FSBLK
  cpu->setByte(0xBF, 0x00  ); // MYCH
  cpu->setByte(0xC0, 0x00  ); // CAS1
  cpu->setByte(0xC1, 0x00  ); // STAL (0xC1 - 0xC2)
  cpu->setByte(0xC5, 0x00  ); // LSTX
  cpu->setByte(0xC6, 0x00  ); // NDX
  cpu->setByte(0xC7, 0x00  ); // RVS
  cpu->setByte(0xC8, 0x00  ); // INDX
  cpu->setByte(0xC9, 0x00  ); // LXSP (0xCA - 0xCA)
  cpu->setByte(0xCB, 0x00  ); // SFDX
  cpu->setByte(0xCC, 0x00  ); // BLNSW
  cpu->setByte(0xCD, 0x00  ); // BLNCT
  cpu->setByte(0xCE, 0x00  ); // GDBLN
  cpu->setByte(0xCF, 0x00  ); // BLNON
  cpu->setByte(0xD0, 0x00  ); // CRSW
  cpu->setByte(0xD1, 0x00  ); // PNT (0xD1 - 0xD2)
  cpu->setByte(0xD3, 0x00  ); // PNTR
  cpu->setByte(0xD4, 0x00  ); // QTSW
  cpu->setByte(0xD5, 0x00  ); // LNMX
  cpu->setByte(0xD6, 0x00  ); // TBLX
  cpu->setByte(0xD7, 0x00  );
  cpu->setByte(0xD8, 0x00  ); // INSRT
  cpu->setByte(0xD9, 0x00  ); // LDTB1 (0xD9 - 0xF2)
  cpu->setByte(0xF3, 0x00  ); // USER (0xF2 - 0xF3)
  cpu->setByte(0xF5, 0x00  ); // KEYTAB (0xF6 - 0xF7)
  cpu->setByte(0xF7, 0x00  ); // RIBUF (0xF7 - 0xF8)
  cpu->setByte(0xF9, 0x00  ); // ROBUF (0xF7 - 0xF8)
  cpu->setByte(0xFB, 0x00  ); // FREEZP (0xFB - 0xFE)
  cpu->setByte(0xFF, 0x00  ); // BASZPT

  cpu->setByte(0x100, 0x00); // Stack Area (0x100 - 0x1FF)

  cpu->setByte(0x200, 0x00); // BASIC Line Editor Input Buffer (0x200 - 0x258)
  cpu->setByte(0x259, 0x00); // Location Range: (0x259 - 0x276)
  cpu->setByte(0x277, 0x00); // Keyboard Buffer : (0x277 - 0x280)

  cpu->setWord(0x281, 0x0000); // MEMSTR Start of Memory (startup 0x800)
  cpu->setWord(0x283, 0x0000); // MEMSIZ End of Memory

  cpu->setByte(0x285, 0x00); // TIMOUT
  cpu->setByte(0x286, 0x00); // COLOR
  cpu->setByte(0x287, 0x00); // GDCOL
  cpu->setByte(0x288, 0x00); // HIBASE
  cpu->setByte(0x289, 0x00); // XMAX
  cpu->setByte(0x28A, 0x00); // RPTFLAG
  cpu->setByte(0x28B, 0x06); // KOUNT
  cpu->setByte(0x28C, 0x00); // DELAY
  cpu->setByte(0x28D, 0x00); // SHFLAG
  cpu->setByte(0x28E, 0x00); // LSTSHF
  cpu->setByte(0x28F, 0x00); // KEYLOG (0x28F - 0x290)
  cpu->setByte(0x291, 0x00); // MODE
  cpu->setByte(0x292, 0x06); // AUTODN

  // RS-232 Pseudo 6551 Registers (0x293 - 0x297)
  cpu->setByte(0x293, 0x00); // M51CTR
  cpu->setByte(0x294, 0x00); // M51CDR
  cpu->setByte(0x295, 0x00); // M51AJB
  cpu->setByte(0x297, 0x00); // $RSSTAT

  cpu->setByte(0x298, 0x00); // BITNUM
  cpu->setByte(0x299, 0x00); // BAUDOF
  cpu->setByte(0x29B, 0x00); // RIDBE
  cpu->setByte(0x29C, 0x00); // RIDBS
  cpu->setByte(0x29D, 0x00); // RODBS
  cpu->setByte(0x29E, 0x00); // RODBE
  cpu->setByte(0x29F, 0x00); // IRQTMP
  cpu->setByte(0x2A1, 0x00); // ENABL
  cpu->setByte(0x2A2, 0x00); //
  cpu->setByte(0x2A3, 0x00); //
  cpu->setByte(0x2A4, 0x00); //
  cpu->setByte(0x2A5, 0x00); //
  cpu->setByte(0x2A6, 0x00); // (PAL/NTSC Flag)

  // BASIC Indirect Vector Table (0x300 - 0x30B)
  cpu->setWord(0x300, 0xE38B); // IERROR
  cpu->setWord(0x302, 0xA483); // IMAIN
  cpu->setWord(0x304, 0xA57C); // ICRNCH
  cpu->setWord(0x306, 0xA71A); // IQPLOP
  cpu->setWord(0x308, 0xA7E4); // IGONE
  cpu->setWord(0x30A, 0xAE86); // IEVAL

  // Register Storage Area
  cpu->setByte(0x30C, 0x00); // SAREG
  cpu->setByte(0x30D, 0x00); // SXREG
  cpu->setByte(0x30E, 0x00); // SYREG
  cpu->setByte(0x30F, 0x00); // SPREG

  cpu->setByte(0x310, 0x4C);   // USRPOK
  cpu->setWord(0x311, 0xB248); // USRADD

  cpu->setWord(0x314, 0xFA31); // CINV
  cpu->setWord(0x316, 0xFE66); // CBINV
  cpu->setWord(0x318, 0xFE47); // NMINV

  // Kernal Indirect Vectors
  cpu->setWord(0x31A, 0xF34A); // IOPEN
  cpu->setWord(0x31C, 0xF291); // ICLOSE
  cpu->setWord(0x31E, 0xF20E); // ICHKIN
  cpu->setWord(0x320, 0xF250); // ICKOUT
  cpu->setWord(0x322, 0xF333); // ICLRCH
  cpu->setWord(0x324, 0xF157); // IBASIN
  cpu->setWord(0x326, 0xF1CA); // IBSOUT
  cpu->setWord(0x328, 0xF6ED); // ISTOP
  cpu->setWord(0x32A, 0xF13E); // IGETIN
  cpu->setWord(0x32C, 0xF32F); // ICLALL
  cpu->setWord(0x32E, 0xFE66); // USRCMD
  cpu->setWord(0x330, 0xF49E); // ILOAD
  cpu->setWord(0x332, 0xF5DD); // ISAVE
  cpu->setWord(0x334, 0x0000); // (Unused)

  cpu->setByte(0x33C, 0x00); // TBUFFER (0x33C - 0x3FB)
  cpu->setByte(0x3FC, 0x00); // (Unused 0x3FC - 0x3FF)

  // Video Screen Memory Area
  cpu->setByte(0x400, 0x00); // VICSCN (0x400 - 0x7FF)

  // Sprite Shape Data Pointers
  cpu->setByte(0x7F8, 0x00); // (0x7F8 - 0x7FF)

  // BASIC Program Text
  cpu->setByte(0x800, 0x00); // (0x800 - 0x9FFF)

  // Character ROM Image for VIC-II Chip When Using Memory Bank 0 (Default)
  cpu->setByte(0x1000, 0x00); // (0x1000 - 0x1FFF)

  // Autostart ROM Cartridge (8K or 16K)
  cpu->setByte(0x8000, 0x00); // (0x8000)

  // Character ROM Image for VIC-II Chip When Using Memory Bank 2
  cpu->setByte(0x9000, 0x00); // (0x9000 - 0x9FFF)

  //---

  // BASIC Registers (0xA000 - 0xBFFF) (initialized from ROM)

  //---

  // 4K Free RAM
  cpu->setByte(0xC000, 0x00); // (0xC000 - 0xCFFF)

  //---

  // Sound Interface Device (SID) Registers (0xD400 - 0xD41C)
  // TODO: every 64 byte area in this 1K block is a mirror of every other
  cpu->setByte(0xD400, 0x00); // FRELO1
  cpu->setByte(0xD401, 0x00); // FREHI1
  cpu->setByte(0xD402, 0x00); // PWLO1
  cpu->setByte(0xD403, 0x00); // PWHI1
  cpu->setByte(0xD404, 0x00); // VCREG1
  cpu->setByte(0xD405, 0x00); // ATDCY1
  cpu->setByte(0xD406, 0x00); // SUREL1
  cpu->setByte(0xD407, 0x00); // FRELO2
  cpu->setByte(0xD408, 0x00); // FREHI2
  cpu->setByte(0xD409, 0x00); // PWLO2
  cpu->setByte(0xD40A, 0x00); // PWHI2
  cpu->setByte(0xD40B, 0x00); // VCREG2
  cpu->setByte(0xD40C, 0x00); // ATDCY2
  cpu->setByte(0xD40D, 0x00); // SUREL2
  cpu->setByte(0xD40E, 0x00); // FRELO3
  cpu->setByte(0xD40F, 0x00); // FREHI3
  cpu->setByte(0xD410, 0x00); // PWLO3
  cpu->setByte(0xD411, 0x00); // PWHI3
  cpu->setByte(0xD412, 0x00); // VCREG3
  cpu->setByte(0xD413, 0x00); // ATDCY3
  cpu->setByte(0xD414, 0x00); // SUREL3
  cpu->setByte(0xD415, 0x00); // CUTLO
  cpu->setByte(0xD416, 0x00); // CUTHI
  cpu->setByte(0xD417, 0x00); // RESON
  cpu->setByte(0xD418, 0x00); // SIGVOL

  cpu->setByte(0xD419, 0x00); // POTX
  cpu->setByte(0xD41A, 0x00); // POTY
  cpu->setByte(0xD41B, 0x00); // RANDOM

  cpu->setByte(0xD41C, 0x00); // ENV3

  // TODO Read always 0xFF
  cpu->setByte(0xD41D, 0x00); // (0xD41D - 0xD41F) (Not used)

  cpu->setByte(0xD420, 0x00); // (0xD420 - 0xD7FF) (Not used ?)

  cpu->setByte(0xD800, 0x00); // Color RAM (0xD800 - 0xDBFF) (Not movable)

  // TODO: more to do here
  cpu->setByte(0xDC00, 0xFF); // CIAPRA (DATA PORT REGISTER A)
  cpu->setByte(0xDC01, 0x00); // CIAPRB (DATA PORT REGISTER B)
  cpu->setByte(0xDC02, 0xFF); // CIDDRA (DATA DIRECTION REGISTER A)
  cpu->setByte(0xDC03, 0x00); // CIDDRB (DATA DIRECTION REGISTER B)

  cpu->setWord(0xDC04, 0x4295); // TIMALO/TIMAHI (Timer A Low/High)
  cpu->setWord(0xDC06, 0x0000); // TIMBLO/TIMBHI (Timer B Low/High)

  // Time of Day Clock (TOD) (0xDC08 - 0xDC0B)
  // TODO: implement
  cpu->setByte(0xDC08, 0x00); // TODTEN
  cpu->setByte(0xDC09, 0x00); // TODSEC
  cpu->setByte(0xDC0A, 0x00); // TODMIN
  cpu->setByte(0xDC0B, 0x00); // TODHRS

  cpu->setByte(0xDC0C, 0x00); // CIASDR
  cpu->setByte(0xDC0D, 0x00); // CIAICR
  cpu->setByte(0xDC0E, 0x00); // CIACRA
  cpu->setByte(0xDC0F, 0x00); // CIACRB

  // TODO: every 16-byte area in this 256-byte block is a mirror of every other
  cpu->setByte(0xDC10, 0x00); // CIA #1 Register Images (0xDC10 - 0xDCFF)

  cpu->setByte(0xDD00, 0x00); // CI2PRA (TODO: handling of video memory)
  cpu->setByte(0xDD01, 0x00); // CI2PRB
  cpu->setByte(0xDD02, 0x00); // C2DDRA
  cpu->setByte(0xDD03, 0x00); // C2DDRB
  cpu->setByte(0xDD04, 0x00); // TI2ALO
  cpu->setByte(0xDD05, 0x00); // TI2AHI
  cpu->setByte(0xDD06, 0x00); // TI2BLO
  cpu->setByte(0xDD07, 0x00); // TI2BHI
  cpu->setByte(0xDD08, 0x00); // TO2TEN
  cpu->setByte(0xDD09, 0x00); // TO2SEC
  cpu->setByte(0xDD0A, 0x00); // TO2MIN
  cpu->setByte(0xDD0B, 0x00); // TO2HRS
  cpu->setByte(0xDD0C, 0x00); // CI2SDR
  cpu->setByte(0xDD0D, 0x00); // CI2ICR
  cpu->setByte(0xDD0E, 0x00); // CI2CRA
  cpu->setByte(0xDD0F, 0x00); // CI2CRB

  // TODO: every 16-byte area in this 256-byte block is a mirror of every other
  cpu->setByte(0xDD10, 0x00); // CIA #2 Register Images (0xDD10 - 0xDDFF)

  cpu->setByte(0xDE00, 0x00); // (0xDE00 - 0xDEFF) Reserved for I/O Expansion

  cpu->setByte(0xDF00, 0x00); // (0xDF00 - 0xDFFF) CIA #2 Register Images

  //---

  // 8K Operating System Kernal ROM
  cpu->setByte(0xE000, 0x00); // Continuation of EXP Routine

  cpu->setByte(0xE043, 0x00); // POLY1
  cpu->setByte(0xE059, 0x00); // POLY2
  cpu->setByte(0xE08D, 0x00); // RMULC
  cpu->setByte(0xE092, 0x00); // RADDC
  cpu->setByte(0xE097, 0x00); // RND

  cpu->setByte(0xE0F9, 0x00); // Call Kernal I/O Routines

  cpu->setByte(0xE12A, 0x00); // SYS
  cpu->setByte(0xE156, 0x00); // SAVE
  cpu->setByte(0xE165, 0x00); // VERIFY
  cpu->setByte(0xE168, 0x00); // LOAD
  cpu->setByte(0xE1BE, 0x00); // OPEN
  cpu->setByte(0xE1C7, 0x00); // CLOSE
  cpu->setByte(0xE1D4, 0x00); // Set Parameters for LOAD, VERIFY, and SAVE
  cpu->setByte(0xE200, 0x00); // Skip Comma and Get Integer in .
  cpu->setByte(0xE206, 0x00); // Fetch Current Character and Check for End of Line
  cpu->setByte(0xE20E, 0x00); // Check for Comma
  cpu->setByte(0xE219, 0x00); // Set Parameters for OPEN and CLOSE
  cpu->setByte(0xE264, 0x00); // COS
  cpu->setByte(0xE268, 0x00); // SIN
  cpu->setByte(0xE2B4, 0x00); // TAN
  cpu->setByte(0xE2E0, 0x00); // PI2
  cpu->setByte(0xE2E5, 0x00); // TWOPI
  cpu->setByte(0xE2EA, 0x00); // FR4
  cpu->setByte(0xE2EF, 0x00); // SINCON
  cpu->setByte(0xE30E, 0x00); // ATN
  cpu->setByte(0xE33E, 0x00); // ATNCON

  cpu->setByte(0xE37B, 0x00); // Warm Start BASIC
  cpu->setByte(0xE38B, 0x00); // Error Message Handler
  cpu->setByte(0xE394, 0x00); // Cold Start BASIC
  cpu->setByte(0xE3A2, 0x00); // INITAT
  cpu->setByte(0xE3BA, 0x00); // Initial RND Seed Value
  cpu->setByte(0xE3BF, 0x00); // INIT
  cpu->setByte(0xE422, 0x00); // Print BASIC Start-Up Messages
  cpu->setByte(0xE447, 0x00); // Table of Vectors to Important BASIC Routines
  cpu->setByte(0xE453, 0x00); // Copy BASIC Vectors to RAM
  cpu->setByte(0xE460, 0x00); // WORDS

  cpu->setByte(0xE4AD, 0x00); // Patch for BASIC Call of CHKOUT
  cpu->setByte(0xE4B7, 0x00); // 35 Unused (0xAA)
  cpu->setByte(0xE4DA, 0x00); // Clear Color RAM to the Color in Background Color Register 0
  cpu->setByte(0xE4E0, 0x00); // Pause after Finding a File on Cassette
  cpu->setByte(0xE4EC, 0x00); // Baud Rate Table for European (PAL) Standard Monitors
  cpu->setByte(0xE500, 0x00); // IOBASE
  cpu->setByte(0xE505, 0x00); // SCREEN
  cpu->setByte(0xE50A, 0x00); // PLOT
  cpu->setByte(0xE518, 0x00); // Initialize Screen and Keyboard
  cpu->setByte(0xE544, 0x00); // Initialize the Screen Line Link Table and Clear the Scree
  cpu->setByte(0xE566, 0x00); // Home the Cursor
  cpu->setByte(0xE56C, 0x00); // Set Pointer to Current Screen Line
  cpu->setByte(0xE5A0, 0x00); // Set Default I/O Devices and Default VIC-II Chip Registers
  cpu->setByte(0xE5B4, 0x00); // LP2
  cpu->setByte(0xE5CA, 0x00); // Wait for a Carriage Return from the Keyboard
  cpu->setByte(0xE684, 0x00); // Test for Quote Marks
  cpu->setByte(0xE691, 0x00); // Add a Character to the Screen
  cpu->setByte(0xE6A8, 0x00); // Return from Outputting a Character to the Screen
  cpu->setByte(0xE6B6, 0x00); // Advance the Cursor
  cpu->setByte(0xE701, 0x00); // Move Cursor Back over a 40-Column Line Boundary
  cpu->setByte(0xE716, 0x00); // Output to the Screen
  cpu->setByte(0xE87C, 0x00); // Move Cursor to Next Line
  cpu->setByte(0xE891, 0x00); // Output a Carriage Return
  cpu->setByte(0xE8A1, 0x00); // If at the Beginning of a Screen Line, Move Cursor to Previous Line
  cpu->setByte(0xE8B3, 0x00); // If at the End of a Screen Line, Move Cursor to the Next Line
  cpu->setByte(0xE8CB, 0x00); // Check for a Color Change
  cpu->setByte(0xE8D1, 0x00); // PETASCII Color Code Equivalent Table
  cpu->setByte(0xE8EA, 0x00); // Scroll Screen
  cpu->setByte(0xE965, 0x00); // Insert a Blank Line on the Screen
  cpu->setByte(0xE9C8, 0x00); // Move Screen Line
  cpu->setByte(0xE9E0, 0x00); // Set Temporary Color Pointer for Scrolling
  cpu->setByte(0xE9F0, 0x00); // Set Pointer to Screen Address of Start of Line
  cpu->setByte(0xE9FF, 0x00); // Clear Screen Line
  cpu->setByte(0xEA13, 0x00); // Set Cursor Blink Timing and Color Memory Addr for Print Screen
  cpu->setByte(0xEA1C, 0x00); // Store to Screen
  cpu->setByte(0xEA24, 0x00); // Synchronize Color RAM Pointer to Screen Line Pointer
  cpu->setByte(0xEA31, 0x00); // IRQ Interrupt Entry
  cpu->setByte(0xEA87, 0x00); // SCNKEY
  cpu->setByte(0xEAE0, 0x00); // Decode the Keystroke and Place ASCII Value in Keyboard Buffer
  cpu->setByte(0xEB48, 0x00); // Set Up the Proper Keyboard Decode Table
  cpu->setByte(0xEB79, 0x00); // Keyboard Decode Table Vectors
  cpu->setByte(0xEB81, 0x00); // Standard Keyboard Matrix Decode Table
  cpu->setByte(0xEBC2, 0x00); // SHIFTed Keyboard Matrix Decode Table
  cpu->setByte(0xEC03, 0x00); // Commodore Logo Keyboard Matrix Decode Table
  cpu->setByte(0xEC44, 0x00); // Set Lowercase/Uppercase or Uppercase/Graphics Character Set
  cpu->setByte(0xEC5E, 0x00); // Set Flag to Enable or Disable Switching Character Sets
  cpu->setByte(0xEC78, 0x00); // Control Keyboard Matrix Decode Table
  cpu->setByte(0xECB9, 0x00); // Video Chip Register Default Table
  cpu->setByte(0xECE7, 0x00); // Text for Keyboard Buffer When SHIFT/RUN is Pressed
  cpu->setByte(0xECF0, 0x00); // Low Byte Table of Screen Line Addresses
  cpu->setByte(0xED09, 0x00); // TALK
  cpu->setByte(0xED0C, 0x00); // LISTEN
  cpu->setByte(0xED11, 0x00); // Send Command Code to a Device on the Serial Bus
  cpu->setByte(0xED40, 0x00); // Send a Byte on the Serial Bus
  cpu->setByte(0xEDB0, 0x00); // Time-Out Error on Serial Bus
  cpu->setByte(0xEDB9, 0x00); // SECOND
  cpu->setByte(0xEDC7, 0x00); // TKSA
  cpu->setByte(0xEDDD, 0x00); // CIOUT
  cpu->setByte(0xEDEF, 0x00); // UNTLK
  cpu->setByte(0xEDFE, 0x00); // UNLSN
  cpu->setByte(0xEE13, 0x00); // ACPTR
  cpu->setByte(0xEE85, 0x00); // Set the Serial Clock Line Low (Active)
  cpu->setByte(0xEE8E, 0x00); // Set the Serial Clock Line High (Inactive)
  cpu->setByte(0xEE97, 0x00); // Set Serial Bus Data Output Line Low
  cpu->setByte(0xEEA9, 0x00); // Get Serial Bus Data Input Bit and Clock Pulse Input Bit
  cpu->setByte(0xEEB3, 0x00); // Perform a One-Millisecond Delay

  cpu->setByte(0xEEBB, 0x00); // Send Next RS-232 Bit (NMI)
  cpu->setByte(0xEF2E, 0x00); // Handle RS-232 Errors
  cpu->setByte(0xEF4A, 0x00); // Set the Word Length For the Current RS-232 Character
  cpu->setByte(0xEF59, 0x00); // Receive Next RS-232 Bit (NMI)
  cpu->setByte(0xEF7E, 0x00); // Setup to Receive a New Byte from RS-232
  cpu->setByte(0xEF90, 0x00); // Test If Start Bit Received from RS-232
  cpu->setByte(0xEF97, 0x00); // Put a Byte of Received Data into RS-232 Receive Buffer
  cpu->setByte(0xEFE1, 0x00); // CHKOUT for the RS-232 device
  cpu->setByte(0xF014, 0x00); // CHROUT for the RS-232 Device
  cpu->setByte(0xF04D, 0x00); // CHKIN for the RS-232 Device
  cpu->setByte(0xF086, 0x00); // GETIN for the RS-232 Device
  cpu->setByte(0xF0A4, 0x00); // Stop CIA #2 RS-232 NMIs for Serial/Cassette Routines
  cpu->setByte(0xF0BD, 0x00); // Kernal Control Messages
  cpu->setByte(0xF12B, 0x00); // Print Kernal Error Message if in Direct Mode
  cpu->setByte(0xF13E, 0x00); // GETIN
  cpu->setByte(0xF157, 0x00); // CHRIN
  cpu->setByte(0xF1CA, 0x00); // CHROUT
  cpu->setByte(0xF20E, 0x00); // CHKIN
  cpu->setByte(0xF250, 0x00); // CHKOUT
  cpu->setByte(0xF291, 0x00); // CLOSE
  cpu->setByte(0xF30F, 0x00); // Find the File in the Logical File Table
  cpu->setByte(0xF31F, 0x00); // Set Current Logical File, Device, and Seconday Address
  cpu->setByte(0xF32F, 0x00); // CLALL
  cpu->setByte(0xF333, 0x00); // CLRCHN
  cpu->setByte(0xF34A, 0x00); // OPEN
  cpu->setByte(0xF49E, 0x00); // LOAD
  cpu->setByte(0xF5A5, 0x00); // Print SEARCHING Message if in Direct Mode
  cpu->setByte(0xF5D2, 0x00); // Print LOADING or VERIFYING
  cpu->setByte(0xF5DD, 0x00); // SAVE
  cpu->setByte(0xF68F, 0x00); // If in Direct Mode, Print SAVING and Filename
  cpu->setByte(0xF69B, 0x00); // UDTIM
  cpu->setByte(0xF6DD, 0x00); // RDTIM
  cpu->setByte(0xF6E4, 0x00); // SETTIM
  cpu->setByte(0xF6ED, 0x00); // STOP
  cpu->setByte(0xF6FB, 0x00); // Set Kernal I/O Error Messages
  cpu->setByte(0xF72C, 0x00); // Get Next Tape File Header from Cassette
  cpu->setByte(0xF76A, 0x00); // Write Tape File Header Block
  cpu->setByte(0xF7D0, 0x00); // Put Pointer to Tape Buffer in .X and .Y Registers
  cpu->setByte(0xF7D7, 0x00); // Set I/O Area Start and End Pointers to Tape Buffer Address
  cpu->setByte(0xF7EA, 0x00); // Search Tape for a Filename
  cpu->setByte(0xF817, 0x00); // Test Cassette Buttons and Handle Messages for Tape Read
  cpu->setByte(0xF82E, 0x00); // Check Cassette Switch
  cpu->setByte(0xF838, 0x00); // Test Cassette Buttons and Handle Messages for Tape Write
  cpu->setByte(0xF841, 0x00); // Start Reading a Block of Data from the Cassette
  cpu->setByte(0xF864, 0x00); // Start Writing a Block of Data to the Cassette
  cpu->setByte(0xF875, 0x00); // Common Code for Reading and Writing a Data Block from/to Tape
  cpu->setByte(0xF8D0, 0x00); // Test the STOP Key during Cassette I/O Operations
  cpu->setByte(0xF8E2, 0x00); // Adjust CIA #1 Timer A for Tape Bit Timing
  cpu->setByte(0xF92C, 0x00); // Read Tape Data (IRQ)
  cpu->setByte(0xFA60, 0x00); // Receive and Store the Next Character from Cassette
  cpu->setByte(0xFB8E, 0x00); // Move the Tape SAVE/LOAD Address into the Pointer at 172
  cpu->setByte(0xFB97, 0x00); // Reset Counters for Reading or Writing a New Byte of Cassette Data
  cpu->setByte(0xFBA6, 0x00); // Toggle the Tape Data Output Line
  cpu->setByte(0xFBC8, 0x00); // Write Data to Cassette--Part 2 (IRQ)
  cpu->setByte(0xFC6A, 0x00); // Write Data fo Cassette--Part 1 (IRQ)
  cpu->setByte(0xFC93, 0x00); // Restores the Default IRQ Routine
  cpu->setByte(0xFCB8, 0x00); // Terminate Cassette I/O
  cpu->setByte(0xFCCA, 0x00); // Turn Off the Tape Motor
  cpu->setByte(0xFCD1, 0x00); // Check the Tape Read/Write Pointer
  cpu->setByte(0xFCDB, 0x00); // Advance the Tape Read/Write Pointer
  cpu->setByte(0xFCE2, 0x00); // Power-On Reset Routine
  cpu->setByte(0xFD02, 0x00); // Check for an Autostart Cartridge
  cpu->setByte(0xFD10, 0x00); // Text for Autostart Cartridge Check
  cpu->setByte(0xFD15, 0x00); // RESTOR
  cpu->setByte(0xFD1A, 0x00); // VECTOR
  cpu->setByte(0xFD30, 0x00); // Table of RAM Vectors to the Default I/O Routines
  cpu->setByte(0xFD50, 0x00); // RAMTAS
  cpu->setByte(0xFD9B, 0x00); // Table of IRQ Vectors
  cpu->setByte(0xFDA3, 0x00); // IOINIT
  cpu->setByte(0xFDF9, 0x00); // SETNAM
  cpu->setByte(0xFE00, 0x00); // SETLFS
  cpu->setByte(0xFE07, 0x00); // READST
  cpu->setByte(0xFE18, 0x00); // SETMSG
  cpu->setByte(0xFE21, 0x00); // SETTMO
  cpu->setByte(0xFE25, 0x00); // MEMTOP
  cpu->setByte(0xFE34, 0x00); // MEMBOT
  cpu->setByte(0xFE43, 0x00); // NMI Interrupt Entry Point
  cpu->setByte(0xFE66, 0x00); // BRK, Warm Start Routine
  cpu->setByte(0xFE72, 0x00); // NMI RS-232 Handler
  cpu->setByte(0xFEC2, 0x00); // RS-232 Baud Rate Tables for U.S. Television Standard (NTSC)
  cpu->setByte(0xFED6, 0x00); // RS-232 Receive the Next Bit (NMI)
  cpu->setByte(0xFF1A, 0x00); // Load Timer with Prescaler Values from the Baud Rate Lookup Table
  cpu->setByte(0xFF48, 0x00); // Main IRQ/BRK Interrupt Entry Point
  cpu->setByte(0xFF5B, 0x00); // CINT
  cpu->setByte(0xFF6E, 0x00); // End of Routine to Set Timer for Sixtieth of a Second IRQ
  cpu->setByte(0xFF80, 0x00); // Kernal Version Identifier Byte

  // The following table will give the entry point, routine name, RAM vector if any,
  // its current address, and a brief summary of its function.

  // 0xFF81 CINT   (0xFF5B) initialize screen editor and video chip
  // 0xFF84 IOINIT (0xFDA3) initialize I/O devices
  // 0xFF87 RAMTAS (0xFD50) initialize RAM, tape buffer, screen
  // 0xFF8A RESTOR (0xFD15) restore default I/O vectors
  // 0xFF8D VECTOR (0xFD1A) read/set I/O vector table
  // 0xFF90 SETMSG (0xFE18) set Kernal message control flag
  // 0xFF93 SECOND (0xEDB9) send secondary address after LISTEN
  // 0xFF96 TKSA   (0xEDC7) send secondary address after TALK
  // 0xFF99 MEMTOP (0xFE25) read/set top of memory pointer
  // 0xFF9C MEMBOT (0xFE34) read/set bottom of memory pointer
  // 0xFF9F SCNKEY (0xEA87) scan the keyboard
  // 0xFFA2 SETTMO (0xFE21) set time-out flag for IEEE bus
  // 0xFFA5 ACPTR  (0xFE13) input byte from serial bus
  // 0xFFA8 CIOUT  (0xEDDD) output byte to serial bus
  // 0xFFAB UNTLK  (0xEDEF) command serial bus device to UNTALK
  // 0xFFAE UNLSN  (0xEDFE) command serial bus device to UNLISTEN
  // 0xFFB1 LISTEN (0xED0C) command serial bus device to LISTEN
  // 0xFFB4 TALK   (0xED09) command serial bus device to TALK
  // 0xFFB7 READST (0xFE07) read I/O status word
  // 0xFFBA SETLFS (0xFE00) set logical file parameters
  // 0xFFBD SETNAM (0xFDF9) set filename parameters
  // 0xFFC0 OPEN   (via 794 ($31A) to 62282, $F34A) open a logical file
  // 0xFFC3 CLOSE  (via 796 ($31C) to 62097, $F291) close a logical file
  // 0xFFC6 CHKIN  (via 798 ($31E) to 61966, $F20E) define an input channel
  // 0xFFC9 CHKOUT (via 800 ($320) to 62032, $F250) define an output channel
  // 0xFFCC CLRCHN (via 802 ($322) to 62259, $F333) restore default devices
  // 0xFFCF CHRIN  (via 804 ($324) to 61783, $F157) input a character
  // 0xFFD2 CHROUT (via 806 ($326) to 61898, $F1CA) output a character
  // 0xFFD5 LOAD   (via 816 ($330) to 62622, $F49E) load from device
  // 0xFFD8 SAVE   (via 818 ($332) to 62941, $F5DD) save to a device
  // 0xFFDB SETTIM (0xF6E4) set the software clock
  // 0xFFDE RDTIM  (0xF6DD) read the software clock
  // 0xFFE1 STOP   (via 808 ($328) to 63213, $F6ED) check the STOP key
  // 0xFFE4 GETIN  (via 810 ($32A) to 61758, $F13E) get a character
  // 0xFFE7 CLALL  (via 812 ($32C) to 62255, $F32F) close all files
  // 0xFFEA UDTIM  (0xF69B) update the software clock
  // 0xFFED SCREEN (0xE505) read number of screen rows and columns
  // 0xFFF0 PLOT   (0xE50A) read/set position of cursor on screen
  // 0xFFF3 IOBASE (0xE500) read base address of I/O devices

  // 6510 Hardware Vectors (0xFFFA -0xFFFF)

  cpu->setWord(0xFFFA, 0xFE43); // Non-Maskable Interrupt Hardware Vector
  cpu->setWord(0xFFFC, 0xFCE2); // System Reset (RES) Hardware Vector
  cpu->setWord(0xFFFE, 0xFF48); // Maskable Interrupt Request and Break Hardware Vectors
}

void
C64::
tick(ushort n)
{
  // microprocessor machine cycles = 1,022,730 cycles per second
  // See line 8560 of mapping-c64.txt
  timerA_.zeroed = (timerA_.count > 0 && timerA_.count <= n);
  timerA_.zeroed = (timerB_.count > 0 && timerB_.count <= n);

  timerA_.count -= n;
  timerB_.count -= n;

  auto cpu = getCPU();

  uchar CIAICR = cpu->getByte(0xDC0D);

  if (timerA_.zeroed) {
    cpu->setByte(0xDC0D, CIAICR | 0x01);
  }
}

void
C64::
startTimerA(bool /*start*/)
{
}

void
C64::
startTimerB(bool /*start*/)
{
}

void
C64::
loadKeyColumn(int i)
{
  uchar c = 0xFF;

  // set bit zero if key pressed
  switch (i) {
    // CRSR DN, F5    ,  F3     , F1     , F7     , CRSR RT, RETURN , DELETE
    case 0: {
      break;
    }
    // LSHIFT , E      , S      , Z      , 4      , A      , W      , 3
    case 1: {
      break;
    }
    // X      , T      , F      , C      , 6      , D      , R      , 5
    case 2: {
      break;
    }
    // V      , U      , H      , B      , 8      , G      , Y      , 7
    case 3: {
      break;
    }
    // N      , O      , K      , M      , 0      , J      , I      , 9
    case 4: {
      break;
    }
    // ,      , @      , :      , .      , -      , L      , P      , +
    case 5: {
      break;
    }
    // /      , ^      , =      , RSHIFT , HOME   , ;      , *      , LIRA
    case 6: {
      break;
    }
    // STOP   , Q      , C=     , SPACE  , 2      , CTRL   , <-     , 1
    case 7: {
      break;
    }
  }

  auto cpu = getCPU();

  cpu->setByte(0xDC01, c);
}
