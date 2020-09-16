#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QStringList categories;

    struct miniature{
        QString path;
        QString description;
        bool in = 0;
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void checkBoxAll_clicked();
    void checkBox_clicked();
    void itemDoubleClicked(QListWidgetItem *);

private:
    Ui::MainWindow *ui;
    QList<miniature> imageList;
    void InsertBufferImage();
    void VisualizeMiniature();
    void init();

};
#endif // MAINWINDOW_H
