/*
     This file is part of carolina.

    carolina is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software
   Foundation, either version 3 of the License, or (at your option) any later
   version.

    carolina is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along with
    carolina. If not, see <https://www.gnu.org/licenses/>.
*/

#include <cassert>

#include <functional>

using std::function;

#include <memory>

using std::make_unique;
using std::unique_ptr;

#include <vector>

using std::vector;

#include "polynomial.hpp"

void check_parameters(vector<double> parameters,
                      vector<double> desired_parameters) {
    assert(parameters.size() == desired_parameters.size());
    for (size_t i = 0; i < desired_parameters.size(); ++i) {
        assert(parameters[i] == desired_parameters[i]);
    }
}

int main() {
    // Test implementation of polynomials
    const vector<double> parameters = {3., 2., 1.};
    unique_ptr<Polynomial> pol = make_unique<Polynomial>(parameters);

    const double x = 2.;
    const double y = 11.;

    assert(pol->operator()(x) == y);

    // Test wrapping into a std::function object.
    Polynomial pol_to_be_wrapped(parameters);
    function<double(double)> wrapper = pol_to_be_wrapped;
    assert(wrapper(x) == y);
    function<double(double, long long)> wrapper_with_two_arguments =
        pol_to_be_wrapped;
    assert(wrapper_with_two_arguments(1., 0) == 6.);

    // Test string input parsing
    // comma separated
    pol = make_unique<Polynomial>("3.,2.,1.");
    check_parameters(pol->parameters, parameters);
    assert(pol->operator()(x) == y);
    // comma separated with additional whitespace
    pol = make_unique<Polynomial>("3., 2.,1.");
    check_parameters(pol->parameters, parameters);
    assert(pol->operator()(x) == y);
    // comma separated with trailing comma
    pol = make_unique<Polynomial>("3.,2.,1.,");
    check_parameters(pol->parameters, parameters);
    assert(pol->operator()(x) == y);
    // whitespace separated
    pol = make_unique<Polynomial>("3. 2. 1.");
    check_parameters(pol->parameters, parameters);
    assert(pol->operator()(x) == y);
    // whitespace separated with additional whitespace
    pol = make_unique<Polynomial>("3. 2.  1.");
    check_parameters(pol->parameters, parameters);
    assert(pol->operator()(x) == y);
}
