#ifndef GEOMETRY_IMPROVER_EDGE_VERTEX_TAYLOR_PATCH
#define GEOMETRY_IMPROVER_EDGE_VERTEX_TAYLOR_PATCH

#include "adjacency_search_closest_points.h"
#include "change_of_basis.h"
#include "geometry_improver.h"
#include "surface_patch.h"
#include <queue>
#include <set>

namespace stk {
namespace middle_mesh {
namespace nonconformal4 {
namespace impl {

class GeometryImproverEdgeVertexSurfacePatch : public GeometryImprover
{
  public:
    GeometryImproverEdgeVertexSurfacePatch(std::shared_ptr<mesh::Mesh> mesh1, std::shared_ptr<mesh::Mesh> mesh2,
                                           std::shared_ptr<mesh::Mesh> meshIn,
                                           std::shared_ptr<MeshRelationalData> relationalData,
                                           mesh::FieldPtr<utils::Point> normalField,
                                           std::shared_ptr<utils::impl::SurfacePatch> surfacePatch,
                                           int numSurfacePatchPoints)
      : GeometryImprover(mesh1, mesh2, meshIn, relationalData)
      , m_normalField(normalField)
      , m_meshInVertsFromInputVert(mesh::create_field<Bool>(meshIn, mesh::impl::FieldShape(1, 0, 0), 1, false))
      , m_closestPointSearch(meshIn, m_meshInVertsFromInputVert)
      , m_surfacePatch(surfacePatch)
      , m_numSurfacePatchPoints(numSurfacePatchPoints)
    {
      setup_vert_status_field();
    }

    void run() override;

  private:
    using Bool = int_least8_t;

    void setup_vert_status_field();

    void reconstruct_edge_vertex_positions();

    void restore_mesh1_vertices();

    utils::Point get_normal_vector(mesh::MeshEntityPtr edge2, double xi);

    mesh::FieldPtr<utils::Point> m_normalField;
    mesh::FieldPtr<Bool> m_meshInVertsFromInputVert;
    mesh::impl::AdjacencySearchClosestPoints m_closestPointSearch;
    std::shared_ptr<utils::impl::SurfacePatch> m_surfacePatch;
    int m_numSurfacePatchPoints;
};

} // namespace impl

} // namespace nonconformal4
} // namespace middle_mesh
} // namespace stk
#endif