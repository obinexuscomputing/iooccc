#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<complex.h>
#define $ double
#define _ return
#define X(x) printf(x)
#define Y(f,...) printf(f,__VA_ARGS__)
#define L(n) for(int i=0;i<n;i++)
#define W(c) while(c)
#define A(x) fabs(x)
#define M(a,b) fmax(a,b)
#define R (rand()%100)
#define G ($)R/100
#define K complex
typedef struct{int s;$ K a;$ p,h;}Q;
void z(Q*t,int n){$ o=0;L(4){
$ w=.25+.15*sin((n+i)*M_PI/4)*cos((n+i)*M_PI/8);
$ u=.1*(G-.5);t[i].p=M(w+u,.05);o+=t[i].p;}L(4){
int j=(i+1)%4;$ d=A(t[i].h-t[j].h)*M_PI/180;
$ f=cos(d)*.1;t[i].p+=f;t[j].p-=f;}$ v=0;L(4)v+=t[i].p;
L(4){t[i].p/=v;$ b=60+20*sin(n*M_PI/3)+(R%20)-10;
t[i].h+=b;W(t[i].h>=360)t[i].h-=360;W(t[i].h<0)t[i].h+=360;
t[i].a=sqrt(t[i].p)*cexp(t[i].h*M_PI/180*_Complex_I);}}
void v(Q*t){X("\nState Distribution:\n");$ x=0;L(4)x=M(x,t[i].p);
L(4){Y("  |%d%d> ",t[i].s>>1&1,t[i].s&1);int l=t[i].p/x*40;
for(int j=0;j<l;j++)X(j<l/4?"\xe2\x96\x91":j<l/2?"\xe2\x96\x92":
j<3*l/4?"\xe2\x96\x93":"\xe2\x96\x88");Y(" %.3f %c%.0f%c\n",
t[i].p,'^',t[i].h,248);}X("\n");}
int main(){srand(time(0));Q t[]={{0,.5,0.25,0},
{1,.5,0.25,90},{2,.5,0.25,180},{3,.5,0.25,270}};
X("Quantum Superposition\n==================\n");
L(5){Y("\nStep %d:\n",i+1);z(t,i+1);v(t);}_ 0;}