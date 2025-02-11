# BentleyOttmann
Implementation of the Bentley-Ottman Algorithm

## How to run
Clone the project
```
mkdir build
cd build
cmake ..
cmake --build .
./bentley_ottmann <input_file_name>
```
## Data presentation


### Input data
The algorithm takes as input an input file in the form of a set of n lines (each with a segment).
Each line contains 4 numbers representing the coordinates of the segment with x1, y1, x2, y2 points respectively

### Output data
The set of points at which segments intersect and, for each point, the set of segment ids (starting with 1) that intersect at that point
