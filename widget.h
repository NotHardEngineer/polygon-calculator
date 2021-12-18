#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_addVertexButton_clicked();

    void on_removeVertexButton_clicked();

    bool GetValueFromItem(QTableWidgetItem *item, double &value);

    void on_resultButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
