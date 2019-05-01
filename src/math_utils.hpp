//
//   Copyright 2019 University of Sheffield
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef UTILS_HPP
#define UTILS_HPP

#include "types.hpp"

#include <numeric>

#include "exceptions.hpp"

void quadratic_from_points(floating x_1, floating x_2, floating x_3,
                           floating y_1, floating y_2, floating y_3,
                           floating &a, floating &b, floating &c);

void quadratic_vertex(floating a, floating b, floating c, floating &x, floating &y);

void binarize_vector(Vec &vec, floating thres);

void dilate_dmda(DM &dmda, Vec &vec);

inline floating mat_size(integer ndim, integer nvox)
{
  floating nd = std::pow(2, ndim);
  // matrix index size seems to be 8 even if PetscInt is 4 byte...
  integer petscintsize = 8;
  return nvox * (nd * sizeof(floating) + (nd + 1) * petscintsize);
}

inline void explain_memory(const intvector &image_size, const intvector &map_size)
{
  if (image_size.size() < 2 || image_size.size() > 3)
  {
    throw InternalError("Image should be 2D or 3D", __FILE__, __LINE__);
  }

  if (map_size.size() != image_size.size())
  {
    throw InternalError("Map and image dimensions should match", __FILE__, __LINE__);
  }

  integer ndim = image_size.size();
  floating nvox = std::accumulate(image_size.begin(), image_size.end(), 1, std::multiplies<>());
  floating nmapnod = std::accumulate(map_size.begin(), map_size.end(), 1, std::multiplies<>());

  integer floatbytes = sizeof(floating);

  integer nimage = 9;
  integer nwarp_mat = 2;
  integer nmap = 2;
  integer nreg_mat = 2;

  floating warp_mat = mat_size(ndim, nvox * (ndim + 1));
  floating image = nimage * nvox * floatbytes;
  floating reg_mat = nreg_mat * mat_size(ndim, nmapnod * (ndim + 1));
  floating map = nmap * nmapnod * floatbytes;

  floating total_bytes = nwarp_mat * warp_mat + nimage * image + nreg_mat * reg_mat + nmap * map;

  std::cout << "Total data memory needed = " << total_bytes << " for " << nvox << " voxels.\n"
            << "Comprising:\n"
            << "\tImage data and working copies: " << nimage << " x " << image << "\n"
            << "\tInterpolation matrices: " << nwarp_mat << " x " << warp_mat << "\n"
            << "\tMap data and working copy: " << nmap << " x " << map << "\n"
            << "\tSolver matrices: " << nreg_mat << " x " << reg_mat << "\n"
            << std::flush;
}

#endif // UTILS_HPP
