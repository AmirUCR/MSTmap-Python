# cython: language_level=3

# Import the necessary Cython modules
from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector
from cpython.exc cimport PyErr_SetString
from cython.operator cimport dereference as deref
from cython.operator cimport address as addr

# Python Modules
from reportlab.lib.units import cm
from Bio.Graphics import BasicChromosome
from reportlab.graphics.shapes import Rect
from Bio.Graphics.GenomeDiagram import _Colors
# ---

cdef extern from "mstmap.h":
    cdef cppclass MSTmap:
        MSTmap()
        void set_default_args() except +
        void summary() except +
        void set_population_type(string type) except +
        void set_input_file(string path) except +
        void set_output_file(string path) except +
        void set_population_name(string name) except +
        void set_distance_function(string function) except +
        void set_cut_off_p_value(double p_value) except +
        void set_no_map_dist(double dist) except +
        void set_no_map_size(int size) except +
        void set_missing_threshold(double threshold) except +
        void set_estimation_before_clustering(string estimation) except +
        void set_detect_bad_data(string detect) except +
        void set_objective_function(string function) except +
        void set_number_of_loci(int loci) except +
        void set_number_of_individual(int individual) except +
        void run_from_file(string input_file, bool quiet) except +
        void run(bool quiet) except +
        vector[string] get_lg_markers_by_index(int index) except +
        void display_lg_by_index(int index) except +
        vector[double] get_lg_distances_by_index(int index) except +
        string get_lg_name_by_index(int index) except +
        double get_lg_lowerbound_by_index(int index) except +
        double get_lg_upperbound_by_index(int index) except +
        double get_lg_cost_by_index(int index) except +
        int get_lg_size_by_index(int index) except +
        int get_lg_num_bins_by_index(int index) except +
        int get_num_linkage_groups() except +

cdef class PyMSTmap:
    cdef dict __dict__
    cdef MSTmap* cpp_mstmap
    
    def __cinit__(self):
        self.cpp_mstmap = new MSTmap()
    
    def __dealloc__(self):
        del self.cpp_mstmap
    
    def set_default_args(self):
        self.cpp_mstmap.set_default_args()
    
    def summary(self):
        self.cpp_mstmap.summary()
    
    def set_population_type(self, str type):
        self.cpp_mstmap.set_population_type(type.encode('utf-8'))
    
    def set_input_file(self, str path):
        self.cpp_mstmap.set_input_file(path.encode('utf-8'))
    
    def set_output_file(self, str path):
        self.cpp_mstmap.set_output_file(path.encode('utf-8'))
    
    def set_population_name(self, str name):
        self.cpp_mstmap.set_population_name(name.encode('utf-8'))
    
    def set_distance_function(self, str function):
        self.cpp_mstmap.set_distance_function(function.encode('utf-8'))
    
    def set_cut_off_p_value(self, double p_value):
        self.cpp_mstmap.set_cut_off_p_value(p_value)
    
    def set_no_map_dist(self, double dist):
        self.cpp_mstmap.set_no_map_dist(dist)
    
    def set_no_map_size(self, int size):
        self.cpp_mstmap.set_no_map_size(size)
    
    def set_missing_threshold(self, double threshold):
        self.cpp_mstmap.set_missing_threshold(threshold)
    
    def set_estimation_before_clustering(self, str estimation):
        self.cpp_mstmap.set_estimation_before_clustering(estimation.encode('utf-8'))
    
    def set_detect_bad_data(self, str detect):
        self.cpp_mstmap.set_detect_bad_data(detect.encode('utf-8'))
    
    def set_objective_function(self, str function):
        self.cpp_mstmap.set_objective_function(function.encode('utf-8'))
    
    def set_number_of_loci(self, int loci):
        self.cpp_mstmap.set_number_of_loci(loci)
    
    def set_number_of_individual(self, int individual):
        self.cpp_mstmap.set_number_of_individual(individual)
    
    def run_from_file(self, str input_file, bool quiet=False):
        self.cpp_mstmap.run_from_file(input_file.encode('utf-8'), quiet)
    
    def run(self, bool quiet=False):
        self.cpp_mstmap.run(quiet)
    
    def get_lg_markers_by_index(self, int index):
        return list(self.cpp_mstmap.get_lg_markers_by_index(index))
    
    def display_lg_by_index(self, int index):
        self.cpp_mstmap.display_lg_by_index(index)
    
    def get_lg_distances_by_index(self, int index):
        return list(self.cpp_mstmap.get_lg_distances_by_index(index))
    
    def get_lg_name_by_index(self, int index):
        return self.cpp_mstmap.get_lg_name_by_index(index)
    
    def get_lg_lowerbound_by_index(self, int index):
        return self.cpp_mstmap.get_lg_lowerbound_by_index(index)
    
    def get_lg_upperbound_by_index(self, int index):
        return self.cpp_mstmap.get_lg_upperbound_by_index(index)
    
    def get_lg_cost_by_index(self, int index):
        return self.cpp_mstmap.get_lg_cost_by_index(index)
    
    def get_lg_size_by_index(self, int index):
        return self.cpp_mstmap.get_lg_size_by_index(index)
    
    def get_lg_num_bins_by_index(self, int index):
        return self.cpp_mstmap.get_lg_num_bins_by_index(index)

    def get_num_linkage_groups(self):
        return self.cpp_mstmap.get_num_linkage_groups()

    def draw_linkage_map(self, str name="linkage_map.pdf"):
        BasicChromosome.AnnotatedChromosomeSegment._overdraw_subcomponents = _overdraw_subcomponents_with_middle

        num_lg = self.get_num_linkage_groups()

        position_lists = list()
        marker_name_lists = list()
        for i in range(num_lg):
            position_lists.append([round(p, 2) for p in self.get_lg_distances_by_index(i)])
            marker_name_lists.append(self.get_lg_markers_by_index(i))

        chr_diagram = BasicChromosome.Organism()

        max_len = max(max(sub_list) for sub_list in position_lists)

        for nlg in range(num_lg):
            positions = position_lists[nlg]
            marker_names = marker_name_lists[nlg]

            telomere_length = max_len / 10
            spacer_length = 0.20 * max_len

            cur_chromosome = BasicChromosome.Chromosome(f'LG{nlg}')
            # Set the scale to the MAXIMUM length plus the two telomeres in bp,
            # want the same scale used on all five chromosomes so they can be
            # compared to each other
            cur_chromosome.scale_num = max_len + 2 * telomere_length + 2 * spacer_length

            features = list()
            for idx, marker in enumerate(marker_names):
                features.append((positions[idx], positions[idx], -1, str(positions[idx]), nlg+1))
                features.append((positions[idx], positions[idx], 1, marker, nlg+1))

            spacer = BasicChromosome.SpacerSegment()
            spacer.scale = spacer_length
            cur_chromosome.add(spacer)

            # Add an opening telomere
            start = BasicChromosome.TelomereSegment()
            start.scale = telomere_length
            cur_chromosome.add(start)

            # Add a body - using bp as the scale length here.
            body = BasicChromosome.AnnotatedChromosomeSegment(max(positions), features)
            body.scale = max(positions)
            cur_chromosome.add(body)

            # Add a closing telomere
            end = BasicChromosome.TelomereSegment(inverted=True)
            end.scale = telomere_length
            cur_chromosome.add(end)

            spacer = BasicChromosome.SpacerSegment()
            spacer.scale = spacer_length
            cur_chromosome.add(spacer)

            # This chromosome is done
            chr_diagram.add(cur_chromosome)

        if not name.endswith('.pdf'):
            name = name + '.pdf'

        chr_diagram.draw(name, "MSTmap Linkage Groups")

