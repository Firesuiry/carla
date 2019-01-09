// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/MsgPack.h"

#include <cmath>
#include <limits>

namespace carla {
namespace geom {

  class Vector3D {
  public:

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vector3D() = default;

    Vector3D(float ix, float iy, float iz)
      : x(ix),
        y(iy),
        z(iz) {}

    Vector3D &operator+=(const Vector3D &rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }

    friend Vector3D operator+(Vector3D lhs, const Vector3D &rhs) {
      lhs += rhs;
      return lhs;
    }

    Vector3D &operator-=(const Vector3D &rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      return *this;
    }

    friend Vector3D operator-(Vector3D lhs, const Vector3D &rhs) {
      lhs -= rhs;
      return lhs;
    }

    Vector3D &operator*=(const double &rhs) {
      x *= rhs;
      y *= rhs;
      z *= rhs;
      return *this;
    }

    friend Vector3D operator*(Vector3D lhs, const double &rhs) {
      lhs *= rhs;
      return lhs;
    }

    friend Vector3D operator*(const double &lhs, Vector3D rhs) {
      rhs *= lhs;
      return rhs;
    }

    Vector3D &operator/=(const double &rhs) {
      x /= rhs;
      y /= rhs;
      z /= rhs;
      return *this;
    }

    friend Vector3D operator/(Vector3D lhs, const double &rhs) {
      lhs /= rhs;
      return lhs;
    }

    friend Vector3D operator/(const double &lhs, Vector3D rhs) {
      rhs /= lhs;
      return rhs;
    }

    bool operator==(const Vector3D &rhs) const {
      return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
    }

    bool operator!=(const Vector3D &rhs) const {
      return !(*this == rhs);
    }

    double SquaredLength() const {
      return x * x + y * y + z * z;
    }

    double Length() const {
       return std::sqrt(SquaredLength());
    }

    Vector3D MakeUnitVector() const {
      const double len = Length();
      DEBUG_ASSERT(len > std::numeric_limits<double>::epsilon());
      double k = 1.0 / len;
      return Vector3D(x * k, y * k, z * k);
    }

#ifdef LIBCARLA_INCLUDED_FROM_UE4

    Vector3D(const FVector &vector) // from centimeters to meters.
      : Vector3D(1e-2f * vector.X, 1e-2f * vector.Y, 1e-2f * vector.Z) {}

    operator FVector() const {
      return FVector{1e2f * x, 1e2f * y, 1e2f * z}; // from meters to centimeters.
    }

#endif // LIBCARLA_INCLUDED_FROM_UE4

    // =========================================================================
    /// @todo The following is copy-pasted from MSGPACK_DEFINE_ARRAY.
    /// This is a workaround for an issue in msgpack library. The
    /// MSGPACK_DEFINE_ARRAY macro is shadowing our `z` variable.
    /// https://github.com/msgpack/msgpack-c/issues/709
    // =========================================================================
    template <typename Packer>
    void msgpack_pack(Packer& pk) const
    {
        clmdep_msgpack::type::make_define_array(x, y, z).msgpack_pack(pk);
    }
    void msgpack_unpack(clmdep_msgpack::object const& o)
    {
        clmdep_msgpack::type::make_define_array(x, y, z).msgpack_unpack(o);
    }
    template <typename MSGPACK_OBJECT>
    void msgpack_object(MSGPACK_OBJECT* o, clmdep_msgpack::zone& sneaky_variable_that_shadows_z) const
    {
        clmdep_msgpack::type::make_define_array(x, y, z).msgpack_object(o, sneaky_variable_that_shadows_z);
    }
    // =========================================================================
  };

} // namespace geom
} // namespace carla
