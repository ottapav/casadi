/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
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


      #include "stabilized_sqp.hpp"
      #include <string>

      const std::string casadi::StabilizedSqp::meta_doc=
      "\n"
"Stabilized Sequential Quadratic Programming method.\n"
"\n"
"\n"
">List of available options\n"
"\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| TReta1          | OT_REAL         | 0.800           | Required        |\n"
"|                 |                 |                 | predicted /     |\n"
"|                 |                 |                 | actual decrease |\n"
"|                 |                 |                 | for TR increase |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| TReta2          | OT_REAL         | 0.200           | Required        |\n"
"|                 |                 |                 | predicted /     |\n"
"|                 |                 |                 | actual decrease |\n"
"|                 |                 |                 | for TR decrease |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| alphaMin        | OT_REAL         | 0.001           | Used to check   |\n"
"|                 |                 |                 | whether to      |\n"
"|                 |                 |                 | increase rho.   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| beta            | OT_REAL         | 0.500           | Line-search     |\n"
"|                 |                 |                 | parameter,      |\n"
"|                 |                 |                 | restoration     |\n"
"|                 |                 |                 | factor of       |\n"
"|                 |                 |                 | stepsize        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| c1              | OT_REAL         | 0.001           | Armijo          |\n"
"|                 |                 |                 | condition,      |\n"
"|                 |                 |                 | coefficient of  |\n"
"|                 |                 |                 | decrease in     |\n"
"|                 |                 |                 | merit           |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| dvMax0          | OT_REAL         | 100             | Parameter used  |\n"
"|                 |                 |                 | to defined the  |\n"
"|                 |                 |                 | max step        |\n"
"|                 |                 |                 | length.         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| eps_active      | OT_REAL         | 0.000           | Threshold for   |\n"
"|                 |                 |                 | the epsilon-    |\n"
"|                 |                 |                 | active set.     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gamma1          | OT_REAL         | 2               | Trust region    |\n"
"|                 |                 |                 | increase        |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gamma2          | OT_REAL         | 1               | Trust region    |\n"
"|                 |                 |                 | update          |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gamma3          | OT_REAL         | 1               | Trust region    |\n"
"|                 |                 |                 | decrease        |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| hessian_approxi | OT_STRING       | \"exact\"         | limited-        |\n"
"| mation          |                 |                 | memory|exact    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| lbfgs_memory    | OT_INTEGER      | 10              | Size of L-BFGS  |\n"
"|                 |                 |                 | memory.         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter        | OT_INTEGER      | 100             | Maximum number  |\n"
"|                 |                 |                 | of SQP          |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter_ls     | OT_INTEGER      | 20              | Maximum number  |\n"
"|                 |                 |                 | of linesearch   |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_time        | OT_REAL         | 1.000e+12       | Timeout         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| merit_memory    | OT_INTEGER      | 4               | Size of memory  |\n"
"|                 |                 |                 | to store        |\n"
"|                 |                 |                 | history of      |\n"
"|                 |                 |                 | merit function  |\n"
"|                 |                 |                 | values          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| min_step_size   | OT_REAL         | 0.000           | The size (inf-  |\n"
"|                 |                 |                 | norm) of the    |\n"
"|                 |                 |                 | step size       |\n"
"|                 |                 |                 | should not      |\n"
"|                 |                 |                 | become smaller  |\n"
"|                 |                 |                 | than this.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| muR0            | OT_REAL         | 0.000           | Initial choice  |\n"
"|                 |                 |                 | of              |\n"
"|                 |                 |                 | regularization  |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| nu              | OT_REAL         | 1               | Parameter for   |\n"
"|                 |                 |                 | primal-dual     |\n"
"|                 |                 |                 | augmented       |\n"
"|                 |                 |                 | Lagrangian.     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| phiWeight       | OT_REAL         | 0.000           | Weight used in  |\n"
"|                 |                 |                 | pseudo-filter.  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_header    | OT_BOOLEAN      | true            | Print the       |\n"
"|                 |                 |                 | header with     |\n"
"|                 |                 |                 | problem         |\n"
"|                 |                 |                 | statistics      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularize      | OT_BOOLEAN      | false           | Automatic       |\n"
"|                 |                 |                 | regularization  |\n"
"|                 |                 |                 | of Lagrange     |\n"
"|                 |                 |                 | Hessian.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| stabilized_qp_s | OT_STRING       | GenericType()   | The Stabilized  |\n"
"| olver           |                 |                 | QP solver to be |\n"
"|                 |                 |                 | used by the SQP |\n"
"|                 |                 |                 | method          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| stabilized_qp_s | OT_DICT   | GenericType()   | Options to be   |\n"
"| olver_options   |                 |                 | passed to the   |\n"
"|                 |                 |                 | Stabilized QP   |\n"
"|                 |                 |                 | solver          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tau0            | OT_REAL         | 0.010           | Initial         |\n"
"|                 |                 |                 | parameter for   |\n"
"|                 |                 |                 | the merit       |\n"
"|                 |                 |                 | function        |\n"
"|                 |                 |                 | optimality      |\n"
"|                 |                 |                 | threshold.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_du          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | dual            |\n"
"|                 |                 |                 | infeasability   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_pr          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | primal          |\n"
"|                 |                 |                 | infeasibility   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| yEinitial       | OT_STRING       | \"simple\"        | Initial         |\n"
"|                 |                 |                 | multiplier.     |\n"
"|                 |                 |                 | Simple (all     |\n"
"|                 |                 |                 | zero) or least  |\n"
"|                 |                 |                 | (LSQ).          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available monitors\n"
"\n"
"+-------------+\n"
"|     Id      |\n"
"+=============+\n"
"| dx          |\n"
"+-------------+\n"
"| eval_f      |\n"
"+-------------+\n"
"| eval_g      |\n"
"+-------------+\n"
"| eval_grad_f |\n"
"+-------------+\n"
"| eval_h      |\n"
"+-------------+\n"
"| eval_jac_g  |\n"
"+-------------+\n"
"| qp          |\n"
"+-------------+\n"
"\n"
"\n"
">List of available stats\n"
"\n"
"+---------------+\n"
"|      Id       |\n"
"+===============+\n"
"| iter_count    |\n"
"+---------------+\n"
"| return_status |\n"
"+---------------+\n"
"\n"
"\n"
"\n"
"\n"
;