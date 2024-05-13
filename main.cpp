//partea de 2D
#include<windows.h>
#include <gl/freeglut.h>
#include <GL/glut.h>
#include <math.h>
# define M_PI           3.14159265358979323846
#include<iostream>

//variabile globale, folosite pentru miscarea elementelor in scena
double i = 0.0;
double j = 0.0;
double alpha = 1.0;
double a = 0;
double b = 0;
double k = 0;
double var = 0;

bool sunPulsing = false;
float sunPulseFactor = 1.0;

double cloudPosition = -600.0;
double cloudSpeed = 0.04;
float birdPositionX = 0.0f;
float birdPositionY = 1600.0f;
float birdSpeed = 0.07f;

//adaugat acum

float woodColor[3] = { 0.52, 0.37, 0.26 };  // RGB pentru maro deschis

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);  //seteaza culoarea alb pentru fereastra
	glMatrixMode(GL_MODELVIEW);        //modul folosit pentru transformarile obiectelor ( translatie,scalare,rotatie)
	glLoadIdentity();                  //reseteaza matricea curenta

	glMatrixMode(GL_PROJECTION);       // proiectia ortogonala a scenei
	gluOrtho2D(-800.0, 800.0, -600.0, 600.0);   // -800 la 800 pe axa x (orizonatala) si -600 la 6000 pe y (verticala
	glClear(GL_COLOR_BUFFER_BIT);              //curata buffer-ul de culoare

}


void circle(GLdouble rad) {
	GLint points = 50;
	GLdouble delTheta = (2.0 * M_PI) / (GLdouble)points;
	GLdouble theta = 0.0;

	glBegin(GL_POLYGON);
	for (int i = 0; i <= points; ++i, theta += delTheta) {
		glVertex2f(rad * cos(theta), rad * sin(theta));
	}
	glEnd();
}

void drawCircle2(float r, float x, float y) {
	float k = 0.0f;

	glBegin(GL_TRIANGLE_FAN);  // pentru a desena un cerc 
	glColor3f(0, 0.3, 0);
	glVertex2f(x, y); // Center
	//itereaza de la 0 la 360 pentru a desena punctele
	for (k = 0.0f; k <= 360; k++)
		glVertex2f(r * cos(M_PI * k / 180.0) + x, r * sin(M_PI * k / 180.0) + y);

	glEnd();

}

void fancyTree(float trunkHeight = 300.0f, float trunkWidth = 30.0f, float crownScale = 80.0f) {
	// Trunchiul copacului
	glColor3f(0.38, 0.21, 0.26); // Maro pentru trunchi
	glBegin(GL_POLYGON);
	glVertex2f(1300, 900); // Coordonate pentru trunchi
	glVertex2f(1300 + trunkWidth, 900);
	glVertex2f(1300 + trunkWidth, 900 + trunkHeight); // Înălțimea trunchiului
	glVertex2f(1300, 900 + trunkHeight);
	glEnd();

	// Frunzele copacului (mai multe straturi) cu compunerea transformărilor
	glPushMatrix();
	glTranslatef(1310, 900 + trunkHeight, 0); // Poziționarea inițială a frunzelor deasupra trunchiului
	glRotatef(-15.0f, 0.0f, 0.0f, 1.0f); // Ușoară înclinare a întregii coroane a copacului pentru dinamism

	glColor3f(0.0, 0.5, 0.0); // Verde pentru stratul inferior
	circle(crownScale); // Strat mare

	// Primul strat lateral de frunze
	glPushMatrix();
	glTranslatef(-30, -30, 0); // Deplasare la stânga și jos
	glScalef(0.75f, 0.75f, 1.0f); // Scalare pentru mărimea frunzelor
	glColor3f(0.0, 0.7, 0.0); // Verde mediu
	circle(crownScale);
	glPopMatrix();

	// Al doilea strat lateral de frunze
	glPushMatrix();
	glTranslatef(30, -30, 0); // Deplasare la dreapta și jos
	glScalef(0.75f, 0.75f, 1.0f); // Scalare similară
	glColor3f(0.0, 0.8, 0.0); // Verde deschis
	circle(crownScale);
	glPopMatrix();

	// Stratul superior de frunze
	glPushMatrix();
	glTranslatef(0, 50, 0); // Deplasare în sus
	glScalef(0.65f, 0.65f, 1.0f); // Mai mică scalare
	glColor3f(0.0, 0.6, 0.0); // Verde intermediar
	circle(crownScale * 0.65f);
	glPopMatrix();

	glPopMatrix(); // Restabilirea matricei originale
}


