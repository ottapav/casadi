/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef SUPERLU_INTERNAL_HPP
#define SUPERLU_INTERNAL_HPP

#include "superlu.hpp"
#include "casadi/fx/linear_solver_internal.hpp"
#include "external_packages/superlu_4_1/SRC/slu_ddefs.h"

namespace CasADi{
  
class SuperLUInternal : public LinearSolverInternal{
  public:
    // Create a linear solver given a sparsity pattern and a number of right hand sides
    SuperLUInternal(const CRSSparsity& sparsity, int nrhs);

    // Copy constructor
    SuperLUInternal(const SuperLUInternal& linsol);

    // Destructor
    virtual ~SuperLUInternal();
    
    // Initialize the solver
    virtual void init();

    // Factorize the matrix
    virtual void prepare();
    
    // Solve the system of equations
    virtual void solve(double* x, int nrhs, bool transpose);
    
    // Clone
    virtual SuperLUInternal* clone() const;
  protected:
    
    // Is initialized
    bool is_init_;
    
    // Has the solve function been called once
    bool called_once_;
    
    // Max number of right hand sides
    int nrhs_;
    
    // SuperLU data structures
    SuperMatrix A_, L_, U_, B_;
    superlu_options_t options_;
    SuperLUStat_t stat_;

    // Data
    std::vector<double> a_, rhs_;
    std::vector<int> perm_r_; // row permutations from partial pivoting
    std::vector<int> perm_c_; // column permutation vector
    int info_;

    std::vector<int> etree_;
    
    // Work vector
    void *work_;
    
    // Size of work
    int lwork_;
    
    // Free SuperLU memory
    void unInit();

    // Allocate work vector
    bool user_work_;
};

} // namespace CasADi

#endif //SUPERLU_INTERNAL_HPP

