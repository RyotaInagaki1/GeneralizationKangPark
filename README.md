# GeneralizationKangPark

**Important: Please Read the attached paper by Inagaki and Tamura (2206.04842.pdf in this repository), especially Sections 1, 2, and 7,  in order to better understand notation and purpose of the code.**

This repository contains code and data used to elucidate potential next steps to prove remaining cases of Conjecture 1.3, which claims$\Delta_{d}^{(3, -)}(n) \geq 0$ for all integers n and g, by using values of d where $q_d^{(1)}(m) \geq Q_{d-3}^{(1, -)}(m)$. This repository contains the computational data referred to in Section 7 of the Inagaki and Tamura 2022 paper. This data is contained in files with prefix output\_file.

## How to Use the C++ code (.cc file) in Linux Terminal

Before you do anything, make sure your pwd is the same directory as is the coefficients\_d\-3\_oneDash.cc

First, compile the C++ file. Type without quotes :\newline"g++ ./coefficients\_d\-3\_oneDash.cc \-o coefficients\_d2."


Then Type without quotes: \newline "./coefficients\_d2 NUM\_TERMS d output\_file\_d" where d is a positive integer parameter and NUM\_TERMS is the positive integer number such that the output calculates $Q_{d-3}^{(1, -)}(n)$, $q_{d}^{(1)}(n)$ and $q_{d}^{(1)}(n) - Q_{d-3}^{(1, -)}(n)$ for integer $n$ between 1 and NUM\_TERMS inclusive.

To stay organized, let d be the integer value of d you inputted earlier in the line.

## Regarding The output\_file in This Repository

In this repository, given a positive integer $d$, output\_file$d$ has the values of $n$ in the first column,
  $Q_{d-3}^{(1, -)}(n)$ in the second column, $q_d^{(1)}(n)$ in the third column, and $q_d^{(1)}(n) - Q_{d-3}^{(1, -)}(n)$ in the fourth column. The examined input values of $n$ range from 1 to 100,000 inclusive. These are output files calculated from running in the Terminal ./coefficients\_d2 NUM\_TERMS $d$ output\_file$d$ for $d = 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 22, 100$ after compiling coefficients\_d\-3\_oneDash.cc.  Open these files through your text editor.
  
  Given the data from the output\_file 's, for d
 in between 3 and 9 inclusive, it seems that $q_d^{(1)}(n) - Q_{d-3}^{(1, -)}(n)$ is negative and decreases very rapidly as $n$ gets large.

  Note that for $d$ at least 10,
  it seems that $q_d^{(1)}(n) - Q_{d-3}^{(1, -)}(n)$ is nonnegative and increases to very very large quantities as $n$ gets large.
  
 ## Acknowledgements
  
  We would like to thank Professsor Robert J. Lemke Oliver for providing original C++ code calculating values of $q_d^{(1)}(m)$ and $Q_{d}^{(1)}(m)$, 
  which we modified to the code in this repository. The comments in the code are the same as in the original except some additional comments made before the beginning of the section calculation $ Q_{d-3}^{(1, -)}(m)$. We have received explicit permission from the original author of the code to put it onto GitHub.