//void drawCar(float x, float y) {
//
//	glBegin(GL_POLYGON);
//	glColor3f(0, 1, 0);
//	glVertex2i(x, y);    //x , y
//	glColor3f(0, 0, 1);
//	glVertex2i(x + 20, y);	//x + 20, y
//	glColor3f(1, 0, 0);
//	glVertex2i(x + 60, y + 40);    //460 100 unde e roata   //x+60, y+40
//	glColor3f(0, 1, 0);
//	glVertex2i(x + 100, y);    //x +100 , y
//	glColor3f(0, 0, 1);
//	glVertex2i(x + 180, y);	//x + 180, y
//	glColor3f(1, 0, 0);
//	glVertex2i(x + 220, y + 40);	//x + 220, y + 40
//	glColor3f(0, 1, 0);
//	glVertex2i(x + 260, y);   //x + 260, y
//	glColor3f(0, 0, 1);
//	glVertex2i(x + 300, y);  //colt dreapta jos  //x + 300, y
//	glColor3f(0, 1, 0);
//	glVertex2i(x + 300, y + 45); //dreapta sus   //x + 300, y + 45
//	glColor3f(1, 0, 0);
//	glVertex2i(x + 285, y + 60); //dreapta sus		//x + 285, y + 60
//	glColor3f(1, 0, 0);
//	glVertex2i(x + 200, y + 60);	//x + 200, y + 60
//	glColor3f(0, 0, 1);
//	glVertex2i(x + 150, y + 100);	//x + 150, y + 100
//	glColor3f(1, 0, 0);
//	glVertex2i(x + 20, y + 100);	//x + 20, y + 100
//	glColor3f(0, 1, 0);
//	glVertex2i(x - 20, y + 50);   //x - 20, y + 50
//	glColor3f(0, 0, 1);
//	glVertex2i(x - 20, y);	//x - 20, y
//	glEnd();
//
//}

void drawCar(float x, float y) {
	float scale = 2.5;  // Factorul de scalare pentru mărimea mașinii

	// Corpul principal al mașinii
	glColor3f(1.0, 0.0, 0.0); // Rosu
	glBegin(GL_POLYGON);
	glVertex2f(x, y); // Partea inferioară stânga
	glVertex2f(x + 80 * scale, y); // Partea inferioară dreapta
	glVertex2f(x + 75 * scale, y + 30 * scale); // Partea superioară dreapta, puțin mai mică pentru unghi
	glVertex2f(x, y + 30 * scale); // Partea superioară stânga
	glEnd();

	// Partea superioară / acoperișul mașinii
	glColor3f(1.0, 0.0, 0.0); // Rosu
	glBegin(GL_POLYGON);
	glVertex2f(x + 10 * scale, y + 30 * scale);
	glVertex2f(x + 70 * scale, y + 30 * scale);
	glVertex2f(x + 65 * scale, y + 60 * scale); // Coborâm un pic spre spate pentru unghiul acoperișului
	glVertex2f(x + 15 * scale, y + 60 * scale);
	glEnd();

	// Ferestrele mașinii
	glColor3f(0.86, 0.86, 0.86); // Culoare pentru ferestre 
	glBegin(GL_POLYGON);
	glVertex2f(x + 15 * scale, y + 30 * scale);
	glVertex2f(x + 25 * scale, y + 30 * scale);
	glVertex2f(x + 25 * scale, y + 50 * scale);
	glVertex2f(x + 15 * scale, y + 50 * scale);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(x + 30 * scale, y + 30 * scale);
	glVertex2f(x + 65 * scale, y + 30 * scale);
	glVertex2f(x + 65 * scale, y + 50 * scale);
	glVertex2f(x + 30 * scale, y + 50 * scale);
	glEnd();

	// Roțile mașinii
	glColor3f(0.0, 0.0, 0.0); // Negru pentru roți
	glPushMatrix();
	glTranslatef(x + 20 * scale, y, 0);
	circle(10 * scale); // Roata din față
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x + 60 * scale, y, 0);
	circle(10 * scale); // Roata din spate
	glPopMatrix();

	glColor3f(0.96, 0.96, 0.96); // Gri pentru jante (245/255 approximated to 0.96)
	glPushMatrix();
	glTranslatef(x + 20 * scale, y, 0);
	circle(6 * scale); // Janta roata din față
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x + 60 * scale, y, 0);
	circle(6 * scale); // Janta roata din spate
	glPopMatrix();
}



