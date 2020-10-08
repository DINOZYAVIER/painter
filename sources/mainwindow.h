#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

public Q_SLOTS:
    void onOpenImage();
    void onAboutClicked();
    void onAboutQtClicked();
protected:
    void paintEvent( QPaintEvent* event );
    void mouseMoveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );

private:
    Ui::MainWindow*     m_ui;
    QPoint              m_lastPoint;
    QPoint              m_currentPoint;
    QString             m_filename;
    QPixmap*            m_pixmap;
};
#endif // MAINWINDOW_H
