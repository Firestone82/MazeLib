# Projekt do C++ a Python (Maze Generator / Solver)
---

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
   - Výpis tabulky

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

## API Usage
```c++
int main() {
    MazeBuilder mazeBuilderGenerated = KruskalAlgorithm().generate(10,10);
    mazeBuilderGenerated.setStart({0,0});
    mazeBuilderGenerated.setEnd({mazeBuilderGenerated.getWidth() - 1, mazeBuilderGenerated.getHeight() - 1});
    mazeBuilderGenerated.setPathWidth(10);

    Maze mazeGenerated = mazeBuilderGenerated.build();
    TextFileSavingMethod().save(mazeGenerated, "maze.txt");

    cout << " Saved maze to file: " << "maze.txt" << endl;
    cout << "  - Created with:    " mazeGenerated.getCreator() << endl;                                      // Returns "Kruskal"
    cout << "  - Creation time    " mazeGenerated.getCreationTime() << endl;                                 // Returns time in milliseconds
    cout << "  - Maze dimensions: " << mazeGenerated.getWidth() << "x" << mazeGenerated.getHeight() << endl; // Returns "10x10"
    cout << "  - MazePath width:      " << mazeGenerated.getPathWidth() << endl;                                 // Returns "10"

    MazePath generatedPath = RecursiveBacktrackerAlgorithm().solve(mazeGenerated);
    TextFileSavingMethod().save(mazeGenerated, "path.txt", generatedPath);

    cout << " Saved path to file: " << "path.txt" << endl;
    cout << "Solved with:         " generatedPath.getAlgorithm() << endl;                                   // Returns "RecursiveBacktracker"
    cout << "Solved in:           " generatedPath.getTime() << "ms" << endl;                                // Returns time in milliseconds
    cout << "MazePath length:         " generatedPath.getLength() << endl;                                      // Returns length of path
    cout << "Amount of junctions: " generatedPath.getJunctionCount() << endl;                               // Returns amount of junctions

    // --------------------------------

    MazeBuilder mazeBuilderLoaded = TextFileLoadingMethod().load("maze.json");
    mazeBuilderLoaded.setStart({0, 0});
    mazeBuilderLoaded.setEnd({mazeBuilderLoaded.getWidth() - 1, mazeBuilderLoaded.getHeight() - 1});
    mazeBuilderLoaded.setPathWidth(10);

    Maze mazeLoaded = mazeBuilderGenerated.build();
    ImageSavingMethod().save(mazeLoaded, "maze.png");

    cout << " Loaded maze from file: " << "maze.json" << endl;
    cout << "  - Created with:       " mazeLoaded.getCreator() << endl;                                      // Returns "Kruskal"
    cout << "  - Creation time       " mazeLoaded.getCreationTime() << endl;                                 // Returns time in milliseconds
    cout << "  - Maze dimensions:    " << mazeLoaded.getWidth() << "x" << mazeLoaded.getHeight() << endl;    // Returns "10x10"
    cout << "  - MazePath width:         " << mazeLoaded.getPathWidth() << endl;                                 // Returns "10"

    MazePath loadedPath = RecursiveBacktrackerAlgorithm().solve(mazeLoaded);
    ImageSavingMethod().save(mazeLoaded, "path.png", loadedPath);

    cout << " Saved path to file: " << "path.png" << endl;
    cout << "Solved with:         " generatedPath.getAlgorithm() << endl;                                   // Returns "RecursiveBacktracker"
    cout << "Solved in:           " generatedPath.getTime() << "ms" << endl;                                // Returns time in milliseconds
    cout << "MazePath length:         " generatedPath.getLength() << endl;                                      // Returns length of path
    cout << "Amount of junctions: " generatedPath.getJunctionCount() << endl;                               // Returns amount of junctions
    
    return 0;
}
```

## CLI Usage
```md
mazelib <cmd> [options]

Commands:
    help            |  - Show help message
    generate        |  - Generate maze to file or image
    solve           |  - Solve maze from file or image
    algorithms      |  - Show all algorithms

Options:
    -h, --help      | Show this help message and exit          | [boolean]
    -v, --version   | Show programs version number and exit    | [boolean]
```
```
mazelib generate [options]

Options:
    -w, --width [value]         | Width of maze to be generated         | [number]
    -h, --height [value]        | Height of maze to be generated        | [number]
    -s, --start [x] [y]         | Start position of maze                | [number] [number]
    -e, --end [x] [y]           | End position of maze                  | [number] [number]
    -a, --algorithm [type]      | Name of algorithm to generate output  | [string]
    -f, --file [path]           | Output path of file generated         | [string]
    -i, --image [path]          | Output path of image generated        | [string] 
    -g, --gap [value]           | Gap between cells on image            | [number]
    -p, --path                  | Whether or not to show origin path    | [bolean]
```
```
mazelib solve [options]
    
Options:
    -i, --input [path]          | Input path of file to be loaded       | [string]
    -a, --algorithm [type]      | Name of algorithm to process input    | [string]
    -o, --output [path]         | Ouput path of file generated          | [string] 
    -im, --image [path]         | Output path of image generated        | [string] 
    -g, --gap [value]           | Gap between cells                     | [number]
    -p, --path                  | Whether or not to show origin path    | [bolean]
```
```
mazelib algorithms [options]

Options:
    -o, --order [type] [asc]    | Order algorithms by specific order    | [type, "asc, desc"] [bolean]
    -f, --filter [type]         | Filter algorithms by type             | [string]
```