void drawVerticalCrosswalk(int startX, int startY, int endY, int lineWidth, int lineLength, int spaceBetween) {
	glColor3f(1.0, 1.0, 1.0); // Setează culoarea la alb
	for (int y = startY; y < endY; y += lineWidth + spaceBetween) {
		glBegin(GL_QUADS);
		glVertex2i(startX, y);
		glVertex2i(startX + lineLength, y);
		glVertex2i(startX + lineLength, y + lineWidth);
		glVertex2i(startX, y + lineWidth);
		glEnd();
	}
}

void drawComplexLampPost(int x, int y) {
	int postHeight = 200;  // Înălțimea stâlpului felinarului
	int baseHeight = 20;   // Înălțimea bazei stâlpului
	int lightRadius = 20;  // Raza luminii

	// Desenăm baza felinarului
	glColor3f(0.2f, 0.2f, 0.2f); // Gri închis pentru bază
	glBegin(GL_QUADS);
	glVertex2i(x - 10, y);
	glVertex2i(x + 17, y);
	glVertex2i(x + 17, y + baseHeight);
	glVertex2i(x - 10, y + baseHeight);
	glEnd();

	// Desenăm stâlpul felinarului
	glColor3f(0.3f, 0.3f, 0.3f); // Gri pentru stâlp
	glBegin(GL_QUADS);
	glVertex2i(x, y + baseHeight);
	glVertex2i(x + 7, y + baseHeight);
	glVertex2i(x + 7, y + baseHeight + postHeight);
	glVertex2i(x, y + baseHeight + postHeight);
	glEnd();


	// Desenăm coroana felinarului (partea superioară unde se află lumina)
	glColor3f(1.0f, 1.0f, 0.0f); // Galben pentru lumina
	glPushMatrix();
	glTranslatef(x + 2.5f, y + baseHeight + postHeight + 5, 0.0f);
	circle(lightRadius); // Lumina principală
	glPopMatrix();
}


void strada(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(-30, 720);    //x , y
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(-30, 80);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(2500, 80);    //x , y
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(2500, 720);
	glEnd();

	// Adăugăm linii întrerupte pe mijlocul străzii
	glLineWidth(2.0); // Lățimea liniilor
	glColor3f(1.0, 1.0, 1.0); // Culoarea liniilor (alb)

	glBegin(GL_LINES);
	for (int i = 0; i <= 2500; i += 100) {
		glVertex2i(i, 400); // Punct de început al unei linii întrerupte
		glVertex2i(i + 50, 400); // Punct de sfârșit al unei linii întrerupte
	}
	glEnd();
	glLineWidth(1.0); // Resetăm lățimea liniei la valoarea implicită

	glLineWidth(4.0); // Lățimea liniilor
	glColor3f(1.0, 1.0, 1.0); // Culoarea liniilor (alb)

	glBegin(GL_LINES);
	glVertex2i(-30, 720); // Linie albă pentru marginea superioară
	glVertex2i(2500, 720);

	glVertex2i(-30, 80); // Linie albă pentru marginea inferioară
	glVertex2i(2500, 80);
	glEnd();

	glLineWidth(1.0); // Resetăm lățimea liniei la valoarea implicită

	// Adăugăm trecerea de pietoni verticală
	int crosswalkStartX = 2100; // Poziția de start pe axa X pentru trecerea de pietoni
	int crosswalkWidth = 50; // Lățimea unei dungi de zebra
	int crosswalkLineLength = 250; // Lungimea dungiilor poate fi ajustată aici
	int crosswalkSpaceBetween = 35; // Spațiu între dungi

	drawVerticalCrosswalk(crosswalkStartX, 80, 720, crosswalkWidth, crosswalkLineLength, crosswalkSpaceBetween);

}


