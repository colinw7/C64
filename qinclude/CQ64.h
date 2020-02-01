#ifndef CQ64_H
#define CQ64_H

#include <C64.h>
#include <QObject>

class CQ64_6502;
class CQ64_VICII;
class CQ64_CIA;
class QImage;

class CQ64 : public QObject, public C64 {
  Q_OBJECT

 public:
  CQ64();

  void init() override;

  CQ64_6502  *getCPU() const { return qcpu_; }
  CQ64_VICII *getGPU() const { return qgpu_; }

  CQ64_CIA *getCIA1() const { return qcia1_; }
  CQ64_CIA *getCIA2() const { return qcia2_; }

  void show();

 signals:
//void registerChangedSignal();
//void flagsChangedSignal();
//void stackChangedSignal();
  void pcChangedSignal();
  void memChangedSignal();

  void handleBreakSignal();
  void breakpointHitSignal();
  void illegalJumpSignal();

  void breakpointsChangedSignal();

 private:
  CQ64_6502  *qcpu_  { nullptr };
  CQ64_VICII *qgpu_  { nullptr };
  CQ64_CIA   *qcia1_ { nullptr };
  CQ64_CIA   *qcia2_ { nullptr };
};

#endif
