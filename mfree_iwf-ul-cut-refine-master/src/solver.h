/*
 * ================================================
 * 					COPYRIGHT:
 * Institute of Machine Tools & Manufacturing (IWF)
 * Department of Mechanical & Process Engineering
 * 					ETH ZURICH
 * ================================================
 *
 *  This file is part of "mfree_iwf-ul-cut-refine".
 *
 * 	mfree_iwf is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	mfree_iwf-ul-cut-refine is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *  along with mfree_iwf-ul-cut-refine.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This is the source code used to produce the results
 *  of the metal cutting simulation presented in:
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  "Meshfree Simulation of Metal Cutting:
 *  An Updated Lagrangian Approach with Dynamic Refinement"
 *
 * 	Authored by:
 * 	Mohamadreza Afrasiabi
 * 	Dr. Matthias Roethlin
 * 	Hagen Klippel
 * 	Prof. Dr. Konrad Wegener
 *
 * 	Published by:
 * 	International Journal of Mechanical Sciences
 * 	28 June 2019
 * 	https://doi.org/10.1016/j.ijmecsci.2019.06.045
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * 	For further descriptions, you may refer to the manuscript
 * 	or the previous works of the same research group
 * 	at IWF, ETH Zurich.
 *
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>

static const unsigned int max_iter = 100;

template <class ftor>
double solve_zero_secant(ftor f, double init, double t, bool &failed) {

	double delta_lambda = init;
	double delta_lambda_old = delta_lambda;

	double iter = 0;

	failed = false;

	do {
		double g = (*f)(delta_lambda);
		double delta_lambda_1 = delta_lambda*1.01;
		double g_1 = (*f)(delta_lambda_1);

		double slope = (g - g_1) / (delta_lambda - delta_lambda_1);

		delta_lambda_old = delta_lambda;
		delta_lambda = delta_lambda - g/slope;

		if (delta_lambda < 0.) {
			delta_lambda = -0.1*delta_lambda;
		}

		if (fabs(delta_lambda - delta_lambda_old) < t) {
			return delta_lambda;
		}

		if (iter > max_iter) {
			printf("radial return failed to converge!\n");
			failed = true;
			return -1.;
		}

		iter++;
	} while(true);
}

#endif //SOLVER_H_
