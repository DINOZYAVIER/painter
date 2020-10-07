#include "precompiled.h"
#include "mainwindow.h"
#include "custompainter.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow( QWidget *parent )
    : QMainWindow( parent )
    , m_ui( new Ui::MainWindow )
{
    m_ui->setupUi(this);

    connect( m_ui->aAbout, &QAction::triggered, this, &MainWindow::onAboutClicked );
    connect( m_ui->aAboutQt, &QAction::triggered, this, &MainWindow::onAboutQtClicked );
    connect( m_ui->aOpen, &QAction::triggered, this, &MainWindow::onOpenImage );
    connect( m_ui->aClose, &QAction::triggered, this, &MainWindow::close );
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::onOpenImage()
{

}

void MainWindow::onAboutClicked()
{
    QMessageBox::about( this, "About the program",
                              "Painter Application \nTest assignment by Arthur Konovalov for NIX Solutions." );
}

void MainWindow::onAboutQtClicked()
{
    QMessageBox::aboutQt( this, "About Qt" );
}
