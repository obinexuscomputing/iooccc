#include<complex.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define P(...) printf(__VA_ARGS__)
#define G(x,y,z) ((x)<(y)?(z[0]):(x)<(y*2)?(z[1]):(x)<(y*3)?(z[2]):(z[3]))
#define R (rand()%100)
#define F(n) for(int i=0;i<n;i++)
#define W while
#define PI M_PI
#define _(x) return x
#define $(x) ((x)*PI/180.)
typedef double d;
typedef double complex c;
struct q{int s;c a;d p,h;}_;
char*b="░▒▓█";d m(d x,d y){_(x>y?x:y);}
void w(d*p,int n,d f){W(*p>=f)*p-=f;W(*p<0)*p+=f;}
void e(struct q*t,d*h,int n){
    d z[4],v=0;F(4){d u=PI/4,k=PI/8;
    z[i]=.25+.15*sin((n+i)*u)*cos((n+i)*k);
    z[i]+=0.1*((d)R/100-.5);
    t[i].p=m(z[i],.05);v+=t[i].p;}F(4){
    int j=(i+1)%4;d f=cos(fabs(t[i].h-t[j].h)*$/180)*.1;
    t[i].p+=f;t[j].p-=f;}d s=0;F(4)s+=t[i].p;
    F(4){t[i].p/=s;d r=60+20*sin(n*PI/3)+(R%20)-10;
    t[i].h+=r;w(&t[i].h,0,360);
    t[i].a=sqrt(t[i].p)*cexp(_Complex_I*$(t[i].h));}}
void v(struct q*t){P("\nState Distribution:\n");d x=0;
F(4)x=m(x,t[i].p);F(4){P("  |%d%d> ",(t[i].s&2)>>1,t[i].s&1);
int l=40*t[i].p/x;F(l)P("%s",G(i,l/4,b));
P(" %.3f ∠%.0f°\n",t[i].p,t[i].h);}P("\n");}
int main(){srand(time(0));struct q t[]={{0,.5,.25,0},
{1,.5,.25,90},{2,.5,.25,180},{3,.5,.25,270}};
P("Quantum Superposition\n==================\n");
F(5){P("\nStep %d:\n",i+1);e(t,0,i+1);v(t);}_(0);}