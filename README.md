
<!--[output-onlinetools (1)](https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/e469ac01-1a3a-497b-af55-5a4872d8040a)-->
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/e469ac01-1a3a-497b-af55-5a4872d8040a" alt="Lion Logo" width="95%" height="100%">
</p>
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project"> ➤ About The Project</a></li>
    <li><a href="#overview"> ➤ Overview</a></li>
    <li><a href="#getting-started"> ➤ Getting Started</a></li>
    <li><a href="#sequence-alignment"> ➤ Sequence Alignment </a></li>
    <li><a href="#needle"> ➤ Needleman-Wunsch Algorithm </a></li>
    <li><a href="#distance"> ➤ Distance Matrix </a></li>
    <li><a href="#upgma"> ➤ Unweighted Pairwise Global Sequence Alignment (UPGMA) </a></li>
    <li><a href="#neighbor-joining"> ➤ Neighbour Joining (NJ) </a></li>
     <li><a href="#references"> ➤ References</a></li>
    <li><a href="#credits"> ➤ Credits</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
<h2 id="about-the-project"> :pencil: About The Project</h2>

<p align="justify"> 
This project focuses on the study of three extinct feline species that once inhabited the American continent: Smilodon (saber-toothed tiger), Homotherium (scimitar-toothed tiger), and Miracinonyx trumani (American cheetah). These species became extinct approximately 13,000 years ago, at the end of the last glacial period. Ancient DNA sequences of the cytochrome b protein from these species have been successfully sequenced, enabling the investigation of their evolutionary relationships with contemporary feline species.
</p>

<!-- OVERVIEW -->
<h2 id="overview"> :cloud: Overview</h2>

<p align="justify"> 
The objective is to reconstruct the phylogenetic tree of these feline species using a method based on calculating evolutionary distances between DNA sequences. The dataset includes sequences from domestic cats, lions, leopards, tigers, pumas, cheetahs, and wild cats from Africa, China, and Europe. Additionally, sequences from non-feline species are present in the dataset.
</p>

<!-- GETTING STARTED -->
<h2 id="getting-started"> :rocket: Getting Started</h2>

<!-- <p>Clone the repository </p>
<pre><code>git clone https://github.com/Jaffar-Hussein/PhyloExplora.git</code></pre>

<pre>
  <code>git clone https://github.com/Jaffar-Hussein/PhyloExplora.git</code>
  <code>cd PhyloExplora</code>
  <code>make</code>
  <code>./phylo all</code>
  <code>./phylo {name of section e.g nj}</code>
</pre>
-->
```bash
# Clone the repository to your local machine
git clone https://github.com/Jaffar-Hussein/PhyloExplora.git

# Change directory to the cloned repository
cd PhyloExplora

# Compile the project using the makefile
make

# Run all sections of the project
./phylo all

# Run a specific section of the project (replace {section name} with the name of the section, e.g., nj)
#./phylo {section name}
```
Here's a preview of what you can expect:
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/d4d7f14b-bd07-4d3c-80eb-c51febf55291)" alt="Getting started" height="80%" width="80%">
</p>

<!-- SEQUENCE ALIGNMENT -->
<h2 id="sequence-alignment"> :dna: Sequence Alignment </h2>

<p align="justify"> 
The method you will use to calculate the phylogenetic tree requires calculating the evolutionary distance between the sequences. Before you can calculate them, you first need to align the sequences considering three types of mutations:

<ul>
<li>Substitutions (one nucleotide is replaced by another)</li>
<li>Insertions</li>
<li>Deletions</li>
</ul>

For example, the sequences "ACTCCTGA" and "ATCTCGTGA" have several possible alignments (there are others):

<pre>
-ACTCCTGA
ATCTCGTGA

A-CTCCTGA
ATCTCGTGA

AC-TCCTGA
ATCTCGTGA
</pre>

It is also possible that a deletion is not a mutation, but actually due to poor sequencing or DNA degradation as is often the case for sequencing DNA from extinct species.

The "-" denotes a gap, which is a "blank" in the alignment that was caused by an insertion or a deletion. These two types of mutations are grouped under the term indel.

These alignments correspond to a multitude of different phylogenetic histories. To select the best alignment, we therefore need to introduce the maximum parsimony hypothesis, which favors the phylogenetic history that involves the fewest assumptions and therefore, the fewest evolutionary changes. For example, among the three alignments above, we will prefer alignment 2 because it corresponds to the scenario with the fewest mutations:
<ul>
<li>Alignment 1 implies at least 1 indel and 2 substitutions</li>
<li>Alignment 2 implies at least 1 indel and 1 substitution</li>
</ul>
</p>

<!-- NEEDLEMAN-WUNSCH ALGORITHM -->
<h2 id="needle"> :dna: Needleman-Wunsch Algorithm</h2>

<p align="justify"> 
The Needleman-Wunsch algorithm is a dynamic programming algorithm used for sequence alignment in bioinformatics. It finds the optimal global alignment between two sequences. The algorithm operates in three main steps:

1. Initialization of a score matrix (M) and a traceback matrix (T) of size (n+1) x (m+1), where n and m are the lengths of the two sequences to be aligned.

2. Filling of the matrices M and T using the following formula:
   
$$
M_{i,j} = \max \left( M_{i-1,j-1} + s(A_i, B_j), M_{i, j-1} + s(A_i, \text{gap}), M_{i-1, j} + s(B_j, \text{gap}) \right)
$$

  where s is a function that calculates the similarity score between two nucleotides. The T matrix is filled with directions ('d' for diagonal, 'l' for left, 'u' for up) based on which value was used to calculate M[i,j].

