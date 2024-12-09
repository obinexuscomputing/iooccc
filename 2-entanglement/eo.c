#include<complex.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define P(...) printf(__VA_ARGS__)
#define R (rand()%100)
#define F(n) for(int i=0;i<n;i++)
#define J(n) for(int j=0;j<n;j++)
#define W while
#define PI M_PI
#define _(x) return x
typedef double d;
typedef double complex c;

struct q{int s,e,b;c a;d p,h;};

void s(d*x){W(*x>=360)*x-=360;W(*x<0)*x+=360;}

const char*g(int n){
    switch(n){
        case 0:return "\xe2\x96\x91";
        case 1:return "\xe2\x96\x92";
        case 2:return "\xe2\x96\x93";
        case 3:return "\xe2\x96\x88";
    }return " ";
}

void z(struct q*t){
    t[0].e=3;t[3].e=0;t[1].e=2;t[2].e=1;
    t[0].b=t[3].b=0;t[1].b=t[2].b=1;
    F(4){t[i].p=.25;t[i].h=(i%2)*180;}
}

void e(struct q*t,int n){d v=0;
    F(2){int p=i*2,q=p+1;d u=n*PI/4;
    d r=.25+.15*sin(u)*cos(u/2)+.1*((d)R/100.-.5);
    t[p].p=t[q].p=fmax(r,.05);v+=t[p].p*2;
    d h=60+20*sin(n*PI/3)+(R%20)-10;
    t[p].h+=h;t[q].h+=h+180;s(&t[p].h);s(&t[q].h);}
    F(4){t[i].p/=v;t[i].a=sqrt(t[i].p)*cexp(I*t[i].h*PI/180);}
}

void v(struct q*t){
    P("\nBell States:\n");d x=0;F(4)x=fmax(x,t[i].p);
    F(4){
        P("%c|%d%d>%s",(i%2?32:124),(t[i].s>>1)&1,t[i].s&1,
          t[i].e>i?"\xe2\x8a\x97":" ");
        int l=40*t[i].p/x;l=fmax(l,1);
        J(l)P("%s",g(j*4/l));
        P(" %.3f \xe2\x88\xa0%.0f\xc2\xb0 %s%d\n",t[i].p,t[i].h,
          t[i].b?"Ψ":"Φ",t[i].b+1);
        if(i&1)P("\n");
    }
}

int main(){
    srand(time(0));
    struct q t[4];F(4){t[i].s=i;t[i].a=.5;t[i].p=.25;t[i].h=i*90;}
    P("Entangled Quantum States\n=====================\n");
    z(t);F(5){P("\nStep %d:\n",i+1);e(t,i+1);v(t);}_(0);
}