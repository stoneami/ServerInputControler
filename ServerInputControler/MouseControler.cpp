#include "StdAfx.h"
#include "MouseControler.h"

MouseControler::MouseControler(void)
{

}

MouseControler::~MouseControler(void)
{
}

void MouseControler::Move(int dx, int dy)
{
	ZeroMemory(&mMove, sizeof(INPUT));
	mMove.type = INPUT_MOUSE;
	mMove.mi.dx = dx;
	mMove.mi.dy = dy;
	mMove.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &mMove, sizeof(INPUT));
}

void MouseControler::Click()
{
	//INPUT inputs[2];
	ZeroMemory(mSingleClick, sizeof(INPUT));
	ZeroMemory(mSingleClick + 1, sizeof(INPUT));

	mSingleClick[0].type = INPUT_MOUSE;
	mSingleClick[1].type = INPUT_MOUSE;

	mSingleClick[0].mi.dwFlags= MOUSEEVENTF_LEFTDOWN;
	mSingleClick[1].mi.dwFlags= MOUSEEVENTF_LEFTUP;

	SendInput(2, mSingleClick, sizeof(INPUT));
}

void MouseControler::DoubleClick()
{
	//INPUT inputs[4];
	ZeroMemory(mDoublicClick, sizeof(INPUT));
	ZeroMemory(mDoublicClick + 1, sizeof(INPUT));
	ZeroMemory(mDoublicClick + 2, sizeof(INPUT));
	ZeroMemory(mDoublicClick + 3, sizeof(INPUT));

	mDoublicClick[0].type = INPUT_MOUSE;
	mDoublicClick[1].type = INPUT_MOUSE;
	mDoublicClick[2].type = INPUT_MOUSE;
	mDoublicClick[3].type = INPUT_MOUSE;

	mDoublicClick[0].mi.dwFlags= MOUSEEVENTF_LEFTDOWN;
	mDoublicClick[1].mi.dwFlags= MOUSEEVENTF_LEFTUP;
	mDoublicClick[2].mi.dwFlags= MOUSEEVENTF_LEFTDOWN;
	mDoublicClick[3].mi.dwFlags= MOUSEEVENTF_LEFTUP;

	SendInput(4, mDoublicClick, sizeof(INPUT));
}

void MouseControler::RightClick()
{
	//INPUT inputs[2];
	ZeroMemory(mRightClick, sizeof(INPUT));
	ZeroMemory(mRightClick + 1, sizeof(INPUT));

	mRightClick[0].type = INPUT_MOUSE;
	mRightClick[1].type = INPUT_MOUSE;

	mRightClick[0].mi.dwFlags= MOUSEEVENTF_RIGHTDOWN;
	mRightClick[1].mi.dwFlags= MOUSEEVENTF_RIGHTUP;

	SendInput(2, mRightClick, sizeof(INPUT));
}

void MouseControler::Roll()
{

}

//void MouseControler::SendKey(short key)
//{
//	ZeroMemory(mKeyboard, sizeof(INPUT));
//	mKeyboard[0].type = INPUT_KEYBOARD;
//	mKeyboard[1].type = INPUT_KEYBOARD;
//	mKeyboard[0].ki.wVk=mKeyboard[1].ki.wVk=0;
//	mKeyboard[0].ki.wScan=mKeyboard[1].ki.wScan=key;
//	mKeyboard[0].ki.dwFlags=KEYEVENTF_UNICODE;
//	mKeyboard[1].ki.dwFlags=KEYEVENTF_UNICODE|KEYEVENTF_KEYUP;
//	SendInput(2, mKeyboard, sizeof(INPUT));
//}

void MouseControler::HandleMouseEvent(char* actions, int size)
{
	if(actions == NULL || size < 1) return;

	for(int i=0; i<size; i++)
	{
		if(actions[i] == GO_LEFT)//move left
		{
			Move(-sStep, 0);
		}
		else if(actions[i] == GO_RIGHT)//move right
		{
			Move(sStep, 0);
		}
		else if(actions[i] == GO_UP)//move up
		{
			Move(0, -sStep);
		}
		else if(actions[i] == GO_DOWN)//move down
		{
			Move(0, sStep);
		}
		else if(actions[i] == DO_SINGLE_CLICK)//single click
		{
			Click();
		}
		else if(actions[i] == DO_RIGHT_CLICK)//right click
		{
			RightClick();
		}
		else if(actions[i] == DO_DOUBLE_CLICK)//double click
		{
			DoubleClick();
		}
		else if(actions[i] == DO_SCROLL)//scroll
		{
			Roll();
		}
	}
}

int MouseControler::sStep = 5;

void MouseControler::SetStep(int step)
{
	if(step<0 || step > 500) return;
	sStep = step;
}