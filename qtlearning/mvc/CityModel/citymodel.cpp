#include "citymodel.h"

CityModel::CityModel(QAbstractTableModel *parent)
    : QAbstractTableModel(parent)
{
}

CityModel::~CityModel()
{

}
/**********************************************************
 * rowCount()和columnCount()函数也是返回list的长度。data()函数根据
 * role的不同返回不同的值。headerData()用于返回表头。
 *********************************************************/
int CityModel::rowCount(const QModelIndex & parent) const
{
    return cities.count();
}

int CityModel::columnCount(const QModelIndex & parent) const
{
    return cities.count();
}

QVariant CityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        if (index.row() == index.column()) {
            return 0;
        }
        int offset = offsetOf(index.row(), index.column());
        return distances[offset];
    }
    return QVariant();
}

QVariant CityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        return cities[section];
    }
    return QVariant();
}
/**********************************************************************************
 * setData()在用户编辑数据时会自动调用。也就是说，这时我们的数据已经不是只读的了。函数开始是一个
 * 长长的判断：index要是合法的；index的row和column不相等，也就是说两个城市是不同的；数据想的role
 * 是Qt::EditRole。如果满足了这三个条件，才会执行下面的操作。首先，由row和column坐标定位到表中的
 * 数据项在vector中的位置。然后用户新修改的数据被作为参数value传入，所以我们要把这个参数赋值给
 * distances。createIndex()函数根据column和row值生成一个QModelIndex对象。请注意这里的顺序：
 * row和column是颠倒的！这就把坐标为(row, column)的点关于主对角线对称的那个点(column, row)的
 * index找到了。还记得我们的需求吗？当我们修改了一个数据时，对应的数据也要被修改，这就是这个功能的实现。
 * 我们需要emit dataChanged()信号，这个信号接收两个参数：一个是被修改的数据的左上角的坐标，一个是
 * 被修改的数据的右下角的坐标。为什么会有两个坐标呢？因此我们修改的数据不一定只是一个。像这里，我们只
 * 修改了一个数据，因此这两个值是相同的。数据更新了，我们用这个信号通知view刷新，这样就可以显示新的数
 * 据了。最后，如果函数数据修改成功就返回true，否则返回false。
 *********************************************************************************/
bool CityModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && index.row() != index.column() && role == Qt::EditRole) {
        int offset = offsetOf(index.row(), index.column());
        distances[offset] = value.toInt();

        QModelIndex transposedIndex = createIndex(index.column(), index.row());
        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }
    return false;
}

Qt::ItemFlags CityModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

void CityModel::setCities(const QStringList &cityNames)
{
    cities = cityNames;
    distances.resize(cities.count() * (cities.count() - 1) / 2);
    distances.fill(0);
}
/********************************************************************
 * 由于在table中坐标是由row和column给出的，因此需要有一个二维坐标到一维坐标的转换，
 * 这就是offsetOf()函数的作用
 *******************************************************************/
int CityModel::offsetOf(int row, int column) const
{
    if (row < column) {
        qSwap(row, column);
    }
    return (row * (row - 1) / 2) + column;
}