void spate(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.5, 0.0); // Verde pentru partea de jos
	glVertex2i(0, 0);
	glVertex2i(2500, 0);
	glVertex2i(2500, 900);
	glVertex2i(0, 900);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.3, 1.0); // Albastru pentru cerul de deasupra
	glVertex2i(0, 900);
	glVertex2i(2500, 900);
	glVertex2i(2500, 1800);
	glVertex2i(0, 1800);
	glEnd();


	// Începe să desenezi poligoanele pentru munți
	glBegin(GL_TRIANGLES);  // Folosim triunghiuri pentru a simplifica munții

	// Definirea culorilor pentru gradient
	float baseGreen[3] = { 0.0, 0.3, 0.0 };  // Verde închis la bază
	float midGreen[3] = { 0.0, 0.5, 0.0 };   // Verde mediu
	float topGreen[3] = { 0.1, 0.7, 0.1 };   // Verde deschis la vârf


	// Munte 1
	glColor3fv(baseGreen);
	glVertex2i(-500, 900);     // Baza stânga
	glColor3fv(topGreen);
	glVertex2i(400, 1300);  // Vârf
	glColor3fv(baseGreen);
	glVertex2i(800, 900);   // Baza dreapta

	// Munte 2
	glColor3fv(baseGreen);
	glVertex2i(600, 900);
	glColor3fv(topGreen);
	glVertex2i(1000, 1400);
	glColor3fv(baseGreen);
	glVertex2i(1400, 900);

	// Munte 4
	glColor3fv(baseGreen);
	glVertex2i(1500, 900);
	glColor3fv(topGreen);
	glVertex2i(2300, 1400);
	glColor3fv(baseGreen);
	glVertex2i(2800, 900);
	// Munte 3
	glColor3fv(baseGreen);
	glVertex2i(1200, 900);
	glColor3fv(topGreen);
	glVertex2i(1600, 1350);
	glColor3fv(baseGreen);
	glVertex2i(2000, 900);

	glEnd();



}

void addWindowFrame(int x1, int y1, int x2, int y2) {
	glColor3fv(woodColor);  // Setează culoarea la maro deschis pentru cadrele de lemn
	int frameWidth = 10;    // Lățimea cadrelor de lemn

	// Cadru exterior
	glBegin(GL_POLYGON);  // Stânga
	glVertex2i(x1 - frameWidth, y1 - frameWidth);
	glVertex2i(x1, y1 - frameWidth);
	glVertex2i(x1, y2 + frameWidth);
	glVertex2i(x1 - frameWidth, y2 + frameWidth);
	glEnd();

	glBegin(GL_POLYGON);  // Dreapta
	glVertex2i(x2, y1 - frameWidth);
	glVertex2i(x2 + frameWidth, y1 - frameWidth);
	glVertex2i(x2 + frameWidth, y2 + frameWidth);
	glVertex2i(x2, y2 + frameWidth);
	glEnd();

	glBegin(GL_POLYGON);  // Sus
	glVertex2i(x1, y2);
	glVertex2i(x2, y2);
	glVertex2i(x2, y2 + frameWidth);
	glVertex2i(x1, y2 + frameWidth);
	glEnd();

	glBegin(GL_POLYGON);  // Jos
	glVertex2i(x1, y1 - frameWidth);
	glVertex2i(x2, y1 - frameWidth);
	glVertex2i(x2, y1);
	glVertex2i(x1, y1);
	glEnd();

	// Cadru în formă de cruce
	int crossWidth = 5;  // Lățimea bării crucii
	int midX = (x1 + x2) / 2;  // Mijlocul ferestrei pe X
	int midY = (y1 + y2) / 2;  // Mijlocul ferestrei pe Y

	glBegin(GL_POLYGON);  // Verticală
	glVertex2i(midX - crossWidth, y1);
	glVertex2i(midX + crossWidth, y1);
	glVertex2i(midX + crossWidth, y2);
	glVertex2i(midX - crossWidth, y2);
	glEnd();

	glBegin(GL_POLYGON);  // Orizontală
	glVertex2i(x1, midY - crossWidth);
	glVertex2i(x2, midY - crossWidth);
	glVertex2i(x2, midY + crossWidth);
	glVertex2i(x1, midY + crossWidth);
	glEnd();
}


