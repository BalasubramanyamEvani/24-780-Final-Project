#ifndef MENU_H_IS_INCLUDED
#define MENU_H_IS_INCLUDED


class GameMenu
{
public:
	enum
	{
		SEL_NONE,
		SEL_RUN_GAME,
		SEL_QUIT
	};

	int n=0;

	int RunOneStep(void);
};


#endif
