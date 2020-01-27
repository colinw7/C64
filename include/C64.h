#ifndef C64_H
#define C64_H

using uchar  = unsigned char;
using ushort = unsigned short;

class C64_6502;
class C64_VICII;
class C6502;

class C64 {
 public:
  C64();

  virtual ~C64() { }

  virtual void init();

  void loadKeyColumn(int i);

  C64_6502  *getCPU() const { return cpu_; }
  C64_VICII *getGPU() const { return gpu_; }

 protected:
  void initMemory();

  void tick(ushort n);

  void startTimerA(bool start);
  void startTimerB(bool start);

 protected:
  friend class C64_6502;

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

  C64_6502*  cpu_ { nullptr };
  C64_VICII* gpu_ { nullptr };
  Timer      timerA_;
  Timer      timerB_;
};

#endif
