#include <stdlib.h>
#include <time.h>
#include "BallDefinition.h"
 
#define WIDTH 700
#define HEIGHT 700
 
// ÿ�θ��� ������ȥ�� 1 ��
#define TimePast 1
 
#include <math.h>
 
// ��̫��ϵ����Ĳ������е����õĺ�
/*  
����̫���ľ��룺
	ˮ�ǣ�58000000ǧ��
	���ǣ�108000000ǧ��
	����150000000ǧ��
	���ǣ�228000000ǧ��
	ľ�ǣ�778000000ǧ��
	���ǣ�1427000000ǧ��
	�����ǣ�2870000000ǧ��
	�����ǣ�4497000000ǧ��	
����Ĺ�ת�뾶��384403ǧ��
̫��ϵ�������ֱ����
	̫����1392000000��
	ˮ�ǣ�4880000��
	���ǣ�12103600��
	����12756300��
	����3476280��
	���ǣ�6794000��
	ľ�ǣ�142984000��
	���ǣ�120536000��
	�����ǣ�51118000��
	�����ǣ�49532000��
*/
//��ת�뾶���ű���
#define KK .000001				//���ǵĹ�ת�뾶���ű�������Ϊ����ϵ����
#define dk (1.07 * KK)			//ˮ�Ǻͽ��ǵĹ�ת�뾶���ű���
#define edk (1.12 * KK)			//����Ĺ�ת�뾶���ű���
#define mk (50 * KK)			//����Ĺ�ת�뾶���ű���
#define fk (.5 * KK)			//ľ�Ǻ����ǹ�ת�뾶���ű���
#define hfk (.4 * KK)			//�����ǵĹ�ת�뾶���ű���
#define ffk (.3 * KK)			//�����ǵĹ�ת�뾶���ű���
//����ֱ�����ű���
#define sk (.035 * KK)			//̫����ֱ�����Ų���
#define vk (1.5 * KK)			//������ǵ�ֱ�����ű���
#define mrk (1.5 * KK)			//�����ֱ�����ű���
#define lsk (.3 * KK)			//ľ�Ǻ����ǵ�ֱ�����ű���
#define k (.5 * KK)				//�����Ǻͺ����ǵ�ֱ�����ű���
//����Ĺ�ת�������ű���
#define tk .3					//ľ�ǵĹ�ת�������ű���
#define ttk .2					//���ǵĹ�ת�������ű���
#define tttk .1					//�����Ǻͺ����ǵĹ�ת�������ű���
 
// ��ת�ٶȣ�������Ϊ��ֵ��
#define SelfRotate 3
 
#define ARRAY_SIZE 10
enum STARS {Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune};
Ball * Balls[ARRAY_SIZE];
 
void init() {
    Float3 Color;
    // ����������Щ����������Ǿ�����ͬ�����仯����
    // ̫��
	srand((unsigned)time(0));

	Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255))/255.0));
    Balls[Sun] = new LightBall(sk * 1392000000, 0, 0, SelfRotate, 0, Color);
    // ˮ��
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Mercury] = new MatBall(vk * 4880000, dk * 58000000, 87, SelfRotate, Balls[Sun], Color);
    // ����
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Venus] = new MatBall(vk * 12103600, dk * 108000000, 225, SelfRotate, Balls[Sun], Color);
    // ����
	Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Earth] = new MatBall(vk * 12756300, edk * 150000000, 365, SelfRotate, Balls[Sun], Color);
    // ����
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Moon] = new MatBall(mrk * 3476280 , mk * 384403, 28, SelfRotate, Balls[Earth], Color);
    // ����
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Mars] = new MatBall(vk * 6794000, KK * 228000000, 687, SelfRotate, Balls[Sun], Color);
    // ľ��
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0),((1.0 * (rand() % 255)) / 255.0));
    Balls[Jupiter] = new MatBall(lsk * 142984000,  fk * 778000000, tk * 4328, SelfRotate, Balls[Sun], Color);
    // ����
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Saturn] = new MatBall(lsk * 120536000, fk * 1427000000, ttk * 10752, SelfRotate, Balls[Sun], Color);
    // ������
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Uranus] = new MatBall(k * 51118000, hfk * 2870000000, tttk * 30664, SelfRotate, Balls[Sun], Color);
    // ������
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Neptune] = new MatBall(k * 49532000, ffk * 4497000000, tttk * 60148, SelfRotate, Balls[Sun], Color);
}
 
// ��ʼ�ӽǣ� �ӵ���(+z, -y)�� ��
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)
 
// lookAt����
GLdouble eyeX = 0, eyeY = REST_Y, eyeZ= REST_Z; 
GLdouble centerX= 0, centerY= 0, centerZ= 0; 
GLdouble upX= 0, upY= 0, upZ= 1;
 
void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
    glClearColor(.7, .7, .7, .1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY,eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
 
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
 
    // ʵ�ʻ���
    for (int i=0; i<ARRAY_SIZE; i++)         
		Balls[i]->Draw();
 
    glutSwapBuffers();
}
 
void OnUpdate(void) {
    // ʵ�ʸ���
    for (int i=0; i<ARRAY_SIZE; i++)         
		Balls[i]->Update(TimePast);
    OnDraw();
}
 
// ÿ�ΰ����ƶ��ľ���
#define OFFSET (20000000 * KK)
 
// ���������仯�ӽ�
// r(+y����)      l(-y����)   u(+z ����)   d(-z ����)   ' '(reset)
void keyboard (unsigned char key, int x, int y) {//key�Ǽ���ASCII�룬x,y�ǰ��¼���ʱ���� λ�á� 
    switch (key)    {
    case 'r': eyeY += OFFSET; break;
    case 'u': eyeZ += OFFSET; break;
    case 'd': eyeZ -= OFFSET; break;
    case 'l': eyeY -= OFFSET; break;
    case ' ':
        eyeX = 0; eyeY = REST_Y; eyeZ= REST_Z; 
        centerX= 0; centerY= 0; centerZ= 0; 
        upX= 0; upY= 0; upZ= 1;
        break;
    case 27: exit(0); break;
    default: break;
    }
}
void Mouse(int button,int state,int x,int y){//x , y ������λ�ã�button���㰴��ʲô�� ,state �ǰ��»���̧�� 
	if(state == GLUT_DOWN) {
		if(button == GLUT_LEFT_BUTTON){
			eyeX += OFFSET;			
		}
		else if(button == GLUT_RIGHT_BUTTON){
			eyeX -= OFFSET;
		}
	}
		
}
 
int main(int argc, char*  argv[]) {
    init();
 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA |  GLUT_DOUBLE);
    glutInitWindowPosition(150, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("ģ��̫��ϵ�������ת��");
    glutDisplayFunc(&OnDraw);
    glutIdleFunc(&OnUpdate);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(Mouse); 
    glutMainLoop();
 
    return 0;
}
