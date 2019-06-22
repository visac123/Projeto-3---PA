#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Voxel {
    float r,g,b;
    float a;
    bool isOn;
};

class sculptor
{
protected:

    Voxel ***v;
    int nx,ny,nz;
    float r,g,b,a;

public:

    sculptor(int _nx, int _ny, int _nz);
    ~sculptor();

    void setColor(float r, float g, float b, float alpha);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void writeOFF(string filename);
    void writeVECT(string filename);
    vector<vector<Voxel>> putMatrix(int dimensao, int plano);


};

#endif // SCULPTOR_H
