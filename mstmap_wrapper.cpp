// MSTmap_wrapper.cpp
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include "mstmap.h"

namespace py = pybind11;

PYBIND11_MODULE(mstmap, m) {
    py::register_exception<std::runtime_error>(m, "MSTmapRuntimeError");

    py::class_<MSTmap>(m, "MSTmap")
        .def(py::init<>())
        .def("set_default_args", &MSTmap::set_default_args, "Set default arguments.")
        .def("summary", &MSTmap::summary, "Print a summary of the current settings.")
        .def("set_population_type", &MSTmap::set_population_type, "Set the population type for the MSTmap instance.")
        .def("set_input_file", &MSTmap::set_input_file, "Set the input file path for the MSTmap instance.")
        .def("set_output_file", &MSTmap::set_output_file, "Set the output file path for the MSTmap instance.")
        .def("set_population_name", &MSTmap::set_population_name, "Set the population name for the MSTmap instance.")
        .def("set_distance_function", &MSTmap::set_distance_function, "Set the distance function for the MSTmap instance.")
        .def("set_cut_off_p_value", &MSTmap::set_cut_off_p_value, "Set the cut-off p-value for the MSTmap instance.")
        .def("set_no_map_dist", &MSTmap::set_no_map_dist, "Set the no-map distance for the MSTmap instance.")
        .def("set_no_map_size", &MSTmap::set_no_map_size, "Set the no-map size for the MSTmap instance.")
        .def("set_missing_threshold", &MSTmap::set_missing_threshold, "Set the missing threshold for the MSTmap instance.")
        .def("set_estimation_before_clustering", &MSTmap::set_estimation_before_clustering, "Set the estimation before clustering for the MSTmap instance.")
        .def("set_detect_bad_data", &MSTmap::set_detect_bad_data, "Set the detect bad data flag for the MSTmap instance.")
        .def("set_objective_function", &MSTmap::set_objective_function, "Set the objective function for the MSTmap instance.")
        .def("set_number_of_loci", &MSTmap::set_number_of_loci, "Set the number of loci for the MSTmap instance.")
        .def("set_number_of_individual", &MSTmap::set_number_of_individual, "Set the number of individuals for the MSTmap instance.")
        .def("run_from_file", &MSTmap::run_from_file, py::arg("input_file"), py::arg("quiet") = false, "Run the MSTmap program using the specified input file.")
        .def("run", &MSTmap::run, py::arg("quiet") = false, "Run the MSTmap program.")
        .def("get_lg_markers_by_index", &MSTmap::get_lg_markers_by_index, "Pass in an index for one of the result groups to get a list of markers in order.")
        .def("display_lg_by_index", &MSTmap::display_lg_by_index, "Pass in an index for one of the result groups to get a summary of attributes.")
        .def("get_lg_distances_by_index", &MSTmap::get_lg_distances_by_index, "Pass in an index for one of the result groups to get a list of marker distances in order.")
        .def("get_lg_name_by_index", &MSTmap::get_lg_name_by_index, "Pass in an index for one of the result groups to get the name of a linkage group.")
        .def("get_lg_lowerbound_by_index", &MSTmap::get_lg_lowerbound_by_index, "Pass in an index for one of the result groups to get the lowerbound of a linkage group.")
        .def("get_lg_upperbound_by_index", &MSTmap::get_lg_upperbound_by_index, "Pass in an index for one of the result groups to get the upperbound of a linkage group.")
        .def("get_lg_cost_by_index", &MSTmap::get_lg_cost_by_index, "Pass in an index for one of the result groups to get the cost of a linkage group.")
        .def("get_lg_size_by_index", &MSTmap::get_lg_size_by_index, "Pass in an index for one of the result groups to get the size of a linkage group.")
        .def("get_lg_num_bins_by_index", &MSTmap::get_lg_num_bins_by_index, "Pass in an index for one of the result groups to get the number of bins of a linkage group.");
}
