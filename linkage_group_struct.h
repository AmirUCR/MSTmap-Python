// linkage_group_struct.h
#ifndef LINKAGE_GROUP_STRUCT_H
#define LINKAGE_GROUP_STRUCT_H

#include <iostream>
#include <vector>
#include <string>

struct ResultLinkageGroup {
    double lowerbound;
    double upperbound;
    double cost;

    int size;
    int num_bins;

    std::vector<std::string> markers;
    std::vector<double> distances;

    std::string name;

    void display() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Lowerbound: " << lowerbound << std::endl;
        std::cout << "Upperbound: " << upperbound << std::endl;
        std::cout << "Size: " << size << std::endl;
        std::cout << "Num. Bins: " << num_bins << std::endl;
        std::cout << "Cost: " << cost << std::endl;
        std::cout << "Markers: ";
        for (const string& str : markers) {
            std::cout << str << " ";
        }
        std::cout << std::endl;
        std::cout << "Distances: ";
        for (const double& dbl : distances) {
            std::cout << dbl << " ";
        }
        std::cout << std::endl;
    }
};

class LGManager {
private:
    std::vector<ResultLinkageGroup> lg_vector;

public:
    // Add a struct to the vector
    void add(const ResultLinkageGroup& s) {
        lg_vector.push_back(s);
    }

    // Prevent adding new content to the old.
    void clear_contents() {
        lg_vector.clear();
    }

    int get_num_linkage_groups() {
        return lg_vector.size();
    }

    // Get and display a struct by index
    void display_lg_by_index(size_t index) const {
        if (index < lg_vector.size()) {
            lg_vector[index].display();
        } else {
            std::cout << "Index out of range." << std::endl;
        }
    }

    std::vector<std::string> get_lg_markers_by_index(size_t index) const {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].markers;
        }

        throw std::runtime_error("Index out of range.");
    }

    std::vector<double> get_lg_distances_by_index(size_t index) const {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].distances;
        }

        throw std::runtime_error("Index out of range.");
    }

    std::string get_lg_name_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].name;
        }

        throw std::runtime_error("Index out of range.");
    }

    double get_lg_lowerbound_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].lowerbound;
        }

        throw std::runtime_error("Index out of range.");
    }

    double get_lg_upperbound_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].upperbound;
        }

        throw std::runtime_error("Index out of range.");
    }

    double get_lg_cost_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].cost;
        }

        throw std::runtime_error("Index out of range.");
    }

    int get_lg_size_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].size;
        }

        throw std::runtime_error("Index out of range.");
    }

    int get_lg_num_bins_by_index(int index) {
        if (index < lg_vector.size() && index >= 0) {
            return lg_vector[index].num_bins;
        }

        throw std::runtime_error("Index out of range.");
    }
};

#endif