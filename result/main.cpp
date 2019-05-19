#include <stdlib.h>
#include <time.h>
#include "BallDefinition.h"
 
#define WIDTH 700
#define HEIGHT 700
 
// 每次更新 看做过去了 1 天
#define TimePast 1
 
#include <math.h>
 
// 对太阳系星球的参数进行调整用的宏
/*  
距离太阳的距离：
	水星：58000000千米
	金星：108000000千米
	地球：150000000千米
	火星：228000000千米
	木星：778000000千米
	土星：1427000000千米
	天王星：2870000000千米
	海王星：4497000000千米	
月球的公转半径：384403千米
太阳系各星球的直径：
	太阳：1392000000米
	水星：4880000米
	金星：12103600米
	地球：12756300米
	月球：3476280米
	火星：6794000米
	木星：142984000米
	土星：120536000米
	天王星：51118000米
	海王星：49532000米
*/
//公转半径缩放比例
#define KK .000001				//火星的公转半径缩放比例（视为比例系数）
#define dk (1.07 * KK)			//水星和金星的公转半径缩放比例
#define edk (1.12 * KK)			//地球的公转半径缩放比例
#define mk (50 * KK)			//月球的公转半径缩放比例
#define fk (.5 * KK)			//木星和土星公转半径缩放比例
#define hfk (.4 * KK)			//天王星的公转半径缩放比例
#define ffk (.3 * KK)			//海王星的公转半径缩放比例
//星球直径缩放比例
#define sk (.035 * KK)			//太阳的直径缩放参数
#define vk (1.5 * KK)			//类地行星的直径缩放比例
#define mrk (1.5 * KK)			//月球的直径缩放比例
#define lsk (.3 * KK)			//木星和土星的直径缩放比例
#define k (.5 * KK)				//天王星和海王星的直径缩放比例
//星球的公转周期缩放比例
#define tk .3					//木星的公转周期缩放比例
#define ttk .2					//土星的公转周期缩放比例
#define tttk .1					//天王星和海王星的公转周期缩放比例
 
// 自转速度（都定义为定值）
#define SelfRotate 3
 
#define ARRAY_SIZE 10
enum STARS {Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune};
Ball * Balls[ARRAY_SIZE];
 
void init() {
    Float3 Color;
    // 定义星球，这些星球的数据是经过不同比例变化过的
    // 太阳
	srand((unsigned)time(0));

	Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255))/255.0));
    Balls[Sun] = new LightBall(sk * 1392000000, 0, 0, SelfRotate, 0, Color);
    // 水星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Mercury] = new MatBall(vk * 4880000, dk * 58000000, 87, SelfRotate, Balls[Sun], Color);
    // 金星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Venus] = new MatBall(vk * 12103600, dk * 108000000, 225, SelfRotate, Balls[Sun], Color);
    // 地球
	Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Earth] = new MatBall(vk * 12756300, edk * 150000000, 365, SelfRotate, Balls[Sun], Color);
    // 月亮
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Moon] = new MatBall(mrk * 3476280 , mk * 384403, 28, SelfRotate, Balls[Earth], Color);
    // 火星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Mars] = new MatBall(vk * 6794000, KK * 228000000, 687, SelfRotate, Balls[Sun], Color);
    // 木星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0),((1.0 * (rand() % 255)) / 255.0));
    Balls[Jupiter] = new MatBall(lsk * 142984000,  fk * 778000000, tk * 4328, SelfRotate, Balls[Sun], Color);
    // 土星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Saturn] = new MatBall(lsk * 120536000, fk * 1427000000, ttk * 10752, SelfRotate, Balls[Sun], Color);
    // 天王星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Uranus] = new MatBall(k * 51118000, hfk * 2870000000, tttk * 30664, SelfRotate, Balls[Sun], Color);
    // 海王星
    Float3(Color, ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0), ((1.0 * (rand() % 255)) / 255.0));
    Balls[Neptune] = new MatBall(k * 49532000, ffk * 4497000000, tttk * 60148, SelfRotate, Balls[Sun], Color);
}
 
// 初始视角（ 视点在(+z, -y)处 ）
#define REST (700000000 * KK)
#define REST_Z (REST)
#define REST_Y (-REST)
 
// lookAt参数
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
 
    // 实际绘制
    for (int i=0; i<ARRAY_SIZE; i++)         
		Balls[i]->Draw();
 
    glutSwapBuffers();
}
 
void OnUpdate(void) {
    // 实际更新
    for (int i=0; i<ARRAY_SIZE; i++)         
		Balls[i]->Update(TimePast);
    OnDraw();
}
 
// 每次按键移动的距离
#define OFFSET (20000000 * KK)
 
// 按键操作变化视角
// r(+y方向)      l(-y方向)   u(+z 方向)   d(-z 方向)   ' '(reset)
void keyboard (unsigned char key, int x, int y) {//key是键的ASCII码，x,y是按下键盘时鼠标的 位置。 
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
void Mouse(int button,int state,int x,int y){//x , y 是鼠标的位置，button是你按了什么键 ,state 是按下还是抬起 
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
    glutCreateWindow("模拟太阳系各星球的转动");
    glutDisplayFunc(&OnDraw);
    glutIdleFunc(&OnUpdate);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(Mouse); 
    glutMainLoop();
 
    return 0;
}
