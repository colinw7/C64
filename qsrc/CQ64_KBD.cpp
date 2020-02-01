#include <CQ64_KBD.h>
#include <CQ64.h>

#include <QPainter>

CQ64_KBD::
CQ64_KBD(CQ64 *c64) :
 c64_(c64)
{
  setObjectName("KBD");

  setFocusPolicy(Qt::StrongFocus);
}

void
CQ64_KBD::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.fillRect(rect(), QColor(0,0,0));
}
