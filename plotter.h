#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QAction>
#include <QColor>
#include <QTimerEvent>
#include <vector>
#include "sculptor.h"


class Plotter : public QWidget
{
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void colocarSelecionado(int tipo, bool clicado);

    int sizeX,sizeY,sizeZ;
    int RaioEsfera, Xelipse, Yelipse,Zelipse;
    int deslizar;
    int verm;
    int verd;
    int azul;
    int opacidad;
    int mxx;
    int mxy;
    int mxz;
    unsigned int plano;
    unsigned int tipo;
    sculptor *univ;

    QAction *actionSelectSize;

private:

    std::vector<std::vector<Voxel>> m;

    bool clicado;
    int mouseX,mouseY;

    int posX,posY,posZ;

    int tamanhoPosicao;

signals:
 void mouseLinha(int);
 void mouseColuna(int);
 void escolha(int);
 void moveX(int);
 void moveY(int);
 void clickX(int);
 void clickY(int);


public slots:

  void colocarSelecionado(int x0, int y0, int z0, int tipo);
  void modificarplano1();
  void modificarplano2();
  void modificarplano3();
  void selecionarpv();
  void selecionarcv();
  void selecionarpb();
  void selecionarcb();
  void selecionarps();
  void selecionarcs();
  void selecionarpe();
  void selecionarce();

  void modificarRed(int red);
  void modificarGreen(int green);
  void modificarBlue(int blue);
  void modificarAlpha(int alpha);
  void modificardeslizar(int plano);
  void modificarSizeX(int size);
  void modificarSizeY(int size);
  void modificarSizeZ(int size);
  void modificarRaioEsfera(int rd);
  void modificarXelipse(int rx);
  void modificarYelipse(int ry);
  void modificarZelipse(int rz);





};

#endif // PLOTTER_H
