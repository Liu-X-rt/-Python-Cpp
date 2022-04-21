#include <windows.h>                			//GetAsyncKeyState所需头文件
#include <iostream>
#include <cstdio>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //用来检测按键的点击事件

POINT p;
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND h=GetForegroundWindow();
CONSOLE_FONT_INFO consoleCurrentFont;

//----------移动光标----------
void gotoxy(int x, int y) {
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

//----------隐藏光标----------
void HideTheCursor() {
	CONSOLE_CURSOR_INFO cciCursor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if(GetConsoleCursorInfo(hStdOut, &cciCursor)) {
		cciCursor.bVisible = FALSE;
		SetConsoleCursorInfo(hStdOut, &cciCursor);
	}
}

void lax()
{
	system("color 6");
	system("color 2F");
	system("mode con cols=200 lines=100");
}
int main() {
	HideTheCursor();                            //隐藏光标
	
	//----------移除快速编辑模式(对于win10用户)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	
	lax();
	//----------循环检测----------
	while(1) {                      			//循环检测
		if(KEY_DOWN(VK_LBUTTON)) {  			//鼠标左键按下
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(h,&p);               //获取鼠标在窗口上的位置
			GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //获取字体信息
			int x=p.x/=consoleCurrentFont.dwFontSize.X;
			int y=p.y/=consoleCurrentFont.dwFontSize.Y;
			gotoxy(x,y);                        //移动光标置鼠标位置
			printf("L");                        //在鼠标位置输出
		}
		Sleep(10);                  			//延时
	}
	return 0;
}//从网上下载了一个东东，看看是啥 
