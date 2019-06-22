#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QtDebug>
#include <vector>
#include <iostream>
#include "plotter.h"
#include "sculptor.h"

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    mxx = 100; mxy = 50; mxz=30;
    univ = new sculptor(mxx,mxy,mxz);

    deslizar=mxz/2; plano=1;

    sizeX=0;
    sizeY=0;
    sizeZ=0;
    RaioEsfera=0;
    Xelipse=0;
    Yelipse=0;
    Zelipse=0;

    verm = 255;
    verd=0;
    azul=255;
    opacidad = 255;

    tipo=1;

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    QPen pen;
    QBrush brush;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    pa.setPen(pen);
    brush.setColor(QColor(255,0,255));
    brush.setStyle(Qt::SolidPattern);
    pa.setBrush(brush);
    m.clear();
    m = univ ->putMatrix(deslizar,plano);
    tamanhoPosicao = height()/m.size();

    //criação da matriz inicial
    for(unsigned int i =0; i<m.size(); i++){
        for(unsigned int j =0; j<m.size(); j++){
            pa.drawRect(i*tamanhoPosicao,j*tamanhoPosicao,tamanhoPosicao, tamanhoPosicao);
        }
    }

    //colocar um quadrado pintado na posição
    for(unsigned int i=0; i<m.size();i++){
       for(unsigned int j=0; j<m[0].size();j++){
            if(m[i][j].isOn){
                    brush.setColor(QColor(m[i][j].r,m[i][j].g,m[i][j].b,m[i][j].a));
                    brush.setStyle(Qt::SolidPattern);
                    pa.setBrush(brush);
                    int x =i*tamanhoPosicao;
                    int y =j*tamanhoPosicao;
                    pa.drawRect(x,y,tamanhoPosicao,tamanhoPosicao);
            }
       }
    }

}

void Plotter::mouseMoveEvent(QMouseEvent *event){
    emit moveX(event->x());
    emit moveY(event->y());

    mouseX = (event->x())/tamanhoPosicao;
    mouseY = (event->y())/tamanhoPosicao;

    switch(plano){
    case 1:
        posX=mouseX;
        posY=mouseY;
        posZ=deslizar;
    break;
    case 2:
        posX=mouseY;
        posY=deslizar;
        posZ=mouseX;
    break;
    case 3:
        posX=deslizar;
        posY=mouseX;
        posZ=mouseY;
    break;

    }
    emit mouseLinha(posX);
    emit mouseColuna(posY);

    Plotter::colocarSelecionado(tipo,clicado);


}

void Plotter::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton){
    emit clickX(event->x());
    emit clickY(event->y());
    clicado = true;
    mouseX = (event->x())/tamanhoPosicao;
    mouseY = (event->y())/tamanhoPosicao;

    switch(plano){
    case 1:
        posX=mouseX;
        posY=mouseY;
        posZ=deslizar;
    break;
    case 2:
        posX=mouseY;
        posY=deslizar;
        posZ=mouseX;
    break;
    case 3:
        posX=deslizar;
        posY=mouseX;
        posZ=mouseY;
    break;

    }
    emit mouseLinha(posX);
    emit mouseColuna(posY);

    Plotter::colocarSelecionado(tipo,clicado);
  }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
       clicado = false;
    }
}

void Plotter::modificarplano1()
{
    plano = 1;
    emit escolha(1);
    deslizar = 0;
    repaint();

}
void Plotter::modificarplano2()
{
    plano = 2;
    emit escolha(2);
    deslizar = 0;
    repaint();
}
void Plotter::modificarplano3()
{
    plano = 3;
    emit escolha(3);
    deslizar = 0;
    repaint();
}

void Plotter::selecionarpv(){
    tipo = 1;
}
void Plotter::selecionarcv()
{
    tipo = 2;
}
void Plotter::selecionarpb()
{
    tipo = 3;
}
void Plotter::selecionarcb()
{
    tipo = 4;
}
void Plotter::selecionarps()
{
    tipo = 5;
}
void Plotter::selecionarcs()
{
    tipo = 6;
}
void Plotter::selecionarpe()
{
    tipo = 7;
}
void Plotter::selecionarce()
{
    tipo = 8;
}



void Plotter::colocarSelecionado(int tipo, bool clicado){

  if(clicado){
    if(tipo == 1)
    {
       univ->setColor(verm,verd,azul,opacidad);
       univ->putVoxel(posX,posY,posZ);
    }
    if(tipo == 2)
    {
       univ->cutVoxel(posX,posY,posZ);
    }
    if(tipo == 3)
    {
        univ->setColor(verm,verd,azul,opacidad);
        univ->putBox(posX,(posX+sizeX),posY,(posY+sizeY),posZ,(posZ+sizeZ));

    }
    if(tipo == 4)
    {
       univ->cutBox(posX,(posX+sizeX),posY,(posY+sizeY),posZ,(posZ+sizeZ));
    }
    if(tipo == 5)
    {
        univ->setColor(verm,verd,azul,opacidad);
        univ->putSphere(posX,posY,posZ,RaioEsfera);

    }
    if(tipo == 6)
    {
       univ->cutSphere(posX,posY,posZ,RaioEsfera);;
    }
    if(tipo == 7)
    {
        univ->setColor(verm,verd,azul,opacidad);
        univ->putEllipsoid(posX,posY,posZ,Xelipse,Yelipse,Zelipse);

    }
    if(tipo == 8)
    {
       univ->cutEllipsoid(posX,posY,posZ,Xelipse,Yelipse,Zelipse);
    }
    repaint();
    }
}

void Plotter::modificarRed(int red)
{
    verm = red;
}
void Plotter::modificarGreen(int green)
{
    verd = green;
}
void Plotter::modificarBlue(int blue)
{
    azul = blue;
}
void Plotter::modificarAlpha(int alpha)
{
    opacidad = alpha;
}

void Plotter::modificarSizeX(int size)
{
    sizeX=size;
}
void Plotter::modificarSizeY(int size)
{
    sizeY=size;
}
void Plotter::modificarSizeZ(int size)
{
    sizeZ=size;
}
void Plotter::modificarRaioEsfera(int rd)
{
    RaioEsfera=rd;
}
void Plotter::modificarXelipse(int rx)
{
    Xelipse=rx;
}
void Plotter::modificarYelipse(int ry)
{
    Yelipse=ry;
}
void Plotter::modificarZelipse(int rz)
{
    Zelipse=rz;
}
void Plotter::modificardeslizar(int plano)
{
    deslizar = plano;
    repaint();
}

