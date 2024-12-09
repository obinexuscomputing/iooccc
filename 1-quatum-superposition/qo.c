#include<complex.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#define P(...) printf(__VA_ARGS__)
#define C(x) cos(x)
#define S(x) sin(x)
#define M(a,b) fmax(a,b)
#define $(n) n*M_PI/180.
#define E(s,n) s##n
#define N(x) case x:return
#define F(a,b) for(int a=0;a<b;a++)
#define O return
#define B break;
#define W while
#define __ ;

typedef double d;
typedef double complex c;

int q(d x){
    x-=360;
    W(x>=360)x-=360;
    W(x<0)x+=360;
    O x;
}

int k(int x){O((1<<4)|8)>>x&1;}

char*h(int n){
    switch(n){
        N(0)"░";
        N(1)"▒";
        N(2)"▓";
        N(3)"█";
    }O"";
}

struct E(s,_){
    int t;
    c a;
    d p,h;
};

void V(int x,c*r){
    *r=csqrt(x)*cexp(_Complex_I*$(x));
}

d U(d x,d y){O M(x,y);}

void E(_,c)(struct E(s,_)*t,int n){
    F(i,4){
        d r=.25+.15*S((n+i)*M_PI/4)*C((n+i)*M_PI/8)+.1*((rand()%100)/100.-0.5);
        t[i].p=M(r,.05);
    }
    d s=0;
    F(i,4){
        int j=(i+1)%4;
        d f=C(fabs(t[i].h-t[j].h)*M_PI/180)*.1;
        t[i].p+=f;
        t[j].p-=f;
    }
    F(i,4)s+=t[i].p;
    F(i,4){
        t[i].p/=s;
        d b=60+20*S(n*M_PI/3)+(rand()%20)-10;
        t[i].h=q(t[i].h+b);
        V(t[i].p,&t[i].a);
    }
}

void E(_,v)(struct E(s,_)*t){
    P("\nState Distribution:\n");
    d m=0;
    F(i,4)m=U(m,t[i].p);
    F(i,4){
        P("  |%d%d> ",k(t[i].t>>1),k(t[i].t));
        int l=40*t[i].p/m;
        F(j,l)P("%s",h(j*4/l));
        P(" %.3f ∠%.0f°\n",t[i].p,t[i].h);
    }
    P("\n");
}

int main(){
    srand(time(0));
    struct E(s,_)t[]={{0,.5,0.25,0},{1,.5,.25,90},
                      {2,.5,.25,180},{3,.5,.25,270}};
    P("Quantum Superposition\n==================\n");
    F(i,5){
        P("\nStep %d:\n",i+1);
        E(_,c)(t,i+1);
        E(_,v)(t);
    }
    O 0;
}