#include <windows.h>                			//GetAsyncKeyState����ͷ�ļ�
#include <iostream>
#include <cstdio>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)  //������ⰴ���ĵ���¼�

POINT p;
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HWND h=GetForegroundWindow();
CONSOLE_FONT_INFO consoleCurrentFont;

//----------�ƶ����----------
void gotoxy(int x, int y) {
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

//----------���ع��----------
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
	HideTheCursor();                            //���ع��
	
	//----------�Ƴ����ٱ༭ģʽ(����win10�û�)----------
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hStdin, mode);
	
	lax();
	//----------ѭ�����----------
	while(1) {                      			//ѭ�����
		if(KEY_DOWN(VK_LBUTTON)) {  			//����������
			POINT p;
			GetCursorPos(&p);
			ScreenToClient(h,&p);               //��ȡ����ڴ����ϵ�λ��
			GetCurrentConsoleFont(hOutput, FALSE, &consoleCurrentFont); //��ȡ������Ϣ
			int x=p.x/=consoleCurrentFont.dwFontSize.X;
			int y=p.y/=consoleCurrentFont.dwFontSize.Y;
			gotoxy(x,y);                        //�ƶ���������λ��
			printf("L");                        //�����λ�����
		}
		Sleep(10);                  			//��ʱ
	}
	return 0;
}//������������һ��������������ɶ 
