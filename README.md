
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
    <li><a href="#scenario1"> ➤ Sequence Alignment </a></li>
    <li><a href="#scenario2"> ➤ Needleman Wusnshc Algorithyjm </a></li>
    <li><a href="#scenario3"> ➤ Distance Matrix </a></li>
    <li><a href="#scenario4"> ➤ Unweighted Pairwise Global Sequence Alignment(UPGMA) </a></li>
    <li><a href="#scenario5"> ➤ Neigbour Joining (NJ) </a></li>
  
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





<!-- SCENARIO 1 -->
<h2 id="scenario1"> :dna: Sequence Alignment</h2>

<p align="justify"> 
Describe the first scenario here. Explain what it does and how to use it.
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

<!-- SCENARIO 4 -->
<h2 id="scenario4"> :link: Unweighted Pairwise Global Sequence Alignment (UPGMA)</h2>

<p align="justify"> 
Describe the fourth scenario here. Explain what it does and how to use it.
</p>

<!-- SCENARIO 5 -->
<h2 id="scenario5"> :handshake: Neighbour Joining (NJ)</h2>

<p align="justify"> 
Describe the fifth scenario here. Explain what it does and how to use it.
</p>