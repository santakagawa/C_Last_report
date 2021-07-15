// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <Windows.h>
#include "sub.h"


//時刻を表示//
void DrawClock(char* s);
//現在時間を読み取り//
void GetTimeStr(char* buf, int n, int cnt);
//iniファイルの絶対ディレクトリを取得//
void getCurrentDirectory(char* currentDirectory);
//iniファイルを読み取り//
void iniRead();
//地点表示//
void cityPrint(int k);


int main(int argc, char* argv[])
{
  iniRead();

  char	buf[BUFLEN];
  int	key;		// 入力キー文字
  int cnt = 0;

  // 画面の初期化
  initscr();

  //キー設定
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  curs_set(0);		// カーソルは表示しない
  
  timeout(0);		// キー入力は待たない


  // 時計の表示
  while (1) {

    erase();

    GetTimeStr(buf, BUFLEN, cnt);

    mvprintw(y + 3, x - 50, "%d", td[cnt]);	// 地点を表示

    DrawClock(buf);			// 時刻文字列を表示
    cityPrint(cnt);
    refresh();

    key = getch();
    if (key == 'q') break;		// [Q]キーで終了
    if (key == 'a') {
      if (cnt >= 0 && cnt < 4) {
        cnt++;
      }
      else if(cnt == 4) {
        cnt = 0;
      }
    }
    if (key == 's') {
      if (cnt > 0 && cnt <= 4) {
        cnt--;
      }
      else if (cnt == 0) {
        cnt = 4;
      }
    }
    
  }

  // 終了
  endwin();

  return (0);
}

void GetTimeStr(char* buf, int n, int cnt)
{
  t = time(NULL);		// 現在の unix時刻を取得
  error = localtime_s(&tm, &t);	// unix時刻を時刻要素（年月日時分秒）へ分解
  tm.tm_hour += td[cnt];
  strftime(buf, n, "%H:%M:%S", &tm);	// 時刻文字列（時:分:秒）を生成
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
  //napms(300);
  mvaddstr(y - 3, x - 50, cities[k0]);	// 地点を表示
  mvaddstr(y - 3, x - 25, cities[k1]);	// 地点を表示
  mvaddstr(y - 3, x, cities[k2]);	// 地点を表示
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
  td[0] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section2");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[1], keyValue);
  td[1] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section3");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[2], keyValue);
  td[2] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section4");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[3], keyValue);
  td[3] = GetPrivateProfileInt(section, td, 0, settingFile);

  sprintf_s(section, "section5");
  GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);
  sprintf_s(cities[4], keyValue);
  td[4] = GetPrivateProfileInt(section, td, 0, settingFile);
}

