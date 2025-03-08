#include "standardCalcGui.h"
#include "./ui_standardCalcGui.h"


#define MAX_FONT 60
#define DEF_FONT 48
#define MIN_WINDOW_W    360
#define MAX_WINDOW_W    550

CalcDisplay::CalcDisplay(QWidget *parent = nullptr) : QLabel("0", parent) {
    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    //setStyleSheet("font-size: 48px;");
    setSizePolicy(QSizePolicy::Ignored , QSizePolicy::Minimum );

    //prev_display->setStyleSheet("font-size: 24px;");
    QFont font = this->font();
    font.setPixelSize(42); // От 10 до 30 пикселей
    setFont(font);

     setText("0");
}



void CalcDisplay::adjust_font_size(QString display_num)
{
    QFont cur_font = this->font();
    int cur_font_size = cur_font.pixelSize();
    int def_size = calc_def_size();

    if(cur_font_size != def_size) //шрифт стремится быть дефолтного размера для текущего размера поля
    {
        cur_font_size = def_size;
        cur_font.setPixelSize(cur_font_size);
        setFont(cur_font);
    }

    int cur_text_width = calc_text_width(cur_font, display_num);
    QSize cur_label_size = this->size();
    int label_width = cur_label_size.width();
    if(cur_text_width > label_width) //если шрифт не помещается, то уменьшаем его
    {
        while (cur_text_width > label_width && cur_font_size > 2) {
            cur_font_size--;  // Уменьшаем размер
            cur_font.setPixelSize(cur_font_size);
            cur_text_width = calc_text_width(cur_font, display_num);  // Обновляем метрики
        }

        setFont(cur_font);
    }
}

int CalcDisplay::calc_text_width(const QFont& font, const QString& disp_text) const
{
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(disp_text);

    return textWidth;
}


int CalcDisplay::calc_def_size()
{
    QSize new_s = this->size();
    int label_width = new_s.width();

    float k = ((float)(label_width - MIN_WINDOW_W)) / (MAX_WINDOW_W - MIN_WINDOW_W);

    k = k > 1 ? 1 : k;

    if(label_width <= MIN_WINDOW_W)
    {
        default_size = DEF_FONT;
    }
    else if(label_width >= MAX_WINDOW_W)
    {
        default_size = MAX_FONT;
    }
    else
    {
        default_size = DEF_FONT + ((int)(MAX_FONT - DEF_FONT) * k);
    }

    return default_size;
}


AuxDisplay::AuxDisplay(QWidget *parent = nullptr) : QLabel("0", parent), aux_display(""), is_eq_repeat(false)
{

    setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont font = this->font();
    font.setPixelSize(18);
    setFont(font);

    setText("");
}

CalcBttn::CalcBttn(QString name = "0", QWidget *parent = nullptr) : QPushButton(name, parent)
{
    setMinimumSize(90, 50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}



Calculator::Calculator(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    CalcDisplay *display = new CalcDisplay(this);

    AuxDisplay *aux_display = new AuxDisplay(this);

    //CalcStandard backEndCalc;
    BackEndWrapper * backEndCalc = new BackEndWrapper(this);

    mainLayout->addWidget(aux_display);
    mainLayout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);


    QStringList buttons = {"%", "CE", "C", "⌫",
                           "1/x", "x²", "√x", "/",
                           "7", "8", "9", "*",
                           "4", "5", "6", "-",
                           "1", "2", "3", "+",
                           "+/-", "0", ".", "="};

    QHash<QString, CalcBttn*> hash;
    int row = 0, col = 0;
    for (const QString &text : buttons) {
        CalcBttn *btn = new CalcBttn(text, this);
        hash[text] = btn;
        gridLayout->addWidget(btn, row, col);
        col++;
        if (col == 4) { col = 0; row++; }
    }

    mainLayout->addLayout(gridLayout);
    mainLayout->setStretch(0, 1);
    mainLayout->setStretch(1, 6);
    mainLayout->setStretch(2, 6);

    // Подключение кнопки "0" к слоту updateDisplay
    // connect(hash.value("0"), &QPushButton::clicked, display, &CalcDisplay::updateDisplay_0_onClick);
    // connect(hash.value("1"), &QPushButton::clicked, display, &CalcDisplay::updateDisplay_1_onClick);
    // connect(hash.value("2"), &QPushButton::clicked, display, &CalcDisplay::updateDisplay_2_onClick);

    // connect(hash.value("%"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::); });
    connect(hash.value("CE"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::CE); });
    connect(hash.value("C"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::C); });
    connect(hash.value("⌫"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::BACKSPACE); });
    // connect(hash.value("1/x"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::); });
    // connect(hash.value("x²"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::); });
    // connect(hash.value("√x"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::); });
    connect(hash.value("/"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::DIV); });
    connect(hash.value("*"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::MUL); });
    connect(hash.value("-"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::SUB); });
    connect(hash.value("="), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::EQUAL); });
    connect(hash.value("+"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::ADD); });
    connect(hash.value("+/-"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_operation_to_backend(CalcStandard::NEGATE); });


    connect(hash.value("."), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::DOT); });
    connect(hash.value("0"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM0); });
    connect(hash.value("1"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM1); });
    connect(hash.value("2"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM2); });
    connect(hash.value("3"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM3); });
    connect(hash.value("4"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM4); });
    connect(hash.value("5"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM5); });
    connect(hash.value("6"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM6); });
    connect(hash.value("7"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM7); });
    connect(hash.value("8"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM8); });
    connect(hash.value("9"), &QPushButton::clicked, backEndCalc, [backEndCalc]() { backEndCalc->send_input_to_backend(CalcStandard::NUM9); });


    connect(backEndCalc, &BackEndWrapper::disp_data_updated_sig, display, display->update_display_slot);
    connect(backEndCalc, &BackEndWrapper::aux_disp_data_updated_sig, aux_display, aux_display->update_display_slot);

    connect(display, &CalcDisplay::sizeChanged, display, display->update_display_onResize_slot);




}

void AuxDisplay::update_display_slot(string & aux_field)
{
    QString aux_disp_str = QString::fromStdString(aux_field);

    setText(aux_disp_str);
}

void CalcDisplay::update_display_slot(string & main_field)
{

    QString main_disp_str = QString::fromStdString(main_field);
    adjust_font_size(main_disp_str);
    setText(main_disp_str);
    main_str = main_disp_str;
}

void CalcDisplay::update_display_onResize_slot()
{
    adjust_font_size(main_str);
    setText(main_str);
}
//**************************************
//*************************************
 //***********************************
BackEndWrapper::BackEndWrapper(QWidget * parent = nullptr): QWidget(parent)
{



}

void BackEndWrapper::send_input_to_backend(CalcStandard::bttns_t bttn_name)
{
    backEndCalc.add_num_to_main_field(bttn_name);
     string main_str = backEndCalc.get_main_field();
     string aux_str = backEndCalc.get_aux_field() ;

    emit disp_data_updated_sig( main_str );
    emit aux_disp_data_updated_sig( aux_str );
}

void BackEndWrapper::send_operation_to_backend(CalcStandard::operations_t op_name)
{
    backEndCalc.do_operation(op_name);
    string main_str = backEndCalc.get_main_field();
    string aux_str = backEndCalc.get_aux_field() ;

    emit disp_data_updated_sig( main_str );
    emit aux_disp_data_updated_sig( aux_str );
}
