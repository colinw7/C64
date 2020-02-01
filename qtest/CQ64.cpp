#include <CQ64.h>
#include <CQ64_6502.h>
#include <QApplication>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  std::string filename;

  bool binary = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if      (arg == "-bin") {
      binary = true;
    }
    else {
      filename = argv[i];
    }
  }

  //---

  CQ64 *c64 = new CQ64;

  c64->init();

  c64->show();

  c64->getCPU()->run();

  return app.exec();
}
