ALGORITHMIQUE AVANCEE - PROJET 1 - GRAPHES DE CHEVAUCHEMENTS

		README

****************************************************************************************************************************************

I - FONCTIONNEMENT DU PROGRAMME

    Ligne de commande : ./main fichierDeSequences
                   ex : ./main sequences.txt

Structures composant le graphe de chevauchement :

    Type GRAPHE : contiend le nombre de sommets (type int) et un tableau de sommets (type Sommet).

    Type Sommet : contiend un fragment d'ADN (type char*) et une liste chaînée de successeurs (type ELEMENT, e.g LISTE-arc)

    Type ELEMENT (e.g LISTE-arc) : représente un arc d'un sommet vers un autre. Contiend le poids de l'arc (int), le numéro du sommet 
    de destination (int)
    
Structure utilisée dans la lecture des fichiers de séquences:

    Type fragment (e.g LISTE-frag) : une liste chaînée de chaînes de caractères ('char* frag').			

		A - FONCTION LISTE_frag fsd(LISTE_frag S);

Supprime les fragments de S dont la chaine de caractère est facteur (e.g. contenus dans) de la chaine d'un autre fragment.
	- Création de deux listes temporaires, l'une égale à S, temp1, et l'autre à S -> suivant, temp2
	- On itère sur temp1 jusqu'à son avant-dernier élément
	- A chaque itération de temp1, on itère sur temp2 jusqu'à son dernier élément
	- On procède aux comparaisons des fragments avec strstr
	- Si l'un des fragments est contenu dans l'autre, on le supprime avec la fonction supprimer(LISTE_frag S, char* fragment)
	- Les itérations continuent sur les listes temporaires, sans être affectées par les suppressions.

		B - FONCTION int lplc(char *x, char *y);

Retourne la longueur du plus long suffixe de la chaine de caractères x qui est le plus long préfixe de la chaine y.
	- Itère depuis sur la chainex, de la fin au début	
	- A chaque itération, la fonction char* sousChaine(char* chaine, int start, int end) extrait le suffixe de x et le préfixe de y,
	qui sont de même longueur.
	- Préfixe et suffixe sont comparés grâce à strcmp (de string.h).
	- Si strcmp est égale à 0, suffixe et préfixe sont identiques: la valeur de retour est égale à strlen(suffixe) (ou strlen(préfixe)

		C- FONCTION LISTE_frag initListeFragments(LISTE_frag S, char *nomf);

Un appel en boucle à la fonction fgets lit chaque ligne et l'insère dans la LISTE_frag S. Cela nécessite quelques astuces:
	- La ligne lue est écrite dans un buffer, une chaine de caractère de longueur 100 (fscanf requiert une taille maximum en paramètre)	
	- La sequence lue est recopiée dans une chaine de caractères déclarée avec une allocation mémoire de la longueur du buffer
	- Finalement, la séquence recopiée est ajoutée dans la liste des fragments, cette liste étant retournée à la fin de la fonction

		D - FONCTION void construitGrapheChevauchement(GRAPHE G, LISTE_frag S);

Construit le graphe de chevauchement des fragments contenus dans le fichier de départ.
	- Initialise G : son nombre de sommets et son tableau de sommets ( de taille nbSommets)
	- On itère sur le tableau de sommets de G pour attribuer chaque fragment issu de initListeFragments à chaque sommet.
	La Liste de successeurs de chaque sommet est mise à NULL.
	- Ajout des arcs et des successeurs de chaque sommet à l'aide de deux boucles imbriquées. Si la valeur renvoyée par lplc est 
	différente de 0, un arc est ajouté du sommet source vers le sommet cible. lplc est utilisé deux fois : 
	comparaison suffixe(chaine1) / prefixe(chaine2) et comparaison suffixe(chaine2)/prefixe(chaine1)

		E - FONCTION void parcoursEnProfondeur(GRAPHE G);

Affiche le fragment de chaque sommet selon un parcours en profondeur, donc en explorant jusqu'au bout chaque chemin de successeurs. Un
tableau d'entiers de longueur NbSommets de G permet de marquer les sommets qui ont déjà été visités (sans quoi la fonction tournerait
indéfiniment). Pour chaque sommet non visité, la fonction récursive visiteEnProfondeur est appellée.

		F - FONCTION void visiteEnProfondeur(GRAPHE g, int s, int* marque);

La fonction est appelée dans parcoursEnProfondeur et prend en paramètre le tableau de marques qui y est créé. 
	- Pour chaque sommet, le fragment qui y est attaché est affiché
	- Le numéro du sommet de destination est récupéré
	- Pour chaque successeur (chaque sommet de destination) non marqué du sommet, la fonction est appelée récursivement
	- La fonction travaille sur des copies des listes de successeurs, pour ne pas modifier le pointeur sur les listes du graphe.

****************************************************************************************************************************************

II - DIFFICULTES RENCONTREES

	- Fonction lplc : j'ai eu du mal à comprendre comment faire car au départ je n'imaginais pas devoir écrire une fonction 
	supplémentaire.	

	- Il m'a fallu un peu de temps pour comprendre qu'il fallait utiliser un buffer avec une taille définie dans la fonction
	initListeFragments, pour ensuite le copier dans une chaine allouée avec un malloc avant de l'insérer dans la liste de fragments.

	- La fonction fsd m'a bloqué pendant plus d'une semaine (et même maintenant, elle ne fonctionne pas dans certains cas particuliers
	*voire dans la partie III *) : j'ai mis beaucoup de temps à trouver comment supprimer des éléments de la liste de fragments en même 
	temps qu'on itère dessus. Une fois la fonction écrite, un bug dû à la fonction initListeFragments m'a longtemps fait croire que fsd 
	ne marchait dans aucun cas (j'ai d'abord utilisé fgets au lieu de fscanf).	

	- Le type void de certaines fonctions de l'énoncé : j'ai changé le type de initListeFragment et de fsd, autrement je n'y arrivais 
	pas.

