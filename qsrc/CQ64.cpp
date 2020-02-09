#include <CQ64.h>
#include <CQ64_6502.h>
#include <CQ64_VICII.h>
#include <CQ64_CIA.h>
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

  cia1_ = qcia1_ = new CQ64_CIA(this, 1);
  cia2_ = qcia2_ = new CQ64_CIA(this, 2);

//connect(qcpu_, SIGNAL(registerChangedSignal()), this, SIGNAL(registerChangedSignal()));

//connect(qcpu_, SIGNAL(flagsChangedSignal()), this, SIGNAL(flagsChangedSignal()));
//connect(qcpu_, SIGNAL(stackChangedSignal()), this, SIGNAL(stackChangedSignal()));

  connect(qcpu_, SIGNAL(pcChangedSignal()), this, SIGNAL(pcChangedSignal()));
  connect(qcpu_, SIGNAL(memChangedSignal(unsigned short, unsigned short)),
          this, SIGNAL(memChangedSignal(unsigned short, unsigned short)));

  connect(qcpu_, SIGNAL(handleBreakSignal()), this, SIGNAL(handleBreakSignal()));
  connect(qcpu_, SIGNAL(breakpointHitSignal()), this, SIGNAL(breakpointHitSignal()));
  connect(qcpu_, SIGNAL(illegalJumpSignal()), this, SIGNAL(illegalJumpSignal()));

  connect(qcpu_, SIGNAL(breakpointsChangedSignal()), this, SIGNAL(breakpointsChangedSignal()));

  connect(qcpu_, SIGNAL(memChangedSignal(unsigned short, unsigned short)),
          qgpu_, SLOT(memChangedSlot(unsigned short, unsigned short)));

  //---

  C64::init();
}

void
CQ64::
show()
{
  getGPU()->show();
}
