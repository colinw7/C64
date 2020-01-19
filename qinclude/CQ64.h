#ifndef CQ64_H
#define CQ64_H

#include <C64.h>
#include <QWidget>

class QImage;

class CQ64 : public QWidget, public C64{
  Q_OBJECT

 public:
  CQ64();

  C64_6502 *createCPU() override;

  int scale() const { return scale_; }
  void setScale(int i);

  void drawPixel(int x, int y, uchar c) override;

  void update() override;

  void resizeEvent(QResizeEvent *) override;

  void paintEvent(QPaintEvent *) override;

 private:
  void setColor(uchar c);

 signals:
  void registerChangedSignal();
  void flagsChangedSignal();
  void stackChangedSignal();
  void pcChangedSignal();
  void memChangedSignal();

 private:
  QImage*   image_    { nullptr };
  QPainter* ipainter_ { nullptr };
  int       scale_    { -1 };
  bool      dirty_    { false };
};

#endif
