#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirIterator>
#include <QRandomGenerator>
#include <QListWidget>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::InsertBufferImage(){
    categories <<"airplaines"<< "lotus" << "panda" << "pyramid" << "strawberry";
    for(QString category: categories){
        QDirIterator it("../Qt/dataset/" + category, QStringList() << "*.jpg");
        while(it.hasNext()){
            qDebug() << it.next();
            miniature image;
            image.path = it.filePath();
            image.description = category;
            imageList.append(image);
        }
    }
}

void MainWindow::init(){
    InsertBufferImage();
    connect(ui->checkBoxAll, SIGNAL(clicked()), this, SLOT(checkBoxAll_clicked()));
    connect(ui->checkBoxAirplaines, SIGNAL(clicked()), this, SLOT(checkBox_clicked()));
    connect(ui->checkBoxLotus, SIGNAL(clicked()), this, SLOT(checkBox_clicked()));
    connect(ui->checkBoxPanda, SIGNAL(clicked()), this, SLOT(checkBox_clicked()));
    connect(ui->checkBoxPyramid, SIGNAL(clicked()), this, SLOT(checkBox_clicked()));
    connect(ui->checkBoxStrawberry, SIGNAL(clicked()), this, SLOT(checkBox_clicked()));
    VisualizeMiniature();

}

void MainWindow::VisualizeMiniature(){
    QList<miniature> filteredImages;
    QList<QCheckBox *> checkboxes = findChildren<QCheckBox *>();
    for(miniature image: imageList){
        QCheckBox *checkbox = Q_NULLPTR;
        for(QCheckBox *check: checkboxes){
            if(image.description.compare(check->text(), Qt::CaseInsensitive)==0)
                checkbox = check;
        }
        if(checkbox!=Q_NULLPTR && checkbox->isChecked()){
            filteredImages.append(image);
        }
    }
    QListWidget *listWidget = new QListWidget();
    ui->scrollArea->setWidget(listWidget);
    listWidget->setViewMode(QListWidget::IconMode);
    listWidget->setIconSize(QSize(120, 120));
    int i = 0;
    while(i<filteredImages.size()){
        int random = QRandomGenerator::global()->bounded(0 , filteredImages.size());
        if(!filteredImages[random].in){
            QListWidgetItem *item = new QListWidgetItem(QIcon(QPixmap(filteredImages[random].path)), filteredImages[random].description);
            item->setToolTip(filteredImages[random].path);
            listWidget->addItem(item);
            filteredImages[random].in = true;
            i++;
        }
    }
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemDoubleClicked(QListWidgetItem *)));
}

void MainWindow::checkBoxAll_clicked(){
    QList<QCheckBox *> checkboxes = findChildren<QCheckBox *>();
    for(QCheckBox *checkbox: checkboxes)
        checkbox->setChecked(ui->checkBoxAll->isChecked());
    VisualizeMiniature();
}

void MainWindow::checkBox_clicked(){
    bool checked = true;
    QList<QCheckBox *> checkboxes = findChildren<QCheckBox *>();
    for(QCheckBox *checkbox: checkboxes)
        if(checkbox != ui->checkBoxAll){
            checked &= checkbox->isChecked();
        }
    ui->checkBoxAll->setChecked(checked);
    VisualizeMiniature();
}

void MainWindow::itemDoubleClicked(QListWidgetItem *item){
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(item->toolTip()));
    label->setAttribute(Qt::WA_DeleteOnClose);
    label->show();
}
