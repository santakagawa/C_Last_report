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
