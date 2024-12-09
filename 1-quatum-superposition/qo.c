#include<complex.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#define P(...) printf(__VA_ARGS__)
#define D(x) for(int i=0;i<x;i++)
#define R (rand()%100)
#define PI M_PI
typedef double d;
typedef double complex c;

struct q{
    int s;  // state
    c a;    // amplitude
    d p,h;  // probability, phase
};

const char *g(int n){
    switch(n){
        case 0: return "░";
        case 1: return "▒";
        case 2: return "▓";
        case 3: return "█";
    }
    return "";
}

void s(d*x){
    if(*x>=360)*x-=360;
    if(*x<0)*x+=360;
}

void e(struct q*t,int n){
    d total=0;
    
    // Generate base probabilities
    D(4){
        t[i].p=0.25+0.1*sin((n+i)*PI/4)*cos((n+i)*PI/8);
        t[i].p=fmax(t[i].p,0.05);
        total+=t[i].p;
    }
    
    // Apply interference
    D(4){
        int next=(i+1)%4;
        d phi=fabs(t[i].h-t[next].h)*PI/180;
        d intf=cos(phi)*0.1;
        t[i].p+=intf;
        t[next].p-=intf;
    }
    
    // Normalize and evolve
    total=0;
    D(4)total+=t[i].p;
    
    D(4){
        t[i].p/=total;
        t[i].h+=60+20*sin(n*PI/3)+(R%20)-10;
        s(&t[i].h);
        t[i].a=sqrt(t[i].p)*cexp(I*t[i].h*PI/180);
    }
}

void v(struct q*t){
    P("\nState Distribution:\n");
    
    // Find max probability
    d max_p=0;
    D(4)max_p=fmax(max_p,t[i].p);
    
    // Display states
    D(4){
        P("  |%d%d> ",(t[i].s>>1)&1,t[i].s&1);
        int len=(int)(40*t[i].p/max_p);
        len=fmax(len,1);
        
        for(int j=0;j<len;j++){
            P("%s",g(j*4/len));
        }
        P(" %.3f ∠%.0f°\n",t[i].p,t[i].h);
    }
    P("\n");
}

int main(){
    srand(time(0));
    
    // Initialize quantum states
    struct q t[4];
    for(int i=0;i<4;i++){
        t[i].s=i;
        t[i].a=0.5;
        t[i].p=0.25;
        t[i].h=i*90.0;
    }
    
    P("Quantum Superposition\n==================\n");
    
    // Evolution steps
    D(5){
        P("\nStep %d:\n",i+1);
        e(t,i+1);
        v(t);
    }
    return 0;
}