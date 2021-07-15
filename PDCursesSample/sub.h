#pragma once

#define CHARBUFF 124
#define BUFFSIZE 1024
#define BUFLEN	10	// 文字列バッファの配列サイズ

int i;
int x=58, y=18;		// 表示位置
char cities[5][BUFFSIZE]; //地域名
int tdf[5]; //時差
time_t t;	// 現在の unix時刻
struct tm tm;	// 時刻要素構造体へのポインタ
errno_t error;

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
// 地点と時間を記録 //
void preserve(char* s, int k);

