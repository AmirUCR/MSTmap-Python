# cython: language_level=3

# Import the necessary Cython modules
from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector
from cpython.exc cimport PyErr_SetString
from cython.operator cimport dereference as deref
from cython.operator cimport address as addr

# Python Modules
import pandas
from reportlab.lib.units import cm
from Bio.Graphics import BasicChromosome
from reportlab.graphics.shapes import Rect
from Bio.Graphics.GenomeDiagram import _Colors
# ---

from reportlab.graphics.shapes import ArcPath
from reportlab.graphics.shapes import Drawing
from reportlab.graphics.shapes import Line
from reportlab.graphics.shapes import Rect
from reportlab.graphics.shapes import String
from reportlab.graphics.shapes import Wedge
from reportlab.graphics.widgetbase import Widget
from reportlab.lib import colors
from reportlab.lib.pagesizes import letter
from reportlab.lib.units import inch
from reportlab.lib.units import mm
from reportlab.pdfbase.pdfmetrics import stringWidth

from Bio.Graphics import _write
from Bio.Graphics.GenomeDiagram import _Colors
_color_trans = _Colors.ColorTranslator()

cdef extern from "mstmap.h":
    cdef cppclass MSTmap:
        MSTmap()
        void set_default_args(string poptype) except +
        void summary() except +
        void set_population_type(string poptype) except +
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
    
    def set_default_args(self, str poptype):
        self.cpp_mstmap.set_default_args(poptype.encode('utf-8'))
    
    def summary(self):
        self.cpp_mstmap.summary()
    
    def set_population_type(self, str poptype):
        self.cpp_mstmap.set_population_type(poptype.encode('utf-8'))
    
    def set_input_file(self, str path):
        df = pandas.read_csv(path, engine='python', sep=None)
        n1, n2 = df.shape
        n2 = n2 - 1

        self.cpp_mstmap.set_number_of_individual(n2)
        self.cpp_mstmap.set_number_of_loci(n1)

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
    
    def set_estimation_before_clustering(self, bool estimation):
        to_mst = ""

        if estimation == True:
            to_mst = "yes"
        else:
            to_mst = "no"

        self.cpp_mstmap.set_estimation_before_clustering(to_mst.encode('utf-8'))
    
    def set_detect_bad_data(self, bool detect):
        to_mst = ""

        if detect == True:
            to_mst = "yes"
        else:
            to_mst = "no"

        self.cpp_mstmap.set_detect_bad_data(to_mst.encode('utf-8'))
    
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

    def draw_linkage_map(self, name="linkage_map.pdf"):
        BasicChromosome.AnnotatedChromosomeSegment._overdraw_subcomponents = _overdraw_subcomponents_with_middle
        BasicChromosome.Chromosome._draw_label = _draw_label_but_less_ugly
        BasicChromosome.Organism.draw = my_own_draw

        num_lg = self.get_num_linkage_groups()

        most_markers = 0
        for nlg in range(num_lg):
            nm = len(self.get_lg_markers_by_index(nlg))
            if nm > most_markers:
                most_markers = nm

        position_lists = list()
        marker_name_lists = list()
        for i in range(num_lg):
            position_lists.append([round(p, 2) for p in self.get_lg_distances_by_index(i)])
            marker_name_lists.append(self.get_lg_markers_by_index(i))

        chr_diagram = BasicChromosome.Organism()

        maxlens = []
        for sublist in marker_name_lists:
            lens = [len(e) for e in sublist]
            maxlens.append(max(lens))

        max_len = max(max(sub_list) for sub_list in position_lists)

        y = max(0.3 * max_len, 0.14 * most_markers, 14)
        x = max(num_lg * 7, 7)

        chr_diagram.page_size = (x * cm, y * cm)

        if max_len == 0:
            max_len = 1

        telomere_length = 0.1

        for nlg in range(num_lg):
            positions = position_lists[nlg]
            marker_names = marker_name_lists[nlg]

            spacer_length = 0.20 * max_len
            middle_len = max(position_lists[nlg])

            if middle_len == 0:
                middle_len = 0.01

            cur_chromosome = BasicChromosome.Chromosome(f'LG{nlg}')
            # Set the scale to the MAXIMUM length plus the two telomeres in bp,
            # want the same scale used on all five chromosomes so they can be
            # compared to each other
            cur_chromosome.scale_num = max_len + 2 * telomere_length
            
            features = list()
            for idx, marker in enumerate(marker_names):
                features.append((positions[idx], positions[idx], -1, str(positions[idx]), 1))
                features.append((positions[idx], positions[idx], 1, marker, 1))

            # spacer = BasicChromosome.SpacerSegment()
            # spacer.scale = spacer_length
            # cur_chromosome.add(spacer)

            # Add an opening telomere
            start = BasicChromosome.TelomereSegment()
            start.fill_color = _color_trans.translate('#8d8bff')
            start.scale = telomere_length
            cur_chromosome.add(start)

            # Add a body - using bp as the scale length here.
            body = BasicChromosome.AnnotatedChromosomeSegment(middle_len, features)
            body.fill_color = _color_trans.translate('#8d8bff')
            body.scale = middle_len
            cur_chromosome.add(body)

            # Add a closing telomere
            end = BasicChromosome.TelomereSegment(inverted=True)
            end.fill_color = _color_trans.translate('#8d8bff')
            end.scale = telomere_length
            cur_chromosome.add(end)

            # spacer = BasicChromosome.SpacerSegment()
            # spacer.scale = spacer_length
            # cur_chromosome.add(spacer)

            # This chromosome is done
            chr_diagram.add(cur_chromosome)

        if not name.endswith('.pdf'):
            name = name + '.pdf'

        chr_diagram.draw(name, "")

def my_own_draw(self, output_file, title):
    """Draw out the information for the Organism.

    Arguments:
        - output_file -- The name of a file specifying where the
        document should be saved, or a handle to be written to.
        The output format is set when creating the Organism object.
        Alternatively, output_file=None will return the drawing using
        the low-level ReportLab objects (for further processing, such
        as adding additional graphics, before writing).
        - title -- The output title of the produced document.

    """
    width, height = self.page_size
    cur_drawing = Drawing(width, height)

    self._draw_title(cur_drawing, title, width, height)

    cur_x_pos = cm * 0.5 * 5
    if len(self._sub_components) > 0:
        x_pos_change = (width - cm * 5) / len(self._sub_components)
    # no sub_components
    else:
        pass

    for sub_component in self._sub_components:
        # set the drawing location of the chromosome
        sub_component.start_x_position = cur_x_pos + 0.4 * x_pos_change
        sub_component.end_x_position = cur_x_pos + 0.6 * x_pos_change
        sub_component.start_y_position = height - 0.25 * inch
        sub_component.end_y_position = self._legend_height + 0.165 * inch

        # do the drawing
        sub_component.draw(cur_drawing)

        # update the locations for the next chromosome
        cur_x_pos += x_pos_change

    self._draw_legend(cur_drawing, self._legend_height + 0.5 * cm, width)

    if output_file is None:
        # Let the user take care of writing to the file...
        return cur_drawing

    return _write(cur_drawing, output_file, self.output_format)

def _draw_label_but_less_ugly(self, cur_drawing, label_name):
    """Draw a label for the chromosome (PRIVATE)."""
    x_position = 0.5 * (self.start_x_position + self.end_x_position)
    y_position = self.end_y_position

    label_string = String(x_position, y_position, label_name)
    label_string.fontName = "Times-Roman"
    label_string.fontSize = 12
    label_string.textAnchor = "middle"

    cur_drawing.add(label_string)

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
                color = _color_trans.translate(f[5])
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