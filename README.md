# Compression & Decompression

Pour compiler la dernière version du projet, il suffit de lancer la commande suivante :

```bash
make 
```

cela va générer un exécutable nommé `main` dans le répertoire courant. 
Le programme supporte les options suivantes :

- `-c` : pour compresser des fichiers et/ou des répertoires
- `-d` : pour décompresser une archive
- `-m` : pour ouvrir l'inteface graphique
- `-h` : pour afficher l'aide
- `-g` : pour lancer le programme en mode debug

Exemple d'utilisation :

```bash
make clean && make && ./main -c ./archive.bin ./file1.txt ./dir1
make clean && make && ./main -d ./archive.bin ./output
make clean && make && ./main -m
```

Les executables des versions précédentes peuvent être généré en compilan le projet avec la commande 
```make v%version%``` avec **%version%** la version du projet (de 1 à 5).

Par exemple pour compiler la version 1 du projet, il suffit de lancer la commande suivante :

```bash
make v1
```
l'exécutable généré sera nommé `main_v1`.
```make v2``` pour la version 2, et ainsi de suite.
Pour générer tout les exécutables des versions précédentes, il suffit de lancer la commande suivante :

```bash
make v-all
```

Pour supprimer tout les exécutables générés, il suffit de lancer la commande suivante :

```bash
make clean
```

L'option `-g` permet de lancer le programme en mode debug, cela va afficher des informations supplémentaires sur le déroulement du programme, 
tel que la table de fréquence des caractères, l'aplphabet utilisé avec les codes associés, et les informations sur les fichiers compressés.

# Génération des fichiers de test

Pour générer les fichiers de test, nécessaires pour l'étude de taux de compression, vous pouvez lancer la commande suivante :

```bash
make generate-test
```

Cela va générer un répertoire `raw` ainsi que des sous répertoires contenant les fichiers de test.
Vous pourrez ensuite lancé la compression sur les fichiers de tests générer en utilisant la commande suivante :

```bash
make run-all-test
```
Cette commande va compresser tout les fichiers de test et générer les archive, en re-créant l'architecture du répertoire `raw` dans le répertoire `compressed`.

Il est possible de compresser les fichiers d'un dossier spécifique, pour cela les commande suivante peuvent être utilisé :

```bash
make run-test-linear
make run-test-uniform
make run-test-normal
make run-test-zipf
make run-test-random
```