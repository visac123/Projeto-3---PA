#include "sculptor.h"
#include <iostream>
using namespace std;


sculptor::sculptor(int _nx, int _ny, int _nz)
{
    nx=_nx;
    ny=_ny;
    nz=_nz;

    v= new Voxel**[nx];
    v[0]= new Voxel*[nx*ny] ;
    v[0][0]= new Voxel[nx*ny*nz];


    for (int i=0;i<nx;i++){
        if(i<(nx-1)){
            v[i+1]= v[i] + ny;
        }
        for (int j=0;j<ny;j++){
            if((j==(ny-1))&&(i!=(nx-1))){
                v[i+1][0]= v[i][j] + nz;
            }
            else{
                v[i][j+1]= v[i][j] + nz;
            }

            for(int k=0;k<nz;k++){
                v[i][j][k].r=0.0;
                v[i][j][k].g=0.0;
                v[i][j][k].b=0.0;
                v[i][j][k].a=0.0;
                v[i][j][k].isOn=false;
            }

        }
    }
}


sculptor::~sculptor()
{
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}


void sculptor::setColor(float _r, float _g, float _b, float alpha){
    {
        if(_r >= 0.0 && _r <= 1.0) r = _r;
        else
        {
            cerr << "Entrada do vermelho invalida\n";
            return;
        }
        if(_g >= 0.0 && _g <= 1.0) g = _g;
        else
        {
            cerr << "Entrada do verde invalida\n";
            return;
        }
        if(_b >= 0.0 && _b <= 1.0) b = _b;
        else
        {
            cerr << "Entrada do azul invalida\n";
            return;
        }
        if(alpha >= 0.0 && alpha <= 1.0) a = alpha;
        else
        {
            cerr << "Entrada da opacidade invalida\n";
            return;
        }
    }
}


void sculptor::putVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}


void sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = false;
}


void sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i< x1; i++){

        for(int j = y0; j< y1; j++){

            for(int z = z0; z< z1; z++){

                putVoxel(i,j,z);

            }
        }
    }
}


void sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i< x1; i++){

        for(int j = y0; j< y1; j++){

            for(int z = z0; z< z1; z++){

                v[i][j][z].isOn = false;

            }
        }
    }
}


void sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                float  eq = ((i-zcenter)*(i-zcenter))+
                        ((j-ycenter)*(j-ycenter))+
                        ((k-xcenter)*(k-xcenter));
                if(eq <= radius*radius){
                   putVoxel(i,j,k);
                }
            }
        }
    }
}


void sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                float  eq = ((i-zcenter)*(i-zcenter))+
                        ((j-ycenter)*(j-ycenter))+
                        ((k-xcenter)*(k-xcenter));
                if(eq <= radius*radius){
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
}


void sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                float  eq = ((i-zcenter)*(i-zcenter)/(rz*rz))+
                        ((j-ycenter)*(j-ycenter)/(ry*ry))+
                        ((k-xcenter)*(k-xcenter)/(rx*rx));
                if(eq <= 1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}


void sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                float  eq = ((i-zcenter)*(i-zcenter)/(rz*rz))+
                        ((j-ycenter)*(j-ycenter)/(ry*ry))+
                        ((k-xcenter)*(k-xcenter)/(rx*rx));
                if(eq <= 1){
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
}

vector<vector<Voxel> > sculptor::putMatrix(int dimensao, int plano)
{
    vector<vector<Voxel>>m;
    vector<Voxel> l;

    switch(plano)
    {
    case 1:  //XY1
        l.resize(ny);

        for(int i = 0; i<nx; i++){
            for (int j = 0; j < ny; ++j) {
                l[j].r=v[i][j][dimensao].r;
                l[j].g=v[i][j][dimensao].g;
                l[j].b=v[i][j][dimensao].b;
                l[j].a=v[i][j][dimensao].a;
                l[j].isOn=v[i][j][dimensao].isOn;
            }

            m.push_back(l);
        }
    break;

    case 2:  //ZX1
        l.resize(nx);

        for(int i = 0; i<nz; i++){
            for (int j = 0; j < nx; ++j) {
                l[j].r=v[j][dimensao][i].r;
                l[j].g=v[j][dimensao][i].g;
                l[j].b=v[j][dimensao][i].b;
                l[j].a=v[j][dimensao][i].a;
                l[j].isOn=v[j][dimensao][i].isOn;
            }

            m.push_back(l);
        }
    break;

    case 3:  //YZ1
        l.resize(nz);

        for(int i = 0; i<ny; i++){
            for (int j = 0; j < nz; ++j) {
                l[j].r=v[dimensao][i][j].r;
                l[j].g=v[dimensao][i][j].g;
                l[j].b=v[dimensao][i][j].b;
                l[j].a=v[dimensao][i][j].a;
                l[j].isOn=v[dimensao][i][j].isOn;
            }

            m.push_back(l);
        }
   break;
    l.clear();
    return m;
}
}

void sculptor::writeOFF(string filename)
{

}


void sculptor::writeVECT(string filename)
{

}

