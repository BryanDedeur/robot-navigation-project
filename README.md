# Robot Navigation Project

![Alt text](OccupancyMap.png?raw=true "Random Snakes Occupancy Map")

## How to compile and execute

For Linux:

Installation
> must run cmake to generate makefile

```cmd
git clone https://github.com/BryanDudeInWater/robot-navigation-project.git
cd [parent-directory]/robot-navigation
cmake .
make
```
Compilation
> type these command in terminal in directory where the files are located. If cmake says the current version doesn't meet the minimum required cmake version, change cmake version from 3.12 to 3.x (where x is the cmake version your computer supports)

```
cmake .
make
```

Execution
> executables are placed in the bin directory. Navigate to the bin directory with command

```
cd bin
```

> after running 'make' a series of executables will be available for each part of the project.

```cmd
./robot-navigation
```

# Section 1 - Occypancy Grid Mapping
Purpose: to simulate LiDAR sensor readings in occupancy grid to help a robot navigate through a 2D environment

## Data Structure
This part of the project required the following classes for successful occupancy tracking
- Vector Map Class - contains the true occupancy data of the map as well as handles the ray casting from the robot LiDAR
- Map Node Class - contains occupancy log odd mean information at a tested coordinate

The main file will define the robot positions where LiDAR readings are measured and random points throughout the map.
The main file also contains code that connects lines between random points for the purpose of the second part of the project.

As the LiDAR beams pass through the free spaces, they update the free spaces by subtracting each free space’s log_odd_mean with log_odd_mean_free constant (0.7). When the beams encounter the obstacle, they stop traveling forward, update the occupied space by adding the space’s log_odd_mean with log_odd_mean_occupied constant (0.9). The length of each beam is 50 units. The lower the log_odd_mean, the redder the pixel gets. The higher the log_odd_mean, the bluer the pixel gets.

### UML Diagram for Class Structure
![Alt text](OccupancyGridMappingUML.png?raw=true "Occupancy Grid Mapping Class UML")

## Results

The output of the data is represented on a portable pixel map (.ppm) image file containing RGB color values for every pixel location.
- Black pixels: occupied positions
- Green pixels: robot positions
- Red pixels: are unoccupied points detected by the LiDAR (log odd mean result)
- Blue pixels: are occupied points detected by the LiDAR (log odd mean result)

##### Reoccuring LiDAR scans at a single point

The following is the results of the log odd mean testing at static robot position

|scan |	LOM (occupied) | LOM (unoccupied) | Occupied Odd | Unoccupied Odd |
|-----|----------------|------------------|--------------|----------------|
| 1	  | 0.9	           | -0.7             |	7.943282347  | 	0.1995262315  |
| 2	  | 1.8	           | -1.4             |	63.09573445  |	0.03981071706 | 
| 3	  | 2.7	           | -2.1             |	501.1872336  |	0.007943282347|
| 4	  | 3.6	           | -2.8             |	3981.071706  |	0.001584893192|
| 5	  | 4.5            |	-3.5          |	31622.7766   |	0.000316227766|
| 6	  | 5.4            |	-4.2          |	251188.6432  |	0.00006309573445|
| 7	  | 6.3            |	-4.9          |1995262.315	 |0.00001258925412|
| 8   | 7.2            |	-5.6          |	15848931.92	 |0.000002511886432|
| 9	  | 8.1            |	-6.3          |	125892541.2	 |0.0000005011872336|

![Alt text](OccupancyResults.png?raw=true "Occupancy Results")

<a href="probability-map.ppm" download="probability-map.ppm">Actual Probability Map.ppm</a>

![Alt text](Probability-map.png?raw=true "Probability Map")

## LiDAR to Occupancy Grid Calculation Approach

The LiDAR will cast 13 rays in the direction of the robot that will return a reading if an area is occupied or not. The length of each beam will have a max range of 50 units from its origin. Each ray being 15 degrees apart we can use this approach for calculating the individual points of interest that a beam will pass through.

Let l = the length of the ray as it is casted

we can simply find the grid points of length 1-50 at any angle by (cos(theta)*l, sin(theta)*l). Since those coordinates will contain a decimal we can round both the x and y off to find the nearest coordinate to occupy. And since these calculations will return negative numbers we also need to find the absolute values.

![Alt text](Calculations.png?raw=true "Calculations")

Let d = the direction of the robot

we only care about the readings in-front of the robot and to the sides (the direction + or - 90 degrees)

sudo code

```cpp
// for (theta = direction - 90; until theta >= direction + 90; theta = theta + 15 ) {
//  for (length = 1; until length == 50 or collides with something; length++) {
//    coordinate point x = round(abs((cos(theta) * length)));
//    coordinate point y = round(abs((sin(theta) * length)));
//  }
// }
```

# Section 2 - Path Planning
Purpose: to map a random path avoiding collidable objects

## Data Structure
This part of the project required the following classes for successful path finding
- Path Map Class - tracks the path list class from start to destination and all nodes in between
- Path List Class - this tracks the individual nodes in a linked list to store a connected chain of all possible results
- Path Node Class - this defines each individual node to ensure connectivity in the list as well as in the path
- Vector Map Class - containing all the occupancy data of the actual map

### UML Diagram for Class Structure

![Alt text](PathPlanning.png?raw=true "Path Planning Class UML")

## Results

![Alt text](RandomLines.png?raw=true "Randomly connected lines")


> this part of the project is not fully debugged so it wont compile properly

## Contributors
Bryan Dedeurwaerder – bdedeurwaerder@nevada.unr.edu  
Eric Duong - eduong@nevada.unr.edu  
Alton Prentice - aprentice@nevada.unr.edu  

## References

http://www.cs.cmu.edu/~16831-f14/notes/F14/16831_lecture06_agiri_dmcconac_kumarsha_nbhakta.pdf
