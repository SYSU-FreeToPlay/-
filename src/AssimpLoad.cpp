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

#include "..\include\AssimpLoad.h"

//��С�Ƚϵĺ�
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)



//�õ������λ��
std::string AssimpLoad::getBasePath(const std::string& path)
{
	size_t pos = path.find_last_of("\\/");
	return (std::string::npos == pos) ? "" : path.substr(0, pos + 1);
}

void AssimpLoad::color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

void AssimpLoad::set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void AssimpLoad::get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max, aiMatrix4x4* trafo)
{
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo, &nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n)
	{
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t)
		{

			aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp, trafo);

			min->x = aisgl_min(min->x, tmp.x);
			min->y = aisgl_min(min->y, tmp.y);
			min->z = aisgl_min(min->z, tmp.z);

			max->x = aisgl_max(max->x, tmp.x);
			max->y = aisgl_max(max->y, tmp.y);
			max->z = aisgl_max(max->z, tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n)
	{
		get_bounding_box_for_node(nd->mChildren[n], min, max, trafo);
	}
	*trafo = prev;
}

void AssimpLoad::get_bounding_box(aiVector3D* min, aiVector3D* max)
{
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z = 1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode, min, max, &trafo);
}

//���ò���, ���ʺ͹��յķ�������Щ�й�
void AssimpLoad::apply_material(const aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	aiColor4D diffuse;
	aiColor4D specular;
	aiColor4D ambient;
	aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// changed: to unsigned

	int texIndex = 0;
	aiString texPath;	//contains filename of texture

	if (isWithText)
	{
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &texPath))
		{
			//bind texture
			unsigned int texId = *textureIdMap[texPath.data];
			glBindTexture(GL_TEXTURE_2D, texId);
		}
	}

	set_float4(c, d[0], d[1], d[2], d[3]);
	if (isWithText && AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, s[0], s[1], s[2], s[3]);
	if (isWithText && AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, a[0], a[1], a[2], a[3]);
	if (isWithText && AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, e[0], e[1], e[2], e[3]);
	if (isWithText && AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	max = 1;
	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
	if ((ret1 == AI_SUCCESS) && (ret2 == AI_SUCCESS))
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
	else
	{
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	//if (AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
	//	fill_mode = wireframe ? GL_LINE : GL_FILL;
	//else
	//	fill_mode = GL_FILL;
	//glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

//����ÿ������ķ������Լ�λ��
void AssimpLoad::recursive_render(const aiScene *sc, const aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n)
	{
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if (mesh->mNormals == NULL)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}

		if (mesh->mColors[0] != NULL)
		{
			glEnable(GL_COLOR_MATERIAL);
		}
		else
		{
			glDisable(GL_COLOR_MATERIAL);
		}

		for (t = 0; t < mesh->mNumFaces; ++t)
		{
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch (face->mNumIndices)
			{
			case 1: face_mode = GL_POINTS; break;
			case 2: face_mode = GL_LINES; break;
			case 3: face_mode = GL_TRIANGLES; break;
			default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);
			for (i = 0; i < face->mNumIndices; i++)
			{
				int vertexIndex = face->mIndices[i];	// get group index for current index
				if (mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][vertexIndex]);
				if (mesh->mNormals != NULL)
					if (mesh->HasTextureCoords(0))		//HasTextureCoords(texture_coordinates_set)
					{
						glTexCoord2f(mesh->mTextureCoords[0][vertexIndex].x, 1 - mesh->mTextureCoords[0][vertexIndex].y); //mTextureCoords[channel][vertex]
					}

				glNormal3fv(&mesh->mNormals[vertexIndex].x);
				glVertex3fv(&mesh->mVertices[vertexIndex].x);
			}
			glEnd();
		}
	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n)
	{
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

//ÿ֡��Ĳ���
void AssimpLoad::do_motion(void)
{
	static GLint prev_time = 0;
	static GLint prev_fps_time = 0;
	static int frames = 0;

	//ͳ����ת�Ƕ�
	int time = glutGet(GLUT_ELAPSED_TIME);
	angle += (time - prev_time)*0.01;
	prev_time = time;

	//���֡��
	frames += 1;
	if ((time - prev_fps_time) > 1000) // update every seconds
	{
		int current_fps = frames * 1000 / (time - prev_fps_time);
		//printf("%d fps\n", current_fps);
		frames = 0;
		prev_fps_time = time;
	}

	glutPostRedisplay();
}

//��ȡģ��
bool AssimpLoad::LoadModel()
{
	scene = aiImportFile(modelpath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (!scene) return false;

	get_bounding_box(&scene_min, &scene_max);
	scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
	scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
	scene_center.z = (scene_min.z + scene_max.z) / 2.0f;

	return true;
}

//�������������ȡ����
bool AssimpLoad::LoadTextures()
{
	if (scene->HasTextures()) printf("Support for meshes with embedded textures is not implemented\d");

	/* getTexture Filenames and Numb of Textures */
	//�õ�������ļ���
	for (unsigned int m = 0; m<scene->mNumMaterials; m++)
	{
		int texIndex = 0;
		aiReturn texFound = AI_SUCCESS;

		aiString path;	// filename

		while (texFound == AI_SUCCESS)
		{
			texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
			//map�洢����������ļ����������ID����Թ�ϵ, ��ʱ�������ļ�����û��ID, ������Ϊnull
			textureIdMap[path.data] = NULL; //fill map with textures, pointers still NULL yet
			texIndex++;
		}
	}

	//�õ����������
	int numTextures = textureIdMap.size();

	//����һ�����������洢�����ID
	textureIds = new GLuint[numTextures];
	std::map<std::string, GLuint*>::iterator itr = textureIdMap.begin();

	//�õ�ģ�����ڵ�λ��, Ĭ��ģ�ͺ��������һ��
	std::string basepath = getBasePath(modelpath);

	//�Ƚ�ÿ���ļ�����һ���ڴ�ռ�ҹ�, Ȼ��SOIL������������ID
	//ID�ʹ��ڶ�Ӧ���ڴ�ռ���
	for (int i = 0; i<numTextures; i++)
	{
		//Ϊÿ�������ļ���ָ��ID��ŵ�λ��
		string filename = (*itr).first;
		(*itr).second = &textureIds[i];
		itr++;

		//�õ����ļ�����.\text��������, ����Ҫ��ǰ���.\ȥ���ź�
		if (filename.length() > 2) filename = filename.substr(2);
		string fileloc = basepath + filename;

		//SOIL��ȡͼƬ, ͬʱ�᷵��ͼƬ��ID
		textureIds[i] = SOIL_load_OGL_texture(
			fileloc.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
		);

		if (textureIds[i] != 0)
		{
			//��ͼƬ��OpenGl_ID
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else
		{
			printf("Couldn't load Image: %s", fileloc.c_str());
		}
	}
	return true;
}


//ÿ֡��ʾ
void AssimpLoad::Display(void)
{
	float tmp;

	tmp = scene_max.x - scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y, tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z, tmp);
	tmp = 1.f / tmp;

	//ֻ�ڿ�ʼ��ʱ�����һ��
	if (scene_list == 0)
	{
		scene_list = glGenLists(1);
		glNewList(scene_list, GL_COMPILE);
		recursive_render(scene, scene->mRootNode);
		glEndList();
	}

	glPushMatrix();
	glScalef(tmp, tmp, tmp);
	glTranslatef(-scene_center.x, -scene_center.y, -scene_center.z);
	glCallList(scene_list);
	glPopMatrix();

	do_motion();

}

//���ö�ȡģ�ͺ�����ĺ���
bool AssimpLoad::Load(const string path)
{
	modelpath = path;
	isWithText = true;
	if (!LoadModel()) return false;
	if (!LoadTextures()) return false;

	return true;
}

void AssimpLoad::SetMaterialColor(float dd[4], float ss[4], float aa[4], float ee[4])
{
	for (int i = 0; i < 4; i++) {
		d[i] = dd[i];
		s[i] = ss[i];
		a[i] = aa[i];
		e[i] = ee[i];
	}
}

bool AssimpLoad::LoadWithoutText(const string path)
{
	modelpath = path;
	isWithText = false;
	if (!LoadModel()) return false;

	return true;
}

void AssimpLoad::Clear()
{
	aiReleaseImport(scene);
	aiDetachAllLogStreams();
	scene_list = 0;
}

AssimpLoad::~AssimpLoad()
{
	aiReleaseImport(scene);
	aiDetachAllLogStreams();
}
