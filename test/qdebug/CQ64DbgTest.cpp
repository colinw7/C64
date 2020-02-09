#include <CQ64Dbg.h>
#include <CQ64_6502.h>
#include <CQApp.h>
#include <CQ64.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

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

  if (binary) {
    if (filename != "") {
      c64->getCPU()->loadBin(filename);
    }
    else {
      std::cerr << "Missing binary filename '" << filename << "'\n";
      exit(1);
    }
  }

  c64->show();

  //---

  CQ64Dbg dbg(c64);

  dbg.init();

  dbg.setFixedFont(QFont("Courier New", 16));

  dbg.show();

  return app.exec();
}
