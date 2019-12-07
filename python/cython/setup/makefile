# build .py to .so

out = dist

all: build_py build_clean

build_py:
	@python3 setup.py build_ext --inplace
	@mkdir -p $(out)
	@mv *.so $(out)

build_clean:
	@rm -rf build
	@find . -name *.c -o -name *.o | xargs rm -rf

clean: build_clean
	@rm -rf *.so $(out)
