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

#ifndef PETSC_HELPERS_HPP
#define PETSC_HELPERS_HPP

#include <petscdmda.h>
#include <petscvec.h>

#include "types.hpp"

floating diagonal_sum(const Mat& matrix);

bool vecs_equivalent(const Vec& vec1, const Vec& vec2);

void block_precondition(const Mat& normmat, integer size, integer ndim);

floating get_condnum_by_poweriter(const Mat& matrix, floating conv_thres, integer max_iter);

floating get_eigenvalue_by_poweriter(const Mat& matrix, floating conv_thres, integer max_iter);

void repeat_stack(const Vec& subvec, const Vec& stacked);
void repeat_stack_petsc_to_nat(const Vec& subvec, const Vec& stacked, const DM& subvec_dmda);
void copy_nth_from_stack_nat_to_petsc(const Vec& subvec, const Vec& stacked, const DM& subvec_dmda, integer n);

#endif
