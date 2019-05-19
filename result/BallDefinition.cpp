#include "BallDefinition.h"
 
Ball::Ball(Float Radius, Float Distance, Float Speed, Float SelfSpeed,
		   Ball * Parent, Float3 color) {
 //   Float4(Color, 0.8f, 0.8f, 0.8f, 1.0f);
	Float4(Color, color[0], color[1], color[2], 1.0f);
    this->Radius = Radius;
    this->SelfSpeed = SelfSpeed;
    if (Speed > 0)
        this->Speed = 36.0f / Speed;
    AlphaSelf = Alpha= 0;
    this->Distance = Distance;
    ParentBall = Parent;
}
 
#include <stdio.h>
#include <math.h>
#define PI 3.1415926535
 
// 对普通的球体进行移动和旋转
void Ball::DrawBall() {
 
    glEnable(GL_LINE_SMOOTH);//允许曲线 
    glEnable(GL_BLEND);//启用颜色混合。例如实现半透明效果 
 
    int n = 1440;
 
    glPushMatrix();
    {
        // 公转
        if (ParentBall != 0 && ParentBall->Distance > 0) {
            glRotatef(ParentBall->Alpha, 0, 0, 1); //角度变化 
            glTranslatef(ParentBall->Distance, 0.0, 0.0);//位置变化 
 
            glBegin(GL_LINES);//画出公转轨道线 
            for(int i=0; i<n; ++i)
                glVertex2f(Distance * cos(2 * PI * i / n), 
                    Distance * sin(2 * PI * i / n));
            glEnd();
 
        } else {
            glBegin(GL_LINES);
            for(int i=0; i<n; ++i)
                glVertex2f(Distance * cos(2 * PI * i / n), 
                    Distance * sin(2 * PI * i / n));
            glEnd();
        }
        glRotatef(Alpha, 0, 0, 1);
        glTranslatef(Distance, 0.0, 0.0);
 
        // 自转
        glRotatef(AlphaSelf, 0, 0, 1);
 
        // 绘图
       // glColor3f(RFloat3(Color));
	//	glColor3f(1.0f,.0f,.0f);
        glutSolidSphere(Radius, 40, 32);
    }
    glPopMatrix();
}
 
void Ball::Update(long TimeSpan) {//这个函数让球随时间变化 
    // TimeSpan 是天
    Alpha += TimeSpan * Speed;
    AlphaSelf += SelfSpeed;
}
 
MatBall::MatBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed, 
    Ball * Parent, Float3 color) : Ball(Radius, Distance, Speed, SelfSpeed, Parent, color) {
        Float4(Color, color[0], color[1], color[2], 1.0f);
}
 
// 对材质进行设置
void MatBall::DrawMat() {
 
	GLfloat mat_ambient[] = {0.8f,0.7f,0.3f,1.0f};//物体对环境光的反射因素 
	GLfloat mat_diffuse[] = {0.3f,0.5f,0.8f,1.0f};//物体对漫反射光的反射因素 
	GLfloat mat_specular[] = {1.0f,1.0f,1.0f,1.0f};//物体对镜面光的反射因素 
//	GLfloat mat_emission[] = {0.3f,0.4f,0.8f,1.0f};//设置物体对荧光的颜色 */


//	GLfloat mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
//  GLfloat mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
//  GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    //下面两句替换可以出现彩色或者蓝色的太阳系模型
	GLfloat mat_emission[] = {RFloat4(Color)};
//	 GLfloat mat_emission[] = {.0f, .0f, 1.0f, 1.0f};
    GLfloat mat_shininess  = 90.0f;
 
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}
 
LightBall::LightBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed, 
    Ball * Parent, Float3 color)
    : MatBall(Radius, Distance, Speed, SelfSpeed, Parent, color) {}
 
// 对光源进行设置
void LightBall::DrawLight() {
    GLfloat light_position[] = {120.0f,120.0f,120.0f,1.0f};
//	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};	//光源位置	
    GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};	//环境光
    GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};	//漫反射光
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};	//镜面光
	glEnable(GL_LIGHTING);		//启用光照
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//设置光源位置
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);	//设置光源环境光
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);	//设置光源漫反射
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//设置光源镜面光
}
