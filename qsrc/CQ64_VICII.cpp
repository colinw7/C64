#include <CQ64_VICII.h>
#include <CQ64_CIA.h>
#include <CQ64_6502.h>
#include <CQ64.h>

#include <QApplication>
#include <QTimer>
#include <QPainter>

CQ64_VICII::
CQ64_VICII(CQ64 *c64) :
 C64_VICII(c64), c64_(c64)
{
  setObjectName("VICII");

  setFocusPolicy(Qt::StrongFocus);

  setScale(4);

  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer_->start(1000/60); // 60Htz
}

void
CQ64_VICII::
setScale(int scale)
{
  if (scale != scale_) {
    scale_ = scale;

    newScale_ = true;
  }
}

void
CQ64_VICII::
memChangedSlot(ushort addr, ushort len)
{
  static int updateCount;

  if (! isScreen(addr, len))
    return;

  dirty_ = true;

  //---

  ++updateCount;

  if (updateCount > 1000) {
    qApp->processEvents();

    updateCount = 0;
  }
}

void
CQ64_VICII::
updateSlot()
{
  if (newScale_) {
    delete ipainter_;
    delete image_;

    // Screen: 40 x 25 (plus margins)
    int xm = scale()*8*margin();
    int ym = scale()*8*margin();

    int w = scale_*textColumns()*8;
    int h = scale_*textRows   ()*8;

    image_ = new QImage(w + 2*xm, h + 2*ym, QImage::Format_ARGB32);

    image_->fill(0);

    ipainter_ = new QPainter(image_);

    newScale_ = false;
    dirty_    = true;
  }

  update();
}

void
CQ64_VICII::
resizeEvent(QResizeEvent *)
{
}

void
CQ64_VICII::
paintEvent(QPaintEvent *)
{
  if (dirty_) {
    xm_ = scale()*8*margin();
    ym_ = scale()*8*margin();

    drawScreen();

    dirty_ = false;
  }

  //---

  QPainter painter(this);

  painter.fillRect(rect(), Qt::black);

  if (image_)
    painter.drawImage(0, 0, *image_);
}

void
CQ64_VICII::
fillScreen(uchar c)
{
  setBrush(c);

  QRect r(0, 0, image_->width(), image_->height());

  ipainter_->fillRect(r, ipainter_->brush());
}

void
CQ64_VICII::
drawPixel(int x, int y, uchar c)
{
  setPen(c);

  int x1 = x*scale();
  int y1 = y*scale();

  for (int iy = 0; iy < scale(); ++iy) {
    for (int ix = 0; ix < scale(); ++ix) {
      ipainter_->drawPoint(xm_ + x1 + ix, ym_ + y1 + iy);
    }
  }
}

void
CQ64_VICII::
setPen(uchar c)
{
  ipainter_->setPen(getColor(c));
}

void
CQ64_VICII::
setBrush(uchar c)
{
  ipainter_->setBrush(getColor(c));
}

const QColor &
CQ64_VICII::
getColor(uchar c) const
{
  // 16 colors
  static QColor colors[] {
    QColor(  0,   0,   0), // Black
    QColor(255, 255, 255), // White
    QColor(136,   0,   0), // Red
    QColor(170, 255, 238), // Cyan
    QColor(204,  68, 204), // Violet / purple
    QColor(  0, 204,  85), // Green
    QColor(  0,   0, 170), // Blue
    QColor(238, 238, 119), // Yellow
    QColor(221, 136,  85), // Orange
    QColor(102,  68,   0), // Brown
    QColor(255, 119, 119), // Light red
    QColor( 51,  51,  51), // Dark grey / grey 1
    QColor(119, 119, 119), // Grey 2
    QColor(170, 255, 102), // Light green
    QColor(  0, 136, 255), // Light blue
    QColor(187, 187, 187)  // Light grey / grey
  };

  return colors[c % 16];
}

void
CQ64_VICII::
keyPressEvent(QKeyEvent *e)
{
  c64_->getCIA1()->handleKey(e, true);
}

void
CQ64_VICII::
keyReleaseEvent(QKeyEvent *e)
{
  c64_->getCIA1()->handleKey(e, false);
}

QSize
CQ64_VICII::
sizeHint() const
{
  int xm = scale()*8*margin();
  int ym = scale()*8*margin();

  int w = scale_*textColumns()*8;
  int h = scale_*textRows   ()*8;

  return QSize(w + 2*xm, h + 2*ym);
}
