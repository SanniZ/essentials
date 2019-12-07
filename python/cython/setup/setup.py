from distutils.core import setup
from Cython.Build import cythonize

setup(name='build-so',
      ext_modules=cythonize('lib/hello.py'))
