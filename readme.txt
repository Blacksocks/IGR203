=== IGR 203 - Travaux Pratiques QT#3 : Statecharts ===

Pour créer l'interface graphique de mon application, je me suis grandement inspiré de l'interface physique présente sur les micro-ondes. Les boutons sont placés de facon similaires et on potentiomettre permet même d'effectuer des réglages, comme sur le modèle.
Cela permet à n'importe quel utilisateur de manipuler l'application sans devoir suivre un tutoriel. Il connait déjà les principales actions que l'interface doit pouvoir enclancher et la disposition des boutons.
Il faut supposer que l'utilisateur soit familié avec l'utilisation de micro-ondes, ce qui est acceptable.

J'ai donc créé mon interface avec QtCretor qui permet de le faire simplement.
J'ai ensuite représenté lociciellement le fonctionnement du micro-onde.
Un statechart m'a permis de produire un code propre facilement compréhensible.
Voici rapidement le principe:
L'utilisateur appuie sur un bouton, ce qui fait changer l'état du statechart.
L'entrée dans un nouvel état provoque l'appel d'une fonction qui peut changer des paramètres du système (puissance de cuisson, durée de cuisson, heure) ou simuler des actions (allumer ou éteindre le four).

Je n'ai malheuresement pas terminé ce projet. Il me manque en effet un cas à traiter: les timers.
Lorsque le temps de cuisson est écoulé, le four doit s'arrêter.

