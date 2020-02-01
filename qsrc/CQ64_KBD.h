#ifndef CQ64_KBD_H
#define CQ64_KBD_H

#include <QWidget>

class CQ64;

class CQ64_KBD : public QWidget {
  Q_OBJECT

 public:
  CQ64_KBD(CQ64 *c64);

  void paintEvent(QPaintEvent *) override;

 private:
  CQ64* c64_ { nullptr };
};

#endif
