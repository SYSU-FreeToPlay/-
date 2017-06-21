//CPP标准头文件
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
using namespace std;

//关于OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//关于SOIL
#include <soil.h>

//关于Assimp
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//大小比较的宏
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

class AssimpLoad {
private:
	string modelpath;

	float d[4] = { 0.8f, 0.8f, 0.8f, 1 }, 
		s[4] = { 0, 0, 0, 1 }, 
		a[4] = { 0.2f, 0.2f, 0.2f, 1 },
		e[4] = { 0, 0, 0, 1 };

	//纹理文件名和纹理ID的映射
	map<std::string, GLuint*> textureIdMap;
	GLuint* textureIds;

	//读入的模型
	const aiScene* scene = NULL;
	GLuint scene_list = 0;
	aiVector3D scene_min, scene_max, scene_center;

	//当前旋转的角度
	float angle = 0;

	//模型是否读入纹理
	bool isWithText = false;

	//得到纹理的位置
	std::string getBasePath(const std::string& path);

	void color4_to_float4(const aiColor4D *c, float f[4]);

	void set_float4(float f[4], float a, float b, float c, float d);

	void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo);

	void get_bounding_box(aiVector3D* min, aiVector3D* max);

	//设置材质, 材质和光照的反射率这些有关
	void apply_material(const aiMaterial *mtl);

	//设置每个顶点的法向量以及位置
	void recursive_render(const aiScene *sc, const aiNode* nd);

	//每帧后的操作
	void do_motion(void);

	//读取模型
	bool LoadModel();

	//这个函数用来读取纹理
	bool LoadTextures();

public:
	//每帧显示
	void Display(void);

	//调用读取模型和纹理的函数
	bool Load(const string path);

	void SetMaterialColor(float dd[4], float ss[4], float aa[4], float ee[4]);

	bool LoadWithoutText(const string path);

	void Clear();

	~AssimpLoad();
};
