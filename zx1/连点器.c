#include <Windows.h>
#include <shellapi.h>
#include <time.h>
#include <stdio.h>

static void click(int mode)
{
	if (mode == 0)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(rand() % (rand() % 3 + 1) + 2);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	}
	else
	{
		mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
		Sleep(rand() % (rand() % 3 + 1) + 2);
		mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	}	
}
static void msgc(int dlay,short mode)
{
	printf("设置成功: %d ms\n当前模式: ", dlay + 6);
	if (mode == 1)
	{
		printf("右键\n\n");
	}
	else
	{
		printf("左键\n\n");
	}
	printf("注意:\n");
	printf("自动点击时，如果鼠标移动超过25.6px，则自动关闭\n\n");
	printf("扩展功能:\n");
	printf("同时点击侧键1 + 2(或单击侧键1)开启，单击中键关闭\n");
	printf("长按侧键2切换点击模式，长按左右SHIFT重新配置\n");
	printf("同时长按 A D M 使用管理员权限重启\n\n");
}
static void admin()
{
	//获取当前路径
	wchar_t path[128];
	DWORD result = GetModuleFileName(NULL, path, 128);
	if (result < 1) {
		printf("获取当前路径失败\n");
		return ;
	}

	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpVerb = L"runas";
	sei.lpFile = path;
	sei.hwnd = NULL;
	sei.nShow = SW_NORMAL;
	if (!ShellExecuteEx(&sei))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_CANCELLED)
		{
			printf("权限获取取消\n");
		}
	}
	else
	{
		printf("重启成功");
		exit(0);
	}
}

int main() 
{
	typedef struct {
		int dlay;
		char autoclick;
		char clickmode;
		short modet;
		short reconfigt;
		short restartt;
	} Click;
	int dlaytimer = 0;

	Click config = {.autoclick=0,.clickmode=0,.modet=0,.reconfigt=0,.restartt=0};
	POINT pos1, pos2;
	srand((unsigned int)time(NULL));
	unsigned int  s = 0;

	printf("版本：V 0.1.2\n更新: \n优化延迟逻辑\n\n");
	printf("输入延迟(ms): ");
	scanf_s("%d", &config.dlay);

	config.dlay -=6;
	system("cls");
	msgc(config.dlay, config.clickmode);
	
	while (1)
	{

		//模式切换

		if (GetAsyncKeyState(VK_XBUTTON2))
		{
			config.modet++;
			if (config.modet >= 15)
			{
				config.clickmode++;
				config.clickmode %= 2;
				config.modet= -1000;
				Beep(330, 200);
				system("cls");
				msgc(config.dlay, config.clickmode);
				
			}
		}
		else
		{
			config.modet = 0;
		}

		//自动点击模式

		if (GetAsyncKeyState(VK_XBUTTON1) && GetAsyncKeyState(VK_XBUTTON2))
		{
			GetCursorPos(&pos1);
			config.autoclick = 1;
		}

		//暂停自动

		if (GetAsyncKeyState(VK_MBUTTON))
		{
			config.autoclick = 0;
		}

		//自动模式取消

		if (config.autoclick == 1)
		{
			GetCursorPos(&pos2);
			
			s = (pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y);
			if (s >= 655) config.autoclick = 0;
		}

		//点击处理

		if (config.autoclick == 1 || GetAsyncKeyState(VK_XBUTTON1))
		{
			if (dlaytimer <=100) 
			{
			click(config.clickmode);
			Sleep(rand() % (rand() % 5 + 7) + dlaytimer);
			dlaytimer = config.dlay;
			}
			else
			{
				dlaytimer -= 100;
				Sleep(100);
			}
			
		}
		else
		{
		dlaytimer = 0;
		Sleep(10);
		}

	//重置

		if (GetAsyncKeyState(VK_LSHIFT) && GetAsyncKeyState(VK_RSHIFT))
		{
			config.reconfigt++;
			if (config.reconfigt > 15)
			{
				config.autoclick = 0, config.clickmode = 0;
				config.reconfigt -= 1000;
				Beep(330, 200);

				while (getchar() != '\n' && getchar() != EOF);
				printf("重新输入延迟(ms): ");
				scanf_s("%d", &config.dlay);
				config.dlay -= 6;

				system("cls");
				msgc(config.dlay, config.clickmode);
			}
		}
		else
		{
			config.reconfigt = 0;
		}

	//管理员重启

		if (GetAsyncKeyState('A') && GetAsyncKeyState('D') && GetAsyncKeyState('M'))
		{
			config.restartt++;
			if (config.restartt > 15)
			{
				admin();
			}
		}
		else
		{
			config.restartt = 0;
		}
	}
	return 0;
}
