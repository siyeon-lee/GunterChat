#include "background.h"



background::background()
{
}


background::~background()
{
}
void	background::drawtileRect()
{
	int iBitmapID = I_BitmapMgr.Load(L"../../data/bitmap/0612.bmp");
	syObject background;
	background.Init();
	syObjectInfo backInfo;
	backInfo.InitPos = syPoint(640/2,480/2);
	RECT rtt = { 0,0,640,480 };
	backInfo.rtClient = rtt;
	backInfo.fSpeed = 0.0f;
	background.Load(L"../../data/bitmap/0612.bmp");
	background.Set(backInfo);
	syBg.m_backgrounds = background;



	FILE* fp;
	char buffer[256] = { 0, };
	fopen_s(&fp, "background.txt", "r");
	if (fp == NULL)
	{
		//경고창 띄워야하는데
	}
	static int col = 0;
	while (!feof(fp))
	{
		fgets(buffer, sizeof(buffer), fp);
		char* tok = strtok(buffer, "\t");
		int row = 0;
		while (tok != NULL)
		{
			int tilevaule = atoi(tok);
		
		
				sySprite* pBk = new sySprite();
				pBk->Init();
				syObjectInfo info;
				info.iNumFrame = 1;
				
				info.InitPos = syPoint(row * 16+8, col * 16+8);
				RECT rt = { row * 16, col * 16, 16, 16 };
				info.rtClient = rt;
				info.bLoop = true;
				info.fSpeed = 0.0f;
				info.rtList.push_back(rt);
				pBk->Set(info, iBitmapID, -1);
				pBk->m_iCurrentFrame = 0;
				if (tilevaule != -1)
				{
					syBg.insertTiles(pBk, tilevaule);
					//때리면 블록 바뀌는거 구현 rtList에 추가하면 됨
				}

			row++;
			tok = strtok(NULL, "\t");
		}
		col++;
	}
	col = 0;
	fclose(fp);
}

bool   background::Init()
{
	drawtileRect();
	return true;
}

