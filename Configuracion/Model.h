#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <cmath>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include  "Shader.h"

using namespace std;

GLint TextureFromFile(const char *path, string directory);

class Model
{
private:
	struct BoneInfo
	{
		glm::mat4 offset;
		glm::mat4 finalTransform;
	};

	struct RigNode
	{
		string name;
		glm::mat4 bindLocal;
		glm::vec3 bindTranslation;
		glm::quat bindRotation;
		glm::vec3 bindScale;
		vector<RigNode> children;
	};

	struct VectorKey
	{
		double time;
		glm::vec3 value;
	};

	struct RotationKey
	{
		double time;
		glm::quat value;
	};

	struct NodeChannel
	{
		vector<VectorKey> positions;
		vector<RotationKey> rotations;
		vector<VectorKey> scales;
	};

	struct AnimationClip
	{
		double duration;
		double ticksPerSecond;
		unordered_map<string, NodeChannel> channels;
	};

public:
	static const unsigned int MaxBones = 55;

	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	Model(GLchar *path, GLfloat horizontalScale = 1.0f)
	{
		this->horizontalScale = horizontalScale;
		this->loadModel(path);
	}

	// Draws the model, and thus all its meshes
	void Draw(Shader shader)
	{
		if (!boneMatrices.empty())
		{
			const GLint location = glGetUniformLocation(shader.Program, "bones[0]");
			if (location >= 0)
				glUniformMatrix4fv(location, static_cast<GLsizei>(boneMatrices.size()), GL_FALSE,
					glm::value_ptr(boneMatrices[0]));
		}

		for (GLuint i = 0; i < this->meshes.size(); i++)
		{
			this->meshes[i].Draw(shader);
		}
	}

	void UpdateAnimation(const string& animationName, GLfloat deltaTime)
	{
		if (currentAnimation != animationName)
		{
			currentAnimation = animationName;
			animationTime = 0.0;
		}
		else if (deltaTime > 0.0f)
		{
			animationTime += deltaTime;
		}

		const auto animation = animations.find(animationName);
		const AnimationClip* clip = animation == animations.end() ? nullptr : &animation->second;
		double timeInTicks = 0.0;
		if (clip != nullptr && clip->duration > 0.0)
			timeInTicks = std::fmod(animationTime * clip->ticksPerSecond, clip->duration);

		CalculatePose(rigRoot, glm::mat4(1.0f), clip, timeInTicks);
		boneMatrices.resize(bones.size(), glm::mat4(1.0f));
		for (size_t i = 0; i < bones.size(); ++i)
			boneMatrices[i] = bones[i].finalTransform;
	}

private:
	/*  Model Data  */
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	GLfloat horizontalScale = 1.0f;
	RigNode rigRoot;
	glm::mat4 rootInverse = glm::mat4(1.0f);
	vector<BoneInfo> bones;
	vector<glm::mat4> boneMatrices;
	unordered_map<string, unsigned int> boneIds;
	unordered_map<string, AnimationClip> animations;
	string currentAnimation;
	double animationTime = 0.0;

										/*  Functions   */
										// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(const string& path)
	{
		// Read file via ASSIMP
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_LimitBoneWeights);

		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		// Retrieve the directory path of the filepath
		const size_t separator = path.find_last_of("/\\");
		this->directory = separator == string::npos ? "." : path.substr(0, separator);
		rigRoot = CopyNode(scene->mRootNode);
		rootInverse = glm::inverse(ToGlm(scene->mRootNode->mTransformation));
		CopyAnimations(scene);

