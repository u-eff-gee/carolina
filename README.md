# carolina: Clover Array ROOT Library for Numerical Analysis

## Table of Contents

1. [Description](#1-description)
2. [Install](#2-install)
   1. [Prerequisites](#2i-prerequisites)
   3. [Build](#2ii-build)
3. [Usage](#3-usage)
4. [License](#4-license)
5. [References](#5-references)

## 1. Description

The `carolina` C++ library processes output in the [ROOT](https://root.cern) [1] format that is created by the [mesytec](https://www.mesytec.com/) [2] `mvme` data acquisition (DAQ) software.
It provides scripts that create (calibrated) one- and two-dimensional histograms that can be further analyzed by other tools.
The library is intended to be used for data from the 2020/2021 Clover Array [3] campaigns at the High-Intensity Gamma-Ray Source (HIγS) [4], but it can also process output from previous campaigns with the γ3 setup [5].
A special focus of `carolina` is the inclusion of physically segmented clover-type high-purity germanium detectors, which often require photon-energy reconstruction ("addback").

Experimental setups for nuclear-resonance-fluorescence and other photonuclear experiments at HIγS are usually optimized for the experiment at hand.
This means that the detectors and readout electronics change often.
The `carolina` library tries to be general enough to support many different setups and standard analysis procedures, but of course it will never be able to provide as much power and performance as an  analysis code that is taylored to a specific experiment.

## 2. Install

### 2.i Prerequisites

* `boost.program_options` from the [boost](https://www.boost.org/) C++ libraries
* A C++ compiler. The ones provided by the [GNU compiler collection](https://gcc.gnu.org/) (GCC) and [clang](https://clang.llvm.org/) have been tested.
* [CMake](https://cmake.org/)
* [ROOT](https://root.cern) (tested with version 6.24/06)

### 2.ii Build

The following instructions describe the build process on a UNIX-like command line.
It is assumed that the code has been obtained from the git repository using the command

```
git clone https://github.com/uga-uga/carolina.git
```

This will create a `carolina` directory that will be referred to as `CAROLINA_SOURCE` in the following.
The first step is to create a build directory, referred to as `CAROLINA_BUILD` in the following:

```
mkdir CAROLINA_BUILD
```

After entering the build directory

```
cd CAROLINA_BUILD
```

use `CMake` to configure the build:

```
cmake CAROLINA_SOURCE
```

At this step, the user can select the desired analysis configuration by specifying the corresponding header file `ANALYSIS_HEADER` in `CAROLINA_SOURCE/include`:

```
cmake -DANALYSIS=ANALYSIS_HEADER CAROLINA_SOURCE
```

By convention, the analysis-configuration files are called `analysis_EXPERIMENT.hpp`, where `EXPERIMENT` is an identifier for an experiment, mostly probably the name of an isotope.

After configuring the build, compile the code using another `CMake` command:

```
cmake --build .
```

This will compile all the libraries and create several executables for different steps in the data-analysis procedure.

## 3. Usage

TODO

## 4. License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see https://www.gnu.org/licenses/.

Copyright (C) 2021 Udo Friman-Gayer (udo.friman-gayer@duke.edu)

## 5. References

[1] [https://root.cern](https://root.cern), accessed on 12/15/2021

[2] [https://www.mesytec.com/](https://www.mesytec.com/), accessed on 12/15/2021

[3] A. D. Ayangeakaa, U. Friman-Gayer, and R. V. F. Janssens, "The Clover Array for Nuclear Structure Studies at HIγS", Innovation News Network (2021) [https://www.innovationnewsnetwork.com/nuclear-structure/10491/](https://www.innovationnewsnetwork.com/nuclear-structure/10491/)

[4] H. R. Weller et al., "Research Opportunities at the upgraded HIγS facility", Prog. Part. Nucl. Phys. **62** (2009) 257-303 [http://dx.doi.org/10.1016/j.ppnp.2008.07.001](http://dx.doi.org/10.1016/j.ppnp.2008.07.001)

[5] B. Löher et al., "The high-efficiency γ-ray spectroscopy setup γ3 at HIγS", Nucl. Instrum. Meth. A **723** (2013), 136-142 [http://dx.doi.org/10.1016/j.nima.2013.04.087](http://dx.doi.org/10.1016/j.nima.2013.04.087)