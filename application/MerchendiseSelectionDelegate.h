#ifndef MERCHENDISESELECTIONDELEGATE_H
#define MERCHENDISESELECTIONDELEGATE_H

#include <QItemDelegate>

class MerchendiseSelectionDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MerchendiseSelectionDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MERCHENDISESELECTIONDELEGATE_H
