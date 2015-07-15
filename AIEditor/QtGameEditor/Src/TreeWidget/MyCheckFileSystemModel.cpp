#include "MyCheckFileSystemModel.h"  

MyCheckFileSystemModel::MyCheckFileSystemModel()
{
}

Qt::ItemFlags MyCheckFileSystemModel::flags(const QModelIndex &index) const
{
	return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;	// û�� Qt::ItemIsUserCheckable ��Ȼ�и�ѡ�򣬵��ǲ���ѡ��
}

QVariant MyCheckFileSystemModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::CheckStateRole)
	{
		return checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
	}
	else
	{
		return QFileSystemModel::data(index, role);
	}
}

bool MyCheckFileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (role == Qt::CheckStateRole)
	{
		if (value == Qt::Checked)
		{
			checkedIndexes.insert(index);
			if (hasChildren(index) == true)
			{
				recursiveCheck(index, value);
			}
		}
		else
		{
			checkedIndexes.remove(index);
			if (hasChildren(index) == true)
			{
				recursiveCheck(index, value);
			}
		}
		emit dataChanged(index, index);
		return true;
	}
	return QFileSystemModel::setData(index, value, role);
}

bool MyCheckFileSystemModel::recursiveCheck(const QModelIndex &index, const QVariant &value)
{
	if (hasChildren(index))
	{
		int i;
		int childrenCount = rowCount(index);
		QModelIndex child;
		for (i = 0; i<childrenCount; i++)
		{
			child = QFileSystemModel::index(i, 0, index);
			setData(child, value, Qt::CheckStateRole);
		}
	}

	return true;
}