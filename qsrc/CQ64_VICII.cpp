#include <CQ64_VICII.h>
#include <CQ64.h>
#include <QTimer>
#include <QPainter>

CQ64_VICII::
CQ64_VICII(CQ64 *c64) :
 C64_VICII(c64), c64_(c64)
{
  setObjectName("VICII");

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
memChangedSlot()
{
  dirty_ = true;
}

void
CQ64_VICII::
updateSlot()
{
  if (newScale_) {
    delete ipainter_;
    delete image_;

    // Screen: 40 x 25
    image_ = new QImage(scale_*textColumns()*8, scale_*textRows()*8, QImage::Format_ARGB32);

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
    drawScreen();

    dirty_ = false;
  }

  //---

  QPainter painter(this);

  painter.fillRect(rect(), QColor(0,0,0));

  if (image_)
    painter.drawImage(0, 0, *image_);
}

void
CQ64_VICII::
drawPixel(int x, int y, uchar c)
{
  setColor(c);

  int x1 = x*scale();
  int y1 = y*scale();

  for (int iy = 0; iy < scale(); ++iy) {
    for (int ix = 0; ix < scale(); ++ix) {
      ipainter_->drawPoint(x1 + ix, y1 + iy);
    }
  }
}

void
CQ64_VICII::
setColor(uchar c)
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

  ipainter_->setPen(colors[c % 16]);
}

QSize
CQ64_VICII::
sizeHint() const
{
  return QSize(scale_*textColumns()*8, scale_*textRows()*8);
}
