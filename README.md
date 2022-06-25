# GeneralizationKangPark

## Important: See the Readme.pdf file! It is much better formatted!

This repository contains code and data used to elucidate potential next steps to prove Conjecture 1.3 ( $\Delta^{(3,-)}_d(n) \geq 1$).

In other words, this repository contains the code and data referred to in Section 7 of the Inagaki and Tamura 2022 paper.

\subsection{How to Use the C++ code (.cc file) in Linux Terminal}

Before you do anything, make sure your pwd is the same directory as is the coefficients\_d\-3\_oneDash.cc\newline

First, compile the C++ file. Type without quotes :\newline"g++ ./coefficients\_d\-3\_oneDash.cc \-o coefficients\_d2."
\newline

Then Type without quotes: \newline "./coefficients\_d2 NUM\_TERMS d output\_file \textless d \textgreater" \newline where d is a positive integer parameter and NUM\_TERMS is the positive integer number of terms you want to compute $Q_{d-3}^{(1, -)}(n)$, $q_{d}^{(1)}(n)$ and $ \Delta^{(3,-)}_d(n)$

To stay organized, let \textless d 
\textgreater be the value of d you inputted earlier in the line.

\section{The output\_file}
In this repository, given a positive integer d, output\_file\textless d \textgreater has the values of 
  $Q_{d-3}^{(1, -)}(n)$,
  $q^{(1)}_{d}(n)$,
  and 
  $\Delta^{(3,-)}_{d}(n)$
  for $n$ from 1 to 100,000 inclusive. Open this through your text editor.
  
  Note from the output\_file 's  for d
 in between 1 and 9, it seems as if 
  $\Delta^{(3,-)}_{d}(n) < 0$ and the $$\Delta^{(3,-)}_{d}(n)$$ decreases rapidly as $n$ gets large.

  Note that for $d$ at least 10,
  it seems as if $\Delta^{(3,-)}_{d}(n)\geq 0$ and the $\Delta^{(3,-)}_{d}(n)$ increases as $n$ gets large.
