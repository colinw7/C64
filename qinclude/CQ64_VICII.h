#ifndef CQ64_VICII_H
#define CQ64_VICII_H

#include <C64_VICII.h>
#include <QWidget>

class CQ64;

class QTimer;
class QImage;

class CQ64_VICII : public QWidget, public C64_VICII {
  Q_OBJECT

  Q_PROPERTY(int margin READ margin WRITE setMargin)
  Q_PROPERTY(int scale  READ scale  WRITE setScale )

 public:
  CQ64_VICII(CQ64 *c64);

  int scale() const { return scale_; }
  void setScale(int i);

  int margin() const { return margin_; }
  void setMargin(int i) { margin_ = i; }

  void fillScreen(uchar c) override;

  void drawPixel(int x, int y, uchar c) override;

  void resizeEvent(QResizeEvent *) override;

  void paintEvent(QPaintEvent *) override;

  void keyPressEvent  (QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

  QSize sizeHint() const override;

 public slots:
  void memChangedSlot(ushort addr, ushort len);

 private slots:
  void updateSlot();

 private:
  void setPen  (uchar c);
  void setBrush(uchar c);

  const QColor &getColor(uchar c) const;

 private:
  CQ64*       c64_      { nullptr };
  QTimer*     timer_    { nullptr };
  QImage*     image_    { nullptr };
  QPainter*   ipainter_ { nullptr };
  int         margin_   { 4 };
  int         scale_    { 1 };
  bool        dirty_    { false };
  bool        newScale_ { false };
  mutable int xm_       { 0 };
  mutable int ym_       { 0 };
};

#endif
