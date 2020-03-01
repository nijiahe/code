#include <QtWidgets/QtWidgets>


int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    QWidget w;

    QVBoxLayout vbox;
    w.setLayout(&vbox);

    QLabel * label;//QLabel,支持HTML写法
    vbox.addWidget(label = new QLabel("<a href =http://www.baidu.com>baidu<\a>"));
    //QObject::connect(label,SIGNAL(linkActivated(QString)),this,SLOT(...));
    //点击超链接发出的信号
    label->setPixmap(QPixmap("../莎雾.jpg"));
    QObject::connect(label,&QLabel::linkActivated,[](QString str){
        qDebug()<<str;
    });

    QPushButton * button;//按钮
    vbox.addWidget(button = new QPushButton("button"));
    button->setStyleSheet("QPushButton {font:bold 30px;color:skyblue}");
    //button.setDefault(true);//setDefault可以让按钮能用回车键触发


    QRadioButton * radio1;//单选按钮
    vbox.addWidget(radio1 = new QRadioButton("radio_button1"));
    QRadioButton * radio2;
    vbox.addWidget(radio2 = new QRadioButton("radio_button2"));
    QButtonGroup *grp = new QButtonGroup(&w);//按钮组
    grp->addButton(radio1);
    grp->addButton(radio2);
    QObject::connect(radio1,&QRadioButton::clicked,[](bool flag){
        qDebug()<<flag;
    });

    QObject::connect(radio2,&QRadioButton::clicked,[](bool flag){
        qDebug()<<flag;
    });

    QCheckBox * checkbox;
    vbox.addWidget(checkbox = new QCheckBox("check_box"));//复选框

    QComboBox * combo;//下拉框
    vbox.addWidget(combo = new QComboBox());
    QStringList slist;
    slist.append("item1");
    slist.append("item2");
    slist.append("item3");
    slist.append("item4");
    slist.append("item5");
    combo->addItems(slist);
    combo->setEditable(true);//设置可以自己写
    //combo->setCompleter(new QCompleter(slist));
    combo->setCompleter(new QCompleter(combo->model()));//效果相同,直接获取combo的所有选项

    QTextEdit * edit;
    vbox.addWidget(edit = new QTextEdit);
    edit->setText("<h1 class=\"test\">示例</h1>");
    edit->setStyleSheet("QTextEdit {color:red}");
    QObject::connect(edit,&QTextEdit::textChanged,[=](){
        qDebug()<<edit->toPlainText();
    });
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置如果需要竖直滚动条就添加
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//设置始终没有竖直滚动条

    QGroupBox * group = new QGroupBox("test");//一个框,用来存放控件,分类控件,这里演示存放两个button
    vbox.addWidget(group);
    QHBoxLayout hbox;
    group->setLayout(&hbox);
    hbox.addWidget(new QPushButton("group_button1"));
    hbox.addWidget(new QPushButton("group_button2"));

    QSlider * slider;//滑条
    vbox.addWidget(slider = new QSlider);
    slider->setMaximum(100);
    slider->setMinimum(0);
    slider->setOrientation(Qt::Horizontal);
    QObject::connect(slider,&QSlider::sliderMoved,[](int value){
        qDebug()<<value;
    });//此方法只有拖动的方式移动才有效
    QObject::connect(slider,&QSlider::valueChanged,[](int value){
        qDebug()<<value;
    });//此方法只要滑条值改变就有效

    QSpinBox * spin;
    vbox.addWidget(spin = new QSpinBox());
    spin->setMaximum(100);
    spin->setMinimum(0);

    QDateTimeEdit * datetime;
    vbox.addWidget(datetime = new QDateTimeEdit);

    QLCDNumber * lcd;
    vbox.addWidget(lcd=new QLCDNumber(10));
    lcd->display(12345);
    lcd->setMode(QLCDNumber::Hex);//16进制显示
    lcd->setSegmentStyle(QLCDNumber::Flat);//设置清晰的风格


    w.show();
    return app.exec();
}
