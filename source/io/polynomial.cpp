#include "polynomial.hpp"

vector<double> Polynomial::parse_string(const string parameter_string) const {
    vector<double> parameters;
    char delimiter;
    if (parameter_string.find(",") != string::npos) {
        delimiter = ',';
    } else {
        delimiter = ' ';
    }

    size_t start = 0;
    for (size_t i = 1; i < parameter_string.size(); ++i) {
        if (parameter_string[i] == delimiter && i > start) {
            parameters.push_back(
                stod(parameter_string.substr(start, i - start)));
            start = i + 1;
        }
    }
    if (start < parameter_string.size() - 1) {
        parameters.push_back(stod(
            parameter_string.substr(start, parameter_string.size() - start)));
    }

    return parameters;
}

double Polynomial::operator()(const double x) const {
    double result = parameters[*parameters.end() - 1];
    for (size_t i = parameters.size(); i > 0; --i) {
        result = parameters[i - 1] + result * x;
    }
    return result;
}

double Polynomial::operator()(const double x,
                              [[maybe_unused]] const long long i) const {
    return operator()(x);
}