#define CHARBUFF 124
#define BUFFSIZE 1024
#define BUFLEN	10	// ������o�b�t�@�̔z��T�C�Y

int i;
int x=58, y=15;		// �\���ʒu
int w, h;		// ��ʃT�C�Y
char buf[BUFFSIZE];
char cities[5][BUFFSIZE]; //�n�於
int td[5]; //����
time_t		t;	// ���݂� unix����
struct tm tm;	// �����v�f�\���̂ւ̃|�C���^
errno_t error;