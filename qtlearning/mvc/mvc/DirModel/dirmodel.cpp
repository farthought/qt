#include "dirmodel.h"

DirModel::DirModel(QWidget *parent)
    : QWidget(parent)
{
    model = new QFileSystemModel;
    model->setReadOnly(false);
#if QT_VERSION >= 0x050000
    model->setRootPath("/");
#else
    //在qt5.0中已经不存在setSorting方法，因此在此处对qt版本进行了判定
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
#endif

    treeView = new QTreeView;
    treeView->setModel(model);
    //把stretchLastSection设置为true，当QTreeView的宽度大于所有列宽之和时，
    //最后一列的宽度自动扩展以充满最后的边界；否则就让最后一列的宽度保持原始大小
    treeView->header()->setStretchLastSection(true);
    //setSortIndicator()函数是设置哪一列进行排序，我们这个传递的第一个参数是0，也就是第1列
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    //setSortIndicatorShown()函数设置显示列头上面的排序小箭头
    treeView->header()->setSortIndicatorShown(true);
    //设置排序小箭头是否可以被点击，在qt5.0中setClickable已经被替换为setSectionsClickable
#if QT_VERSION >= 0x050000
    treeView->header()->setSectionsClickable(true);
#else
    treeView->header()->setClickable(true);
#endif
    //QDir::currentPath()获取当前文件运行时路径，并把这个路径当成程序启动时显示的路径
    //expand()函数即展开这一路径；scrollTo()函数是把视图的视口滚动到这个路径的位置；
    //resizeColumnToContents()是要求把列头适应内容的宽度，也就是不产生...符号
    QModelIndex index = model->index(QDir::currentPath());
    treeView->expand(index);
    treeView->scrollTo(index);
    treeView->resizeColumnToContents(0);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *createBtn = new QPushButton(tr("Create Directory..."));
    QPushButton *delBtn = new QPushButton(tr("Remove"));
    btnLayout->addWidget(createBtn);
    btnLayout->addWidget(delBtn);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeView);
    mainLayout->addLayout(btnLayout);
    this->setLayout(mainLayout);

    connect(createBtn, SIGNAL(clicked()), this, SLOT(mkdir()));
    connect(delBtn, SIGNAL(clicked()), this, SLOT(rm()));
}

DirModel::~DirModel()
{

}

/************************************************************************
 * 首先获取选择的目录。后面这个isValid()的判断很重要，因为默认情况下是没有目录被选择
 * 的，此时这个路径是非法的，为了避免程序出现异常，必须要有这一步判断。然后会弹出对话
 * 框询问新的文件夹名字，如果创建失败会有提示，否则就是创建成功。
 * *********************************************************************/
void DirModel::mkdir()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    QString dirName = QInputDialog::getText(this,
                                            tr("Create Directory"),
                                            tr("Directory name"));
    if (!dirName.isEmpty()) {
        if (!model->mkdir(index, dirName).isValid()) {
            QMessageBox::information(this,
                                     tr("Create Directory"),
                                     tr("Failed to create the directory"));
        }
    }
}

/***********************************************************************
 * 这个函数和上面的函数一样都需要实现检测路径是否合法。另外需要注意的是，目录和文件的
 * 删除不是一个函数，需要调用isDir()函数检测。这一步在代码中有很清楚的描述，这里就不
 * 再赘述了
 * ********************************************************************/

void DirModel::rm()
{
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    bool ok;
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok) {
        QMessageBox::information(this,
                                 tr("Remove"),
                                 tr("Failed to remove %1").arg(model->fileName(index)));
    }
}
