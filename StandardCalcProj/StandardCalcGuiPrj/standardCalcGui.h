#ifndef STANDARDCALCGUI_H
#define STANDARDCALCGUI_H
#include "../../TestExampleEmpty/src/production/include/CalcLogic.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>

class BackEndWrapper: public QWidget
{
    Q_OBJECT
public:
    CalcStandard backEndCalc;
    BackEndWrapper(QWidget *parent);
    //~BackEndWrapper();

signals:
    void disp_data_updated_sig(string & main_field);
    void aux_disp_data_updated_sig(string & aux_field);
public slots:
    void send_input_to_backend(CalcStandard::bttns_t bttn_name);
    void send_operation_to_backend(CalcStandard::operations_t op_name);

};

class CalcDisplay : public QLabel {
    Q_OBJECT

private:

    int default_size;
    QString main_str = "";

public:
    explicit CalcDisplay(QWidget *parent);

    int calc_def_size();
    int calc_text_width(const QFont& font, const QString& disp_text) const;
    void update_display();
    void adjust_font_size(QString display_num);

    QString get_display_num();


public slots:
    void update_display_slot(string & main_field);
    void update_display_onResize_slot();

signals:
    void sizeChanged();

protected:
    void resizeEvent(QResizeEvent *event) override {
        QSize new_s = this->size();
        emit sizeChanged(); // Вызываем сигнал при изменении размера
        qDebug() << "Размер QLabel изменился на:" << new_s.width();
        QLabel::resizeEvent(event);
    }
};


class AuxDisplay : public QLabel
{
    Q_OBJECT
private:
    QString aux_display;
    bool is_eq_repeat;
public:

    explicit AuxDisplay(QWidget *parent);


public slots:
    void update_display_slot(string & main_field);


};

class CalcBttn : public QPushButton {
public:
    CalcBttn(QString name, QWidget *parent ) ;

};


class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent ) ;
        // Подключение кнопки "0" к слоту updateDisplay


};
#endif // STANDARDCALCGUI_H
