#include "ModelLoader.h"
std::vector<Mesh*> ModelLoader::parents;
std::vector<Mesh*> ModelLoader::planeBSP;
void ModelLoader::LoadModel(std::string const& path, ModelStruct& structure)
{
    parents.clear();
    //textures_loaded.clear();
    //meshes.clear();
    //directory = "";
    ModelStruct _structure;
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Error::Assimp" << importer.GetErrorString() << std::endl;
        return;
    }
    _structure.directory = path.substr(0, path.find_last_of('/'));
    std::string aux = path.substr(path.find_last_of('/') + 1);
    std::cout << _structure.directory << std::endl;
    if (aux == "Planes.fbx")
    {
        ProcessRootPlane(scene->mRootNode, scene, _structure);

    }
    else
    {
      ProcessRootNode(scene->mRootNode, scene, _structure);
    }
    //parents[0]->isRoot = true;
    structure = _structure;
}

void ModelLoader::ProcessRootPlane(aiNode* root, const aiScene* scene, ModelStruct& _structure)
{
    Mesh* rootMesh = ProcessMeshForRoot(root, scene, _structure);
    if (rootMesh) {
        _structure.meshes.insert(_structure.meshes.begin(), rootMesh);
    }
    _structure.parentMesh = rootMesh;
    for (size_t i = 0; i < root->mNumChildren; i++) {
        Mesh* newchildren = ProcessNode(root->mChildren[i], scene, _structure, false);
        newchildren->parent = rootMesh;
        if(rootMesh) rootMesh->children.push_back(newchildren); 
        planeBSP.push_back(newchildren);
        BSP::AddPlane(newchildren);
    }
}


void ModelLoader::ProcessRootNode(aiNode* root, const aiScene* scene, ModelStruct& _structure) 
{
    // Procesar el mesh del root (puede ser nulo si no tiene meshes)
    Mesh* rootMesh = ProcessMeshForRoot(root, scene, _structure);
    if (rootMesh) {
        _structure.meshes.insert(_structure.meshes.begin(), rootMesh);
    }
    _structure.parentMesh = rootMesh;
    // Llamar a la función recursiva para procesar nodos hijos
    for (size_t i = 0; i < root->mNumChildren; i++) {
        Mesh* newchildren = ProcessNode(root->mChildren[i], scene, _structure, false);
        newchildren->parent = rootMesh;
        if(rootMesh)rootMesh->children.push_back(newchildren);
    }
}

Mesh* ModelLoader::ProcessMeshForRoot(aiNode* root, const aiScene* scene, ModelStruct& _structure) {
    Mesh* rootMesh = nullptr;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;

    Vertex vertex;
    vertex.position = glm::vec3(0.0f, 0.0f, 0.0f);
    vertices.push_back(vertex);
    indices.push_back(0);


    rootMesh = new Mesh(vertices, indices, textures,glm::vec3(0,0,0));
    rootMesh->vertices.clear();
    vertices.clear();
    rootMesh->isRoot = true;

    parents.push_back(rootMesh);

    return rootMesh;
}


Mesh* ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, ModelStruct& _structure, bool isRoot)
{
    Mesh* m;
    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m = ProcessMesh(mesh, scene, _structure, isRoot);
        m->SetNode(node);
        
        for (int i = 0; i < parents.size(); i++)
            if (m->GetNode()->mParent == parents[i]->GetNode())
            {
                m->SetParent(parents[i]);
                parents[i]->AddMeshSon(m);
                break;
            }
        m->isRoot = isRoot;
        if (node->mNumChildren > 0)
            if (!m->imParent)
            {
                m->imParent = true;
                parents.push_back(m);
            }
    }
    _structure.meshes.push_back(m);
    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, _structure, false);
        
    }
    return m;
}

Mesh* ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene, ModelStruct &_structure,bool isRoot) 
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texCoord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    
    std::vector<TextureData> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", _structure);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<TextureData> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", _structure);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<TextureData> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", _structure);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<TextureData> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", _structure);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return new Mesh(vertices, indices, textures,glm::vec3(mesh->mNormals[0].x, mesh->mNormals[0].y, mesh->mNormals[0].z));
}

std::vector<TextureData> ModelLoader::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName,ModelStruct &_structure) 
{
    std::vector<TextureData> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < _structure.textures_loaded.size(); j++)
        {
            if (std::strcmp(_structure.textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_structure.textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            TextureData texture;
            texture = TextureImporter::ImportFromFile(str.C_Str(), _structure.directory);
            if (texture.path == "")
            {
                _structure.directory = "../SlayerWxEngine/assets/texture";
                texture = TextureImporter::ImportFromFile("blank.jpg", _structure.directory);
            }
            texture.txType = typeName;
            textures.push_back(texture);
            _structure.textures_loaded.push_back(texture);
        }
    }
    return textures;
}