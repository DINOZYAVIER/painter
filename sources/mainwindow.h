#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CustomPainter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    void onOpenImage();
    void onAboutClicked();
    void onAboutQtClicked();
protected:
    void paintEvent( QPaintEvent* event );
    void mouseMoveEvent( QMouseEvent *event );

private:
    Ui::MainWindow*     m_ui;
    QPoint              m_point;
    QString             m_filename;
};
#endif // MAINWINDOW_H
