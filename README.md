# 🎮 Conway's Game of Life - Raylib C++

Une implémentation interactive et moderne du célèbre automate cellulaire **Jeu de la Vie** de John Conway, développée en C++ avec la bibliothèque graphique Raylib.

![Game of Life Demo](screenshot.png)
*Capturez une image de votre jeu en action et nommez-la `screenshot.png`*

## ✨ Fonctionnalités

- 🖱️ **Dessin interactif** : Dessinez avec le clic gauche, effacez avec le clic droit
- ⏸️ **Contrôles de simulation** : Lecture/Pause avec bouton ou barre d'espace
- ⚡ **Vitesse ajustable** : Slider pour contrôler la vitesse de simulation (1-60 FPS)
- 💾 **Sauvegarde/Chargement** : Sauvegardez vos motifs favoris (touches S/L)
- 🔄 **Réinitialisation** : Effacez la grille en un clic (touche R)
- 📱 **Interface responsive** : S'adapte automatiquement à votre résolution d'écran
- 🎨 **Interface moderne** : Design épuré avec code couleur (or/noir)

## 🎯 Règles du Jeu de la Vie

1. Une cellule vivante avec **moins de 2 voisins** meurt (sous-population)
2. Une cellule vivante avec **2 ou 3 voisins** survit
3. Une cellule vivante avec **plus de 3 voisins** meurt (surpopulation)
4. Une cellule morte avec **exactement 3 voisins** devient vivante (reproduction)

## 🕹️ Commandes

| Action | Contrôle |
|--------|----------|
| Dessiner une cellule | Clic gauche (maintenir) |
| Effacer une cellule | Clic droit (maintenir) |
| Pause/Lecture | Barre d'espace ou bouton |
| Sauvegarder motif | Touche `S` ou bouton Save |
| Charger motif | Touche `L` ou bouton Load |
| Réinitialiser grille | Touche `R` ou bouton Reset |
| Ajuster vitesse | Slider de vitesse |

## 🚀 Installation et Compilation

### Prérequis

- **C++ Compiler** (GCC, Clang, MSVC)
- **CMake** 3.11+ (recommandé) ou Make
- **Raylib** sera téléchargé automatiquement via CMake

### Option 1 : CMake (Recommandé)

Cloner le dépôt

git clone https://github.com/votre-username/game-of-life-raylib.git
cd game-of-life-raylib
Configurer le projet

cmake -B build
Compiler

cmake --build build
Exécuter (depuis le dossier racine)

./build/GameOfLife


## 🛠️ Architecture du Code

### Classes principales

- **`Cell`** : Représente une cellule individuelle (position x,y et état alive)
- **`Grid`** : Gère la grille complète avec logique du Jeu de la Vie
  - Constructeur de copie et opérateur d'assignation pour deep copy
  - Calcul des voisins avec gestion des bordures
  - Double buffering pour mise à jour correcte
- **`Button`** : Bouton cliquable avec état toggle
- **`Slider`** : Slider draggable pour ajuster la vitesse

### Optimisations

- Gestion mémoire propre avec destructeurs
- Deep copy pour sauvegarde/chargement de motifs
- Interface adaptative basée sur pourcentages
- Double buffer pour éviter les artefacts de mise à jour

## 🎨 Motifs Célèbres à Tester

Essayez ces motifs classiques :

- **Glider** : Un motif qui se déplace en diagonale
- **Oscillateurs** : Motifs qui alternent entre états (Blinker, Toad, Pulsar)
- **Vaisseaux spatiaux** : Structures mobiles (LWSS, MWSS, HWSS)
- **Canons** : Générateurs de gliders (Canon de Gosper)

## 📝 TODO / Améliorations Futures

- [ ] Zoom/Pan pour grilles plus grandes
- [ ] Bibliothèque de motifs prédéfinis
- [ ] Export/Import de motifs (fichiers .cells, .rle)
- [ ] Compteur de générations et de cellules vivantes
- [ ] Mode grille infinie (torique)
- [ ] Historique des états (undo/redo)

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit vos changements (`git commit -m 'Ajout fonctionnalité'`)
4. Push (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

## 📄 Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.

## 🙏 Remerciements

- [Raylib](https://www.raylib.com/) - Framework graphique simple et efficace
- [John Conway](https://en.wikipedia.org/wiki/John_Horton_Conway) - Créateur du Jeu de la Vie
- La communauté des automates cellulaires

## 📧 Contact

Votre Nom - [@votre_twitter](https://twitter.com/votre_twitter)

Lien du projet: [https://github.com/votre-username/game-of-life-raylib](https://github.com/votre-username/game-of-life-raylib)

---

⭐ Si ce projet vous a plu, n'hésitez pas à lui donner une étoile sur GitHub !
