#ifndef __MyCheckFileSystemModel_H
#define __MyCheckFileSystemModel_H

#include "QtIncAll.h"

class MyCheckFileSystemModel : public QFileSystemModel
{
public:
	MyCheckFileSystemModel();
	QSet<QPersistentModelIndex> checkedIndexes;
	// flags( )�з��� ItemIsUserCheckable��
	Qt::ItemFlags flags(const QModelIndex &index) const;
	// data( )���жϸ��������Ƿ���checkedIndexes�У��еĻ��ͷ���Qt::Checked��û�� �ͷ���Qt::Unchecked��
	QVariant data(const QModelIndex &index, int role) const;
	// setData( )���ֵΪQt::Checked�ĸ�����Լ����������������ڵ㣬ȫ����ӵ�checkedIndexes�
	bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
	// recursiveCheck( )���ڵݹ�����ӽڵ㡣
	bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};

#endif // __FileSystemModel_H  