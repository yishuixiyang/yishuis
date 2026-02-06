#include <Windows.h>
#include <conio.h>
#include <stdio.h>
void play(char key)
{
	switch (key)
	{
	case 'a':
		printf("DO ");
		Beep(262, 500);
		break;
	case 's':
		printf("RE ");
		Beep(294, 500);
		break;
	case 'd':
		printf("MI ");
		Beep(330, 500);
		break;
	case 'f':
		printf("FA ");
		Beep(349, 500);
		break;
	case 'g':
		printf("SOL ");
		Beep(392, 500);
		break;
	case 'h':
		printf("LA ");
		Beep(440, 500);
		break;
	case 'j':
		printf("SI ");
		Beep(494, 500);
		break;
	case 'q':
		printf("DO2 ");
		Beep(523,500);
		break;
	case 'w':
		printf("RE2 ");
		Beep(587, 500);
		break;
	case 'e':
		printf("MI2 ");
		Beep(659, 500);
		break;
	case 'r':
		printf("FA2 ");
		Beep(698, 500);
		break;
	case 't':
		printf("SOL2 ");
		Beep(784, 500);
		break;
	case 'y':
		printf("LA2 ");
		Beep(880, 500);
		break;
	case 'u':
		printf("SI2 ");
		Beep(988, 500);
		break;
	
	default:
		printf("\n");
		break;
	}
}
int  main()
{
	printf("Ä£ÄâÇÙ \ndo-sol: a s d f g h j \ndo2-sol2: q w e r t y u\n");
	char key;
	while (1)
	{
		key = _getch();
		if (key == 27) break;
		play(key);

	}
	return 0;
}