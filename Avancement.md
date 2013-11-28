ShootScores
===========
27/11
Nous avons réussi à mettre en évidence les différentes zones d'une cible pistolet 10 m pour "n'importe quelle photo" d'une cible. Nous pourrons ainsi déterminer précisément le score pour chaque impact dans un futur proche. La prochaine étape sera d'arriver à déterminer les impacts au sein de l'image, plus précisément à l'intérieur de la cible. Afin de pouvoir déterminer, les différents cercles correspondant aux points de la cible, nous avons cherché à isoler le visuel (la partie noire du centre de la cible qui correspond aux points supérieurs à 7) et à créer un cercle autour de celui-ci. Grâce au diamètre de ce cercle, nous avons pu faire une relation afin de déterminer tous les autres cercles en utilisant la valeur réelle du diamètre des cercles correspondant. Nous avons principalement utilisé la fonction HoughCircles() afin de chercher des cercles au sein d'une images et la fonction circle() qui permet de dessiner un cercle.
===========
Afin de pouvoir déterminer les différentes zones de la cible, il faut nous faut connaître les diamètres des cercles qui composent la cible.

Le diametre du visuel (rond noir)  au pistolet 10m est de  59,5 mm.
        
Diamètre des zones (en mm)
10    9       8       7       6       5       4       3       2       1
11.5  27.5    43.5    59.5    75.5    91.5    107.5   123.5   139.5   155.5
