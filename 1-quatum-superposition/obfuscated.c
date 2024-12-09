#define Z(n)for(int i=0;i<n;i++)
#define W while
#define R (rand()%100)
#define G(n)(R*1./n)
#define D double
#define V void
#define O return
#define P(...) printf(__VA_ARGS__)
#define H(x) P("%c%c%c",226,150,x)
#define DEG "\xc2\xb0"
typedef struct{int s;D _Complex a;D p,h;}q;
#include<complex.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
V _(q*t,int n){D o=0,v;Z(4){D w=.25+
.15*sin((n+i)*M_PI/4)*cos((n+i)*M_PI/8),
u=.1*(G(100)-.5);t[i].p=fmax(w+u,.05),o+=t[i].p;}Z(4){int 
j=(i+1)%4;D d=fabs(t[i].h-t[j].h)*M_PI/180,f=cos(d)*.1;t[i].p+=f,
t[j].p-=f;}v=0;Z(4)v+=t[i].p;Z(4){t[i].p/=v;D b=60+20*sin(n*M_PI/3)+
G(20)-10;t[i].h+=b;W(t[i].h>=360)t[i].h-=360;W(t[i].h<0)t[i].h+=360;
t[i].a=sqrt(t[i].p)*cexp(t[i].h*M_PI/180*_Complex_I);}}V m(q*t){P(
"\nState Distribution:\n");D x=0;Z(4)x=fmax(x,t[i].p);Z(4){P("  |%d%d> ",
(t[i].s>>1)&1,t[i].s&1);int l=t[i].p/x*40;for(int j=0;j<l;j++)H(j<l/4?
145:j<l/2?146:j<3*l/4?147:136);P(" %.3f \u2220%.0f%s\n",t[i].p,t[i].h,DEG);
}P("\n");}int main(){srand(time(0));q t[]={{0,.5,0.25,0},{1,.5,.25,90},
{2,.5,.25,180},{3,.5,.25,270}};P("\x1b[1;36mQuantum Superposition"
"\n==================\n\x1b[0m");Z(5){P("\n\x1b[1;33mStep %d:\x1b[0m\n",
i+1);_(t,i+1);m(t);}O 0;}