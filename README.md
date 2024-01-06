
<!--[output-onlinetools (1)](https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/e469ac01-1a3a-497b-af55-5a4872d8040a)-->
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/e469ac01-1a3a-497b-af55-5a4872d8040a" alt="Pacman Logo" width="95%" height="100%">
</p>
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project"> ➤ About The Project</a></li>
    <li><a href="#overview"> ➤ Overview</a></li>
    <li><a href="#project-files-description"> ➤ Project Files Description</a></li>
    <li><a href="#getting-started"> ➤ Getting Started</a></li>
    <li><a href="#sequence-alignment"> ➤ Sequence Alignment </a></li>
    <li><a href="#scenario2"> ➤ Needleman-Wunsch Algorithm </a></li>
    <li><a href="#scenario3"> ➤ Distance Matrix </a></li>
    <li><a href="#upgma"> ➤ Unweighted Pairwise Global Sequence Alignment (UPGMA) </a></li>
    <li><a href="#scenario5"> ➤ Neighbour Joining (NJ) </a></li>
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

<p>Clone the repository </p>
<pre><code>git clone https://github.com/Jaffar-Hussein/PhyloExplora.git</code></pre>
<p align="center"> 
  <img src="https://github.com/Jaffar-Hussein/PhyloExplora/assets/57854451/7f91ebee-b161-4645-a9e8-713cc9c42f71" alt="Animated gif pacman game" height="80%" width="80%">
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

The "-" denotes a gap, which is a "hole" in the alignment that was caused by an insertion or a deletion. These two types of mutations are grouped under the term indel.

These alignments correspond to a multitude of different phylogenetic histories. To select the best alignment, we therefore need to introduce the maximum parsimony hypothesis, which favors the phylogenetic history that involves the fewest assumptions and therefore, the fewest evolutionary changes. For example, among the three alignments above, we will prefer alignment 2 because it corresponds to the scenario with the fewest mutations:
<ul>
<li>Alignment 1 implies at least 1 indel and 2 substitutions</li>
<li>Alignment 2 implies at least 1 indel and 1 substitution</li>
</ul>
</p>

<!-- SCENARIO 2 -->
<h2 id="scenario2"> :microscope: Needleman Wunsch Algorithm</h2>

<p align="justify"> 
Describe the second scenario here. Explain what it does and how to use it.
</p>

<!-- SCENARIO 3 -->
<h2 id="scenario3"> :chart_with_upwards_trend: Distance Matrix</h2>

<p align="justify"> 
To construct phylogenetic trees, we need a set of aligned sequences (multiple alignment). Therefore, we cannot use the Needleman-Wunsch algorithm as it only allows for pairwise alignment (between two sequences). As a result, the "cat_dna_aligne.fasta" file contains the sequences already aligned.

In the case of very close sequences (which is the case here), we estimate that the real evolutionary distance between the sequences is close to the `p-distance`, which is simply the number of substitutions in the alignment over the total number of nucleotides. To simplify, we ignore positions aligned to gaps.

We then apply the Jukes-Cantor correction to take into account the phenomenon of saturation (the same site can mutate several times over time). Its formula is:

$$
d = - \frac{3}{4} \ln\left(1 - \frac{4}{3} \times p\text{-distance}\right)
$$

where `d` is the Jukes-Cantor distance and `p-distance` is the proportion of differing nucleotide sites.
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


<!-- SCENARIO 5 -->
<h2 id="scenario5"> :handshake: Neighbour Joining (NJ)</h2>

<p align="justify"> 
Describe the fifth scenario here. Explain what it does and how to use it.
</p>