#include "FileSystemModel.h"  

MyFileSystemModel::MyFileSystemModel()
{
}

Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex &index) const
{
	return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;	// 没有 Qt::ItemIsUserCheckable 虽然有复选框，但是不能选中
}

QVariant MyFileSystemModel::data(const QModelIndex &index, int role) const
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

bool MyFileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
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

bool MyFileSystemModel::recursiveCheck(const QModelIndex &index, const QVariant &value)
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