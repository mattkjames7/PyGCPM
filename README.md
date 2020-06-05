# PyGCPM

PyGCPM is a Python 3 wrapper for the Global Core Plasma Model
(Gallagher et al., 2000). This module uses version 2.4 from
https://plasmasphere.nasa.gov/models/

The original code has been modified slightly such that it produces less 
output to the terminal and the path of the data files used is passed 
through a C wrapper so that the Fortran code is able to find them.

## Installation

Using `pip`:

```bash
python3 -m pip install PyGCPM --user
```

or,

```bash
pip3 install PyGCPM --user
```

From this repo:

```
git clone https://github.com/mattkjames7/PyGCPM.git
cd PyGCPM/
python3 setup.py install --user
```

## Usage

So far, there are only two working functions - `GCPM` and `PlotEqSlice`,
the `PlotMLTSlice` function is doing odd things. It's worth noting that
this model will take some time to run with large numbers of points.

### `GCPM`

This function takes in position in the Solar Magnetospheric (SM) 
coordinate system, along with a date and a time then produces a model
output for each position.

```python
import PyGCPM
ne,nH,nHe,nO = PyGCPM.GCPM(x,y,z,Date,ut,Kp=Kp,Verbose=Verbose)
```

Where the inputs are:

| Variable | Data Type | Description | 
|:--:|:---:|:---|
| `x` | `float` or `numpy.ndarray` | Scalar or array _x_ position(s) in _R<sub>E</sub>_ |
| `y` | `float` or `numpy.ndarray` | Scalar or array _y_ position(s) in _R<sub>E</sub>_ |
| `z` | `float` or `numpy.ndarray` | Scalar or array _z_ position(s) in _R<sub>E</sub>_ |
| `Date` | `int` or `numpy.ndarray` | Integer date in format yyyymmdd - if provided with a scalar then all positions will use the same date, otherwise an array can be provided for a time series |
| `ut` | `float` or `numpy.ndarray` | Floating point hours where `ut = hh + mm/60 + ss/3600`. As with `Date` - if provided with a scalar then all positions will use the same time, otherwise an array can be provided for a time series |
| `Kp` | `float` or `numpy.ndarray` | (optional) Kp index, as with `Date` and `ut` - this can be a scalar or an array |
| `Verbose` | `bool` | (optional) If `True` then the function will display its progress in the terminal |

Function outputs:

| Variable | Data Type | Description | 
|:--:|:---:|:---|
| `ne` | `float32` | Electron density at each position (cm<sup>-3</sup>) |
| `nH` | `float32` | Proton density at each position (cm<sup>-3</sup>)  |
| `nHe` | `float32` | Helium ion density at each position (cm<sup>-3</sup>)  |
| `nO` | `float32` | Oxygen ion density at each position (cm<sup>-3</sup>)  |


### `PlotEqSlice`

This function will plot a slice through the SM equator (_z<sub>SM</sub>_ = 0).

```python
import PyGCPM
PyGCPM.PlotEqSlice(Date,ut,Parameter='ne',Rmax=10.0,dR=0.5,Kp=1.0,fig=None,
		maps=[1,1,0,0],zlog=True,cmap='gnuplot',scale=None,Verbose=False)
```

| Variable | Data Type | Description | 
|:--:|:---:|:---|
| `Date` | `int` | Integer date in format yyyymmdd |
| `ut` | `float` | Floating point hours where `ut = hh + mm/60 + ss/3600` |
| `Parameter` | `str` | String containing the name of the parameter to plot: `'ne'|'nH'|'nHe'|'nO'` |
| `Rmax` | `float` | This defines the maximum postion along _x_ and _y_ axes to calculate the model at - the _x_ and _y_ limits of the plot are `(-Rmax,Rmax)` and `(Rmax,-Rmax)`, respectively |
| `dR` | `float` | The plot is a grid - this is the size of a grid box in _R<sub>E</sub>_ |
| `Kp` | `float` | Kp index |
| `fig` | `object` or `None` | If `None` - a new plot is created; if set to an instance of `matplotlib.pyplot`, then the current figure is used and a new subplot is created within; if a `matplotlib.pyplot.Axes` instance is used then plotting is done on the current axes |
| `maps` | `list` or `tuple` | This defines the number of subplots and the position of the current plot: `maps = [xmaps,ymaps,xmap,ymap]` |
| `zlog` | `bool` | If True, the color scale is logarithmic |
| `cmap` | `str` | String containing the name of the colormap to use (alternatively provide the colormap object itself) |
| `scale` | `list`, `tuple` or `None` | If `None` then the limits of the color scale are detemined automatically. If `list` or `tuple` then these should contain two elements defining the minimum and maximum scale limits. |
| `Verbose` | `bool` | If `True` then the function will display its progress in the terminal |



## References

Gallagher, D. L., Craven, P. D., & Comfort, R. H. (2000, aug). Global core plasma model.
J. Geophys. Res. Sp. Phys., 105(A8), 18819–18833. doi: 10.1029/1999JA000241
