/// @file glm/ext.hpp
///
/// @ref core (Dependence)
/// 
/// @defgroup gtc GTC Extensions (Stable)
///
/// @brief Functions and types that the GLSL specification doesn't define, but useful to have for a C++ program.
/// 
/// GTC extensions aim to be stable. 
/// 
/// Even if it's highly unrecommended, it's possible to include all the extensions at once by
/// including <glm/ext.hpp>. Otherwise, each extension needs to be included  a specific file.
/// 
/// @defgroup gtx GTX Extensions (Experimental)
/// 
/// @brief Functions and types that the GLSL specification doesn't define, but 
/// useful to have for a C++ program.
/// 
/// Experimental extensions are useful functions and types, but the development of
/// their API and functionality is not necessarily stable. They can change 
/// substantially between versions. Backwards compatibility is not much of an issue
/// for them.
/// 
/// Even if it's highly unrecommended, it's possible to include all the extensions 
/// at once by including <glm/ext.hpp>. Otherwise, each extension needs to be 
/// included  a specific file.

#pragma once

#include "glm.hpp"

#if GLM_MESSAGES == GLM_MESSAGES_ENABLED && !defined(GLM_MESSAGE_EXT_INCLUDED_DISPLAYED)
#	define GLM_MESSAGE_EXT_INCLUDED_DISPLAYED
#	pragma message("GLM: All extensions included (not recommanded)")
#endif//GLM_MESSAGES

#include "bin/dependencies/include/glm/gtc/bitfield.hpp"
#include "bin/dependencies/include/glm/gtc/color_space.hpp"
#include "bin/dependencies/include/glm/gtc/constants.hpp"
#include "bin/dependencies/include/glm/gtc/epsilon.hpp"
#include "bin/dependencies/include/glm/gtc/functions.hpp"
#include "bin/dependencies/include/glm/gtc/integer.hpp"
#include "bin/dependencies/include/glm/gtc/matrix_access.hpp"
#include "bin/dependencies/include/glm/gtc/matrix_integer.hpp"
#include "bin/dependencies/include/glm/gtc/matrix_inverse.hpp"
#include "bin/dependencies/include/glm/gtc/matrix_transform.hpp"
#include "bin/dependencies/include/glm/gtc/noise.hpp"
#include "bin/dependencies/include/glm/gtc/packing.hpp"
#include "bin/dependencies/include/glm/gtc/quaternion.hpp"
#include "bin/dependencies/include/glm/gtc/random.hpp"
#include "bin/dependencies/include/glm/gtc/reciprocal.hpp"
#include "bin/dependencies/include/glm/gtc/round.hpp"
//#include "./gtc/type_aligned.hpp"
#include "bin/dependencies/include/glm/gtc/type_precision.hpp"
#include "bin/dependencies/include/glm/gtc/type_ptr.hpp"
#include "bin/dependencies/include/glm/gtc/ulp.hpp"
#include "bin/dependencies/include/glm/gtc/vec1.hpp"
#if GLM_HAS_ALIGNED_TYPE
#	include "bin/dependencies/include/glm/gtc/type_aligned.hpp"
#endif

#include "bin/dependencies/include/glm/gtx/associated_min_max.hpp"
#include "bin/dependencies/include/glm/gtx/bit.hpp"
#include "bin/dependencies/include/glm/gtx/closest_point.hpp"
#include "bin/dependencies/include/glm/gtx/color_space.hpp"
#include "bin/dependencies/include/glm/gtx/color_space_YCoCg.hpp"
#include "bin/dependencies/include/glm/gtx/compatibility.hpp"
#include "bin/dependencies/include/glm/gtx/component_wise.hpp"
#include "bin/dependencies/include/glm/gtx/dual_quaternion.hpp"
#include "bin/dependencies/include/glm/gtx/euler_angles.hpp"
#include "bin/dependencies/include/glm/gtx/extend.hpp"
#include "bin/dependencies/include/glm/gtx/extended_min_max.hpp"
#include "bin/dependencies/include/glm/gtx/fast_exponential.hpp"
#include "bin/dependencies/include/glm/gtx/fast_square_root.hpp"
#include "bin/dependencies/include/glm/gtx/fast_trigonometry.hpp"
#include "bin/dependencies/include/glm/gtx/gradient_paint.hpp"
#include "bin/dependencies/include/glm/gtx/handed_coordinate_space.hpp"
#include "bin/dependencies/include/glm/gtx/integer.hpp"
#include "bin/dependencies/include/glm/gtx/intersect.hpp"
#include "bin/dependencies/include/glm/gtx/log_base.hpp"
#include "bin/dependencies/include/glm/gtx/matrix_cross_product.hpp"
#include "bin/dependencies/include/glm/gtx/matrix_interpolation.hpp"
#include "bin/dependencies/include/glm/gtx/matrix_major_storage.hpp"
#include "bin/dependencies/include/glm/gtx/matrix_operation.hpp"
#include "bin/dependencies/include/glm/gtx/matrix_query.hpp"
#include "bin/dependencies/include/glm/gtx/mixed_product.hpp"
#include "bin/dependencies/include/glm/gtx/norm.hpp"
#include "bin/dependencies/include/glm/gtx/normal.hpp"
#include "bin/dependencies/include/glm/gtx/normalize_dot.hpp"
#include "bin/dependencies/include/glm/gtx/number_precision.hpp"
#include "bin/dependencies/include/glm/gtx/optimum_pow.hpp"
#include "bin/dependencies/include/glm/gtx/orthonormalize.hpp"
#include "bin/dependencies/include/glm/gtx/perpendicular.hpp"
#include "bin/dependencies/include/glm/gtx/polar_coordinates.hpp"
#include "bin/dependencies/include/glm/gtx/projection.hpp"
#include "bin/dependencies/include/glm/gtx/quaternion.hpp"
#include "bin/dependencies/include/glm/gtx/raw_data.hpp"
#include "bin/dependencies/include/glm/gtx/rotate_vector.hpp"
#include "bin/dependencies/include/glm/gtx/spline.hpp"
#include "bin/dependencies/include/glm/gtx/std_based_type.hpp"
#if !(GLM_COMPILER & GLM_COMPILER_CUDA)
#	include "bin/dependencies/include/glm/gtx/string_cast.hpp"
#endif
#include "bin/dependencies/include/glm/gtx/transform.hpp"
#include "bin/dependencies/include/glm/gtx/transform2.hpp"
#include "bin/dependencies/include/glm/gtx/vector_angle.hpp"
#include "bin/dependencies/include/glm/gtx/vector_query.hpp"
#include "bin/dependencies/include/glm/gtx/wrap.hpp"

#if GLM_HAS_TEMPLATE_ALIASES
#	include "bin/dependencies/include/glm/gtx/scalar_multiplication.hpp"
#endif

#if GLM_HAS_RANGE_FOR
#	include "bin/dependencies/include/glm/gtx/range.hpp"
#endif
