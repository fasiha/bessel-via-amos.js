```sh
git clone https://github.com/scipy/scipy.git --depth=1
cp -pr scipy/scipy/special/amos .
cd amos

curl -LO http://www.netlib.org/blas/i1mach.f 
curl -LO http://www.netlib.org/blas/r1mach.f
curl -LO http://www.netlib.org/blas/d1mach.f 

f2c *f
gcc -lf2c -L/Users/fasiha/miniconda3/envs/ebisu-v2.1/lib  -I/Users/fasiha/miniconda3/envs/ebisu-v2.1/include *c -o main
DYLD_LIBRARY_PATH=/Users/fasiha/miniconda3/envs/ebisu-v2.1/lib ./main
```

For emscripten, first install Emscripten and activate emsdk. Then
```
git clone https://github.com/gergondet/libf2c-emscripten
cd libf2c-emscripten
make -j4
cp f2c.h libf2c.a /PATH/TO/amos-js/amos
```
Then in `amos-js/amos`, ensuring that emsdk is installed and activated,
```
emcc -lm -lf2c -L. *c
```

Now to make a library:
```sh
mv main.c main.old
# create kv_kve.c
emcc -Os -lm -lf2c -L. -sMODULARIZE -sEXPORTED_FUNCTIONS=_kve,_kv *c
```
Now run `node demo.js`.