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

struct q{int s;c a;d p,h;d f;};  // Added frequency for interference

const char*g(int n){
    switch(n){
        case 0:return "\xe2\x96\x91";
        case 1:return "\xe2\x96\x92";
        case 2:return "\xe2\x96\x93";
        case 3:return "\xe2\x96\x88";
    }return " ";
}

void s(d*x){W(*x>=360)*x-=360;W(*x<0)*x+=360;}

void z(struct q*t){
    F(4){
        t[i].s=i;
        t[i].p=0.25;
        t[i].h=i*90.0;
        t[i].f=(i+1)*PI/4;  // Different frequencies for interference
    }
}

void i(struct q*t,int n){
    d v=0;
    
    // Generate interference pattern
    F(4){
        d u=n*t[i].f;
        d w1=sin(u)*cos(u/2);  // First wave
        d w2=cos(u)*sin(u/3);  // Second wave
        d w3=sin(u/2)*cos(u/4); // Third wave
        
        // Combine waves with phase-dependent interference
        t[i].p=0.25+0.1*(w1+w2+w3)*cos(t[i].h*PI/180);
        t[i].p=fmax(t[i].p,0.05);
        v+=t[i].p;
        
        // Phase evolution with interference effects
        d dh=45+15*sin(u)+10*cos(u/2)+(R%20)-10;
        t[i].h+=dh;
        s(&t[i].h);
    }
    
    // Apply interference between states
    F(4){
        int n1=(i+1)%4;
        int n2=(i+2)%4;
        d dp=0.05*sin((t[i].h-t[n1].h)*PI/180);
        dp+=0.03*cos((t[i].h-t[n2].h)*PI/180);
        t[i].p+=dp;
    }
    
    // Normalize and update amplitudes
    v=0;F(4)v+=t[i].p;
    F(4){
        t[i].p/=v;
        t[i].a=sqrt(t[i].p)*cexp(I*t[i].h*PI/180);
    }
}

void v(struct q*t){
    P("\nInterference Pattern:\n");
    d x=0;F(4)x=fmax(x,t[i].p);
    
    F(4){
        P("|%d%d> ",(t[i].s>>1)&1,t[i].s&1);
        int l=40*t[i].p/x;l=fmax(l,1);
        J(l)P("%s",g(j*4/l));
        P(" %.3f \xe2\x88\xa0%.0f\xc2\xb0 ",t[i].p,t[i].h);
        // Show interference pattern
        P("~%.2f\n",sin(t[i].f)*cos(t[i].h*PI/180));
    }P("\n");
}

int main(){
    srand(time(0));
    struct q t[4];
    P("Quantum Interference\n===================\n");
    z(t);F(5){P("\nStep %d:\n",i+1);i(t,i+1);v(t);}_(0);
}