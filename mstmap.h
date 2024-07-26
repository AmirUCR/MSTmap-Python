// mstmap.h
#ifndef MSTMAP_H
#define MSTMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cassert>
#include "constants.h"
#include "linkage_group_DH.h"
#include "genetic_map_DH.h"
#include "genetic_map_RIL.h"
#include "linkage_group_struct.h"

class MSTmap {
public:
    MSTmap();
    ~MSTmap();

    void check_if_population_type_is_set();
    void check_all_args_are_set();
    void set_default_args();
    void summary();

    void set_population_type(const std::string& population_type);
    void check_population_type(const std::string& population_type);

    void set_input_file(const std::string& input_file);
    void set_output_file(const std::string& output_file);

    void set_population_name(const std::string& population_name);

    void set_distance_function(const std::string& distance_function);
    void check_distance_function(const std::string& distance_function);

    void set_cut_off_p_value(double cut_off_p_value);
    void check_cut_off_p_value(double cut_off_p_value);

    void set_no_map_dist(double no_map_dist);
    void check_no_map_dist(double no_map_dist);

    void set_no_map_size(std::size_t no_map_size);
    void check_no_map_size(std::size_t no_map_size);

    void set_missing_threshold(double missing_threshold);
    void check_missing_threshold(double missing_threshold);

    void set_estimation_before_clustering(const std::string& estimation_before_clustering);
    void check_estimation_before_clustering(const std::string& estimation_before_clustering);

    void set_detect_bad_data(const std::string& detect_bad_data);
    void check_detect_bad_data(const std::string& detect_bad_data);

    void set_objective_function(const std::string& objective_function);
    void check_objective_function(const std::string& objective_function);

    void set_number_of_loci(std::size_t number_of_loci);
    void check_number_of_loci(std::size_t number_of_loci);

    void set_number_of_individual(std::size_t number_of_individual);
    void check_number_of_individual(std::size_t number_of_individual);

    void run_from_file(const std::string& input_file, bool quiet = false);
    void run(bool quiet = false);

    vector<std::string> get_lg_markers_by_index(int index);
    vector<double> get_lg_distances_by_index(int index);
    std::string get_lg_name_by_index(int index);
    double get_lg_lowerbound_by_index(int index);
    double get_lg_upperbound_by_index(int index);
    double get_lg_cost_by_index(int index);
    int get_lg_size_by_index(int index);
    int get_lg_num_bins_by_index(int index);
    void display_lg_by_index(int index);
    int get_num_linkage_groups();

private:
    void reset_args();

    bool is_set_population_type = false;
    bool is_set_input_file = false;
    bool is_set_output_file = false;
    bool is_set_population_name = false;
    bool is_set_distance_function = false;
    bool is_set_cut_off_p_value = false;
    bool is_set_no_map_dist = false;
    bool is_set_no_map_size = false;
    bool is_set_missing_threshold = false;
    bool is_set_estimation_before_clustering = false;
    bool is_set_detect_bad_data = false;
    bool is_set_objective_function = false;
    bool is_set_number_of_loci = false;
    bool is_set_number_of_individual = false;

    std::string population_type;
    std::string input_file;
    std::string output_file;
    std::string distance_function;
    std::string estimation_before_clustering;
    std::string detect_bad_data;
    std::string objective_function;

    genetic_map* barley;
    LGManager* lg_manager;
};

#endif // MSTMAP_H
