// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <Windows.h>
#include "sub.h"
#include "myMath.cpp"


int main(int argc, char* argv[])
{
  iniRead();

  char	buf[BUFFSIZE];
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

    //画面の初期化
    erase();

    //現在時間取得
    GetTimeStr(buf, BUFLEN, cnt);

    //画面表示
    mvaddstr(y - 14, x - 50, "World Clock");
    mvaddstr(y - 11, x - 50, "press 'a' turn Left, press 'l' turn Right");
    mvaddstr(y - 8, x - 50, "press 's' output location and time and close the application");
    DrawClock(buf);			// 時刻文字列を表示
    cityPrint(cnt);
    refresh();

    //キー判定
    key = getch();

    //右にシフト(行きすぎたら左端に戻る)
    if (key == 'l') {
      if (cnt >= 0 && cnt < 4) {
        cnt++;
      }
      else {
        cnt = 0;
      }
    }

    //左にシフト(行きすぎたら右端に戻る)
    if (key == 'a') {
      if (cnt > 0 && cnt <= 4) {
        cnt--;
      }
      else {
        cnt = 4;
      }
    }

    //時刻を保存して終了
    if (key == 's') {
      preserve(buf, cnt);
      break;
    }
  }

  // 終了
  endwin();

  return (0);
}


