# PROJET BASE ALGORITHMIQUE

## Description
Le projet vise a decouper une image en plusieurs segments. Pour cela, on divise l'image en differents blocks, puis on regroupe ces blocks qui sont semblables.

## Visuals

On peut passer de cette image : 

![Image non modifiée](https://github.com/Cleanz7/Traitement-d-image/blob/main/IMAGES/fleurs.png)

à ces images en fonction du paramètres :

![](https://github.com/Cleanz7/Traitement-d-image/blob/main/resultats/fleurs1.png)

![](https://github.com/Cleanz7/Traitement-d-image/blob/main/resultats/fleurs2.png)

![](https://github.com/Cleanz7/Traitement-d-image/blob/main/resultats/fleurs3.png)

## Support
Clément JANTET <clement.jantet@ecole.ensicaen.fr> et Achraf ABOULAKJAM <achraf.aboulakjam@ecole.ensicaen.fr>

## Make Commands 
Pour produire l'exécutable, on se place dans le dossier racine et on exécute la commande suivante :

```sh
make
```

Pour générer la documentation doxygen :

```sh
make doc
```

Pour supprimer les fichiers objets il vous suffit de faire la commande :

```sh
make clean
```

Enfin, pour supprimer le fichier exécutable vous devez utiliser la commande :

```sh
make distclean
```

