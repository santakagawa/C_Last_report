#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <Windows.h>
#include "sub.h"


void preserve(char* s,int k) {
  FILE* fp;
  char f[BUFFSIZE];
  errno_t errorfile;
  if (k < 3) {
    k += 2;
  }
  else if (k >= 3) {
    k -= 3;
  }
  errorfile = fopen_s(&fp, "output.txt", "w");
  if (errorfile != 0) {
    fprintf_s(stderr, "failed to open");
  }
  else {
    fprintf_s(fp, "%s\n%s", cities[k], s);
  }
  fclose(fp);
}

void GetTimeStr(char* buf, int n, int cnt)
{
  if (cnt < 3) {
    cnt += 2;
  }
  else if(cnt >= 3) {
    cnt -= 3;
  }
  t = time(NULL);		// 現在の unix時刻を取得
  error = localtime_s(&tm, &t);	// unix時刻を時刻要素（年月日時分秒）へ分解
  if (tm.tm_hour + tdf[cnt] < 0) {
    tm.tm_hour = tm.tm_hour + tdf[cnt] + 24;
  }
  else if (tm.tm_hour + tdf[cnt] > 23) {
    tm.tm_hour = tm.tm_hour + tdf[cnt] - 24;
  }
  else {
    tm.tm_hour += tdf[cnt];
  }
  strftime(buf, n, "%H:%M:%S", &tm);	// 時刻文字列（時:分:秒）を生成
  //mvprintw(y + 3, x - 50, "%s has a time dofference of %d hours from %s", cities[cnt], tdf[cnt], cities[2]);
}

void DrawClock(char* s)
{
  mvaddstr(y, x, s);	// 時刻を表示 
}

void getCurrentDirectory(char* currentDirectory) {
  GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void cityPrint(int k) {
  int k0, k1, k2, k3, k4;
  if (k == 0) {
    k0 = 0;
    k1 = 1;
    k2 = 2;
    k3 = 3;
    k4 = 4;
  }
  else if (k == 1) {
    k0 = 1;
    k1 = 2;
    k2 = 3;
    k3 = 4;
    k4 = 0;
  }
  else if (k == 3) {
    k0 = 3;
    k1 = 4;
    k2 = 0;
    k3 = 1;
    k4 = 2;
  }
  else if (k == 4) {
    k0 = 4;
    k1 = 0;
    k2 = 1;
    k3 = 2;
    k4 = 3;
  }
  else {
    k0 = 2;
    k1 = 3;
    k2 = 4;
    k3 = 0;
    k4 = 1;
  }
  mvaddstr(y - 3, x - 50, cities[k0]);	// 地点を表示
  mvaddstr(y - 3, x - 25, cities[k1]);	// 地点を表示
  mvaddch(y - 3, x - 6, '<' );
  mvaddstr(y - 3, x, cities[k2]);	// 地点を表示
  mvaddch(y - 3, x + 15, '>');
  mvaddstr(y - 3, x + 25, cities[k3]);	// 地点を表示
  mvaddstr(y - 3, x + 50, cities[k4]);	// 地点を表示
  refresh();
}

void iniRead() {
  //iniファイル読みとり//
  char currentDirectory[CHARBUFF];
  getCurrentDirectory(currentDirectory);

  char section[CHARBUFF];
  sprintf_s(section, "section1");
  char keyWord[CHARBUFF];
  sprintf_s(keyWord, "keyword");
  char td[CHARBUFF];
  sprintf_s(td, "td");
  char settingFile[CHARBUFF];
  sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
  char keyValue[CHARBUFF];

  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[0], keyValue);
  tdf[0] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section2");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[1], keyValue);
  tdf[1] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section3");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[2], keyValue);
  tdf[2] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section4");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[3], keyValue);
  tdf[3] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section5");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[4], keyValue);
  tdf[4] = GetPrivateProfileInt(section, td, 0, settingFile);
}
