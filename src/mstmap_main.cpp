// MSTmap.cpp
#include "mstmap.h"

MSTmap::MSTmap() : barley(nullptr) {}

MSTmap::~MSTmap() {
    if (this->barley != nullptr) {
        delete this->barley;
        this->barley = nullptr;
    }
}

void MSTmap::set_default_args() {
    if (this->barley != nullptr) {
        delete this->barley;
        this->barley = nullptr;
    }
    this->barley = new genetic_map_DH();
    this->barley->set_population_type(default_population_type);
    this->is_set_population_type = true;

    this->barley->set_population_name(default_population_name);
    this->is_set_population_name = true;

    this->barley->set_df("kosambi");
    this->distance_function = default_distance_function;
    this->is_set_distance_function = true;

    this->barley->set_clustering_prob_cut_off(default_cut_off_p_value);
    this->is_set_cut_off_p_value = true;

    this->barley->set_no_map_dist(default_no_map_dist);
    this->is_set_no_map_dist = true;

    this->barley->set_no_map_size(default_no_map_size);
    this->is_set_no_map_size = true;

    this->barley->set_missing_threshold(default_missing_threshold);
    this->is_set_missing_threshold = true;

    this->barley->set_estimation_before_clustering(false);
    this->estimation_before_clustering = default_estimation_before_clustering;
    this->is_set_estimation_before_clustering = true;

    this->barley->set_detect_bad_data(true);
    this->detect_bad_data = default_detect_bad_data;
    this->is_set_detect_bad_data = true;

    this->barley->set_objective_function("COUNT");
    this->objective_function = default_objective_function;
    this->is_set_objective_function = true;

    this->barley->set_number_of_loci(default_number_of_loci);
    this->is_set_number_of_loci = true;

    this->barley->set_number_of_individual(default_number_of_individual);
    this->is_set_number_of_individual = true;

    this->input_file = default_input_file;
    this->is_set_input_file = true;

    this->output_file = default_output_file;
    this->is_set_output_file = true;
}

void MSTmap::reset_args() {
    if (this->barley != nullptr) {
        delete this->barley;
        this->barley = nullptr;
    }

    this->is_set_population_type = false;
    this->is_set_input_file = false;
    this->is_set_output_file = false;
    this->is_set_population_name = false;
    this->is_set_distance_function = false;
    this->is_set_cut_off_p_value = false;
    this->is_set_no_map_dist = false;
    this->is_set_no_map_size = false;
    this->is_set_missing_threshold = false;
    this->is_set_estimation_before_clustering = false;
    this->is_set_detect_bad_data = false;
    this->is_set_objective_function = false;
    this->is_set_number_of_loci = false;
    this->is_set_number_of_individual = false;
}

void MSTmap::check_all_args_are_set() {
    if (this->barley == nullptr) throw std::runtime_error("Please initialize MSTmap with set_default_args() or set_population_type(pop_type) first before calling run().");
    if (!is_set_population_type) throw std::runtime_error("Population type is not set.");
    if (!is_set_input_file) throw std::runtime_error("Input file is not set.");
    if (!is_set_output_file) throw std::runtime_error("Output file is not set.");
    if (!is_set_population_name) throw std::runtime_error("Population name is not set.");
    if (!is_set_distance_function) throw std::runtime_error("Distance function is not set.");
    if (!is_set_cut_off_p_value) throw std::runtime_error("Cutoff p-value is not set.");
    if (!is_set_no_map_dist) throw std::runtime_error("No. mapping distance is not set.");
    if (!is_set_no_map_size) throw std::runtime_error("No. mapping size is not set.");
    if (!is_set_missing_threshold) throw std::runtime_error("Missing threshold is not set.");
    if (!is_set_estimation_before_clustering) throw std::runtime_error("Set estimation before clustering is not set.");
    if (!is_set_detect_bad_data) throw std::runtime_error("Set detect bad data is not set.");
    if (!is_set_objective_function) throw std::runtime_error("Objective function is not set.");
    if (!is_set_number_of_loci) throw std::runtime_error("Number of loci is not set.");
    if (!is_set_number_of_individual) throw std::runtime_error("Number of individuals is not set.");
}

