#ifndef CQ64Dbg_H
#define CQ64Dbg_H

#include <CQ6502Dbg.h>

class CQ64;

class CQ64Dbg : public CQ6502Dbg {
 public:
  CQ64Dbg(CQ64 *machine);

 private:
  CQ64 *machine_ { nullptr };
};

#endif
