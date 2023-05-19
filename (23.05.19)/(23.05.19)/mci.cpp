#include<Windows.h>
#include<mmsystem.h>
#include<Digitalv.h>
#pragma comment(lib, "winmm.lib")

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;

MCI_OPEN_PARMS openEffect;
MCI_PLAY_PARMS playEffect;

UINT Bgmid;
UINT Effectid;

void PlayBgm()
{
	openBgm.lpstrElementName =TEXT("evolution.mp3");
	openBgm.lpstrDeviceType =TEXT("mpegvideo");
	// 디바이스 ID, 뭘할건지, 3, 4 플래그
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR) & openBgm);
	Bgmid = openBgm.wDeviceID;
	mciSendCommand(Bgmid, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&playBgm);
}

void PlayEffect()
{
	openEffect.lpstrElementName = TEXT("explosion.wav");
	openEffect.lpstrDeviceType = TEXT("wavevideo");
	// 디바이스 ID, 뭘할건지, 3, 4 플래그
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openEffect);
	Effectid = openEffect.wDeviceID;
	mciSendCommand(Effectid, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playEffect);
	Sleep(100);
	mciSendCommand(Effectid, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playEffect);
}

int main()
{
	PlayBgm();
	while (true);
}