# build .py to .so

1. push .py to lib/ folder.  
lib/xxx.py will be built to .so

2. modify setup.py.  
update ext_modules=cythonize(xxx) to lib/xxx.py

3. make .so  
run 'make', it will create .so to dist

4. how to uses .so  
copy .so to your app folder, import xxx module.  
you can set to xxx.py, for example: hello.so.  

for example:  
```
from hello import hello

if __name__ == '__main__':
    hello()
```