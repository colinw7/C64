#include <CQ64Dbg.h>
#include <CQ64_6502.h>
#include <CQ64.h>

CQ64Dbg::
CQ64Dbg(CQ64 *machine) :
 machine_(machine)
{
  setCPU(machine_->getCPU());

//connect(machine, SIGNAL(registerChangedSignal()), this, SLOT(updateSlot()));

//connect(machine, SIGNAL(flagsChangedSignal()), this, SLOT(updateSlot()));
//connect(machine, SIGNAL(stackChangedSignal()), this, SLOT(updateSlot()));

  connect(machine, SIGNAL(pcChangedSignal()), this, SLOT(updateSlot()));

//connect(machine, SIGNAL(memChangedSignal(ushort addr, ushort len)), this, SLOT(updateSlot()));

  connect(machine, SIGNAL(handleBreakSignal()), this, SLOT(forceHalt()));
  connect(machine, SIGNAL(breakpointHitSignal()), this, SLOT(forceHalt()));
  connect(machine, SIGNAL(illegalJumpSignal()), this, SLOT(forceHalt()));

  connect(machine, SIGNAL(breakpointsChangedSignal()), this, SLOT(breakpointsChangedSlot()));
}
