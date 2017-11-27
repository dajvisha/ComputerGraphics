# Diego Adolfo José Villa - A00815260
# Computer Graphics
# HW 9 - Interative Lineal Interpolation

# This is a recursive function to fill a given grid of heights 
function fillGrid (rowStart, rowEnd, colStart, colEnd)
  global myGrid;
  lengthGrid = (rowEnd - rowStart) + 1; 
  middleRow = int32((rowStart+rowEnd)/2);
  middleCol = int32((colStart+colEnd)/2);
  if (lengthGrid >= 3)
    if (myGrid(rowStart, middleCol) == 0)
      myGrid(rowStart, middleCol) = 0.5 * (myGrid(rowStart,colStart) + myGrid(rowStart,colEnd));
    endif
    if (myGrid(rowEnd, middleCol) == 0)
      myGrid(rowEnd, middleCol) = 0.5 * (myGrid(rowEnd,colStart) + myGrid(rowEnd,colEnd));
    endif
    if (myGrid(middleRow,colStart) == 0)
      myGrid(middleRow,colStart) = 0.5 * (myGrid(rowStart,colStart) + myGrid(rowEnd,colStart));
    endif
    if (myGrid(middleRow,colEnd) == 0)
      myGrid(middleRow,colEnd) = 0.5 * (myGrid(rowStart,colEnd) + myGrid(rowEnd,colEnd));
    endif
    if (myGrid(middleRow,middleCol) == 0)
      myGrid(middleRow,middleCol) =  0.25 * (myGrid(rowStart, middleCol) + myGrid(rowEnd, middleCol) + myGrid(middleRow,colStart) + myGrid(middleRow,colEnd));
    endif
    fillGrid(rowStart, middleRow, colStart, middleCol);
    fillGrid(rowStart, middleRow, middleCol, colEnd);
    fillGrid(middleRow, rowEnd, colStart, middleCol);
    fillGrid(middleRow, rowEnd, middleCol, colEnd);
   endif
endfunction