		// Process ASSIMP's root node recursively
		this->processNode(scene->mRootNode, scene);
		UpdateAnimation("Idle", 0.0f);
	}

	static glm::mat4 ToGlm(const aiMatrix4x4& value)
	{
		return glm::mat4(
			value.a1, value.b1, value.c1, value.d1,
			value.a2, value.b2, value.c2, value.d2,
			value.a3, value.b3, value.c3, value.d3,
			value.a4, value.b4, value.c4, value.d4);
	}

	static glm::vec3 ToGlm(const aiVector3D& value)
	{
		return glm::vec3(value.x, value.y, value.z);
	}

	static glm::quat ToGlm(const aiQuaternion& value)
	{
		return glm::quat(value.w, value.x, value.y, value.z);
	}

	static RigNode CopyNode(const aiNode* source)
	{
		RigNode result;
		result.name = source->mName.C_Str();
		result.bindLocal = ToGlm(source->mTransformation);
		aiVector3D scaling;
		aiVector3D position;
		aiQuaternion rotation;
		source->mTransformation.Decompose(scaling, rotation, position);
		result.bindTranslation = ToGlm(position);
		result.bindRotation = ToGlm(rotation);
		result.bindScale = ToGlm(scaling);
		for (unsigned int i = 0; i < source->mNumChildren; ++i)
			result.children.push_back(CopyNode(source->mChildren[i]));
		return result;
	}

	void CopyAnimations(const aiScene* scene)
	{
		for (unsigned int i = 0; i < scene->mNumAnimations; ++i)
		{
			const aiAnimation* source = scene->mAnimations[i];
			std::cout << "[ASSIMP] Found animation: " << source->mName.C_Str() << " channels: " << source->mNumChannels << " duration: " << source->mDuration << std::endl;
			AnimationClip clip;
			clip.duration = source->mDuration;
			clip.ticksPerSecond = source->mTicksPerSecond > 0.0 ? source->mTicksPerSecond : 25.0;

			for (unsigned int channelIndex = 0; channelIndex < source->mNumChannels; ++channelIndex)
			{
				const aiNodeAnim* sourceChannel = source->mChannels[channelIndex];
				std::cout << "   Channel: " << sourceChannel->mNodeName.C_Str() << std::endl;
				NodeChannel channel;
				for (unsigned int key = 0; key < sourceChannel->mNumPositionKeys; ++key)
					channel.positions.push_back({ sourceChannel->mPositionKeys[key].mTime,
						ToGlm(sourceChannel->mPositionKeys[key].mValue) });
				for (unsigned int key = 0; key < sourceChannel->mNumRotationKeys; ++key)
					channel.rotations.push_back({ sourceChannel->mRotationKeys[key].mTime,
						ToGlm(sourceChannel->mRotationKeys[key].mValue) });
				for (unsigned int key = 0; key < sourceChannel->mNumScalingKeys; ++key)
					channel.scales.push_back({ sourceChannel->mScalingKeys[key].mTime,
						ToGlm(sourceChannel->mScalingKeys[key].mValue) });
				clip.channels[sourceChannel->mNodeName.C_Str()] = channel;
			}

			animations[source->mName.C_Str()] = clip;
		}
	}

	static glm::vec3 SampleVector(const vector<VectorKey>& keys, double time, const glm::vec3& fallback)
	{
		if (keys.empty())
			return fallback;
		if (keys.size() == 1 || time <= keys.front().time)
			return keys.front().value;
		if (time >= keys.back().time)
			return keys.back().value;

		for (size_t i = 0; i + 1 < keys.size(); ++i)
		{
			if (time <= keys[i + 1].time)
			{
				const double span = keys[i + 1].time - keys[i].time;
				const float factor = span > 0.0 ? static_cast<float>((time - keys[i].time) / span) : 0.0f;
				return glm::mix(keys[i].value, keys[i + 1].value, factor);
			}
		}
		return keys.back().value;
	}

	static glm::quat SampleRotation(const vector<RotationKey>& keys, double time, const glm::quat& fallback)
	{
		if (keys.empty())
			return fallback;
		if (keys.size() == 1 || time <= keys.front().time)
			return keys.front().value;
		if (time >= keys.back().time)
			return keys.back().value;

		for (size_t i = 0; i + 1 < keys.size(); ++i)
		{
			if (time <= keys[i + 1].time)
			{
				const double span = keys[i + 1].time - keys[i].time;
				const float factor = span > 0.0 ? static_cast<float>((time - keys[i].time) / span) : 0.0f;
				glm::quat first = keys[i].value;
				glm::quat second = keys[i + 1].value;
				float cosine = first.w * second.w + first.x * second.x + first.y * second.y + first.z * second.z;
				if (cosine < 0.0f)
				{
					second = -second;
					cosine = -cosine;
				}
				if (cosine > 0.9995f)
				{
					return glm::normalize(glm::quat(
						first.w + factor * (second.w - first.w),
						first.x + factor * (second.x - first.x),
						first.y + factor * (second.y - first.y),
						first.z + factor * (second.z - first.z)));
				}
				const float angle = std::acos(glm::clamp(cosine, -1.0f, 1.0f));
				const float sine = std::sin(angle);
				const float firstWeight = std::sin((1.0f - factor) * angle) / sine;
				const float secondWeight = std::sin(factor * angle) / sine;
				return glm::normalize(first * firstWeight + second * secondWeight);
			}
		}
		return keys.back().value;
	}

	void CalculatePose(const RigNode& node, const glm::mat4& parentGlobal,
		const AnimationClip* clip, double timeInTicks)
	{
		glm::mat4 local = node.bindLocal;
		if (clip != nullptr)
		{
			const auto channel = clip->channels.find(node.name);
			if (channel != clip->channels.end())
			{
				const glm::vec3 translation = SampleVector(channel->second.positions, timeInTicks, node.bindTranslation);
				const glm::quat rotation = SampleRotation(channel->second.rotations, timeInTicks, node.bindRotation);
				const glm::vec3 scale = SampleVector(channel->second.scales, timeInTicks, node.bindScale);
				local = glm::translate(glm::mat4(1.0f), translation) * glm::mat4_cast(rotation) *
					glm::scale(glm::mat4(1.0f), scale);
			}
		}

		const glm::mat4 global = parentGlobal * local;
		const auto bone = boneIds.find(node.name);
		if (bone != boneIds.end())
			bones[bone->second].finalTransform = rootInverse * global * bones[bone->second].offset;

		for (const RigNode& child : node.children)
			CalculatePose(child, global, clip, timeInTicks);
	}

	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(const aiNode* node, const aiScene* scene)
	{
		// Process each mesh located at the current node
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			// The node object only contains indices to index the actual objects in the scene.
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			this->meshes.push_back(this->processMesh(mesh, scene));
		}

		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(const aiMesh *mesh, const aiScene *scene)
	{
		// Data to fill
		vector<Vertex> vertices;
		vector<GLuint> indices;
		vector<Texture> textures;

		// Walk through each of the mesh's vertices
		for (GLuint i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

							  // Positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vector.x *= horizontalScale;
			vector.z *= horizontalScale;
			vertex.Position = vector;

			// Normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		// std::cout << "[ASSIMP] Mesh " << mesh->mName.C_Str() << " bones count: " << mesh->mNumBones << std::endl;
		for (unsigned int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
		{
			const aiBone* sourceBone = mesh->mBones[boneIndex];
			const string boneName = sourceBone->mName.C_Str();
			auto bone = boneIds.find(boneName);
			unsigned int boneId;
			if (bone == boneIds.end())
			{
				if (bones.size() >= MaxBones)
				{
					cerr << "ERROR::ASSIMP:: El esqueleto supera el limite de " << MaxBones << " huesos." << endl;
					continue;
				}
				boneId = static_cast<unsigned int>(bones.size());
				boneIds[boneName] = boneId;
				bones.push_back(BoneInfo{ ToGlm(sourceBone->mOffsetMatrix), glm::mat4(1.0f) });
			}
			else
			{
				boneId = bone->second;
			}

			for (unsigned int weightIndex = 0; weightIndex < sourceBone->mNumWeights; ++weightIndex)
			{
				const aiVertexWeight& weight = sourceBone->mWeights[weightIndex];
				if (weight.mVertexId >= vertices.size())
					continue;
				Vertex& vertex = vertices[weight.mVertexId];
				for (int influence = 0; influence < 4; ++influence)
				{
					if (vertex.Weights[influence] == 0.0f)
					{
						vertex.BoneIDs[influence] = static_cast<int>(boneId);
						vertex.Weights[influence] = weight.mWeight;
						break;
					}
				}
			}
		}

		for (Vertex& vertex : vertices)
		{
			const float totalWeight = vertex.Weights.x + vertex.Weights.y + vertex.Weights.z + vertex.Weights.w;
			if (totalWeight > 0.0f)
				vertex.Weights /= totalWeight;
		}

		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Process materials
		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
			// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
			// Same applies to other texture as the following list summarizes:
			// Diffuse: texture_diffuseN
			// Specular: texture_specularN
			// Normal: texture_normalN

			// 1. Diffuse maps
			aiString materialName;
			material->Get(AI_MATKEY_NAME, materialName);
			const string materialNameString = materialName.C_Str();
			if (CharacterTextureForMaterial(materialNameString) != nullptr)
			{
				Texture texture = LoadCharacterTexture(CharacterTextureForMaterial(materialNameString));
				if (texture.id != 0)
					textures.push_back(texture);
				else
				{
					vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
					textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
				}
			}
			else if (TreeTextureForMaterial(materialNameString) != nullptr)
			{
				Texture texture = LoadTreeTexture(TreeTextureForMaterial(materialNameString));
				if (texture.id != 0)
					textures.push_back(texture);
				else
				{
					vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
					textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
				}
			}
			else
			{
				vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			}

			// 2. Specular maps
			vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		// Return a mesh object created from the extracted mesh data
		return Mesh(vertices, indices, textures);
	}

	static const char* CharacterTextureForMaterial(const string& materialName)
	{
		if (materialName == "middleage_asian_male") return "middleage_lightskinned_male_diffuse2.png";
		if (materialName == "short04") return "short04_diffuse.png";
		if (materialName == "Eye_brown") return "brown_eye.png";
		if (materialName == "eyebrow001") return "eyebrow001.png";
		if (materialName == "male_casualsuit02") return "male_casualsuit02_diffuse.png";
		if (materialName == "Shoes02") return "shoes02_diffuse.png";
		if (materialName == "teethMaterial") return "teeth.png";
		if (materialName == "tongue01Material") return "tongue01_diffuse.png";
		if (materialName == "Material_Hombre" || materialName.find("hombre") != string::npos || materialName.find("Hombre") != string::npos) return "hombre_diffuse.png";
		return nullptr;
	}

	Texture LoadCharacterTexture(const string& filename)
	{
		const string relativePath = "Textures/textures_hombre/" + filename;
		for (const Texture& loaded : textures_loaded)
		{
			if (relativePath == loaded.path.C_Str())
				return loaded;
		}

		Texture texture;
		texture.id = TextureFromFile(relativePath.c_str(), directory);
		if (texture.id == 0)
			return texture;
		texture.type = "texture_diffuse";
		texture.path.Set(relativePath.c_str());
		textures_loaded.push_back(texture);
		return texture;
	}

	static const char* TreeTextureForMaterial(const string& materialName)
	{
		if (materialName.find("Hoja") != string::npos) return "Hoja_Df.png";
		if (materialName.find("Tronco") != string::npos) return "Tronco_Df.png";
		if (materialName.find("Flor") != string::npos) return "Flores_Df.png";
		return nullptr;
	}

	Texture LoadTreeTexture(const string& filename)
	{
		const string relativePath = "Textures/textures_arbol/" + filename;
		for (const Texture& loaded : textures_loaded)
		{
			if (relativePath == loaded.path.C_Str())
				return loaded;
		}

		Texture texture;
		texture.id = TextureFromFile(relativePath.c_str(), directory);
		if (texture.id == 0)
			return texture;
		texture.type = "texture_diffuse";
		texture.path.Set(relativePath.c_str());
		textures_loaded.push_back(texture);
		return texture;
	}

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// The required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;

		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			GLboolean skip = false;

			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (textures_loaded[j].path == str)
				{
					textures.push_back(textures_loaded[j]);
					skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)

					break;
				}
			}

			if (!skip)
			{   // If texture hasn't been loaded already, load it
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory);
				if (texture.id == 0)
					continue;
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);

				this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			}
		}

		return textures;
	}
};

