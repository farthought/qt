#include "sortfilterproxy.h"

SortFilterProxy::SortFilterProxy(QWidget *parent)
    : QWidget(parent)
{
    model = new QStringListModel(QColor::colorNames(), this);

    modelProxy = new QSortFilterProxyModel(this);
    modelProxy->setSourceModel(model);
    //setFilterKeyColumn()函数设置程序需要过滤哪一列
    modelProxy->setFilterKeyColumn(0);

    view = new QListView(this);
    view->setModel(modelProxy);

    //设置过滤的输入框
    QLineEdit *filterInput = new QLineEdit;
    QLabel *filterLabel = new QLabel(tr("Filter"));
    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterInput);

    //设置组合框，选择不同的过滤方式
    //QregExp::RegExp提供了最一般的正则表达式语法，不过这个语法不支持贪婪限定符。这也是Qt默认的规则。
    //如果你需要使用贪婪限定符，需要使用QRegExp::RegExp2，根据文档描述，这个将会是 Qt5 的默认规则
    //QRegExp::Wildcard，是unix shell的匹配规则，通配符
    //QRegExp::FixedString使用固定的字符串进行匹配
    syntaxBox = new QComboBox;
    syntaxBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    syntaxBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxBox->addItem(tr("Fixed string"), QRegExp::FixedString);
    QLabel *syntaxLabel = new QLabel(tr("Syntax"));
    QHBoxLayout *syntaxLayout = new QHBoxLayout;
    syntaxLayout->addWidget(syntaxLabel);
    syntaxLayout->addWidget(syntaxBox);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    layout->addLayout(filterLayout);
    layout->addLayout(syntaxLayout);

    connect(filterInput, SIGNAL(textChanged(QString)), this, SLOT(filterChanged(QString)));

}

SortFilterProxy::~SortFilterProxy()
{

}

/************************************************************************
 * 该函数的作用用于匹配，当输入框输入需要匹配的字符之后，第一步，使用QComboBox的选择值
 * 创建一个QRegExp::PatternSyntax对象syntax，然后利用这个语法规则构造一个正则表达式
 * regExp，注意我们在QLineEdit里面输入的内容是通过参数传递进来的，然后设置proxy的过滤
 * 器的表达式。
 * *********************************************************************/
void SortFilterProxy::filterChanged(QString text)
{
        QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
                        syntaxBox->itemData(syntaxBox->currentIndex()).toInt());
        QRegExp regExp(text, Qt::CaseInsensitive, syntax);
        modelProxy->setFilterRegExp(regExp);
}
