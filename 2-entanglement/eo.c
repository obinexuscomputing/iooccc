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
struct q{int s,e,b;c a;d p,h;}_;
char*B="ΦΨ",*g="░▒▓█";d m(d x,d y){_(x>y?x:y);}
void w(d*p){W(*p>=360)*p-=360;W(*p<0)*p+=360;}
void z(struct q*t){t[0].e=3;t[3].e=0;t[1].e=2;t[2].e=1;
t[0].b=t[3].b=0;t[1].b=t[2].b=1;F(4){t[i].p=.25;t[i].h=(i%2)*180.;}}
void e(struct q*t,int n){d v=0;F(2){int p=i*2,q=p+1;d u=n*PI/4,
r=.25+.1*sin(u)*cos(u/2)+.1*(G(100)/100.-.5);t[p].p=t[q].p=m(r,.05);
v+=t[p].p*2;d h=60+20*sin(n*PI/3)+(R%20)-10;t[p].h+=h;t[q].h+=h+180;
w(&t[p].h);w(&t[q].h);}F(4){t[i].p/=v;t[i].a=sqrt(t[i].p)*cexp(I*$(t[i].h));}}
void v(struct q*t){P("\n%s+/%s+ States:\n",B,B+2);d x=0;F(4)x=m(x,t[i].p);
F(4){P("%c|%d%d>%c",(i%2?32:124),(t[i].s>>1)&1,t[i].s&1,t[i].e>i?4*16:32);
int l=40*t[i].p/x;l=m(l,1);F(l)P("%s",G(j,l/4,g));
P(" %.3f ∠%.0f° %s+\n",t[i].p,t[i].h,B+t[i].b);
if(i&1)P("\n");}}int main(){srand(time(0));struct q t[4];
F(4){t[i].s=i;t[i].a=.5;t[i].p=.25;t[i].h=i*90;}
P("Bell State Evolution\n=================\n");z(t);
F(5){P("\nStep %d:\n",i+1);e(t,i+1);v(t);}_(0);}