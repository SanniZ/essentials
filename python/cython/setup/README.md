# build .py to .so

1. *push xxx.py to lib/ folder*  
   lib/xxx.py will be built to xxx.so  
  
2. *make xxx.so*  
   run 'make', it will create xxx.so to dist  
  
3. *how to uses xxx.so*  
  copy xxx.so to your app folder, import xxx module.  
  
for example:  
```
from hello import hello

if __name__ == '__main__':
    hello()
```
