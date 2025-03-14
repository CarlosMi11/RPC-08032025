#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>


using namespace std;

#define AreaDeTrianguloLado1 0.433012701892
#define DistaceBetween(a,b) (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)))


struct point{
    double x, y;
    point (){
        x = y = 0;
    }
    point (double e, double i){
        x = e;
        y = i;
    }
    void set(double e, double i){
        x = e;
        y = i;
    }
};


double areaOf(vector<point> poligono){
    //calcula el volumen de una figura formada por las rectas que se forman al conectar los puntos en orden
    //debe ser un poligono cerrado (ya lo es por definicion) y no se deben cruzar los lados
    //ej: estrella, cuadrado, panal de abejas contando solo el perimetro
    double area = 0;
    for(int i = 0; i < poligono.size(); i++){
        area += (poligono[i%poligono.size()].x * poligono[(i+1)%poligono.size()].y) - (poligono[i%poligono.size()].y * poligono[(i+1)%poligono.size()].x);
    }
    return -0.5*area;
}


double areaWithScale(double area, vector<double> originalLines, double alfa = 1, int n = 11){
    if(n == 0){
        return area;
    }
    double areasOfChilds = 0;


    for(int i = 0; i < originalLines.size(); i++){
        double newLineSize = alfa * originalLines[i];
        areasOfChilds += areaWithScale(area * pow(newLineSize,2), originalLines, newLineSize, n-1);
    }


    return areasOfChilds + area;
}

double areaOfFractal(vector<point> poligono){
    double areaOfFirstIteration = areaOf(poligono);
    vector<double> LineSizes;
    
    for(int i = 0; i < poligono.size() - 1; i++){
        LineSizes.push_back(DistaceBetween(poligono[i%poligono.size()], poligono[(i+1)%poligono.size()]));


        //cout<<setprecision(1)<<poligono[i%poligono.size()].x<<" "<<poligono[i%poligono.size()].y<<"  ";
        //cout<<setprecision(1)<<poligono[(i+1)%poligono.size()].x<<" "<<poligono[(i+1)%poligono.size()].y<<endl;
        //cout<<DistaceBetween(poligono[i%poligono.size()], poligono[(i+1)%poligono.size()])<<endl;
    }

    
    
    double fractalArea = areaWithScale(areaOfFirstIteration, LineSizes);
    return fractalArea;
}


int main(){
    vector<point> cuadrado;
    point p;
    int n; cin>>n;
    
    
    for(int i = 0; i < n; i++){
        cin>>p.x>>p.y;
        cuadrado.push_back(p);
    }
    
    
    cout<<areaOfFractal(cuadrado)*3.0 + AreaDeTrianguloLado1<<endl;
}
/*
5
0.000000 0.000000
0.200000 0.000000
0.600000 -0.200000
0.500000 0.000000
1.000000 0.000000

5
0.000000 0.000000
0.333333 0.000000
0.500000 0.288675
0.666667 0.000000
1.000000 0.000000
*/