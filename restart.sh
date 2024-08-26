#!/bin/bash

python setup.py clean --all
python setup.py build_ext --inplace
pip uninstall mstmap -y
pip install .