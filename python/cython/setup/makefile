
# build .py to .so

HOME_DIR = $(shell pwd)


DIST = dist
SETUP_DIR = setup
SETUP_SH = setup.sh

PY_DIRS := $(shell find lib -type d)
PY_FILES := $(foreach dir, $(shell find lib -type d), $(filter-out $(dir)/__init__.py, $(wildcard $(dir)/*.py)))



all: build_setup build_py build_clean


build_clean:
	@rm -rf build setup.py *.so $(SETUP_DIR)
	@find . -name *.c -o -name *.o | xargs rm -rf

build_setup:
	$(shell mkdir -p $(SETUP_DIR))
	$(foreach py, $(PY_FILES), \
		touch $(SETUP_DIR)/setup_$(notdir $(py)) && \
		echo  'from distutils.core import setup' >> $(SETUP_DIR)/setup_$(notdir $(py))  && \
		echo  'from Cython.Build import cythonize' >> $(SETUP_DIR)/setup_$(notdir $(py)) && \
		echo  "setup(name='build-$(basename $(py))-so', ext_modules=cythonize('$(HOME_DIR)/$(py)'))" >> $(SETUP_DIR)/setup_$(notdir $(py)) && \
		echo '')
	$(shell echo "#!/bin/bash" >> $(SETUP_SH)) \
	$(foreach py, $(PY_FILES), \
		$(shell echo "python3 $(SETUP_DIR)/setup_$(notdir $(py)) build_ext --inplace" >> $(SETUP_SH)) \
		$(shell echo "mkdir -p $(DIST)/$(dir $(py))" >> $(SETUP_SH))  \
		$(shell echo "mv $(basename $(notdir $(py)))*.so $(DIST)/$(dir $(py))" >> $(SETUP_SH)) )

build_py:
	. $(SETUP_SH)
	rm -rf build setup.py *.so tmp *.sh $(SETUP_DIR)
	find . -name *.c -o -name *.o | xargs rm -rf

.PHONY: clean

clean: build_clean
	@rm -rf *.so $(DIST)

