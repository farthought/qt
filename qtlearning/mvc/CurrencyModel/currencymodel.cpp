#include "currencymodel.h"

CurrencyModel::CurrencyModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

CurrencyModel::~CurrencyModel()
{

}

int CurrencyModel::rowCount(const QModelIndex & parent) const
{
        return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex & parent) const
{
        return currencyMap.count();
}

/********************************************************************
 * data()函数返回单元格的数据。它有两个参数：第一个是QModelIndex，也就是单元格的位置；
 * 第二个是role，也就是这个数据的角色。这个函数的返回值是QVariant。至此，我们还是第一
 * 次见到这个类型。这个类型相当于是Java里面的Object，它把绝大多数Qt提供的数据类型都封
 * 装起来，起到一个数据类型“擦除”的作用。比如我们的table单元格可以是string，也可以是int，
 * 也可以是一个颜色值，那么这么多类型怎么返回呢？于是，Qt提供了这个QVariant类型，你可以把
 * 这很多类型都存放进去，到需要使用的时候使用一系列的to函数取出来即可。比如你把int包装成一
 * 个QVariant，使用的时候要用QVariant::toInt()重新取出来。这里需要注意的是，QVariant
 * 类型的放入和取出必须是相对应的，你放入一个int就必须按int取出，不能用toString(), Qt不
 * 会帮你自动转换。下面看这个类的内容。首先判断传入的index是不是合法，如果不合法直接return
 * 一个空白的QVariant。然后如果role是Qt::TextAlignmentRole，也就是文本的对象方式，那么
 * 就返回int(Qt::AlignRight | Qt::AlignVCenter)；否则，role如果是Qt::DisplayRole，
 * 就按照我们前面所说的逻辑进行计算，然后按照字符串返回。这时候你就会发现，其实我们在if…else…
 * 里面返回的不是一种数据类型，if里面是int，而else里面是QString，这就是QVariant的作用了，
 * 也正是“类型擦除”的意思
 *******************************************************************/
QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
        if (!index.isValid())
                return QVariant();

        if (role == Qt::TextAlignmentRole) {
                return int(Qt::AlignRight | Qt::AlignVCenter);
        } else if (role == Qt::DisplayRole) {
                QString rowCurrency = currencyAt(index.row());
                QString columnCurrency = currencyAt(index.column());
                if (currencyMap.value(rowCurrency) == 0.0)
                        return "####";
                double amount = currencyMap.value(columnCurrency) / currencyMap.value(rowCurrency);
                return QString("%1").arg(amount, 0, 'f', 4);
        }
        return QVariant();
}

/******************************************************************
 * headerData()返回列名或者行名；
 * setCurrencyMap()用于设置底层的数据源；
 * currencyAt()返回偏移量为offset的键值。
 * ***************************************************************/
QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
        if (role != Qt::DisplayRole)
                return QVariant();
        return currencyAt(section);
}

void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
        currencyMap = map;
        //reset();
}

QString CurrencyModel::currencyAt(int offset) const
{
        return (currencyMap.begin() + offset).key();
}
