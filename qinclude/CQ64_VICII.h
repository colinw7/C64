#ifndef CQ64_VICII_H
#define CQ64_VICII_H

#include <C64_VICII.h>
#include <QWidget>

class CQ64;
class QTimer;
class QImage;

class CQ64_VICII : public QWidget, public C64_VICII {
  Q_OBJECT

  Q_PROPERTY(int scale READ scale WRITE setScale)

 public:
  CQ64_VICII(CQ64 *c64);

  int scale() const { return scale_; }
  void setScale(int i);

  void drawPixel(int x, int y, uchar c) override;

  void resizeEvent(QResizeEvent *) override;

  void paintEvent(QPaintEvent *) override;

  QSize sizeHint() const override;

 public slots:
  void memChangedSlot();

 private slots:
  void updateSlot();

 private:
  void setColor(uchar c);

 private:
  CQ64*     c64_      { nullptr };
  QTimer*   timer_    { nullptr };
  QImage*   image_    { nullptr };
  QPainter* ipainter_ { nullptr };
  int       scale_    { -1 };
  bool      dirty_    { false };
  bool      newScale_ { false };
};

#endif
