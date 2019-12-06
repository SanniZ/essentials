all: build_hello 

build_hello:
	@python3 setup.py build_ext --inplace
	@rm -rf *.c *.o build
	@mkdir -p dist
	@mv *.so dist/

.PHONY: clean

clean:
	@rm -rf *.c *.o *.so build dist
