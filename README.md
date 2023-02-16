This is a very hastily-put-together library to export Scipy's [`kv`](https://docs.scipy.org/doc/scipy/reference/generated/scipy.special.kv.html) and [`kve`](https://docs.scipy.org/doc/scipy/reference/generated/scipy.special.kve.html) functions (modified Bessel functions of the second kind) to JavaScript/Node via WebAssembly.

The Scipy functions call a public domain Fortran library called AMOS, which were converted to C via `f2c`, which were then transpiled to WebAssembly via Emscripten.

This library adds some light library sugar around AMOS to give export a Scipy-like syntax.

Note: although AMOS and Scipy both operate on arrays of inputs, this library only exports JavaScript to handle scalar inputs because I can't figure out how to make Emscripten call AMOS' `ZBESK` routine fully. This is very much a proof-of-concept and AMOS deserves to be brought fully into WebAssembly (not just these two functions), and hopefully this library can help towards that goal.

## Installation
```
npm i bessel-via-amos.js
```

## Usage
TypeScript:
```ts
import amosPromise from 'bessel-via-amos.js';
(async function main() {
  const amos = await amosPromise;
  console.log(amos.kve(4.4, 3.3));
})();
```

Browser: I'm not sure but it hopefully won't be hard.

## Dev
Diary of how I made this.

First set up [miniconda](https://docs.conda.io/en/latest/miniconda.html), then
```sh
conda create -n amos-env
conda activate amos-env
conda install -c conda-forge f2c # might need more things
```

Now get AMOS, via Scipy.
```sh
git clone https://github.com/scipy/scipy.git --depth=1
cp -pr scipy/scipy/special/amos .
cd amos

curl -LO http://www.netlib.org/blas/i1mach.f 
curl -LO http://www.netlib.org/blas/r1mach.f
curl -LO http://www.netlib.org/blas/d1mach.f 

f2c *f

export CONDA_TOP_LEVEL=`conda info --envs | grep '*' | awk '{print $NF}'`

gcc -lf2c -L $CONDA_TOP_LEVEL/lib  -I $CONDA_TOP_LEVEL/include *c -o main
DYLD_LIBRARY_PATH=$CONDA_TOP_LEVEL/lib ./main
```

For emscripten, first [install Emscripten](https://emscripten.org/docs/getting_started/downloads.html) and activate emsdk. Then
```sh
git clone https://github.com/gergondet/libf2c-emscripten
cd libf2c-emscripten
make -j4
cp f2c.h libf2c.a /PATH/TO/amos-js/amos
```
I haven't bundled these because likely as emsdk advances, these files will change?

Then back in `amos`, ensuring that emsdk is installed and activated,
```sh
emcc -lm -lf2c -L. *c
```
Confirm this runs and outputs something like `cyr=7.443113`:
```
node a.out.js
```

Now to make a library:
```sh
emcc -Os -lm -lf2c -L. -sMODULARIZE -sEXPORTED_FUNCTIONS=_kve,_kv,_zbesk_ *c
```

Now
```sh
cp a.out.* ../
```
And run `node demo.js` and confirm that it prints out `7.44311267732952`.