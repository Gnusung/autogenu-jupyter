# AutoGenU for Jupyter

[![build](https://github.com/mayataka/autogenu-jupyter/actions/workflows/build.yaml/badge.svg?branch=master)](https://github.com/mayataka/autogenu-jupyter/actions/workflows/build.yaml)
[![doxygen](https://github.com/mayataka/autogenu-jupyter/actions/workflows/doxygen.yaml/badge.svg)](https://github.com/mayataka/autogenu-jupyter/actions/workflows/doxygen.yaml)


## Introduction
This project provides the continuation/GMRES method (C/GMRES method) based solvers for nonlinear model predictive control (NMPC) and an automatic code generator for NMPC, called `AutoGenU`.

The following C/GMRES based solvers are provided: 
- `MultipleShootingCGMRESSolver` : The multiple shooting based C/GMRES method with condensing of the state and costate directions.
- `SingleShootingCGMRESSolver` : The original C/GMRES method (single shooting).

## Requirement
- C++17 (MinGW or MSYS and PATH to either are required for Windows users)
- CMake, git
- Python 3.8 or later, Jupyter Lab or Jupyter Notebook, SymPy, NumPy, and collection (to generate `ocp.hpp`, `main.cpp`, and `CMakeLists.txt` by `AutoGenU.ipynb`)
- Matplotlib (to plot simulation data on `AutoGenU.ipynb`)
- ffmpeg (to generate animations in the example notebooks)


## Usage
### 1. Setup requirements
Please confirm that you clone this repository as 
```
git clone https://github.com/mayataka/autogenu-jupyter --recursive
```
Otherwise, please do the following command:
```
git submodule update --init --recursive
```
The python modules can be installed via
```
pip install -r requirements.txt
```

### 2. Code generation
`AutoGenU.ipynb` generates the following source files under your setting state equation, constraints, cost function, and parameters: 
- `ocp.hpp` : A definition of the optimal control problem (OCP).
- `main.cpp` : An executablb of the closed-loop simulation.
- `CMakeLists.txt` : Scripts to build C++ projects. 
- Files in `python` directory : Source files of Python interface via pybind11.

You can generate these files, run simulations, plot results, and install the Python interfaces through `AutoGenU.ipynb`.


### 3. Install header-only `cgmres` C++ library
Aside from the notebook for the code-generation, the C++ `cgmres` library, which is a header-only library, can be installed via
```
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=YOUR_INSTALL_DESTINATION
make install 
```
Then you can build the NMPC code with the generated `ocp.hpp` file and without `.ipynb` notebook files. 
The examples are found in `examples/cpp` directory.


### 4. Python bindings
Python bindings are installed via `.ipynb` files. 
To use the installed Python bindings, set `PYTHONPATH` as 
```
export PYTHONPATH=$PYTHONPATH:$DESTINATION/lib/python3.x/site-packages
``` 
Then you can use python interfaces as 
```
import cgmres.common # this includes horizon, solver settings, etc.
import cgmres.your_ocp_name # this includes OCP definition and NMPC solvers 
```


## Demos
Demos are presented in `cartpole.ipynb`, `pendubot.ipynb`, `hexacopter.ipynb`, and `mobilerobot.ipynb`. You can obtain the following simulation results jusy by runnig these `.ipynb` files. The details of the each OCP formulations are described in each `.ipynb` files.

<img src="https://raw.githubusercontent.com/wiki/mayataka/CGMRES/images/cartpole.gif" width="300"> &nbsp;
<img src="https://raw.githubusercontent.com/wiki/mayataka/CGMRES/images/pendubot.gif" width="300"> 

<img src="https://raw.githubusercontent.com/wiki/mayataka/CGMRES/images/hexacopter.gif" width="450">  

<img src="https://raw.githubusercontent.com/wiki/mayataka/CGMRES/images/mobilerobot.gif" width="450"> 


## License
MIT

## Citing autogenu-jupyter

We'd appriciate if you use cite the following conference paper:

```
@inproceedings{katayama2020autogenu,
  title={Automatic code generation tool for nonlinear model predictive control with {J}upyter},
  author={Sotaro Katayama and Toshiyuki Ohtsuka},
  booktitle={{The 21st IFAC World Congress 2020}},
  pages={7033-7040},
  year={2020}}
```

## References
1. [T. Ohtsuka A continuation/GMRES method for fast computation of nonlinear receding horizon control, Automatica, Vol. 40, No. 4, pp. 563-574 (2004)](https://doi.org/10.1016/j.automatica.2003.11.005)
2. [C. T. Kelly, Iterative methods for linear and nonlinear equations, Frontiers in Apllied Mathematics, SIAM (1995)](https://doi.org/10.1137/1.9781611970944)
3. [Y. Shimizu, T. Ohtsuka, M. Diehl, A real‐time algorithm for nonlinear receding horizon control using multiple shooting and continuation/Krylov method, International Journal of Robust and Nonlinear Control, Vol. 19, No. 8, pp. 919-936 (2008)](https://doi.org/10.1002/rnc.1363)
