#include <CQ64.h>
#include <CQ64_6502.h>
#include <QPainter>

CQ64::
CQ64()
{
  setScale(4);
}

C64_6502 *
CQ64::
createCPU()
{
  CQ64_6502 *cpu = new CQ64_6502(this);

  connect(cpu, SIGNAL(registerChangedSignal()), this, SIGNAL(registerChangedSignal()));
  connect(cpu, SIGNAL(flagsChangedSignal()), this, SIGNAL(flagsChangedSignal()));
  connect(cpu, SIGNAL(stackChangedSignal()), this, SIGNAL(stackChangedSignal()));
  connect(cpu, SIGNAL(pcChangedSignal()), this, SIGNAL(pcChangedSignal()));
  connect(cpu, SIGNAL(memChangedSignal()), this, SIGNAL(memChangedSignal()));

  return cpu;
}

void
CQ64::
setScale(int scale)
{
  if (scale != scale_) {
    scale_ = scale;

    delete image_;
    delete ipainter_;

    // Screen: 300 x 200
    image_ = new QImage(scale_*300, scale_*200, QImage::Format_ARGB32);

    image_->fill(0);

    ipainter_ = new QPainter(image_);
  }
}

void
CQ64::
update()
{
  dirty_ = true;

  QWidget::update();
}

void
CQ64::
resizeEvent(QResizeEvent *)
{
}

void
CQ64::
paintEvent(QPaintEvent *)
{
  if (dirty_) {
    drawScreen();

    dirty_ = false;
  }

  QPainter painter(this);

  painter.fillRect(rect(), QColor(0,0,0));

  if (image_)
    painter.drawImage(0, 0, *image_);
}

void
CQ64::
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
CQ64::
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
