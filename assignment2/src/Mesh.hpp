#include "atlas/utils/Geometry.hpp"
#include "atlas/gl/VertexArrayObject.hpp"
#include "atlas/gl/Buffer.hpp"
#include "atlas/math/Math.hpp"
#include "MarchingCubes.hpp"
#include "Sphere.hpp"
#include "atlas\utils\Mesh.hpp"
#include <numeric>


#include <iostream>

namespace assignment2
{
    using Vector3 = atlas::math::Point;
    using AtlasMesh = atlas::utils::Mesh;

    class Mesh : public atlas::utils::Geometry
    {
        enum RenderTypes
        {
            ATLAS_MESH = 0,
            LINES,
            VERTICES
        };

        public:
            Mesh::Mesh();

            void addSceneSphere(Sphere *sphere);
            void createMesh();
            void renderGeometry(atlas::math::Matrix4 const& projection,
                atlas::math::Matrix4 const& view) override;
            void setRenderType(int type);

        private:
            RenderTypes currentRenderType;

        protected:
            std::vector<Sphere*> mMeshSpheres;
            std::vector<atlas::math::Point> mMeshVertices;
            std::vector<atlas::math::Normal> mMeshNormals;
            std::size_t mNumIndices;

            atlas::gl::VertexArrayObject mVao;
            atlas::gl::Buffer mBuffer;


            MarchingCubes marchingCubes;
            AtlasMesh mAtlasMesh;

            
    };
}
