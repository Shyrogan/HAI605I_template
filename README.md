# template (HAI605I)

## Prérequis

**MacOS**
- `imagemagick` (`brew install imagemagick`)
- `mactex` (`brew install mactex`)

**Linux (Pas testé)**
- `yay -S latex-make`
- `yay -S imagemagick-full`

## Structure

`src` contient des fichiers `.cpp` qui seront tous compilés dans des programmes à part.  
`bin` contient les executables une fois que les fichiers `.cpp` sont compilés.  
`output` contient les images (au format .pgm ou .ppm) qui seront converties au format `.png` lorsque la commande `make est executée`.  
`report` contient un fichier `.tex` qui sera compilé en `.pdf` lorsque la commande `make` est executée.  