void MSTmap::summary() {
    if (this->barley == nullptr) throw std::runtime_error("Please initialize MSTmap with set_default_args() or set_population_type(pop_type) first before calling summary().");
    std::cout << "Population type: " << this->barley->get_population_type() << std::endl;
    std::cout << "Population name: " << this->barley->get_population_name() << std::endl;
    std::cout << "Distance function: " << this->distance_function << std::endl;
    std::cout << "Cutoff p-value: " << this->barley->get_clustering_prob_cut_off() << std::endl;
    std::cout << "No. mapping distance threshold (cM): " << this->barley->get_no_map_dist() << std::endl;
    std::cout << "No. mapping size threshold: " << this->barley->get_no_map_size() << std::endl;
    std::cout << "Missing threshold: " << this->barley->get_missing_threshold() << std::endl;
    std::cout << "Estimation before clustering: " << this->estimation_before_clustering << std::endl;
    std::cout << "Detect bad data: " << this->detect_bad_data << std::endl;
    std::cout << "Objective function: " << this->objective_function << std::endl;
    std::cout << "Number of loci: " << this->barley->get_number_of_loci() << std::endl;
    std::cout << "Number of individual: " << this->barley->get_number_of_individual() << std::endl;
    std::cout << "Input file: " << this->input_file << std::endl;
    std::cout << "Output file: " << this->output_file << std::endl;
}

void MSTmap::check_if_population_type_is_set() {
    if (!this->is_set_population_type) {
        throw std::runtime_error("Please set the population type to either DH or RIL first by calling set_population_type(str).");
    }
}

// --
void MSTmap::check_population_type(const std::string& population_type) {
    if (population_type != "DH" && population_type != "RIL") {
        throw std::runtime_error("Population type must be either DH or RIL.");
    }
}

void MSTmap::set_population_type(const std::string& population_type) {
    this->check_population_type(population_type);

    if (this->barley != nullptr) {
        delete this->barley;
        this->barley = nullptr;
    }
    if (population_type == "DH") {
        this->barley = new genetic_map_DH();
    }
    else if (population_type == "RIL") {
        this->barley = new genetic_map_RIL();
    }

    this->barley->set_population_type(population_type);
    this->is_set_population_type = true;
}
// --

// --
void MSTmap::set_population_name(const std::string& population_name) {
    this->check_if_population_type_is_set();
    this->barley->set_population_name(population_name);
    this->is_set_population_name = true;
}
// --

// --
void MSTmap::check_distance_function(const std::string& distance_function) {
    if (distance_function != "kosambi" && distance_function != "haldane") {
        throw std::runtime_error("Distance function must be either kosambi or haldane.");
    }
}

void MSTmap::set_distance_function(const std::string& distance_function) {
    this->check_if_population_type_is_set();
    this->set_distance_function(distance_function);
    
    if (distance_function == "kosambi") {
        this->barley->set_df("kosambi");
    }
    else if (distance_function == "haldane") {
        this->barley->set_df("haldane");
    }

    this->distance_function = distance_function;
    this->is_set_distance_function = true;
}
// --

// --
void MSTmap::check_cut_off_p_value(double cut_off_p_value) {
    if (cut_off_p_value < 0) {
        throw std::runtime_error("Cut-off p-value must be non-negative.");
    }
    else if (cut_off_p_value > 1) {
        throw std::runtime_error("Cut-off p-value must be under 1.");
    }
}

void MSTmap::set_cut_off_p_value(double cut_off_p_value) {
    this->check_if_population_type_is_set();
    this->check_cut_off_p_value(cut_off_p_value);
    this->barley->set_clustering_prob_cut_off(cut_off_p_value);
    this->is_set_cut_off_p_value = true;
}
// --

// --
void MSTmap::check_no_map_dist(double no_map_dist) {
    if (no_map_dist < 0) {
        throw std::runtime_error("No. mapping distance threshold (cM) must be non-negative.");
    }
}