void bloc()
{
	glBegin(GL_POLYGON);
	glColor3f(0.623529, 0.623529, 0.372549);
	glVertex2i(300, 900);
	glColor3f(0.623529, 0.623529, 0.372549);
	glVertex2i(1100, 900);
	glColor3f(0.623529, 0.623529, 0.372549);
	glVertex2i(1100, 1700);
	glColor3f(0.623529, 0.623529, 0.372549);
	glVertex2i(300, 1700);
	glEnd();

	//ferestre

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(350, 1600);
	glVertex2i(450, 1600);
	glVertex2i(450, 1500);
	glVertex2i(350, 1500);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(550, 1600);
	glVertex2i(650, 1600);
	glVertex2i(650, 1500);
	glVertex2i(550, 1500);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(750, 1600);
	glVertex2i(850, 1600);
	glVertex2i(850, 1500);
	glVertex2i(750, 1500);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(950, 1600);
	glVertex2i(1050, 1600);
	glVertex2i(1050, 1500);
	glVertex2i(950, 1500);
	glEnd();

	//

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(350, 1400);
	glVertex2i(450, 1400);
	glVertex2i(450, 1300);
	glVertex2i(350, 1300);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(550, 1400);
	glVertex2i(650, 1400);
	glVertex2i(650, 1300);
	glVertex2i(550, 1300);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(750, 1400);
	glVertex2i(850, 1400);
	glVertex2i(850, 1300);
	glVertex2i(750, 1300);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(950, 1400);
	glVertex2i(1050, 1400);
	glVertex2i(1050, 1300);
	glVertex2i(950, 1300);
	glEnd();

	//

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(350, 1200);
	glVertex2i(450, 1200);
	glVertex2i(450, 1100);
	glVertex2i(350, 1100);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(550, 1200);
	glVertex2i(650, 1200);
	glVertex2i(650, 1100);
	glVertex2i(550, 1100);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(750, 1200);
	glVertex2i(850, 1200);
	glVertex2i(850, 1100);
	glVertex2i(750, 1100);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex2i(950, 1200);
	glVertex2i(1050, 1200);
	glVertex2i(1050, 1100);
	glVertex2i(950, 1100);
	glEnd();

	//usa

	 // Usă îmbunătățită
	glBegin(GL_POLYGON);
	glColor3f(0.33, 0.24, 0.11); // Maro închis pentru ușă
	glVertex2i(650, 900);
	glVertex2i(750, 900);
	glVertex2i(750, 1050);
	glVertex2i(650, 1050);
	glEnd();

	// Mânerul ușii
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.0); // Galben auriu pentru mâner
	glTranslatef(730, 975, 0);
	circle(5); // Funcția circle trebuie definită pentru a desena un cerc
	glPopMatrix();

	// Pragul ușii
	glLineWidth(5.0);
	glBegin(GL_LINES);

	glColor3f(0.2, 0.2, 0.2); // Gri închis pentru prag
	glVertex2i(620, 900);
	glVertex2i(780, 900);
	glEnd();

	glLineWidth(5.0);
	glBegin(GL_LINES);

	glColor3f(0.2, 0.2, 0.2); // Gri închis pentru prag
	glVertex2i(630, 915);
	glVertex2i(770, 915);
	glEnd();

	glLineWidth(1.0);  //resetarea liniei la latimea normala

	// Adaugă cadre pentru fiecare fereastră
	addWindowFrame(350, 1600, 450, 1500);
	addWindowFrame(550, 1600, 650, 1500);
	addWindowFrame(750, 1600, 850, 1500);
	addWindowFrame(950, 1600, 1050, 1500);
	addWindowFrame(350, 1400, 450, 1300);
	addWindowFrame(550, 1400, 650, 1300);
	addWindowFrame(750, 1400, 850, 1300);
	addWindowFrame(950, 1400, 1050, 1300);
	addWindowFrame(350, 1200, 450, 1100);
	addWindowFrame(550, 1200, 650, 1100);
	addWindowFrame(750, 1200, 850, 1100);
	addWindowFrame(950, 1200, 1050, 1100);


}

