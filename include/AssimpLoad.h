//CPP��׼ͷ�ļ�
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
using namespace std;

//����OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//����SOIL
#include <soil.h>

//����Assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//��С�Ƚϵĺ�
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class AssimpLoad {
private:
	string modelpath;

	float d[4] = { 0.8f, 0.8f, 0.8f, 1 }, 
		s[4] = { 0, 0, 0, 1 }, 
		a[4] = { 0.2f, 0.2f, 0.2f, 1 },
		e[4] = { 0, 0, 0, 1 };

	//�����ļ���������ID��ӳ��
	map<std::string, GLuint*> textureIdMap;
	GLuint* textureIds;

	//�����ģ��
	const aiScene* scene = NULL;
	GLuint scene_list = 0;
	aiVector3D scene_min, scene_max, scene_center;

	//��ǰ��ת�ĽǶ�
	float angle = 0;

	//ģ���Ƿ��������
	bool isWithText = false;

	//�õ������λ��
	std::string getBasePath(const std::string& path);

	void color4_to_float4(const aiColor4D *c, float f[4]);

	void set_float4(float f[4], float a, float b, float c, float d);

	void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);

	void get_bounding_box(aiVector3D* min, aiVector3D* max);

	//���ò���, ���ʺ͹��յķ�������Щ�й�
	void apply_material(const aiMaterial *mtl);

	//����ÿ������ķ������Լ�λ��
	void recursive_render(const aiScene *sc, const aiNode* nd);

	//ÿ֡��Ĳ���
	void do_motion(void);

	//��ȡģ��
	bool LoadModel();

	//�������������ȡ����
	bool LoadTextures();

public:
	//ÿ֡��ʾ
	void Display(void);

	//���ö�ȡģ�ͺ�����ĺ���
	bool Load(const string path);

	void SetMaterialColor(float dd[4], float ss[4], float aa[4], float ee[4]);

	bool LoadWithoutText(const string path);

	void Clear();

	~AssimpLoad();
};