void MSTmap::set_no_map_dist(double no_map_dist) {
    this->check_if_population_type_is_set();
    this->check_no_map_dist(no_map_dist);
    this->barley->set_no_map_dist(no_map_dist);
    this->is_set_no_map_dist = true;
}
// --

// --
void MSTmap::check_no_map_size(std::size_t no_map_size) {
    if (no_map_size < 0) {
        throw std::runtime_error("No. mapping size threshold must be non-negative.");
    }
}

void MSTmap::set_no_map_size(std::size_t no_map_size) {
    this->check_if_population_type_is_set();
    this->check_no_map_size(no_map_size);
    this->barley->set_no_map_size(no_map_size);
    this->is_set_no_map_size = true;
}
// --

// --
void MSTmap::check_missing_threshold(double missing_threshold) {
    if (missing_threshold < 0) {
        throw std::runtime_error("No. mapping missing threshold (%) must be non-negative.");
    }
}

void MSTmap::set_missing_threshold(double missing_threshold) {
    this->check_if_population_type_is_set();
    this->check_missing_threshold(missing_threshold);
    this->barley->set_missing_threshold(missing_threshold);
    this->is_set_missing_threshold = true;
}
// --

// --
void MSTmap::check_estimation_before_clustering(const std::string& estimation_before_clustering) {
    if (estimation_before_clustering != "yes" && estimation_before_clustering != "no") {
        throw std::runtime_error("estimation_before_clustering must be either yes or no.");
    }
}

void MSTmap::set_estimation_before_clustering(const std::string& estimation_before_clustering) {
    this->check_if_population_type_is_set();
    this->check_estimation_before_clustering(estimation_before_clustering);

    if (estimation_before_clustering == "yes") {
        this->barley->set_estimation_before_clustering(true);
    }
    else if (estimation_before_clustering == "no") {
        this->barley->set_estimation_before_clustering(false);
    }

    this->estimation_before_clustering = estimation_before_clustering;
    this->is_set_estimation_before_clustering = true;
}
// --

// --
void MSTmap::check_detect_bad_data(const std::string& detect_bad_data) {
    if (detect_bad_data != "yes" && detect_bad_data != "no") {
        throw std::runtime_error("detect_bad_data must be either yes or no.");
    }
}

void MSTmap::set_detect_bad_data(const std::string& detect_bad_data) {
    this->check_if_population_type_is_set();
    this->check_detect_bad_data(detect_bad_data);

    if (detect_bad_data == "yes") {
        this->barley->set_detect_bad_data(true);
    }
    else if (detect_bad_data == "no") {
        this->barley->set_detect_bad_data(false);
    }

    this->detect_bad_data = detect_bad_data;
    this->is_set_detect_bad_data = true;
}
// --

// --
void MSTmap::check_objective_function(const std::string& objective_function) {
    if (objective_function != "ML" && objective_function != "COUNT" && objective_function != "CM") {
        throw std::runtime_error("objective_function must be either ML or COUNT.");
    }
}

void MSTmap::set_objective_function(const std::string& objective_function) {
    this->check_if_population_type_is_set();
    this->check_objective_function(objective_function);

    if (objective_function == "ML") {
        this->barley->set_objective_function("ML");
    }
    else if (objective_function == "COUNT") {
        this->barley->set_objective_function("COUNT");
    }
    else if (objective_function == "CM") {
        this->barley->set_objective_function("CM");
    }

    this->objective_function = objective_function;
    this->is_set_objective_function = true;
}
// --

// --
void MSTmap::check_number_of_loci(std::size_t number_of_loci) {
    if (number_of_loci < 0) {
        throw std::runtime_error("number_of_loci must be non-negative.");
    }
}

void MSTmap::set_number_of_loci(std::size_t number_of_loci) {
    this->check_if_population_type_is_set();
    this->check_number_of_loci(number_of_loci);
    this->barley->set_number_of_loci(number_of_loci);
    this->is_set_number_of_loci = true;
}
// --