****************************************************************************************************************************************

III - AMELIORATIONS ENVISAGEABLES

	- Faire en sorte que la fonction sousChaine gère les cas d'erreurs (cela ne peut pas arriver lorsqu'elle est utlisée dans lplc, mais
	c'est par souci de rigueur). L'implémentation initiale d ela fonction était prévue pour, mais cela ne marchait pas.
	
	- Ré-implémenter initListeFragments et fsd avec un type de retour void, comme intialement dans l'énoncé.

	- La fonction fsd ne marche pas un cas particulier, lorsque les fragments ne sont constitués que d'une seule lettre :	
	AAA
	AAAAAA
	AAAA
	AA
	A
	Il reste deux fragments au lieu d'un seul (le plus long, plus un autre qui devrait pourtant être supprimé). Le problème est au niveau
	suivant :
		- Les pointeurs utilisés pour itérer sont rémis en tête de listes après la suppression d'un fragment.
		- Ensuite, ils sont avancés d'un cran en fin de boucle while : un fragment est sauté. C'est difficile à détecter et à corriger
		car dans les autres fichiers ça ne donnait pas de mauvais résultats. La version corrigée pour le fichier décrit ci dessus
		conduit à une erreur de segmentation lors des tests avec les autres ficheirs ...
	
	Cette même fonction est perfectible : à la suite d'une erreur de segmentation que je n'arrivais pas à résoudre, je traite séparément
	les cas où la liste ne contiend que deux fragments, dont un à supprimer.

****************************************************************************************************************************************

IV - LISTE DES "PETITES" FONCTIONS NECESSAIRES AUX FONCTIONS PRINCIPALES

	Il a fallu implémenter (ou copier depuis les autres projets) des fontions supplémentaires  :	

	- int getNbSommets(GRAPHE g);
			Retourne le nombre de sommets d'un graphe G.

	- int estVideGraphe(GRAPHE g);
			Teste si un graphe est vide.

	- LISTE_frag supprimer(LISTE_frag S, char* frag);
			Supprime un élément d'une liste chainée.

	- char* sousChaine(char* chaine, int start, int end);
			Retourne la sous-chaine de start à end d'une chaîne de caractères.

	- LISTE_frag getSuivant(LISTE_frag liste);
			Retourne l'élément suivant de la liste chaînée de fragments passée en paramètre.

	- LISTE_arc getSuivantArc(LISTE_arc liste);
			Retourne l'élément suivant de la liste chaînée d'arcs passée en paramètre.

	- LISTE_frag inserer(LISTE_frag l, char* k);
			Insère un élément en tête d'une liste chaînée de fragments.

	- void printFrags(LISTE_frag S);
			Affiche une lsite chaînée de fragments.

	- void printArc(LISTE_arc A);
			Affiche une liste chaînée d'arcs.

	- int lenListe(LISTE_frag S);
			Retourne la longueur d'une liste chaînée de fragments.

	- LISTE_frag inserer(LISTE_frag S, char* k);
			Insère un fragment en tête d'une liste chaînée de fragments.

	- LISTE_arc insererArc(LISTE_arc A, int pds, int dest);
			Insère un arc en tête d'une liste chaînée d'arcs.
	
	- Sommet nouveauSommet(char *e);
			Crée un sommet auquel est attaché le fragment 'e'; permet d'attribuer des somemts dans le tableau de sommets d'un graphe.

	- GRAPHE nouveauGraphe(int n);
			Crée un nouveau graphe de n sommets.

****************************************************************************************************************************************

V - SUPPLEMENT : Recherche du parcours assemblant les fragments dans le bon ordre

	J'ai trouvé une méthode - qui ne marche que dans certains cas - permettant de mettre les fragments dans le bon ordre pendant le 
	parcours en profondeur. Il s'agit de trier par ordre décroissant de poids les listes de successeurs de chaque sommet. Ainsi, le
	parcours en profondeur passe de tête de liste en liste, le fragment porté par le sommet suivant étant toujours celui se chevauchant
	le plus	avec le fragment porté par le précédent.

	Cependant, cela ne marche pas dans plusieurs cas :

	- Si deux arcs ont le même poids, le parcours ne sait pas faire la différence ; il choisira le premier dans la liste, faussant 
	tout le reste du parcours si ce n'est pas le bon.

	- Il peut arriver, par hasard, qu'un fragment aie un meilleur score de chevauchement avec un autre fragment, plus élevé encore que
	le score avec son successeur attendu.
	
	Fonctions :
	
	- void echangerElement(LISTE_arc A, LISTE_arc B);
		Cette fonction permute deux éléments voisins dans une liste chaînée. Elle ne manipule pas les pointeurs, mais permute seulement
		les poids et les destinations.
	
	- LISTE_arc triDecroissant(LISTE_arc A);
		On itère sur une copie de la liste jusqu'à trouver deux éléments voisins qui ne sont pas dans le bon ordre. Ils sont alors 
		permutés dans la liste d'origine avec la fonction echangerElement. Ensuite, la fonction est appelée récursivement (un booléen
		permet d'annuler cet appel lorsque le tri est terminé).		
	
****************************************************************************************************************************************

Victor Mataigne - M2.1 BIM - UE SIB - Algorithimique avancée - Février 2017
