# build .py to .so

DIST = dist

PY_FILES = $(wildcard lib/*.py)

all: build_py build_clean


build_clean:
	@rm -rf build setup.py
	@find . -name *.c -o -name *.o | xargs rm -rf

.PHONY: clean

clean: build_clean
	@rm -rf *.so $(DIST)

build_py:
	$(foreach py, $(PY_FILES), \
		rm -rf setup.py; \
		echo 'from distutils.core import setup' >> setup.py; \
		echo 'from Cython.Build import cythonize' >> setup.py; \
		echo "setup(name='build-$(basename $(py))-so', ext_modules=cythonize('$(py)'))" >> setup.py; \
		python3 setup.py build_ext --inplace; \
		mkdir -p $(DIST); \
		mv -f *.so $(DIST); \
	)
