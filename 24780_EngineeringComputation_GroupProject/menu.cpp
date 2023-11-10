#include <string>

#include "fssimplewindow.h"


#include "menu.h"
#include "ysglfontdata.h"


int GameMenu::RunOneStep(void)
{
	int returnValue=SEL_NONE;

	FsPollDevice();
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		returnValue=SEL_QUIT;
	}
	else if(FSKEY_S==key)
	{
		returnValue=SEL_RUN_GAME;
	}

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3f(0,0,0);
	glRasterPos2i(100,100);
	YsGlDrawFontBitmap16x20("ESC...Quit the Program.");
	glRasterPos2i(100,120);
	YsGlDrawFontBitmap16x20("S.....Start the Game.");

	std::string title="SHOOTINGGAME";

	glRasterPos2i(100,60);
	for(int i=0; i<n/100; ++i)
	{
		char c[2]={title[i],0};
		YsGlDrawFontBitmap16x20(c);
	}
	++n;
	if(title.size()<n/100)
	{
		n=0;
	}


	FsSwapBuffers();

	return returnValue;
}