//functia care deseneaza soarele
void drawSun(float x, float y, float radius, int numRays) {
	// Desenează cercul central al soarelui
	int numSegments = 100;  // Numărul de segmente pentru un cerc mai rotund
	float angle;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 0.0f);  // Galben
	glVertex2f(x, y);  // Centru

	for (int i = 0; i <= numSegments; ++i) {
		angle = 2.0f * M_PI * float(i) / float(numSegments);
		glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
	}
	glEnd();

	// Desenează razele cu factorul de pulsare
	glColor3f(1.0f, 1.0f, 0.0f);  // Galben
	float modulatedRayLength = radius * 1.5 * sunPulseFactor;
	glBegin(GL_LINES);
	for (int i = 0; i < numRays; ++i) {
		angle = 2.0f * M_PI * float(i) / float(numRays);
		glVertex2f(x, y);
		glVertex2f(x + cos(angle) * modulatedRayLength, y + sin(angle) * modulatedRayLength);
	}
	glEnd();
}

void updateSun() {
	if (sunPulseFactor >= 1.2)
		sunPulseFactor = 1.0;
	else
		sunPulseFactor += 0.05;

	glutPostRedisplay();
}

void drawCloud(float x, float y, float scale) {
	// Creăm nori cu mai multe cercuri pentru a oferi volum
	glColor3f(0.9f, 0.9f, 0.9f);  // Alb-gri deschis
	glPushMatrix();
	glTranslatef(x, y, 0);
	circle(30 * scale);
	glTranslatef(30 * scale, 10 * scale, 0);
	circle(40 * scale);
	glTranslatef(30 * scale, -10 * scale, 0);
	circle(30 * scale);
	glTranslatef(-45 * scale, -20 * scale, 0);
	circle(20 * scale);
	glTranslatef(30 * scale, 0, 0);
	circle(25 * scale);
	glPopMatrix();
}

void drawBird(float x, float y, float scale) {
	glBegin(GL_TRIANGLES);
	// Aripa stângă
	glColor3f(0.0f, 0.0f, 0.0f);  // Negru
	glVertex2f(x, y);  // Vârful aripii stângi
	glVertex2f(x - 20 * scale, y + 10 * scale);  // Colțul interior al aripii stângi
	glVertex2f(x - 10 * scale, y - 10 * scale);  // Baza aripii stângi

	// Aripa dreaptă
	glVertex2f(x, y);  // Vârful aripii drepte
	glVertex2f(x + 20 * scale, y + 10 * scale);  // Colțul interior al aripii drepte
	glVertex2f(x + 10 * scale, y - 10 * scale);  // Baza aripii drepte

	// Coada
	glVertex2f(x, y);  // Vârful cozii
	glVertex2f(x - 10 * scale, y - 10 * scale);  // Colțul stâng al cozii
	glVertex2f(x + 10 * scale, y - 10 * scale);  // Colțul drept al cozii

	glEnd();
}
void updateCloudsAndBirds() {
	// Actualizează poziția norilor
	cloudPosition += cloudSpeed;
	if (cloudPosition > 2500)
		cloudPosition = -600.0;

	// Actualizează poziția păsărilor
	birdPositionX += birdSpeed;
	if (birdPositionX > 2500)
		birdPositionX = -600.0;


	glutPostRedisplay();
}

bool carsMoving = false;  // Inițial mașinile nu se mișcă

void idleHandler(void) {
	updateCloudsAndBirds();
	// Actualizare pulsatie soare
	if (sunPulsing) {
		updateSun();
	}

	// Verifică dacă mașinile trebuie să se miște
	if (carsMoving) {
		i += alpha;
		if (i > 70000.0 || i < 0.0)
			alpha = -alpha;  // Inversează direcția dacă depășește limitele
		if (k < 320)
			k += alpha;
		a += 1.2;
	}


	glutPostRedisplay(); // Apelare desenare scena actualizata
}


