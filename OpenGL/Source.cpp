#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <iostream>
#include <vector>

using namespace std;

struct coordpct
{
	int x, y;
};
struct segment
{
	float xa;
	float xb;
	float ya;
	float yb;
};
segment ab;
segment cd;
vector<coordpct> v;
vector<bool> l;
int punct_x[200];
int punct_y[200];
int n = 0;
void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void intersect(segment x, segment y)
{
	float m = (x.yb - x.ya) / (x.xb - x.xa);
	float n = x.ya - x.xa*m;
	float m1 = (y.yb - y.ya) / (y.xb - y.xa);
	float n1 = y.ya - y.xa*m1;
	float xint = (n1 - n) / (m - m1);
	float yint = (xint*m + n);
	cout << xint << ";" << yint;

}
bool intersectie(coordpct a, coordpct b, coordpct c, coordpct d)
{
	float ec1 = (b.y - a.y) * c.x + (a.x - b.x) * c.y + a.y * b.x - a.x * b.y;
	float ec2 = (b.y - a.y) * d.x + (a.x - b.x) * d.y + a.y * b.x - a.x * b.y;
	if (ec1 * ec2 >= 0)
		return false;
	else return true;
}

void desen() // procedura desenare  
{
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < v.size() - 1; i++) {
		if (!l[i]) {
			glVertex2i(v[i].x, v[i].y);
			glVertex2i(v[i + 1].x, v[i + 1].y);
		}
	}

	glColor3f(1.0, 0.5, 0.0);
	for (int i = 0; i < v.size() - 1; i++) {
		if (l[i]) {
			glVertex2i(v[i].x, v[i].y);
			glVertex2i(v[i + 1].x, v[i + 1].y);
		}
	}
	glEnd();
	glFlush();
}
void desen2()
{
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(ab.xa, ab.ya);
	glVertex2i(ab.xb, ab.yb);
	glVertex2i(cd.xa, cd.ya);
	glVertex2i(cd.xb, cd.yb);
	glEnd();
	glFlush();

}
/*void dau_click(int buton, int stare, int x, int y) //x si y din acea scena reprezinta coordonatele cursorului care vor fi stocate intr-un vector
{
if (buton == GLUT_LEFT_BUTTON && stare == GLUT_DOWN)
{
cout << buton << ' ' << stare << ' ' << x << ' ' << y << endl;
punct_x[n] = x;
//punct_y[n]=y;  daca ar fi asa, am avea pe oY inversat deoarece porneste din coltul de jos; ar trebui sa scadem dimensiunea pe
punct_y[n] = 800 - y;
n++;
}
}*/
void main(int argc, char** argv)
{
	int nr_prob;
	cout << "Problema 1 sau 2";
	cin >> nr_prob;
	if (nr_prob == 1)
	{
		cout << "introduceti coordonatele A";
		cin >> ab.xa;
		cin >> ab.ya;
		cout << "Introduceti coordonatele B";
		cin >> ab.xb;
		cin >> ab.yb;
		cout << "Introduceti coordonatele C";
		cin >> cd.xa;
		cin >> cd.ya;
		cout << "Introduceti coordonatele D";
		cin >> cd.xb;
		cin >> cd.yb;

		intersect(ab, cd);
		glutInit(&argc, argv); // initializare GLUT
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
		glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
		glutInitWindowSize(800, 600); // dimensiunile ferestrei 
		glutCreateWindow("Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

		init(); // executa procedura de initializare
		glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
		glutDisplayFunc(desen2); // procedura desen este invocata ori de cate ori este nevoie
								 //glutMouseFunc(dau_click);
		glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	}
	else if (nr_prob == 2)
	{
		int nr_varf;
		coordpct p;
		cin >> nr_varf;
		for (int i = 0; i < nr_varf; i++)
		{
			cin >> p.x;
			cin >> p.y;
			v.push_back(p);
			l.push_back(false);
		}

		for (int i = 0; i < v.size() - 2; i++) {
			for (int j = i + 2; j < l.size() - 1; j++) {
				l[i] = l[j] = intersectie(v[i], v[i + 1], v[j], v[j + 1]);
			}
		}

		glutInit(&argc, argv); // initializare GLUT
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
		glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
		glutInitWindowSize(800, 600); // dimensiunile ferestrei 
		glutCreateWindow("Segmente"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

		init(); // executa procedura de initializare
		glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
		glutDisplayFunc(desen); // procedura desen este invocata ori de cate ori este nevoie
								//glutMouseFunc(dau_click);
		glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
	}

}