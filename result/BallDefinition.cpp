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
 
// ����ͨ����������ƶ�����ת
void Ball::DrawBall() {
 
    glEnable(GL_LINE_SMOOTH);//�������� 
    glEnable(GL_BLEND);//������ɫ��ϡ�����ʵ�ְ�͸��Ч�� 
 
    int n = 1440;
 
    glPushMatrix();
    {
        // ��ת
        if (ParentBall != 0 && ParentBall->Distance > 0) {
            glRotatef(ParentBall->Alpha, 0, 0, 1); //�Ƕȱ仯 
            glTranslatef(ParentBall->Distance, 0.0, 0.0);//λ�ñ仯 
 
            glBegin(GL_LINES);//������ת����� 
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
 
        // ��ת
        glRotatef(AlphaSelf, 0, 0, 1);
 
        // ��ͼ
       // glColor3f(RFloat3(Color));
	//	glColor3f(1.0f,.0f,.0f);
        glutSolidSphere(Radius, 40, 32);
    }
    glPopMatrix();
}
 
void Ball::Update(long TimeSpan) {//�������������ʱ��仯 
    // TimeSpan ����
    Alpha += TimeSpan * Speed;
    AlphaSelf += SelfSpeed;
}
 
MatBall::MatBall(Float Radius, Float Distance, Float Speed, Float SelfSpeed, 
    Ball * Parent, Float3 color) : Ball(Radius, Distance, Speed, SelfSpeed, Parent, color) {
        Float4(Color, color[0], color[1], color[2], 1.0f);
}
 
// �Բ��ʽ�������
void MatBall::DrawMat() {
 
	GLfloat mat_ambient[] = {0.8f,0.7f,0.3f,1.0f};//����Ի�����ķ������� 
	GLfloat mat_diffuse[] = {0.3f,0.5f,0.8f,1.0f};//������������ķ������� 
	GLfloat mat_specular[] = {1.0f,1.0f,1.0f,1.0f};//����Ծ����ķ������� 
//	GLfloat mat_emission[] = {0.3f,0.4f,0.8f,1.0f};//���������ӫ�����ɫ */


//	GLfloat mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
//  GLfloat mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
//  GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    //���������滻���Գ��ֲ�ɫ������ɫ��̫��ϵģ��
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
 
// �Թ�Դ��������
void LightBall::DrawLight() {
    GLfloat light_position[] = {120.0f,120.0f,120.0f,1.0f};
//	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};	//��Դλ��	
    GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};	//������
    GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};	//�������
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};	//�����
	glEnable(GL_LIGHTING);		//���ù���
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//���ù�Դλ��
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);	//���ù�Դ������
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);	//���ù�Դ������
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);	//���ù�Դ�����
}