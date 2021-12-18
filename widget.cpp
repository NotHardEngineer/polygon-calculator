#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    on_resetButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::GetValueFromItem(QTableWidgetItem *item, double &value){
    bool ok = 0;
    if (item != NULL){
        QString s1 = item->text();
        value = s1.toDouble(&ok);
    }
    if(ok){
        item->setBackground(Qt::white);
    }
    else{
        item->setBackground(Qt::red);
    }
    return ok;
}


double twoPointRange(double x1, double y1, double x2, double y2){
    return sqrt(pow((x1 - x2),2) + pow((y1 - y2),2));
}


void Widget::on_addVertexButton_clicked()
{
    int n = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(n+1);
    ui->tableWidget->setItem(n, 0, new QTableWidgetItem);
    ui->tableWidget->setItem(n, 1, new QTableWidgetItem);
    ui->tableWidget->setVerticalHeaderItem(n, new QTableWidgetItem(QString::number(n+1)+"-я вершина"));
}
void Widget::on_removeVertexButton_clicked()
{
    int n = ui->tableWidget->rowCount();
    if(n>3){
        ui->tableWidget->setRowCount(n-1);
    }
}


void Widget::on_resultButton_clicked()
{
    int n = ui->tableWidget->rowCount();
    bool flag = 1;
    double sum1 = 0, sum2 = 0, per = 0;
    for(int r = 0; r < n; r++){
        bool ok = 1;
        double X1Cord = 0, Y1Cord = 0, X2Cord = 0, Y2Cord = 0;
        if (r == n - 1){
            ok = GetValueFromItem(ui->tableWidget->item(r,0), X1Cord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r,1), Y1Cord) && ok;

            ok = GetValueFromItem(ui->tableWidget->item(0,0), X2Cord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(0,1), Y2Cord) && ok;
        }
        else{
            ok = GetValueFromItem(ui->tableWidget->item(r,0), X1Cord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r,1), Y1Cord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r + 1,0), X2Cord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r + 1,1), Y2Cord) && ok;
        }
        if(ok && flag){
            per += twoPointRange(X1Cord, Y1Cord, X2Cord, Y2Cord);
            sum1 = sum1 + X1Cord * Y2Cord;
            sum2 = sum2 + X2Cord * Y1Cord;
        }
        else{
            flag = 0;
        }
    }
    double area = abs(sum1 - sum2)/2;

    //Вывод результатов
    ui->SResult->setText(QString::number(area));
    ui->PResult->setText(QString::number(per));

}


void Widget::on_resetButton_clicked()
{
    int n = ui->tableWidget->rowCount();

    for(int r = 0; r < n; r++){
        ui->tableWidget->setItem(r, 0, new QTableWidgetItem);
        ui->tableWidget->setItem(r, 1, new QTableWidgetItem);
        ui->tableWidget->item(r, 0)->setBackground(Qt::white);
        ui->tableWidget->item(r, 1)->setBackground(Qt::white);

        ui->tableWidget->item(r, 0)->setText("");
        ui->tableWidget->item(r, 1)->setText("");
    }

}

