#ifndef CQ64_CIA_H
#define CQ64_CIA_H

#include <C64_CIA.h>
#include <QObject>

class CQ64;

class QKeyEvent;
class QTimer;

class CQ64_CIA : public QObject, public C64_CIA {
  Q_OBJECT

 public:
  CQ64_CIA(CQ64 *c64, int id);

  uchar getKeyColumns(uchar) override;

  void handleKey(QKeyEvent *e, bool press);

 private slots:
  void timerSlot();

 private:
  CQ64*   c64_     { nullptr };
  QTimer* timer_   { nullptr };
  uchar   keyA_[8] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uchar   keyB_[8] { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
};

#endif
