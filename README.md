# CS3388 Assignment 1

[Course Website](https://owl.uwo.ca/access/content/group/1b026160-e391-4236-b962-9783a9ab6a99/CS3388-Outline.html)

Due date: Friday Jan. 25th 2019, at 11:00pm.
Weight: 10% of final mark


The purpose of this assignment is to learn how to open a window of any size and address pixels within it, drawing lines using Bresenham's integer line drawing algorithm.

Your program must:
- Open a window of size 512x512 pixels
- Set the background colour to white
- Draw lines withing the window using Breseham's algorithm and the test program fragment below
- The resulting image should be identical to the image below
- The program must work for all symmetric cases
- The user must be able to quit the program by typing q

Before submitting your assignment, please refer to the [assignment marking](http://www.csd.uwo.ca/faculty/beau/CS3388/CS3388-Marking-Scheme.html) scheme and [submission guidelines](http://www.csd.uwo.ca/faculty/beau/CS3388/CS3388-Submission.html).

## Test Program Fragment
```
dt = 2.0*M_PI/200.0 ;
for (t = 0.0 ; t < 2.0*M_PI;) {
  x1 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
  y1 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
  t += dt ;
  x2 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
  y2 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
  Bresenham(x1,y1,x2,y2) ;
}
```
## Expected Resulting Image
![result](http://www.csd.uwo.ca/faculty/beau/CS3388/CS3388-Assign1-Output-Image.png "Resulting Image")
