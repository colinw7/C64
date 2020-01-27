#include <CQ64_6502.h>
#include <CQ64.h>

CQ64_6502::
CQ64_6502(CQ64 *machine) :
 C64_6502(machine)
{
  setObjectName("6502");
}