// --
void MSTmap::check_number_of_individual(std::size_t number_of_individual) {
    if (number_of_individual < 0) {
        throw std::runtime_error("number_of_individual must be non-negative.");
    }
}

void MSTmap::set_number_of_individual(std::size_t number_of_individual) {
    this->check_if_population_type_is_set();
    this->check_number_of_individual(number_of_individual);
    this->barley->set_number_of_individual(number_of_individual);
    this->is_set_number_of_individual = true;
}
// --

// --
void MSTmap::set_input_file(const std::string& input_file) {
    std::ifstream file(input_file);
    if (!file) {
        throw std::runtime_error("Input file does not exist: " + input_file);
    }
    this->input_file = input_file;
    this->is_set_input_file = true;
}

// --
void MSTmap::set_output_file(const std::string& output_file) {
    this->output_file = output_file;
    this->is_set_output_file = true;
}
// --

// --
void MSTmap::run_from_file(const std::string& input_file, bool quiet) {
    std::ifstream raw_mapping_data_file(input_file);

    if (!raw_mapping_data_file) {
        throw std::runtime_error("Input file does not exist: " + input_file);
    }

    std::string tmp_str;
    std::string population_type;

    raw_mapping_data_file >> tmp_str;
    if (tmp_str != "population_type") {
        throw std::runtime_error("The first line of the input file must be population_type.");
    }
    raw_mapping_data_file >> this->population_type;
    this->check_population_type(this->population_type);
    raw_mapping_data_file.close();

    if (this->barley != nullptr) {
        delete this->barley;
        this->barley = nullptr;
    }
    if (this->population_type == "DH") {
        this->barley = new genetic_map_DH();
    }
    else {
        this->barley = new genetic_map_RIL();
    }

    if (this->is_set_output_file == false) {
        this->output_file = default_output_file;
        this->is_set_output_file = true;
    }

    this->barley->set_quiet(quiet);
    this->barley->read_raw_mapping_data(input_file);
    this->barley->generate_map();
    
    std::ofstream output_stream(this->output_file);
    this->lg_manager = this->barley->write_output(output_stream);
    output_stream.close();
    
    delete barley;
    this->barley = nullptr;

    reset_args();
}
// --

// --
void MSTmap::run(bool quiet) {
    check_all_args_are_set();
    if (!quiet) summary();

    this->barley->set_quiet(quiet);
    this->barley->read_mapping_data_with_args(this->input_file);
    this->barley->generate_map();
    
    std::ofstream output_stream(this->output_file);
    this->lg_manager = this->barley->write_output(output_stream);
    output_stream.close();
    
    delete barley;
    this->barley = nullptr;

    reset_args();
}

vector<std::string> MSTmap::get_lg_markers_by_index(int index) {
    return this->lg_manager->get_lg_markers_by_index(index);
}

vector<double> MSTmap::get_lg_distances_by_index(int index) {
    return this->lg_manager->get_lg_distances_by_index(index);
}

std::string MSTmap::get_lg_name_by_index(int index) {
    return this->lg_manager->get_lg_name_by_index(index);
}

double MSTmap::get_lg_lowerbound_by_index(int index) {
    return this->lg_manager->get_lg_lowerbound_by_index(index);
}

double MSTmap::get_lg_upperbound_by_index(int index) {
    return this->lg_manager->get_lg_upperbound_by_index(index);
}

double MSTmap::get_lg_cost_by_index(int index) {
    return this->lg_manager->get_lg_cost_by_index(index);
}

int MSTmap::get_lg_size_by_index(int index) {
    return this->lg_manager->get_lg_size_by_index(index);
}

int MSTmap::get_lg_num_bins_by_index(int index) {
    return this->lg_manager->get_lg_num_bins_by_index(index);
}

void MSTmap::display_lg_by_index(int index) {
    this->lg_manager->display_lg_by_index(index);
}

int MSTmap::get_num_linkage_groups() {
    return this->lg_manager->get_num_linkage_groups();
}
