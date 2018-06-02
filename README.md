#  8-connected component

I. Input: A binary image. 

II. Outputs: 

(a) outFile1:  in argv[1] for:

1) Pretty print the result of the Pass-1 *and* the EQAry with proper captions
2) Pretty print the result of the Pass-2 *and* the EQAry with proper captions
3) print EQAry after manage the EQAry 
4) Pretty print the result of the Pass-3 and the EQAry with proper caption

(b) outFile2:   in argv[2] for:

5) create an image file from the result of Pass-3 with header

(c) outFile3: in argv[3] for:

(6) Output the connected component property using the format: print the header of the CC image, follows by the true numbers of the c.c. follows by the properties of each c.c. components

*******************************
III. Data structure:
*******************************
- numRows (int)
- numCols (int)
- minVal (int)
- maxVal (int)
- newMin (int)
- newMax (int)

- newLabel (int) // initallize to 0

- zeroFramedAry (int **) a 2D array, need to dynamically allocate at run time of size numRows + 2 by numCols + 2.

- NeighborAry[5](int) // during the first pass, p(i,j) looks at upper 3 and left neighbors, and during the second pass, p(i,j) looks at bottom 3 and right neighbors and itself 

- EQAry (int *) // a 1-D array, need to dynamically allocate at run time of size ( numRows * numCols) / 2 and initallize to EQAry[i] = i. 

- Property (1D struct) //a table that store the properties of connected components.
- label
- numbpixels
- boundingBox : (minRow, minCol, maxRow, maxCol)

- methods:
- constructor(s) // need to dynamically allocate all arrays;  and assign values to numRows,..., etc.

- zeroFramed // mirrow framing the image as taught in class
- loadImage // read from input file and load zeroFramedAry begin at (1,1)
- loadNeighbors // load the respective neighbors of given pixel(i,j)

- 8ConnectCC_Pass1
- 8ConnectCC_Pass2    
- 8ConnectCC_Pass3  

- updateEQAry
- manageEQAry      // manage the EQAry so to findout true number of connected components..
- printCCProperty   // print the header of the CC image, follows by the 

- prettyPrint


*******************************
III. Algorithms 
*******************************

step 0: read the image header
           dynamically allocate zeroFramedAry and all other arrays

step 1: load the input image onto zeroFramedAry

step 2: - 8ConnectCC_Pass1
- prettyprint the result of pass1

- print EQAry    // with index up to newLable with proper caption

step 3: - 8ConnectCC_Pass2
- prettyprint the result of pass2

- print EQAry // with index up to newLable with caption

step 4:  - manageEQAry 
- print EQAry // with index up to newLable with caption

step 5: - 8ConnectCC_Pass3  
- prettyprint the result of pass3 of the connected c.c.  // with caption

- Output the result of pass3 to outFile2 with updated image header

- print the propertis of the connected c.c. // with proper caption
