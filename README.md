# Introduction
MSTmap is a software tool that builds genetic linkage maps efficiently and accurately. It is published by Nucleic Acid Research [https://doi.org/10.1093/nar/gkaf332](https://doi.org/10.1093/nar/gkaf332)

- Find the web version here [https://mstmap.org/](https://mstmap.org/)
- This repo contains the Python library for the original C++ software [https://github.com/ucrbioinfo/MSTmap](https://github.com/ucrbioinfo/MSTmap)
- Extremely fast and computationally efficient
- Written in Python, Cython, and C++

# Documentation
You may find the documentation for MSTmap Python at its [GitHub Wiki](https://github.com/AmirUCR/MSTmap-Python/wiki).

Install the package via `pip install mstmap`, also here [https://pypi.org/project/mstmap/](https://pypi.org/project/mstmap/). Supported on Ubuntu Linux and Python >= 3.7.

If you wish to install from this repo and not PyPI, download the repo and do the following, preferably in a virtual or Conda environment:

`pip install cython`

`python setup.py build_ext --inplace`

`pip install .`

# Support
If you run into any issues or have suggestions for MSTmap Python or the web server, please report them on our GitHub Issues tracker. It's the fastest way to get support and helps us improve MSTmap for everyone.

# About
MSTmap Python and the online web-server have been developed and are maintained by <ins>Amir</ins>sadra Mohseni, and Stefano Lonardi at the University of California, Riverside.

If you use MSTMap Online or any of the provided packages, please cite at least the latest paper:

Mohseni, A., & Lonardi, S. (2025). MSTmap Online: enhanced usability, visualization, and accessibility. Nucleic Acids Research, _gkaf332_. 

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.15192382.svg)](https://doi.org/10.5281/zenodo.15192382)
