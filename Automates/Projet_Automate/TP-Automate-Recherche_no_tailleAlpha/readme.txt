ALGORITHMIQUE AVANCEE - PROJET 2 - AUTOMATE RECONNAISSANT A*x

	README

****************************************************************************************************************************************

Ce programme construit un automate reconnaissant un mot, et l'utilise pour trouver la position de sa première occurrence dans un texte.
	n.b : l'affichage d'un '-1' signifie qu'aucune occurrence n'a été trouvée.


I - FONCTIONNEMENT DU PROGRAMME

	1 - Ligne de commande : ./main <motRecherché> <fichiersTests/fichierCible> <fichiersTests/fichierAlphabet>
	 		motRecherché : tapé directement en console
	 		fichierCible : un fichier contenant le texte où effectuer la recherche
	 		fichierAlphabet : un fichier contenant l'alphabet

	 les associations fichiers_texte/fichiers_alphabet sont détaillés plus bas, en partie II.

	Une fois lancé, le programme affiche l'automate du mot (nombre d'états, taille de l'alphabet, états initiaux et terminaux, liste 
	des transitions), puis le résultat de la recherche.

				--------------------------------------------------------------------------------------------------------

	2 - Structures de données :

		Type automate : contiend un nombre d'états, une taille d'alphabet, un état intial, un état terminal, et un tableau de 
		transitions, de taille nbetats, chaque indice du tableau étant une liste chaînée de transitions de l'état correspondant.

		Type transition : comporte un état source, un état destination, et la lettre assurant la transition.

		Types etat et ensemble : re-définition des types int et int*. Je ne m'en suis que très peu servi.

				--------------------------------------------------------------------------------------------------------

	3- main:

		Le main a été modifié à plusieurs reprises : le mot et le texte passés en arguments sont lus avant d'être passés dnas les 
		fonctions, pour vérifier leur conformité à l'alphabet. La taille de l'alphabet n'est plus passée en ligne de commande mais
		calculée à partir du fichier. L'automate construit s'affiche dans le termina à l'éxécution du programme.

				--------------------------------------------------------------------------------------------------------

	4 - Fonctions principales :

		A - void creer_automate_mot(pautomate Aut, char* x, char* fichierAlphabet) :

	La fonction crée l'automate reconnaissant A*x pour le mot x, avec le paramètre fichierAlphabet étant passé dans la ligne de 
	commande.
	
	- Sont d'abord déclarés et/ou initialisés le nombre d'états (mot vide + nombre de lettres de x) et le tableau des listes de
	transitions (tableau de taille nbetat : une case = un état = une liste chaînée de transitions).
	
	- L'algorithme crée toutes les transitions 0-a-0, a étant chacune des lettres/symboles de l'alphabet.
	
	- L'algorithme itère ensuite sur les lettres du mot x et les états de l'automate, et modifie en conséquence la transition de l'état
	précédent à l'état courant : la transition (n-1)-x[i]-(n-1) devient (n-1)-x[i]-n.
	
	- A chacune de ces itérations, l'algorithme parcourt la liste des transitions de l'état destination de l'état et de la lettre 
	courants, et ajoute des transitions de l'état courant+1 vers cet état. Cela permet de reprendre la recherche de mot plus loin 
	que l'état 0 à l'itération suivante, et ainsi de gagner du temps.

		B - int recherche_Mot_Auto(pautomate Aut, char* texte_fichier) :

	La fonction utilise l'automate pour trouver la première occurrence du mot de l'automate dans un texte passé en argument de la 
	ligne de commande. L'algorithme itère sur toute la longueur du texte cible, à la manière d'un algorithme naïf, mais gagne du
	temps par rapport à celui là en évitant de retourner à l'état 0 lorsque des bords sont présents. On avance d'état en état gâce à la 
	fonction destination(). Lorsqu'une occurrence est trouvée, un break stoppe l'algorithme et la position de l'occurrence +1 (pour ne
	pas compter à partir de 0) est retournée.

				--------------------------------------------------------------------------------------------------------

	5 - Autres fonctions :

		A - ptransition supprimer(ptransition transi, etat dest, char a) :

	Supprime la transition 'dest-a' dans une liste chaînée de transition dont l'indice dans le tableau de transitions est précisé en 
	dehors de la fonction. Gère les cas de suppression en début/fin de liste. Probablement perfectible car il y a beaucoup de
	manipulations de pointeurs et je ne suis pas toujours à l'aise avec.
	n.b. : reprise et adaptée du projet précédent, d'où le type ptransition au lieu de void et le type ptransition au lieu ptransition*.

		B - void ajout_transition(ptransition* tabT, etat source, etat dest, char a) :

	Ajoute une transition dans le tableau de transitions tabT, à l'indice 'source'.

		C - etat destination (pautomate Aut, etat source, char a) : 

	Renvoie le numéro de l'état destination de l'état et de la lettre p passés en paramètres.

		D - pautomate nouvel_automate(void) :

	Allocation mémoire d'un automate, à utiliser avant la fonction de création de l'automate. Elle prenait à l'origine la taille de
	l'alphabet en paramètre, mais cette taille est finalement calculée dans la fonction de création de l'automate.

		E - ptransition* creer_transitions(int nbE) :

	Allocation mémoire du tableau des listes de transitions de l'automate.

		F - void mettreTerminal(pautomate A, etat e) : 

	Définit l'état terminal.

		G - void affiche_automate(pautomate Aut, char* mot, char* alphabet) :

	Affiche l'automate : le mot reconnu, la taille de l'alphabet, l'alphabet, le nombre d'états, l'état initial, l'état terminal, la
	liste des transitions.

		H - char* lireFichier(char* file) :

	Lit le contenu d'un fichier (passé en argument de la ligne de commande) et le stocke dans une chaine de caractères. Le nombre de
	lignes n'est pas limité. Le fichier est d'abor parcouru une fois avec fseek,le nombre de caractères total est reteu avec ftell.
	On revient ensuite au début et le contenu est stocké ligne par ligne (ou tabulation par tabulation ou espace par espace) dans une
	chaine de caractères avec fscanf.
	Fonction améliorable (voir parties III et IV-B).

		I - int gestionErreur(char* mot, char* texte, char* alphabet) :

	Cette fonction vérifie la conformité du mot recherché et du texte cible avec l'alphabet (chacun est parcouru caractère par 
	caractère jusqu'à trouver une lettre non conforme; cela peut prendre du temps dans le cas du fichier texte cible). Dans le cas
	d'une non-conformité, l'automate n'est pas construit et le	programme est stoppé.

