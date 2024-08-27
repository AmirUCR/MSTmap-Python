from setuptools import setup, Extension
from Cython.Build import cythonize
import os

# Get the directory containing the setup.py script
current_dir = os.path.abspath(os.path.dirname(__file__))

# Set the include directory relative to the setup.py script's location
include_dir = os.path.join(current_dir, 'src')

# Cython extension module
extensions = [
    Extension(
        "mstmap",
        sources=[
            os.path.join("src", "mstmap.pyx"),  # Path to the .pyx file
            os.path.join("src", "mstmap_main.cpp"),   # Path to the .cpp file
            os.path.join("src", "genetic_map_DH.cpp"),
            os.path.join("src", "genetic_map_RIL.cpp"),
            os.path.join("src", "linkage_group_DH.cpp"),
            os.path.join("src", "linkage_group_RIL.cpp"),
            os.path.join("src", "MSTOpt.cpp")
        ],
        language="c++",
        extra_compile_args=["-std=c++11"],  # Adjust C++ standard if necessary
        include_dirs=[include_dir],  # Use the portable include directory
    )
]

setup(
    name='mstmap',
    version='1.0.8',
    author='Amirsadra Mohseni',
    author_email='amohs002@ucr.edu',
    description='A C++ library for genetic mapping with Cython interface',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    ext_modules=cythonize(extensions),
    zip_safe=False,
    python_requires='>=3.7',
)
