#ifndef NONCONFORMAL_FOUR_OPTS_H
#define NONCONFORMAL_FOUR_OPTS_H

// #include "predicates/point_classifier_normal_wrapper.h"
#include "edge_tracer_opts.h"
#include "geometry_improver_factory.h"
#include "predicates/point_classifier_opts.h"

namespace stk {
namespace middle_mesh {

struct NormalProjectionOpts
{
    impl::PointClassifierNormalWrapperTolerances classifierTolerances;
    impl::EdgeTracerTolerances edgeTracerTolerances;
    std::vector<nonconformal4::impl::GeometryImprovers> geometryImprovers;
};

} // namespace middle_mesh
} // namespace stk

#endif