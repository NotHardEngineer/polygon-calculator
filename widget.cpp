#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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
    return ok;
}



void Widget::on_addVertexButton_clicked()
{
    int n = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(n+1);
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
    double sum1 = 0, sum2 = 0;
    for(int r = 0; r < n; r++){
        bool ok = 1;
        double XCord = 0, YCord = 0;
        if (r == n - 1){
            ok = GetValueFromItem(ui->tableWidget->item(r,0), XCord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(0,1), YCord) && ok;
        }
        else{
            ok = GetValueFromItem(ui->tableWidget->item(r,0), XCord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r + 1,1), YCord) && ok;
        }
        if(ok){
            sum1 = sum1 + XCord * YCord;
        }
        else{
            break;
        }
    }
    ui->label->setText(ui->label->text() + "\n");
    for(int r = 0; r < n; r++){
        bool ok = 1;
        double XCord = 0, YCord = 0;
        if (r == n - 1){
            ok = GetValueFromItem(ui->tableWidget->item(0,0), XCord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r,1), YCord) && ok;
        }
        else{
            ok = GetValueFromItem(ui->tableWidget->item(r + 1,0), XCord) && ok;
            ok = GetValueFromItem(ui->tableWidget->item(r,1), YCord) && ok;
        }
        if(ok){
            sum2 = sum2 + XCord * YCord;
        }
        else{
            break;
        }
    }
    double area = abs(sum1 - sum2)/2;
    ui->SResult->setText(QString::number(area));


}