****************************************************************************************************************************************

II - Fichiers de tests:

	Plusieurs sont disponibles :
		
		Alphabet des nucléotides :
		    - cible1a.txt / alphabet1.txt
		    - cible1b.txt / alphabet1.txt
		    - randomDNA.txt
		Alphabet [a-z]
			- cible2.txt / alphabet2.txt
			- randomAlpha.txt
		Alphabet [A-Z]
			- cible3.txt / alphabet3.txt		
		Alphabet alphanumérique + point et virgule
			- cible4.txt / alphabet4.txt
		Alphabet numérique:
			- cible5.txt / alphabet5.txt
			- randomNumbers.txt
		Alphabet des nucléotides en majuscules :
			- cible6.txt / alphabet6.txt
			- randomAlphaNum.txt

	Les fichiers "random" sont des fichiers très longs générés aléatoirement grâce un script python. Ils ont été utilisé pour les
	comparaisons avec les algorithmes naïf, Morris-Pratt et KMP.

III - Difficultés rencontrées :

	- Revoir et comprendre l'algorithme vu en cours. Difficulté surmontée rapidement une fois des explications demandées à Mme 
	Prieur-Gaston et aux collègues de M2.1.

	- La fonction de lecture de fichier :
		- fermeture des fichiers lus, bug toujours non résolu.
		- rigueur d'écriture : vérifications d'ouverture du fichier et des allocations mémoires, tailles maximales d'allocations ...
		- lecture des fichiers très longs (résolu avec une V2 utilisant fseek et ftell avant fscanf, au prix d'un temps d'éxécution 
		probablement un peu plus long).

****************************************************************************************************************************************

