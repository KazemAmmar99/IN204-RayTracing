# Project Analysis - [RayTracing](./projet_informatique_-_oort.pdf)
Ce document présente les idées que nous avons eu le premier jour du projet. Il présente ensuite l'avancement du projet, une comparaison avec ce que nous attendions et ce que nous aurions pu espérer améliorer si nous avions eu plus de temps.
Pendant notre phase d'analyse du sujet nous avons réfléchi aux points suivants :
* Analyse d'usage (Contexte, fonctions souhaitées par l'utilisateur, interactions, fonctions de base)
* Analyse fonctionnelle (Blocs fonctionnels, interactions avec l'environnement)
* Architecture gros grains (Classes principales, modularité/extensibilité, interactions)

## Analyse d'usage
### Contexte 
Notre projet consiste à :
- Fournir une bibliothèque d’objets permettant de décrire les éléments composant une scène
- Fournir une bibliothèque d’objets permettant d’implanter différents moteurs implantant le rendu d’image par lancer de rayons

### Fonctions souhaitées
Il faudrait prévoir une interface pour que l'utilisateur du logiciel puisse choisir les éléments qu'il souhaite rajouter sur la scène.
L'idéal serait que le logiciel tourne sur le CPU ou le GPU de l'utilisateur s'il en possède un.

### Interactions 
On utilisera le format de fichiers OBJ pour les éléments composant la scène. Les scènes seront décrites par le biais du langage XML (langage de description de scènes) qui sera convertit vers les objets définis dans la bibliothèque. 
Pour gagner en efficacité et rapidité on pourra utiliser les connaissances acquises en cours de Programmation Parallèle (MPI & OpenMP)

### Fonctions de test de base 
- une fonction vérifiant que le format des fichiers utilisés est supporté
- une fonction testant le bon transfert des données entre CPU et GPU
- une fonction de test pour vérifier que le 'hit' fonctionne

## Analyse fonctionnelle 
### Blocs fonctionnels 
Les blocs fonctionnels de notre programmes seront, au minimum :
- un bloc pour l'interface utilisateur
- un bloc de transmission des données entre la machine et le logiciel
- un bloc pour la réalisation de la scène (avec plusieurs objets à différents endroits)
- un bloc de calcul du rendu des rayons pour un objet et une ou plusieurs sources
- un bloc traitant l'affichage du résultat

### Interactions 
Le bloc de transmission des données utilisateurs devra transmettre ses résultats à la machine pour démarrer la réalisation de la scène puis le calcul des rayons. Ce résultat sera à nouveau transmis au logiciel pour le rendu.

## Architecture gros grains du logiciel
### Classes principales
- Sphere
- Plan
- Rectangle
- Triangle
- Surface
- Point
- Rayon

### Modularité/Extensibilité
Il faudra que l'utilisation de sous-classes ne perturbe pas le fonctionnement général du logiciel

### Interactions
Lorsqu'une source de lumière arrive sur un object il faut déterminer le rendu.




## Retour sur le projet

### Ce que nous avons produit
Nous avons produit un programme de calcul de rayons fonctionnel qui permet de réaliser une scène constituée d'objets simples (sphères et plans), de calculer le rendu des rayons pour une source lumineuse et d'afficher ce rendu. Nous avons essayé de programmer un bloc permettant l'utilisation d'un format XML pour le fichier d'entrée, permettant de réaliser des scènes complexes plus simplement. Nous étions en cours de réflexion pour cela mais n'avons pas encore abouti à un code fonctionnel. 
Le calcul des rayons prend en compte la couleur des différents objets, leur brillance et leur reflexivité. Pour le moment nous nous sommes restreints à des plans et sphères mais nous avons tout de même anticipé l'ajout d'objets de formes différentes. Le calcul de rendu des rayons, permettant d'afficher les ombres et les objets réfléchissants (miroirs), se fait récursivement.

### Ce que nous aurions aimé ajouter
Nous aurions aimé pouvoir avoir plus de formes disponibles pour la scène, nous n'avons juste pas eu le temps d'implémenter la méthode hit() pour chacune de ces formes et donc le programme n'était pas encore fonctionnel pour d'autres formes que des plans et des sphères.
Nous aurions aussi souhaiter avoir plus de textures disponibles.
D'autre part, nous aurions aimé paralléliser notre programme (à l'aide de MPI ou OpenMP), cependant ce n'est pas tellement nécessaire finalement étant donné que notre programme ne nécessite pas tant de temps de calcul que ça finalement.
Enfin, nous aurions aimé pouvoir calculer un rendu avec plusieurs sources lumineuses.


### Ce qu'il serait bien de rajouter mais c'est plus complexe
On aurait aimé pouvoir permettre d'implémenter des formes plus complexes (compositions de formes etc...) pour pouvoir créer des scènes plus réalistes.
A terme, l'idéal aurait été d'implémenter une interface utilisateur pour que la mise en place de la scène se fasse facilement et de façon ergonomique.
