from distutils.core import setup
from Cython.Build import cythonize

setup(name='hello-app',
      ext_modules=cythonize('hello.py'))