IV - AMELIORATIONS :

	A - EFFECTUEES :

		1 - Faire en sorte que le fichier cible ne soit pas limité à un texte tenant sur une seule ligne
			-> Modification de ma fonction lireFichier(char* nomFichier)

		2 - Implémenter une gestion d'erreurs pour reconnaître les incompatibilités alphabet/mot_recheché et alphabet/texte_cible.
		 C'est un algorithme naïf, qui parcours toute la séquence du mot recherché jusqu'à trouver une lettre non conforme, puis est
		 interrompu par un break, ce qui limite le temps d'éxécution sur des textes_cibles trop longs (en espérant que les lettre
		 non conformes ne soient pas tout à la fin du fichier). J'ai fait en sorte que ces vérifications soient faites en début de 
		 programme, avant la construction de l'automate et la recherche de mot
		 	-> Ecriture d'une fonction gestionErreur et modification du main.

		3 - Enlever l'argument <tailleAlphabet> de la ligne de commande et faire en sorte qu'il soit calculé à partir de 
		<fichierAlphabet>
			-> modification de la fonction nouvel_automate, qui se retrouve sans paramètre. La variable tailleAlpha de
			l'automate est calculée dans la fonction creer_automate_mot, par strlen(alphabet). Le main est également 
			un peu modifié.

		4 - Le programme gère les espaces dans les fichiers cibles (ce n'est pas à proprement parler une amélioration, j'ai 
		juste vérifié si ça marchait).

				--------------------------------------------------------------------------------------------------------

	B - EFFECTUEES LORS DES COMPARAISONS D'ALGORITHMES :

		- Une méthode alternative est de lire l'argument <motRecherché> à partir d'un fichier, ce qui est plus confortable pour 
		écrire la ligne de commande dans le cas de la recherche d'un mot très long.
			-> Utilisation de la fonction lireFichier(char* nomFichier), légère modification du main.

		Je m'en suis servi lors des comparaisons de vitesse d'éxécution des différents algorithmes, pour rechercher des mots de
		500 et 5000 caractères.

	C - ENVISAGEABLES :		

		1 - Trouver toutes les occurrences du mot recherché au lieu de seulement la première occurrence
			-> Utiliser une liste chaînée

****************************************************************************************************************************************

V - COMPARAISONS AVEC LES ALGORITHMES NAIF, MORRIS-PRATT ET KMP :

	La durée d'éxécution a été mesurée pour chaque algorithme dans plusieurs cas : différentes taille de fichier, différents alphabets,
	différentes longueurs de mots recherchés. Chaque mot recherché était situé dans les dernières lignes des fichiers de test 
	(fichiers générés aléatoirement par un script python).

		- Fichiers de 100 000 et 500 000 lignes.
		- Alphabet des nucléotides, numérique, [a-z] et alphanumérique.
		- taille des mots recherchés : 50, 500, 5000.

	Les résultats sont visibles dans le fichier '.pdf'.

		Remarques :

	- La gestion d'erreur dans le programme de l'automate est désactivée pour ces tests

	- Pour les mots recherchés de 5000 aractères, l'affichage de l'automate est désactivé.

	- Les temps mesurés sont les temps d'éxécution des programmes dans leur entièreté : ils incluent le temps de lecture des
	fichiers. Comme la même fonction est utilisée à dans chaque cas, ce n'est pas très grave, mais étant donné que cela représente la
    majorité du temps d'éxécution, il est moins aisé de voir la réelle différence de rapidité de chaque algorithme.

****************************************************************************************************************************************

VI - BUGS :

	- La fonction lireFichier fonctionne mal avec les fichiers d'une seule ligne : des caractères supplémentaires (sortis d'on ne sait
	 où), sont rajoutés à l'alphabet. Cela n'empêche pas le bon fonctionnement du programme.

	- Plus grave : Il y a une erreur de segmentation lors de la création de l'automate si la fonction lireFichier fait un appel à
	fclose(). Il m'est impossible de comprendre pourquoi, malgré les améliorations apportées après avoir demandé de l'aide sur le net. 
	J'ai essayé toutes sortes de versions (avec fscanf, fgets, fread, ainsi que les fonctions d'autres personnes du master), et le 
	problème persiste. Les fichiers sont pourtant correctement lus (un print affiche un contenu correct).

		L'erreur ne survient pas dans la fonction lireFichier mais dans la boucle while de la fonction creer_automate_mot. J'ai implémenté
		un compteur pour analyser ce qu'il se passait (je l'ai laissé, il est passé en commentaires), et il n'est jamais remis à 0 lorsque
		fclose() est activée.

****************************************************************************************************************************************

Victor Mataigne - M2.1 BIM - UE SIB - Algorithimique avancée - Mars 2017