/*
 *  single_mapping_population_raw_data.h
 *  ApproxMap
 *
 *  Created by yonghui on 4/7/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef single_mapping_population_raw_data_header
#define single_mapping_population_raw_data_header

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include "constants.h"
#include <queue>
#include "linkage_group_DH.h"
#include "linkage_group_struct.h"  // Added by Amir

using namespace std;

class genetic_map {
    protected:
        /*The following members are supposed to be constant after initialization*/
        int number_of_loci;
        int number_of_individual;
        int total_number_of_missing_obs;
        
        string population_name;
        string distance_function;
        string population_type;
        vector<vector<char> > raw_mapping_data;
        vector<string> marker_names;
        vector<string> individual_names;

        // The function used to convert cm to rp 
        DF* df_;

        double clustering_prob_cut_off;
        bool estimation_before_clustering;
        bool detect_bad_data;
        ObjFunc objective_function;

        // if a small set of markers (by default 3) is more than no_map_threshold away from the rest of the 
        // markers, it is not mapped.
        double no_map_dist; 
        int no_map_size;
        double missing_threshold;
        
        vector<vector<double> > pair_wise_distances;
        
        //the number of linkage groups in the map
        int number_of_connected_components;
        
        //the markers for each linkage group
        vector<vector<int> > connected_components;
        
        //level of reference: linkage group, bin, markers
        vector<vector<vector<int> > > linkage_group_bins;
        vector<vector<int> > orders;
        vector<vector<double> > distance_between_adjacent_pairs; // this is the distance is cM
        
        vector<double> upperbounds;
        vector<double> lowerbounds;
        vector<double> approx_bounds;

        /*calculate the chernoff_bound*/
        double calculate_hoeffding_bound(double prob_cut_off);
    
        /*condense the markers into bins*/
        void condense_markers_into_bins();

        /*cluster the markers into linkage groups*/
        int cluster();
        
        // Added by Yonghui on Oct 20, 2007
        // When the input genotype data contains a lot of missing observations, the number of bins could be 
        // unnecessarily too many. As a result, the distance between adjacent bins is almost 0. 
        // When this happens, we really need to combine the adjacent bins into one single bin. 
        // The following function does what I have just described above. 
        // The function should be called by the end of the generate_map function
        // level of reference: linkage group, bin, markers
        vector<vector<vector<int> > > lg_bins_condensed;
        vector<vector<double> > dist_condensed; //this is the distance in cM
        void condense_bin();

        LGManager* lg_manager; // Added by Amir
        bool quiet; // Added by Amir
     public:
        genetic_map();
        ~genetic_map();
                
        /*return 0 if the function finishes successfully*/
        int read_raw_mapping_data(string file_path);
        
        // Added by Amir
        int read_mapping_data_with_args(string file_path);
        
        /*used for debugging purposes*/
        void dump();
        
        void dump_distance_matrix();
        
        // this function is supposed to be called after the order of each lg has been figured out
        void dump_connected_components_edges();    
        
        virtual void generate_map() = 0;
        
        LGManager* write_output(ostream& _output);  // Return type modified by Amir

        // Added by Amir - Getters and setters for protected variables.
        void set_population_type(const string& population_type);
        string get_population_type();

        void set_population_name(const string& population_name);
        string get_population_name();

        void set_df(const string& df_name);

        void set_clustering_prob_cut_off(double clustering_prob_cut_off);
        double get_clustering_prob_cut_off();

        void set_no_map_dist(double no_map_dist);
        double get_no_map_dist();

        void set_no_map_size(int no_map_size);
        int get_no_map_size();

        void set_missing_threshold(double missing_threshold);
        double get_missing_threshold();

        void set_estimation_before_clustering(bool estimation_before_clustering);
        bool get_estimation_before_clustering();

        void set_detect_bad_data(bool detect_bad_data);
        bool get_detect_bad_data();

        void set_objective_function(const string& objective_function);
        string get_objective_function();

        void set_number_of_loci(int number_of_loci);
        int get_number_of_loci();

        void set_number_of_individual(int number_of_individual);
        int get_number_of_individual();

        void set_quiet(bool quiet);
};

class genetic_map_DH: public genetic_map {
    private:
    	vector<pair<string, string> > suspicious_data;
        /*calculate the pair-wise distance*/
        void calculate_pair_wise_distance();
 
        /*generate a linkage group*/
        linkage_group_DH* construct_linkage_group(int group_id);
        linkage_group_DH* construct_linkage_group_whole_map();
        void print_suspicious_data();
    public:
        genetic_map_DH():genetic_map(){};
        ~genetic_map_DH();
        virtual void generate_map();
        void print_double_cross_overs();
};

#endif