3. Traceback from the final element of the T matrix, T[n,m], to the start ('o'), following the directions. This gives the optimal global alignment between the two sequences.

The final element of the M matrix, M[n,m], gives the score of the alignment.
</p>

<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/cd4943f7-1b79-426c-a5a7-4184285d8549" alt="Matrix" height="80%" width="80%">
</p>


<!-- Distance Matrix -->
<h2 id="distance"> :chart_with_upwards_trend: Distance Matrix</h2>

<p align="justify"> 
To construct phylogenetic trees, we need a set of aligned sequences (multiple alignment). Therefore, we cannot use the Needleman-Wunsch algorithm as it only allows for pairwise alignment (between two sequences). As a result, the "cat_dna_aligne.fasta" file contains the sequences already aligned.

In the case of very close sequences (which is the case here), we estimate that the real evolutionary distance between the sequences is close to the `p-distance`, which is simply the number of substitutions in the alignment over the total number of nucleotides. To simplify, we ignore positions aligned to gaps.

We then apply the Jukes-Cantor correction to take into account the phenomenon of saturation (the same site can mutate several times over time). Its formula is:

$$
d = - \frac{3}{4} \ln\left(1 - \frac{4}{3} \times p\text{-distance}\right)
$$

where `d` is the Jukes-Cantor distance and `p-distance` is the proportion of differing nucleotide sites.
</p>

<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/0bc048c4-c540-4ad7-9466-e32e9946a50d" alt="Alignment" height="80%" width="80%">
</p>

<!-- UPGMA -->
<h2 id="upgma"> :dna: Unweighted Pair Group Method with Arithmetic Mean (UPGMA) </h2>

<p align="justify"> 
UPGMA is a simple hierarchical clustering method used to construct phylogenetic trees. The method operates on a distance matrix, which provides the distances between each pair of sequences. The steps of the UPGMA method are as follows:

1. Start with a forest of trees, each consisting of a single leaf for each sequence.
2. Find the minimum distance in the matrix, join the two corresponding nodes into a single node, and update the distance matrix.
3. Repeat step 2 until only a single node remains.

The distance between two clusters is calculated as the average distance between all pairs of sequences in the two clusters. This is where the "unweighted" and "arithmetic mean" parts of the name come from.

The result of the UPGMA method is a rooted tree, which means that it assumes a constant rate of evolution (molecular clock hypothesis).

Here's an example of how the UPGMA method works:

<pre>
Initial distance matrix:

  A   B   C   D
A  -   5   4   7
B  5   -   7   10
C  4   7   -   7
D  7   10  7   -

Step 1: Join A and C (smallest distance), update distance matrix:

  AC  B   D
AC  -  6   5.5
B   6  -   10
D   5.5 10 -

Step 2: Join AC and D, update distance matrix:

  ACD B
ACD  -  8
B    8  -

Step 3: Join ACD and B:

  ACD-B
ACD-B  -
</pre>

The final tree is (((A,C),D),B).
</p>
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/1538cea4-cd67-4a10-825f-998dd37f76eb" alt="UPGMA" height="80%" width="80%">
</p>



<!-- NEIGHBOR JOINING -->
<h2 id="neighbor-joining"> :dna: Neighbor Joining (NJ) </h2>

<p align="justify"> 
Neighbor Joining is another algorithm for calculating a phylogenetic tree from a distance matrix. It has the advantage of making fewer assumptions than UPGMA on the data (they are not necessarily ultrametric) and therefore gives better trees in almost all cases.

The steps of the Neighbor Joining method are as follows:

1. For each pair of taxa, calculate the sum of the distances to all other taxa.
2. Calculate the matrix of "neighbor-joining distances" based on the original distances and the sums calculated in step 1.
3. Find the pair of taxa with the smallest neighbor-joining distance and join them into a single node, updating the distance matrix.
4. Repeat steps 1-3 until only a single node remains.

Note: To simplify life when building our tree, we ignore the distance between the branches. We are only interested in the links of kinship.

You can find an example of applying this algorithm [here](http://www.evolution-textbook.org/content/free/tables/Ch_27/T11_EVOW_Ch27.pdf).
</p>
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/64b6a124-0ddc-4997-93da-061a85588be7" alt="NJ" height="80%" width="80%">
</p>



<!-- REFERENCES -->
<h2 id="references"> :books: References</h2>

<p align="justify"> 
The following resources were used in the creation of this project:

1. **Project Description by [George Marchment](https://github.com/George-Marchment)**: The project description provided by the professor heavily influenced the structure and content of this README. The project description can be found [here](consignes.pdf).
2. **Wikipedia**: For the description of the algorithm and examples

3. **Youtube**: For learning more about binary trees and Linked Lists.
</p>

4. **AI**: For advice on creation of ASCII art in C .

5. **README Inspiration**: Github Awesome README's [awesome readme](https://github.com/matiassingers/awesome-readme)
<!-- CREDITS -->
<h2 id="credits"> :trophy: Credits</h2>

<p align="justify"> 
This project would not have been possible without the contributions of the following individuals:</p>

 **[George Marchment](https://github.com/George-Marchment)** - For providing the project and guidance in its development.

 Made with :heart: by : 

- **[Leo Jourdain](https://github.com/LeoooJR)**
- **[Mapathe Faye](https://github.com/Mapathefaye)**
- **[Jaffar Hussein](https://github.com/Jaffar-Hussein)**

And lots of :coffee:!
