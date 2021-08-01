#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <iostream>
#include <vector>

Model::Model(const std::vector<Mesh*>& meshes, const std::vector<Material*>& materials, const std::vector<uint64_t>& meshMaterialIndices)
    : m_Meshes(meshes), m_Materials(materials), m_meshMaterialIndices(meshMaterialIndices)
{}

Model::~Model() {
    for (auto material : m_Materials) delete(material);
    for (auto mesh : m_Meshes) delete(mesh);
}

void Model::addMaterial(Material* material) {
    m_Materials.push_back(material);
}

void Model::setCommonShader(Shader* shader) {
    for (auto material : m_Materials) material->setShader(shader);
}

Model Model::loadFromFile(const std::string& path) {
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./assets/sponza_scene"; // Path to material files
    reader_config.triangulate = true;

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<Mesh*> o_meshes;
    std::vector<Material*> o_materials;
    std::vector<uint64_t> o_meshMaterialIndices;

    // Loop over shapes
    for (size_t shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
        // Create buffers for Vertices and Indices for each Mesh
        std::vector<Vertex> verts;
        std::vector<uint32_t> indices;

        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[shapeIndex].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[shapeIndex].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[shapeIndex].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

                // Check if `normal_index` is zero or positive. negative = no normal data
                tinyobj::real_t nx = 0.0f;
                tinyobj::real_t ny = 0.0f;
                tinyobj::real_t nz = 0.0f;
                if (idx.normal_index >= 0) {
                    nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                tinyobj::real_t tx = 0.0f;
                tinyobj::real_t ty = 0.0f;
                if (idx.texcoord_index >= 0) {
                    tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                }

                verts.push_back({ {vx,vy,vz}, {nx,ny,nz}, {tx,ty} });
                indices.push_back(verts.size() - 1);

                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
            }
            index_offset += fv;

            // per-face material
            if (o_meshMaterialIndices.size() <= shapeIndex) o_meshMaterialIndices.push_back(shapes[shapeIndex].mesh.material_ids[f]);
        }

        o_meshes.push_back(new Mesh(verts, indices));
    }

    for (size_t materialIndex = 0; materialIndex < materials.size(); ++materialIndex) {
        auto matDesc = materials[materialIndex]; // Material descriptor
        Material* material = new Material();

        if (matDesc.diffuse_texname != "") material->addTexture("./assets/sponza_scene/" + matDesc.diffuse_texname);

        o_materials.push_back(material);
    }

    return Model(o_meshes, o_materials, o_meshMaterialIndices);
}
