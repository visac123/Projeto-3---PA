#include <QString>
#include <QProcess>
#include <QtDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sculptor.h"
#include "plotter.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->HSvermelho->setMaximum(255);
    ui->HSverde->setMaximum(255);
    ui->HSazul->setMaximum(255);
    ui->HSopacidade->setMaximum(255);
    ui->HSvermelho->setMinimum(1);
    ui->HSverde->setMinimum(1);
    ui->HSazul->setMinimum(1);
    ui->HSopacidade->setMinimum(1);
    ui->HSvermelho->setSliderPosition(1);
    ui->HSverde->setSliderPosition(1);
    ui->HSazul->setSliderPosition(1);
    ui->HSopacidade->setSliderPosition(1);



    //////////////////////////////////
    connect(ui->putVoxel,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarpv()));

    connect(ui->cutVoxel,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarcv()));

    connect(ui->putBox,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarpb()));

    connect(ui->cutBox,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarcb()));

    connect(ui->putSphere,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarps()));

    connect(ui->cutSphere,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarcs()));

    connect(ui->putEllipse,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarpe()));

    connect(ui->cutEllipse,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(selecionarce()));

    connect(ui->buttonPXY,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(modificarplano1()));

    connect(ui->buttonPXZ,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(modificarplano2()));

    connect(ui->buttonPYZ,
            SIGNAL(clicked(bool)),
            ui->widget,
            SLOT(modificarplano3()));

    connect(ui->buttonPXY,
            SIGNAL(clicked(bool)),
            this,
            SLOT(updatedeslizarSlider()));

    connect(ui->buttonPXZ,
            SIGNAL(clicked(bool)),
            this,
            SLOT(updatedeslizarSlider()));

    connect(ui->buttonPYZ,
            SIGNAL(clicked(bool)),
            this,
            SLOT(updatedeslizarSlider()));

    ///////////////////////////////////////////

    connect(ui->HSX,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarSizeX(int)));

    connect(ui->HSY,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarSizeY(int)));

    connect(ui->HSZ,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarSizeZ(int)));

    connect(ui->HSraioEsfera,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarRaioEsfera(int)));

    connect(ui->HSraioX,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarXelipse(int)));

    connect(ui->HSraioY,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarYelipse(int)));

    connect(ui->HSraioZ,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarZelipse(int)));

    connect(ui->HSvermelho,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarRed(int)));

    connect(ui->HSverde,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarGreen(int)));

    connect(ui->HSazul,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarBlue(int)));

    connect(ui->HSopacidade,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificarAlpha(int)));

    connect(ui->HSdeslizar,
            SIGNAL(valuemodificard(int)),
            ui->widget,
            SLOT(modificardeslizar(int)));


}
MainWindow::~MainWindow()
{
    delete ui;
}