GLint TextureFromFile(const char *path, string directory)
{
	//Generate texture ID and load texture data
	string filename = string(path);
	string fullPath = directory + '/' + filename;
	int width = 0;
	int height = 0;
	unsigned char *image = SOIL_load_image(fullPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == nullptr || width <= 0 || height <= 0)
	{
		string alt1 = "Models/Plaza_Colonial_Blender_3D/" + filename;
		image = SOIL_load_image(alt1.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (image != nullptr && width > 0 && height > 0)
			fullPath = alt1;
	}
	if (image == nullptr || width <= 0 || height <= 0)
	{
		string alt2 = "Models/Plaza_Colonial_Blender_3D/textures/" + filename;
		image = SOIL_load_image(alt2.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (image != nullptr && width > 0 && height > 0)
			fullPath = alt2;
	}
	if (image == nullptr || width <= 0 || height <= 0)
	{
		std::cerr << "ERROR::TEXTURE::LOAD_FAILED: " << fullPath
			<< " (" << SOIL_last_result() << ")" << std::endl;
		if (image != nullptr)
			SOIL_free_image_data(image);
		return 0;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLint previousUnpackAlignment;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousUnpackAlignment);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glPixelStorei(GL_UNPACK_ALIGNMENT, previousUnpackAlignment);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters (UV repeat y filtrado anisotropico de alta calidad para evitar texturas estiradas o borrosas)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
	GLfloat maxAniso = 0.0f;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
	if (maxAniso > 0.0f)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, std::min(maxAniso, 16.0f));
#endif
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}
