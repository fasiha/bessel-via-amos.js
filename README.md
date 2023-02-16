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