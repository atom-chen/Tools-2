#include "MImport3dMax.h"

#include "assimp/Importer.hpp"      // �������ڸ�ͷ�ļ��ж���
#include "assimp/scene.h"           // ��ȡ����ģ�����ݶ�����scene��
#include "assimp/postprocess.h"     // ��ͷ�ļ��а�������ı�־λ����

bool MImport3dMax::import(const std::string& pFile)
{
	// ����һ�������� 
	Assimp::Importer importer;

	// ʹ�õ���������ѡ����ģ���ļ� 
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |            //�����־���Զ��������ߺ͸�����
		aiProcess_Triangulate |					//�����־���Զ����ı�����ת��Ϊ������
		aiProcess_JoinIdenticalVertices |		//�����־���Զ��ϲ���ͬ�Ķ���
		aiProcess_SortByPType);					//�����־������ͬͼԪ���õ���ͬ��ģ����ȥ��ͼƬ���Ϳ����ǵ㡢ֱ�ߡ������ε�
	//��������־���Բο�Assimp���ĵ�  
	if (!scene)
	{
		//������󣬻�ȡ������Ϣ��������Ӧ�Ĵ���
		//DoTheErrorLogging( importer.GetErrorString());     
		return false;
	}
	// ������Ҫ��ȡscene�е�ģ�����ݣ��������ݵĻ�ȡ��ʽ���Բο�Assimp���ĵ�
	//DoTheSceneProcessing( scene);   

	return true;
}