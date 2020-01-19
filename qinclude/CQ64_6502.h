#ifndef CQ64_6502_H
#define CQ64_6502_H

#include <C64_6502.h>
#include <QObject>

class CQ64;

class CQ64_6502 : public QObject, public C64_6502 {
  Q_OBJECT

 public:
  CQ64_6502(CQ64 *machine);

  void registerChanged(Reg) override { emit registerChangedSignal(); }

  void flagsChanged() override { emit flagsChangedSignal(); }
  void stackChanged() override { emit stackChangedSignal(); }
  void pcChanged   () override { emit pcChangedSignal   (); }
  void memChanged  () override { emit memChangedSignal  (); }

 signals:
  void registerChangedSignal();
  void flagsChangedSignal();
  void stackChangedSignal();
  void pcChangedSignal();
  void memChangedSignal();
};

#endif
