#ifndef VARIABLE_SIZE_FIELD_H
#define VARIABLE_SIZE_FIELD_H

#include "field_base.h"
#include "mesh.h"
#include "variable_size_field_impl.h"
#include <vector>

namespace stk {
namespace middle_mesh {
namespace mesh {

class Mesh;

template <typename T>
class VariableSizeField : public impl::FieldBase
{
  public:
    VariableSizeField(const impl::FieldShape& fshape, const impl::EntityCount count, std::shared_ptr<Mesh> mesh)
      : m_fshape(fshape)
      , m_mesh(mesh)
      , m_fields{{0, fshape.count[0], count.count[0]},
                 {1, fshape.count[1], count.count[1]},
                 {2, fshape.count[2], count.count[2]}}
    {}

    VariableSizeField<T>& operator=(const VariableSizeField<T>&) = delete;

    using ValueType = T;

    T& operator()(MeshEntityPtr entity, int node, int component)
    {
      assert(is_entity_on_mesh(entity));
      return m_fields[get_type_dimension(entity->get_type())].operator()(entity, node, component);
    }

    const T& operator()(MeshEntityPtr entity, int node, int component) const
    {
      assert(is_entity_on_mesh(entity));
      return m_fields[get_type_dimension(entity->get_type())].operator()(entity, node, component);
    }

    void insert(MeshEntityPtr entity, int node, const T& val = T())
    {
      assert(is_entity_on_mesh(entity));
      return m_fields[get_type_dimension(entity->get_type())].insert(entity, node, val);
    }

    void clear(int dim) { m_fields[dim].clear(); }

    int get_num_nodes(int dim) const { return m_fields[dim].get_num_nodes(); }

    int get_num_comp(MeshEntityPtr entity, int node) const
    {
      assert(is_entity_on_mesh(entity));
      return m_fields[get_type_dimension(entity->get_type())].get_num_comp(entity, node);
    }

    void set(const T& init)
    {
      for (auto& field : m_fields)
        field.set(init);
    }

    const impl::FieldShape& get_field_shape() const { return m_fshape; }

    std::shared_ptr<Mesh> get_mesh() const { return m_mesh; }

  protected:
    void add_entity(int dim) override { m_fields[dim].add_entity(); }

    void condense_arrays(const std::vector<MeshEntityPtr>& verts, const std::vector<MeshEntityPtr>& edges,
                         const std::vector<MeshEntityPtr>& elements) override
    {
      m_fields[0].condense_array(verts);
      m_fields[1].condense_array(edges);
      m_fields[2].condense_array(elements);
    }

    bool is_entity_on_mesh(MeshEntityPtr entity) const
    {
      int dim               = get_type_dimension(entity->get_type());
      MeshEntityPtr entity2 = m_mesh->get_mesh_entities(dim)[entity->get_id()];
      return entity == entity2;
    }

  private:
    impl::FieldShape m_fshape;
    std::shared_ptr<Mesh> m_mesh;
    std::vector<impl::VariableSizeFieldForDimension<T>> m_fields;
};

template <typename T>
using VariableSizeFieldPtr = std::shared_ptr<VariableSizeField<T>>;

template <typename T>
VariableSizeFieldPtr<T> create_variable_size_field(std::shared_ptr<Mesh> mesh, const impl::FieldShape& fshape)
{
  impl::EntityCount count(mesh->get_vertices().size(), mesh->get_edges().size(), mesh->get_elements().size());
  auto field = std::make_shared<VariableSizeField<T>>(fshape, count, mesh);
  mesh->attach_field(field);

  return field;
}

} // namespace mesh

} // namespace middle_mesh
} // namespace stk
#endif