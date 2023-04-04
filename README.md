# Projekt do C++ a Python (Maze Generator / Solver)

#### Autor projektu: Pavel Mikula (MIK0486)

## Téma Projektu
Projekt se bude zabývat generaci a řešením bludišť. Pro zpracování bude rozdělen do dvou částí. 
První část bude spíše zaměřena na logiku, tím bude API/CLI, která bude psaná v C++. 
Tato API nebo CLI bude přijímat uživatelská vstupní data a na základě parametrů vytvářet bludiště a řešit je. 
Druhá část projektu bude spíše zaměřená na grafiku v jazyce Python. 
Zde bude graficky zpracováno obsluhování API, toto grafické GUI poté poslouží také do předmětu URO.

## Logická část projektu (API/CLI)
Tato část bude obsluhovat jednotlivé funkce:
 - Vytvoření bludiště pomocí specifikovaného algoritmu
   - Uložení do souboru nebo do obrázku
 - Vyřešení bludiště pomocí specifikovaného algoritmu
   - Načtení vstupu ze souboru
   - Uložení do souboru nebo do obrázku
 - Zjištění nejrychlejšího algoritmu pro vyřešení bludiště
   - Výpis tabulky s výsledky
 - Výpis všech dostupných algoritmů

## Grafická část projektu (GUI)
Grafická část projektu napsána v jazyce python, bude pomocí knihovny tkinker a 
knihovny z první části projektu propojovat uživatelská rozhraní s grafickým.
Aplikace bude zasílat žádosti API a jejich výstupy vykreslovat na obrazovku.

## Architektura API
Důležité třídy pro práci:
- Maze (Třída pro uchování bludiště)
- Algorithm (Třída pro využívání algoritmu)
  - GeneratingAlgorithm (Podtřída pro generujicí algoritmus)
  - SolvingAlgorithm (Podtřída pro řešící algoritmus)
- Graph (Třída pro uchování obsahu bludiště)
  - Node (Podtřída pro uchování pole bludiště)
- Image (Třída pro export bludiště do obrázku)
- Interface (Třída pro uchování rozhraní)

## API Usage
```c++
void example() {
    // Creation of a maze
    MazeBuilder mazeBuilderGenerated = KruskalAlgorithm(time(nullptr)).generate(10,10);
    mazeBuilderGenerated.setStart({0,0});
    mazeBuilderGenerated.setEnd({mazeBuilderGenerated.getWidth() - 1,mazeBuilderGenerated.getHeight() - 1});
    mazeBuilderGenerated.setPathWidth(30);
    mazeBuilderGenerated.setWallWidth(3);

    // Building the maze
    Maze mazeGenerated = mazeBuilderGenerated.build();

    // Exporting the maze to a file
    TextFileSavingMethod().save(mazeGenerated,"maze.txt");

    // Exporting the maze to an image
    ImageSavingMethod().save(mazeGenerated,"maze.png");

    // Loading a maze from a file
    Expected<MazeBuilder> mazeBuilderLoaded = TextFileLoadingMethod().load("maze.txt");

    // Checking for errors
    if (mazeBuilderLoaded.hasError()) {
        cout << "Error: " << mazeBuilderLoaded.error() << endl;
        return 1;
    }

    // Solving the maze
    MazePath generatedPath = DepthFirstSearchAlgorithm().solve(mazeGenerated);

    // Exporting the maze to a file with the path
    TextFileSavingMethod().save(mazeGenerated,"mazePath.txt",generatedPath);

    // Exporting the maze to an image with the path
    ImageSavingMethod().save(mazeGenerated,"mazePath.png",generatedPath);
}
```

## Requirements:
- C++17
- CMake 3.22.1+
- Python 3.9.7+ (for GUI)

## Images
Example maze output:

![Generated maze](assets/maze.png)
![Solved maze](assets/mazeSolved.png)

## CLI Usage
<details>
<summary>Click to show help CLI</summary>

```
 __  __               _      _ _
|  \/  |             | |    (_) |
| \  / | __ _ _______| |     _| |__
| |\/| |/ _` |_  / _ \ |    | | '_ \
| |  | | (_| |/ /  __/ |____| | |_) |
|_|  |_|\__,_/___\___|______|_|_.__/
Author: Pavel Mikula (MIK0486)

Format: mazelib <cmd> [options]

Commands:
  help                           | Show program help message (this)
  version, ver                   | Show programs version number
  generate, gen                  | Generate maze to file or image
  solve                          | Solve maze from file or image
  test                           | Test algorithms
  algorithms, algs, algos        | Show available algorithms

Options:
  -h, --help      | Show this help message and exit          | [boolean]
  -v, --version   | Show programs version number and exit    | [boolean]
```
</details>

<details>
<summary>Click to show generate CLI</summary>

```
Command: mazelib generate [options]

Options:
  -w, --width           | Width of maze                                     REQUIRED | [int]
  -h, --height          | Height of maze                                    REQUIRED | [int]
  -a, --algorithm       | Algorithm to generate maze                        REQUIRED | [string]
  -se, --seed           | Seed of the maze                                           | [double]
  -s, --start           | Start position of maze                                     | [int] [int]
  -e, --end             | End position of maze                                       | [int] [int]
  -pw, --pathWidth      | Width of the path between walls                            | [int]
  -ww, --wallWidth      | Width of wall between paths                                | [int]
  -f, --file            | Path to the file, where maze will be saved                 | [string]
  -i, --image           | Path to the image, where maze will be saved                | [string]
```
</details>

<details>
<summary>Click to show solve CLI</summary>

```
Command: mazelib solve [options]

Options:
  -fi, --fileIn         | Path to the input file of maze                    REQUIRED | [string]
  -a, --algorithm       | Algorithm to solve maze                           REQUIRED | [string]
  -s, --start           | Start position of maze                                     | [int] [int]
  -e, --end             | End position of maze                                       | [int] [int]
  -fo, --fileOut        | Path to the file, where maze will be saved                 | [string]
  -i, --image           | Path to the image, where maze will be saved                | [string]
```
</details>

<details>
<summary>Click to show test CLI</summary>

```
Command: mazelib test [options]

Options:
  -fi, --fileIn         | Path to the file, from which maze will be loaded  REQUIRED | [string]
  -a, --algorithm       | Algorithms to test, separated by commas                    | [string]
  -fo, --fileOut        | Path to the file, where maze will be saved                 | [string]
  -t, --table           | Output results printed in table                            |
```
</details>

<details>
<summary>Click to show algorithms CLI</summary>

```
Command: mazelib algorithms

Options:
  -o, --order           | Order of algorithms                                        | [string]
  -t, --type            | Type of algorithms                                         | [string]
  -d, --description     | Hide description of algorithms                             |
```
</details>