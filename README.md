# Dots and Boxes Game implementation in C++ with Minimax and Alpha-Beta Pruning and Graphical User Interface using SFML

This Dots and Boxes game is a classic two-player strategy game implemented in C++ using GUI library SFML. The game features an AI opponent utilizing the Minimax algorithm with alpha-beta pruning to make intelligent moves. The implementation includes various functionalities such as player score tracking, dynamic turn management, and an advanced evaluation mechanism for the AI to assess the game state effectively.
You can check the instructions of setting up sfml library from the links below: <br/>
For running application in Windows (e.g. in Visual Studio) go to "https://www.sfml-dev.org/download/sfml/2.6.1/" and 
download the suitable version for you, then extract the files of the downloaded zip file to you desired path.
Afterward go to `CMakeLists.txt` file and change these two paths to with your own paths in the following lines: <br/>
`set(SFML_DIR "YourPathTo/SFML/SFML-2.6.1/lib/cmake/SFML") # Change this to your path` <br/>
`set(SFML_DLL "YourPathTo/SFML/SFML-2.6.1") # Change this to your path`.` <br/>
Then open the project in Visual Studio and run the application. <br/>
<br/>
For running application in MacOS please follow the instructions: "https://dev.to/giovannicodes/sfml-2-5-1-setup-on-macos-with-clion-505m". <br/>
For running application in Linux please follow the instructions: "https://www.sfml-dev.org/tutorials/2.5/start-linux.php". <br/>
<br/>
You need to have at least C++ 17 to run the application. <br/>
## Implementation Details

The implementation includes several components: the Board, Player, Move, and Game classes, which are structured to manage the game logic, user interactions, and AI strategies. Here is a detailed breakdown of how each component works and how a user can run and interact with the game.<br/>

Structs and Classes:<br/>

Edge: Represents whether an edge of a box is drawn.<br/>
Player: Manages player details including the name, symbol, and score. Provides a method to increment the score when a box is completed.<br/>
Box: Represents a box on the board with four edges and an owner.<br/>
Move: Used to represent a move on the board with coordinates (x, y) and a direction (L, R, U, D).<br/>

========================================================================================================================

Board Class:
Manages the game board with methods to make moves, check for completed boxes, print the board, and evaluate the game state. <br/>
makeMove(): Executes a move, updates the board, and optionally updates the player's score if a box is completed.<br/>
checkCompleteBox(): Checks if a move results in a completed box to possibly grant an extra turn.<br/>
evaluateBoard(): Provides a simple evaluation of the current board state by counting the boxes owned by each player.<br/>
getAllPossibleMoves(): Generates all possible legal moves based on the current state of the board.<br/>

========================================================================================================================

GameController Class:
The GameView class serves as the graphical interface for the Dots and Boxes game, handling all visual components 
and user interactions. This report examines how GameView integrates with GameController to provide a seamless 
and interactive gaming experience, focusing on user inputs and visual feedback.<br/>

GameController acts as the bridge between the game logic encapsulated within the Board and Player classes 
and the graphical user interface provided by GameView. The controller manages game states, 
player actions, and transitions between different stages of the game while utilizing GameView to render the 
game board and capture player inputs through graphical elements.<br/>

Functionality and Implementation<br/>
Initialization:<br/>
GameController is initialized with parameters such as board size, player names, and symbols that can be set up through GameView. The view prompts the user for these parameters using graphical forms and input fields.
Upon receiving the input data, GameController configures the game settings accordingly and initializes the game board.<br/>
Game Play:<br/>
GameController manages the game loop where each player's turn is processed. For human players, moves are solicited through GameView which captures mouse clicks or touch inputs on the graphical board.<br/>
For the computer-controlled player, GameController calculates the optimal move using AI algorithms (e.g., minimax) and updates the board state.<br/>
After each move, GameView is called to update the board's graphical representation, highlighting the latest moves and updating the score display.<br/>
User Interaction:<br/>
GameView provides interactive elements such as buttons and text fields to capture user inputs like board size and player symbols. It also handles events such as button clicks and form submissions to initiate game start and player moves.<br/>
Graphical feedback such as highlighting possible moves, displaying active player indicators, and showing messages (e.g., "Invalid move", "Your turn") enhances user engagement and guides the player through the game flow.<br/>
End of Game:<br/>
Once the game concludes (either through a win or draw), GameController determines the outcome based on the game logic and instructs GameView to display the final scores and a conclusion message.<br/>
GameView may offer options to restart the game or exit, handling these choices through user interface elements and informing GameController of the subsequent actions.<br/>
Integration Mechanisms<br/>
Data Passing: GameController communicates with GameView primarily through method calls that pass data such as board states and game outcomes. GameView returns user inputs back to the controller.<br/>
Event Handling: GameView captures user events and translates them into game actions, which are then processed by GameController. This keeps the UI responsive and interactive.<br/>
Rendering and Updates: GameController triggers rendering updates in GameView based on game state changes, ensuring that the visual representation is always synchronized with the underlying game logic.<br/>

========================================================================================================================

GameController Class:<br/>
The GameView class in the Dots and Boxes game application serves as the primary interface for all user interactions and visual outputs. This report outlines the design and functionalities of the GameView, which utilizes the SFML library to render graphics and handle input events.<br/>
GameView manages the graphical display of the game state, including the game board, player prompts, and score displays. It encapsulates all the necessary tools to visually represent the game's progress and to interact dynamically with the user.<br/>

Functionalities and Implementation<br/>

Window Initialization and Settings:<br/>
The class initializes a window using SFML, setting properties like framerate limit and window title. It also loads necessary resources such as fonts and prepares visual elements for interaction.<br/>
Drawing Functions:<br/>
drawBoard2(): This method handles the visualization of the game board, including dots, lines, and box owners. It updates the board based on the current game state.<br/>
drawLine2(): Draws lines between dots to represent moves made by the players.<br/>
drawAllLines(): Iterates through all lines stored in the game state and calls drawLine2() to draw them on the board.<br/>
User Input Handling:<br/>
handleMouseInput(): Captures mouse clicks and determines if they are valid game moves based on the game rules and current state.<br/>
determineMove2(): Translates the raw click positions into game moves, identifying the appropriate game logic coordinates and directions.<br/>
User Interaction via Text Inputs:<br/>
Various methods (promptForBoardSize2(), promptForPlayerName2(), etc.) allow for interaction through textual input, collecting essential game settings such as board size and player symbols.<br/>
These methods integrate basic form controls and validation to ensure correct input while maintaining user engagement through interactive text prompts.<br/>
Feedback and Messaging:<br/>
showMessage() and showMessage2(): Provide feedback and information to the player, displaying text messages directly on the game window. These are crucial for guiding the user through the game setup and for providing updates during gameplay.<br/>
Utility Functions:<br/>
setupText(): Configures the text properties used throughout the game interface.<br/>
clearClicks(), addLine(), setOwners(): Manage the internal state of the view, such as clearing input after processing or updating the visual representation of the board after moves.<br/>
Integration with GameController<br/>
GameView acts as a fully encapsulated module for handling all user interface elements, directly interacting with GameController to reflect the game's logic and state changes visually. It provides methods that GameController calls to update the display based on game progress and player actions. This separation adheres to the MVC pattern, enhancing maintainability and scalability.<br/>

Conclusion<br/>
The integration of GameView with GameController encapsulates the principles of MVC architecture, promoting a clear separation of concerns where GameController handles the game logic and state management, while GameView deals with all aspects of the user interface. This structure not only simplifies the management of game states and user interactions but also enhances maintainability and scalability of the application, making it easier to extend or modify either component without affecting the other.<br/>

Minimax algorithm - minimax(), minimax_advanced() (minimax_advanced() uses the advanced evaluation function)<br/>
Recursion and Depth Limitation: The algorithm operates recursively, exploring all possible moves up to a specified depth (DEPTH constant). It alternates between maximizing and minimizing turns to simulate the moves of both the computer (AI) and the human player.<br/>
Alpha-Beta Pruning: To optimize the Minimax process, alpha-beta pruning is used to cut off branches of the game tree that cannot possibly affect the final decision, reducing the number of nodes evaluated.<br/>
Turn Management: It checks if a move completes a box, allowing the current player to continue if true, or switching players if not. This is crucial because completing a box grants an extra turn, affecting game dynamics and strategy.<br/>

Evaluation Functions<br/>
Evaluation functions assess the game state's value from the perspective of the AI. Two types of evaluation functions are used in your game: a basic one and an advanced one.<br/>
Basic Evaluation Function - evaluateBoard():<br/>
Simple Counting: This function calculates the score by simply counting the number of boxes owned by each player. The AI's aim is to maximize the difference between its score and the human player's score.<br/>
Advanced Evaluation Function - evaluateBoardAdvanced():<br/>
Chain Potential and Risk Evaluation: This function goes deeper by not only counting completed boxes but also considering the potential to complete more boxes in subsequent moves. It analyzes the board to evaluate chains (potential sequences of connected boxes that can be captured in a series of moves) and includes this in the score calculation.<br/>
Dynamic Adjustment Based on Player: It adjusts the scores based on who is the current player, potentially giving more weight to potential scores if the current player can immediately act on them.<br/>


## Gameplay

When the game starts the program asks you to input the desired board size (minimum size 3x3 and maximum 5x5), you should enter a single number like: 3 or 5 and hit enter.<br/>
Then the program asks you to choose your player name, you should type your username in the box and hit enter(if the username is longer than 10 characters, then it will be cut to use first 10 characters) .<br/>
Then the program asks you to choose your symbol either 'X' or 'O', you should write 'X' and hit enter if you want to play with symbol 'X', otherwise it will assign you symbol 'O'.<br/>
Afterward the program will ask you to decide whether you want to start the game or let the AI-agent do. You need to type symbol 'Y' if you want to start first, otherwise the AI-agent will start firstly.
When you want to place a move, just click to two adjacent dots in the window and th program will display your move on the board and also will write down you last move, before the other player's turn.<br/>
The game continues until all boxes are completed or when the window is closed.<br/>

Ending the Game:
Once no more moves are possible, the game ends, and the scores are displayed.
The player with the most boxes wins.<br/>

