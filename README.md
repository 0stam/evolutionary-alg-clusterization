# Evolutionary Algorithm Clusterization

*Note: this project is a competition entry. All code placed directly in the root folder was written by the competition host. My code is placed entirely in the `population` folder.*

This project solves a clusterization problem. More specifically, for a given set of points and number of clusters, it tries to minimize the sum of distances between points within each cluster, with access to distances between points, but not their exact coordinates. This is different from the usual problem of minimizing distance between points and their cluster's center, which can easily be solved using k-means or k-means++.

## Features

- Pure C++ implementation of genetic algorithm
- Multithreading support
- Preprocessing:
  - Initialization similar to K-means algorithm
  - First improvement hill climber for quick discovery of decent solutions
- Single-point gene crossing
- Tournament selection for crossing candidates
- Score caching and the ability to recalculate the score based only on a diff from newly changed genes
- Python result visualization

## Example results

Showcase of how this particular clusterization problem is impacted by point density:

<img width="75%" src="https://github.com/user-attachments/assets/a721556a-d72b-46d3-991f-b87a86cbd755" />

Multiple shapes:

<img width="75%" src="https://github.com/user-attachments/assets/235e9f10-2c7f-443b-bb57-4c7d0dfb8357" />

## Build and run

### Prerequisites

*   C++ Compiler (supporting C++14)
*   CMake (3.30 or higher recommended)

### Building the Project

1.  Clone the repository or navigate to the project root.
2.  Create a build directory:
    ```bash
    mkdir build
    cd build
    ```
3.  Configure the project with CMake:
    ```bash
    cmake ..
    ```
4.  Build the executable:
    ```bash
    make
    ```

### Running the Project

To run the project, execute the generated binary from the project root directory.

```bash
# Assuming you are in the 'build' directory after building
cd ..
./build/project
```
