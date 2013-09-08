#include <QtGui>
#include "TowarDelegate.h"
#include "TowarModel.h"

TowarDelegate::TowarDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *TowarDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex & index ) const
{
    const TowarModel* m = static_cast<const TowarModel*>(index.model());

    if(m->isIlosc(index))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(0);
        editor->setMaximum(99999);
        editor->setSingleStep(1);
        return editor;
    }

    if(m->isRabat(index))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setMinimum(0);
        editor->setMaximum(100);
        editor->setSingleStep(0.1);
        return editor;
    }

    return new QWidget();
}

void TowarDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const TowarModel* m = static_cast<const TowarModel*>(index.model());
    if(m->isRabat(index) || m->isIlosc(index))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(m->data(index, Qt::EditRole).toDouble());
    }
}

void TowarDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    const TowarModel* m = static_cast<const TowarModel*>(index.model());
    if(m->isIlosc(index) || m->isRabat(index))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        model->setData(index, spinBox->value(), Qt::EditRole);
    }
}

void TowarDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

