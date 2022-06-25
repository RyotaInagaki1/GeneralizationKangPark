# GeneralizationKangPark

## Important: See the Readme.pdf file! It is much better formatted!

This repository contains code and data used to elucidate potential next steps to prove remaining cases of Conjecture 1.3 $\Delta^{(3,-)}_d(n) \geq 1$ by using values of d where $q_d^{(1)}(m) \geq Q_{d-3}^{(1, -)}(m)$. This repository contains the code and data referred to in Section 7 of the Inagaki and Tamura 2022 paper.

## How to Use the C++ code (.cc file) in Linux Terminal

Before you do anything, make sure your pwd is the same directory as is the coefficients\_d\-3\_oneDash.cc

First, compile the C++ file. Type without quotes :\newline"g++ ./coefficients\_d\-3\_oneDash.cc \-o coefficients\_d2."


Then Type without quotes: \newline "./coefficients\_d2 NUM\_TERMS d output\_file \textless d \textgreater" where d is a positive integer parameter and NUM\_TERMS is the positive integer number of terms you want to compute $Q_{d-3}^{(1, -)}(n)$, $q_{d}^{(1)}(n)$ and $ \Delta^{(3,-)}_d(n)$

To stay organized, let d be the integer value of d you inputted earlier in the line.

## Regarding The output\_file

In this repository, given a positive integer $d$, output\_file$d$ has the values of $n$ in the first column,
  $Q_{d-3}^{(1, -)}(n)$ in the second column, $q^{(1)}_d(n)$ in the third column, and q^{(1)}_d(n) - Q_{d-3}^{(1, -)}(n)$ in the fourth column. $n$ ranges from 1 to 100,000 inclusive. Open these files through your text editor.
  
  Note from the output\_file 's  for d
 in between 1 and 9, it seems as if 
  $\Delta^{(3,-)}_d(n) < 0$ and the $\Delta^{(3,-)}_d(n)$ decreases rapidly as $n$ gets large.

  Note that for $d$ at least 10,
  it seems as if $\Delta^{(3,-)}_d(n) \geq 0$ and the $\Delta^{(3,-)}_d(n)$ increases as $n$ gets large.
  
 ## Acknowledgements
  
  We would like to thank Professsor Robert J. Lemke Oliver for providing original C++ code calculating the $q_d^{(1)}(m)$ and $ Q_{d}^{(1)}(m)$ values, which we modified to calculate $q_d^{(1)}(m)$ and $ Q_{d-3}^{(1, -)}(m)$.
