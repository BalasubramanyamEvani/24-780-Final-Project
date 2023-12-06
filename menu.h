#ifndef MENU_H_IS_INCLUDED
#define MENU_H_IS_INCLUDED

#include <string>

#include "yspng.h"

class GameMenu {
   public:
    GameMenu();
    ~GameMenu();
    int RunOneStep(void);

   private:
    std::string logoPng = "huntinghouselogo.png";
    YsRawPngDecoder png;
};

#endif
