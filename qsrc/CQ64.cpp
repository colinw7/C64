#include <CQ64.h>
#include <CQ64_6502.h>
#include <CQ64_VICII.h>
#include <QPainter>

CQ64::
CQ64()
{
  setObjectName("C64");
}

void
CQ64::
init()
{
  cpu_ = qcpu_ = new CQ64_6502 (this);
  gpu_ = qgpu_ = new CQ64_VICII(this);

//connect(qcpu_, SIGNAL(registerChangedSignal()), this, SIGNAL(registerChangedSignal()));

//connect(qcpu_, SIGNAL(flagsChangedSignal()), this, SIGNAL(flagsChangedSignal()));
//connect(qcpu_, SIGNAL(stackChangedSignal()), this, SIGNAL(stackChangedSignal()));

  connect(qcpu_, SIGNAL(pcChangedSignal()), this, SIGNAL(pcChangedSignal()));
  connect(qcpu_, SIGNAL(memChangedSignal()), this, SIGNAL(memChangedSignal()));

  connect(qcpu_, SIGNAL(handleBreakSignal()), this, SIGNAL(handleBreakSignal()));
  connect(qcpu_, SIGNAL(breakpointHitSignal()), this, SIGNAL(breakpointHitSignal()));
  connect(qcpu_, SIGNAL(illegalJumpSignal()), this, SIGNAL(illegalJumpSignal()));

  connect(qcpu_, SIGNAL(breakpointsChangedSignal()), this, SIGNAL(breakpointsChangedSignal()));

  connect(qcpu_, SIGNAL(memChangedSignal()), qgpu_, SLOT(memChangedSlot()));

  //---

  C64::init();
}

void
CQ64::
show()
{
  getGPU()->show();
}