# Replacement function for basicchromosome. The difference is that it draws a
# straight line through the middle for each marker.
def _overdraw_subcomponents_with_middle(self, cur_drawing):
    _color_trans = _Colors.ColorTranslator()

    # set the coordinates of the segment -- it'll take up the MIDDLE part
    # of the space we have.
    segment_y = self.end_y_position
    segment_width = (self.end_x_position - self.start_x_position) * self.chr_percent
    label_sep = (
        self.end_x_position - self.start_x_position
    ) * self.label_sep_percent
    segment_height = self.start_y_position - self.end_y_position
    segment_x = self.start_x_position + 0.5 * (
        self.end_x_position - self.start_x_position - segment_width
    )

    left_labels = []
    right_labels = []
    for f in self.features:
        try:
            # Assume SeqFeature objects
            start = f.location.start
            end = f.location.end
            strand = f.location.strand
            try:
                # Handles Artemis colour integers, HTML colors, etc
                color = _color_trans.translate(f.qualifiers["color"][0])
            except Exception:
                color = self.default_feature_color
            fill_color = color
            name = ""
            for qualifier in self.name_qualifiers:
                if qualifier in f.qualifiers:
                    name = f.qualifiers[qualifier][0]
                    break
        except AttributeError:
            # Assume tuple of ints, string, and color
            start, end, strand, name, color = f[:5]
            color = _color_trans.translate(color)
            if len(f) > 5:
                fill_color = _color_trans.translate(f[5])
            else:
                fill_color = color
        assert 0 <= start <= end <= self.bp_length
        # if strand == +1:
        #     # Right side only
        #     x = segment_x + segment_width * 0.6
        #     w = segment_width * 0.4
        # elif strand == -1:
        #     # Left side only
        #     x = segment_x
        #     w = segment_width * 0.4
        # else:
            # Both or neither - full width
        x = segment_x
        w = segment_width
        local_scale = segment_height / self.bp_length
        fill_rectangle = Rect(
            x,
            segment_y + segment_height - local_scale * start,
            w,
            local_scale * (start - end),
        )
        fill_rectangle.fillColor = fill_color
        fill_rectangle.strokeColor = color
        cur_drawing.add(fill_rectangle)

        if name:
            if fill_color == color:
                back_color = None
            else:
                back_color = fill_color
            value = (
                segment_y + segment_height - local_scale * start,
                color,
                back_color,
                name,
            )
            if strand == -1:
                self._left_labels.append(value)
            else:
                self._right_labels.append(value)
