#include <CQ64_CIA.h>
#include <CQ64.h>

#include <QKeyEvent>
#include <QTimer>

CQ64_CIA::
CQ64_CIA(CQ64 *c64, int id) :
 C64_CIA(c64, id), c64_(c64)
{
  setObjectName("CIA");

  timer_ = new QTimer(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(timerSlot()));

  timer_->start(1000/60); // 60Htz
}

void
CQ64_CIA::
timerSlot()
{
}

uchar
CQ64_CIA::
getKeyColumns(uchar a)
{
  uchar res = 0xFF;

  for (int i = 0; i < 8; ++i) {
    if (! (a & (1 << i))) // read columns for zero bits
      res &= keyA_[i];
  }

  if (isDebug()) {
    if (res != 0xFF)
      std::cerr << "getKeyColumns I=" << std::hex << int(a) <<
                   ", O=" << std::hex << int(res) << "\n";
  }

  return res;
}

void
CQ64_CIA::
handleKey(QKeyEvent *e, bool press)
{
  // SHIFT LOCK = toggles LSHIFT always on
  // RESTORE    = NMI

  int A = 0, B = 0;

  switch (e->key()) {
    case Qt::Key_Escape:      { A = 7; B = 7; break; } // STOP
    case Qt::Key_Q:           { A = 7; B = 6; break; }
    case Qt::Key_Print:       { A = 7; B = 5; break; } // Commodore
    case Qt::Key_Space:       { A = 7; B = 4; break; } // SPACE
    case Qt::Key_2:           { A = 7; B = 3; break; }
    case Qt::Key_Control:     { A = 7; B = 2; break; } // CTRL
    case Qt::Key_Backspace:   { A = 7; B = 1; break; } // <-
    case Qt::Key_1:           { A = 7; B = 0; break; }

    case Qt::Key_Slash:       { A = 6; B = 7; break; } // /
    case Qt::Key_AsciiCircum: { A = 6; B = 6; break; } // ^
    case Qt::Key_Equal:       { A = 6; B = 5; break; } // =
    case Qt::Key_Shift:       { A = 6; B = 4; break; } // RSHIFT
    case Qt::Key_Home:        { A = 6; B = 3; break; } // HOME
    case Qt::Key_Semicolon:   { A = 6; B = 2; break; } // ;
    case Qt::Key_Asterisk:    { A = 6; B = 1; break; } // *
    case Qt::Key_Dollar:      { A = 6; B = 0; break; } // LIRA (POUND SIGN)

    case Qt::Key_Comma:       { A = 5; B = 7; break; } // ,
    case Qt::Key_At:          { A = 5; B = 6; break; } // @
    case Qt::Key_Colon:       { A = 5; B = 5; break; } // :
    case Qt::Key_Period:      { A = 5; B = 4; break; } // .
    case Qt::Key_Minus:       { A = 5; B = 3; break; } // -
    case Qt::Key_L:           { A = 5; B = 2; break; }
    case Qt::Key_P:           { A = 5; B = 1; break; }
    case Qt::Key_Plus:        { A = 5; B = 0; break; } // +

    case Qt::Key_N:           { A = 4; B = 7; break; }
    case Qt::Key_O:           { A = 4; B = 6; break; }
    case Qt::Key_K:           { A = 4; B = 5; break; }
    case Qt::Key_M:           { A = 4; B = 4; break; }
    case Qt::Key_0:           { A = 4; B = 3; break; }
    case Qt::Key_J:           { A = 4; B = 2; break; }
    case Qt::Key_I:           { A = 4; B = 1; break; }
    case Qt::Key_9:           { A = 4; B = 0; break; }

    case Qt::Key_V:           { A = 3; B = 7; break; }
    case Qt::Key_U:           { A = 3; B = 6; break; }
    case Qt::Key_H:           { A = 3; B = 5; break; }
    case Qt::Key_B:           { A = 3; B = 4; break; }
    case Qt::Key_8:           { A = 3; B = 3; break; }
    case Qt::Key_G:           { A = 3; B = 2; break; }
    case Qt::Key_Y:           { A = 3; B = 1; break; }
    case Qt::Key_7:           { A = 3; B = 0; break; }

    case Qt::Key_X:           { A = 2; B = 7; break; }
    case Qt::Key_T:           { A = 2; B = 6; break; }
    case Qt::Key_F:           { A = 2; B = 5; break; }
    case Qt::Key_C:           { A = 2; B = 4; break; }
    case Qt::Key_6:           { A = 2; B = 3; break; }
    case Qt::Key_D:           { A = 2; B = 2; break; }
    case Qt::Key_R:           { A = 2; B = 1; break; }
    case Qt::Key_5:           { A = 2; B = 0; break; }

    case Qt::Key_Alt:         { A = 1; B = 7; break; } // LSHIFT
    case Qt::Key_E:           { A = 1; B = 6; break; }
    case Qt::Key_S:           { A = 1; B = 5; break; }
    case Qt::Key_Z:           { A = 1; B = 4; break; }
    case Qt::Key_4:           { A = 1; B = 3; break; }
    case Qt::Key_A:           { A = 1; B = 2; break; }
    case Qt::Key_W:           { A = 1; B = 1; break; }
    case Qt::Key_3:           { A = 1; B = 0; break; }

    case Qt::Key_Down:        { A = 0; B = 7; break; } // CRSR DN
    case Qt::Key_F5:          { A = 0; B = 6; break; }
    case Qt::Key_F3:          { A = 0; B = 5; break; }
    case Qt::Key_F1:          { A = 0; B = 4; break; }
    case Qt::Key_F7:          { A = 0; B = 3; break; }
    case Qt::Key_Right:       { A = 0; B = 2; break; } // CRSR RT
    case Qt::Key_Return:      { A = 0; B = 1; break; } // RETURN
    case Qt::Key_Delete:      { A = 0; B = 0; break; } // DELETE

    default: return;
  }

  if (isDebug())
    std::cerr << "Key A=" << A << ", B=" << B << "\n";

  if (press) { // clear bits
    keyA_[A] = keyA_[A] & ~(1 << B);
    keyB_[B] = keyB_[B] & ~(1 << A);
  }
  else {       // set bits
    keyA_[A] = keyA_[A] |  (1 << B);
    keyB_[B] = keyB_[B] |  (1 << A);
  }
}
