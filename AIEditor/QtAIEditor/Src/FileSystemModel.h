#ifndef __FileSystemModel_H
#define __FileSystemModel_H

#include "QtIncAll.h"

class FileSystemModel : public QFileSystemModel
{
public:
	FileSystemModel();
	QSet<QPersistentModelIndex> checkedIndexes;
	// flags( )中返回 ItemIsUserCheckable。
	Qt::ItemFlags flags(const QModelIndex &index) const;
	// data( )中判断给定的项是否在checkedIndexes中，有的话就返回Qt::Checked，没有 就返回Qt::Unchecked。
	QVariant data(const QModelIndex &index, int role) const;
	// setData( )则把值为Qt::Checked的给定项，以及给定项的所有子孙节点，全都添加到checkedIndexes里。
	bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
	// recursiveCheck( )用于递规添加子节点。
	bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};

#endif // __FileSystemModel_H  