//functia care deseneaza scene 
void deseneazaScena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  //curata fereastra
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//deseneaza background-ul strada si blocul
	spate();
	strada();
	bloc();

	// Felinare plasate la intervale de 1000 de unități, începând de la 120 și terminând la 2450
	for (int x = 120; x < 2500; x += 800) {
		drawComplexLampPost(x, 720);
	}

	// Desenăm primul copac în stânga blocului
	glPushMatrix();
	glTranslatef(-1070, 0, 0); // Poziționează primul copac la stânga blocului
	fancyTree(300, 30, 80);
	glPopMatrix();

	// Desenăm al doilea copac în dreapta blocului
	glPushMatrix();
	glTranslatef(-150, 0, 0); // Poziționează al doilea copac la dreapta blocului
	fancyTree(300, 30, 80);
	glPopMatrix();


	drawSun(2300, 1600, 100, 30);  // Desenează soarele cu 30 de raze
	// Desenează norii animați
	drawCloud(cloudPosition, 1700, 1.5f); // Norul mare
	drawCloud(cloudPosition + 400, 1750, 1.0f); // Norul mai mic
	drawCloud(cloudPosition + 600, 1650, 2.0f);

	// Desenează păsările
	drawBird(birdPositionX, birdPositionY, 2.0f);
	drawBird(birdPositionX + 80, birdPositionY - 50, 1.5f);
	drawBird(birdPositionX + 150, birdPositionY - 100, 1.0f);


	glPopMatrix();
	glPushMatrix();
	glTranslated(i - 200, 0, 0);

	drawCar(600, 200);
	glTranslated(a, k, 0);
	drawCar(150, 200);
	glPopMatrix();


	glutSwapBuffers();

	glFlush();
}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 2500.0, 0.0, 1800, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscad(void)
{
	i = i + alpha;
	if (i > 70000.0)
		alpha = -1;
	else if (i < 0.0)
		alpha = 1;
	j = j + alpha;
	if (k < 320)
		k = k + alpha;
	a = a + 1.2;


	glutPostRedisplay();
}

void miscas(void)
{
	i = i + alpha;
	if (i < 0.0)
		alpha = 1;
	else if (i > 70000.0)
		alpha = -1;
	j = j + alpha;

	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
	//switch (button) {
	//case GLUT_LEFT_BUTTON:
	//	if (state == GLUT_DOWN)
	//	{
	//		alpha = -1; glutIdleFunc(miscas);

	//	}
	//	break;
	//case GLUT_RIGHT_BUTTON:
	//	if (state == GLUT_DOWN)
	//	{
	//		alpha = 1; glutIdleFunc(miscad);

	//	}
	//	break;
	//default:
	//	break;
	//}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Transforma coordonatele mouse-ului
		float mx = x * (2500.0 / glutGet(GLUT_WINDOW_WIDTH));
		float my = (glutGet(GLUT_WINDOW_HEIGHT) - y) * (1800.0 / glutGet(GLUT_WINDOW_HEIGHT));

		// Verifica dacă click-ul este pe soare
		if (mx > 2200 && mx < 2400 && my > 1600 && my < 1800) {
			sunPulsing = !sunPulsing;


			//if (sunPulsing) {
			//	glutIdleFunc(updateSun);
			//}
			//else {
			//	glutIdleFunc(NULL);
			//	sunPulseFactor = 1.0;  // Resetează factorul de pulsare la normal
			//	glutPostRedisplay();
			//}
		}
		else {
			carsMoving = !carsMoving;  // Toggle starea de mișcare a mașinilor
			alpha = (button == GLUT_LEFT_BUTTON) ? -1 : 1;  // Setează direcția în funcție de butonul apăsat
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		carsMoving = !carsMoving;  // Toggle starea de mișcare a mașinilor
		alpha = (button == GLUT_LEFT_BUTTON) ? -1 : 1;
	}

}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Depasire");

	init();
	glutDisplayFunc(deseneazaScena);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idleHandler);
	glutMainLoop();
}