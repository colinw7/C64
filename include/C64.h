#ifndef C64_H
#define C64_H

using uchar  = unsigned char;
using ushort = unsigned short;

class C64_6502;
class C64_VICII;
class C64_CIA;

class C6502;

class C64 {
 public:
  C64();

  virtual ~C64() { }

  virtual void init();

  C64_6502  *getCPU() const { return cpu_; }
  C64_VICII *getGPU() const { return gpu_; }

  C64_CIA *getCIA1() const { return cia1_; }
  C64_CIA *getCIA2() const { return cia2_; }

 protected:
  void initMemory();

  void tick(ushort n);

  void startTimerA(bool start);
  void startTimerB(bool start);

 protected:
  friend class C64_6502;

  C64_6502*  cpu_  { nullptr };
  C64_VICII* gpu_  { nullptr };
  C64_CIA*   cia1_ { nullptr };
  C64_CIA*   cia2_ { nullptr };
};

#endif
