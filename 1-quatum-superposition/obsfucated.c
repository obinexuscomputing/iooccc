#define Q(x,y)int*_##x##y
#define Z(n)*(int*)&n
#define R rand()
#define E(x)expl(x)
#define C(x)cosl(x)
#define S(x)sinl(x)
#define P printf
#include<complex.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define O return
#define V void
#define D double
#define B(x,y)P(#x#y)
#define F for
#define W while
#define I if
typedef struct{int s;D complex a;D p,h;}q;V 
_(q*t,int n){D l=0;F(int i=0;i<4;i++){D 
w=.25+.15*S((n+i)*M_PI/4)*C((n+i)*M_PI/8);D 
u=.1*((D)(R%100)/100-.5);t[i].p=fmax(w+u,.05);l+=t[i].p;}F(int 
i=0;i<4;i++){int j=(i+1)%4;D d=fabs(t[i].h-t[j].h)*M_PI/180;D 
f=C(d)*.1;t[i].p+=f;t[j].p-=f;}D o=0;F(int 
i=0;i<4;i++)o+=t[i].p;F(int i=0;i<4;i++){t[i].p/=o;D 
b=60+20*S(n*M_PI/3)+(R%20)-10;t[i].h+=b;W(t[i].h>=360)t[i].h-=360;W(t[i].h<0)t[i].h+=360;t[i].a=sqrt(t[i].p)*
cexp(I*t[i].h*M_PI/180);}}V m(q*t){P("\nState Distribution:\n");D 
x=0;F(int i=0;i<4;i++)x=fmax(x,t[i].p);F(int 
i=0;i<4;i++){P("  |%d%d⟩ ",t[i].s>>1&1,t[i].s&1);int 
l=t[i].p/x*40;F(int j=0;j<l;j++)P("%s",j<l/4?"░":j<l/2?"▒":j<3*l/4?"▓":"█");P(" 
%.3f ∠%.0f°\n",t[i].p,t[i].h);}P("\n");}int main(){srand(time(0));q 
t[]={{0,.5,0.25,0},{1,.5,0.25,90},{2,.5,0.25,180},{3,.5,0.25,270}};P("Quantum 
Superposition\n==================\n");F(int 
i=1;i<6;i++){P("\nStep %d:\n",i);_(t,i);m(t);}O 0;}