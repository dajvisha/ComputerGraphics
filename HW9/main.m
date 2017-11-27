# Diego Adolfo José Villa - A00815260
# Computer Graphics
# HW 9 - Interative Lineal Interpolation

# This is the main of the program

# Ask for the values
n = input("n: ");
begBeg = input("A(1,1): ");
begLast = input("A(1,last): ");
lastBeg = input("A(last,1): ");
lastLast = input("A(last,last): ");

# Create the grid
gridSize = 2^n + 1;
global myGrid = zeros(gridSize,gridSize);

myGrid(1,1) = begBeg;
myGrid(1,gridSize) = begLast;
myGrid(gridSize,1) = lastBeg;
myGrid(gridSize, gridSize) = lastLast;

# First iteration
gridMiddle = int32(gridSize/2);

myGrid(1, gridMiddle) = 0.5 * (myGrid(1,1) + myGrid(1, gridSize));
myGrid(gridSize, gridMiddle) = 0.5 * (myGrid(gridSize,1) + myGrid(gridSize,gridSize));
myGrid(gridMiddle, 1) = 0.5 * (myGrid(1,1) + myGrid(gridSize,1));
myGrid(gridMiddle, gridSize) = 0.5 * (myGrid(1,gridSize) + myGrid(gridSize,gridSize));
myGrid(gridMiddle, gridMiddle) = 0.25 * (myGrid(1, gridMiddle) + myGrid(gridSize, gridMiddle) + myGrid(gridMiddle, 1) + myGrid(gridMiddle, gridSize));

# Fills all the grid
fillGrid(1, gridSize, 1, gridSize);

# Generates the 3D plot
xPos = [1:1:gridSize];
yPos = [1:1:gridSize];
mesh(xPos, yPos, myGrid);
xlabel ("x");
ylabel ("y");
zlabel ("z");
title ("Interative Lineal Interpolation");