# Riviera HPC Documentation
This repository contains assorted documentation for the Riviera HPC system at Colorado State University. 

## Table of Contents

- [sBatch Documentation](https://github.com/Ioscipescu/HPC_Docs/blob/main/SBATCH_Documentation/main.pdf)
- [Setting up LaTeX](#setting-up-latex)
- [Editing or Adding to Documentation](#editing-or-adding-to-documentation)

## Setting up LaTeX

1. Install VSCode or any other LaTeX editor of your choice. These installation instructions will focus on setting up VSCode.
2. [Install LaTeX for your system ](https://https://www.latex-project.org/get/) making sure that your LaTeX distribution contains LuaLaTeX.
3. If using VSCode install the [LaTeX Workshop](https://marketplace.visualstudio.com/items?itemName=James-Yu.latex-workshop), [LaTeX Utilities](https://marketplace.visualstudio.com/items?itemName=tecosaur.latex-utilities), and [LaTeX language support](https://marketplace.visualstudio.com/items?itemName=torn4dom4n.latex-support) extensions.
4. Update your settings.json to include the necessary tools for building latex, here is an example settings.json for use with LaTeX:

``` json
{
  "editor.formatOnSave": false,
  "latex-workshop.formatting.latex":"latexindent",
  "latex-workshop.view.pdf.viewer": "tab",
  "latex-workshop.latex.autoBuild.run": "onSave",
  "latex-workshop.latex.tools": [
    {
      "name": "lualatex",
      "command": "lualatex",
      "args": [
        "-synctex=1",
        "-interaction=nonstopmode",
        "-file-line-error",
        "%DOC%"
      ]
    },
    {
      "name": "biber",
      "command": "biber",
      "args": [
          "%DOCFILE%"
      ],
      "env": {}
    }
  ],
  "latex-workshop.latex.recipes": [
    {
      "name": "lualatex",
      "tools": ["lualatex"]
    },
    {
      "name": "lualatex -> biber -> lualatex",
      "tools": ["lualatex", "biber", "lualatex", "lualatex"]
    },
  ],
  "[latex]": {
    "editor.suggestSelection": "recentlyUsedByPrefix",
    "editor.wordWrap": "on"
  }
}
```

## Editing or Adding to Documentation

### File Structure

``` txt
HPC_Latex_Documentation/
├── header.tex
├── Onboard_QuickStart
│   ├── main.pdf
│   └── main.tex
├── README.md
└── SBATCH_Documentation
    ├── main.pdf
    ├── main.tex
    ├── source_code
    │   ├── job_arrays
    │   │   └── array-example.sh
    │   ├── MPI
    │   │   ├── mpi-binary-search.c
    │   │   └── mpi-bin.sh
    │   ├── OpenMP
    │   │   ├── openmp-binary-search.c
    │   │   └── openmp-bin.sh
    │   └── PyTorch
    │       ├── cuda
    │       │   ├── pytorch-cuda.py
    │       │   └── pytorch-cuda.sh
    │       ├── nlp
    │       │   ├── nlp.py
    │       │   └── pytorch-nlp.sh
    │       └── stream
    │           ├── pytorch-stream.py
    │           └── pytorch-stream.sh
    └── use_cases
        ├── cuda.tex
        ├── job_arrays.tex
        ├── MPI.tex
        ├── OpenMP.tex
        └── pytorch.tex

```

- header.tex contains all of the package declarations needed for the documentation and also sets up a couple of environments and package specific settings.
- HPC_Latex_Documentation contains all of the source code specific to the SBATCH documentation.
  - main.pdf is the output pdf from the LaTeX code.
  - main.tex collects all sub-files to be able to create main.pdf.
  - source_code contains all code examples for SBATCH tasks, both the SBATCH .sh files and when needed the corresponding program files (such as C programs to show how MPI and OpenMP work).
  - use_cases contains tex files for every specific use case (job_arrays, MPI, OpenMP, etc) that is then imported into main.tex. Splitting files up like this will help manage merge conflicts if multiple people are attempting to edit documentation.
- Onboarding_QuickStart contains all sourcecode for the Onboarding documentation.

### Best Practices

We use the minted package to input source code into our documentation. All source code for a specific use case should be contained in its own subfolder within the source_code directory. After any change is made to a source code file the file will need to be saved and the main pdf document compiled again to see the change reflected in it.
