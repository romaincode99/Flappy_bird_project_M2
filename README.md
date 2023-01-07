# Flappy_bird_project_M2

## Le Makefile donne accès à plusieurs programmes :
    - main
    - TestU_image
    - TestU_contact
    - TestU_compteurs

## main :
    C'est le jeu flappy bird à proprement parler.
    Les differentes commandes sont :
        - Appuyer sur la barre espace pour faire sauter l'oiseau.
        - Appuyer sur échap pour mettre le jeu en pause et rappuyer sur Espace pour continuer.
        - Appuyer sur la touche "r" pour recommencer. 
        - Si vous avez perdu, appuyez sur Entrer pour recommencer.

## TestU_image :
    C'est le test unitaire qui vérifie que l'affichage d'une image se fait comme l'utilisateur
    l'a demandé et que si le chemin d'accès à l'image est mal indiqué, qu'une erreur apparait bien.
    Pour vérifier l'erreur du chemin d'accès, il suffit de retirer des information lors de son renseignement dans
    le fichier TestU_image.cpp et vérifier que le bon message apparaît.

## TestU_contact
    C'est le test unitaire qui vérifie que l'oiseau meurt bien au moment  ou il touche les côtés de
    l'écran ou l'un des obstacles.
    Pour cela il suffit de sélectionner la situation de notre choix, en rentrant le numéro correspondant
    dans les choix qui nous sont proposées lors de l'exécution du programme.

## TestU_compteurs
    C'est le test unitaire qui vérifie le bon fonctionnement de l'affichage des chiffres
    et des nombres. Il vérifie que les chiffres et les nombres s'affichent correctement.
    Pour cela il faut :
        - appuyer sur la flèche de gauche pour voir les chiffres de 0 -> 9 s'afficher en boucle et dans l'ordre.
        - appuyer sur la flèche de droite pour voir les nombres s'afficher dans l'ordre en commençant par 0.

    Les chiffres doivent correspondre à ce que l'on attend, les nombres également, mais ils doivent aussi vérifier
    que l'écart entre les chiffres est respecté et que le passage de chaque dizaine dans tout les cas.
