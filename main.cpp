#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum for difficulty levels
enum Difficulty {
    EASY,
    MEDIUM,
    HARD,
    VERY_HARD,
    CUSTOM // Custom option to choose the number of displayed numbers
};

// Struct to store indices
struct stIndex {
    int Row;
    int Colm;
};

// Global variables
vector<stIndex> vHidenValues;
int Matrix[9][9];

// Function prototypes
int ReadNum(string Message, int From = -9999, int To = 9999);
int RandomNumber(int From, int To);
bool FoundInRow(int Row, int Value);
bool FoundInColm(int Colm, int Value);
int GetSquirIndex(int Index);
bool FoundInSquir(int Row, int Colm, int Value);
bool isAllowed(int Row, int Colm, int Value);
vector<int> GetAllowedNumbers(int Row, int Colm);
int GetAllowedRandNum(int Row, int Colm);
void DrawGameMatrix(string FakeMatrix[9][9]);
void FillGameMatrixWith0();
void FillRowWithRand(int Row, int& TryingCounter);
void FillGameMatrixWithRandNum();
bool isFoundInHideList(int, int);
void HideRandValue();
string GetLine(string FM[9]);
bool isValiedRowChar(char Row);
bool isValiedColm(char Colm);
short IndexInInt(char RowOrColm);
bool isAcceptedIndex(string Index);
stIndex GetIndex(string In);
stIndex ReadIndex();
int ReadNewValue();
void UpdateValueInMatrix(string FakeMatrix[9][9], stIndex Index, short Value);
bool isEquel(string FM[9][9], short Pos);
bool CheckWin(string FakeMatrix[9][9]);
bool CheckSolution(string FakeMatrix[9][9]); // Added function
void CopyFakeMatrix(string FakeMatrix[9][9]);
void HideRandomValues(int HiddenValues);
void ResetScreen();
void GameOverScreen();
void Sudoku();

// Main function
int main() {

    srand(static_cast<unsigned int>(time(0)));
    Difficulty selectedLevel;

    cout << " \n\n\n\n\t\t\t\tS\tU\tD\tO\tK\tU \t\tG\tA\tM\tE \t\t\t\t\t\t\n " << endl;
    cout << " \t\t\t\t\t Made By : Mina Mamdouh , Menna Alrefaay , Rawan Abd Alrahman \t\t\t\t\n " << endl;
    cout << " \t\t\t\t\t UNIVERISTY \t:\t E\tR\tU \t\t\t\t\n\n\n " << endl;

    cout << "Dear, Select the difficulty level you want to play : " << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Very Hard" << endl;
    cout << "5. Custom" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            selectedLevel = EASY;
            break;
        case 2:
            selectedLevel = MEDIUM;
            break;
        case 3:
            selectedLevel = HARD;
            break;
        case 4:
            selectedLevel = VERY_HARD;
            break;
        case 5:
            selectedLevel = CUSTOM;
            break;
        default:
            cout << "Invalid choice. Defaulting to Easy." << endl;
            selectedLevel = EASY;
            break;
    }

    int numbersToShow = 5; // Default number of numbers to show
    if (selectedLevel == CUSTOM) {
        cout << "Enter the number of numbers to show (1-9): ";
        cin >> numbersToShow;
        if (numbersToShow < 1 || numbersToShow > 9) {
            cout << "Invalid number. Defaulting to 5." << endl;
            numbersToShow = 5;
        }
    }

    // Call to Sudoku function
    Sudoku();
    return 0;
}

// Function to read a number within a specified range
int ReadNum(string Message, int From, int To) {
    int Number;

    do {
        cout << Message;
        cin >> Number;

    } while (Number < From || Number > To);

    return Number;
}

// Function to generate a random number within a range
int RandomNumber(int From, int To) {
    return rand() % (To - From + 1) + From;
}

// Function to check if a value is found in a row
bool FoundInRow(int Row, int Value) {
    for (int Colm = 0; Colm < 9; Colm++)
        if (Matrix[Row][Colm] == Value)
            return true;

    return false;
}

// Function to check if a value is found in a column
bool FoundInColm(int Colm, int Value) {
    for (int Row = 0; Row < 9; Row++)
        if (Matrix[Row][Colm] == Value)
            return true;

    return false;
}

// Function to get the index of the starting square for a given index
int GetSquirIndex(int Index) {
    if (Index < 3)
        return 0;
    else if (Index < 6)
        return 3;
    else
        return 6;
}

// Function to check if a value is found in a square
bool FoundInSquir(int Row, int Colm, int Value) {
    int SquirRow, SquirColm;

    SquirRow = GetSquirIndex(Row);
    SquirColm = GetSquirIndex(Colm);

    for (int i = SquirRow; i < SquirRow + 3; i++)
        for (int j = SquirColm; j < SquirColm + 3; j++)
            if (Matrix[i][j] == Value)
                return true;

    return false;
}

// Function to check if a value is allowed in a cell
bool isAllowed(int Row, int Colm, int Value) {
    return !(FoundInRow(Row, Value) || FoundInColm(Colm, Value) || FoundInSquir(Row, Colm, Value));
}

// Function to get the allowed numbers for a cell
vector<int> GetAllowedNumbers(int Row, int Colm) {
    vector<int> vAllowedValues;

    for (int Value = 1; Value <= 9; Value++)
        if (isAllowed(Row, Colm, Value))
            vAllowedValues.push_back(Value);

    return vAllowedValues;
}

// Function to get a random allowed number for a cell
int GetAllowedRandNum(int Row, int Colm) {
    vector<int> vAllowedValues = GetAllowedNumbers(Row, Colm);

    if (vAllowedValues.size() == 0) {
        return 0;
    }

    return vAllowedValues[RandomNumber(0, vAllowedValues.size() - 1)];
}

// Function to draw the game matrix
void DrawGameMatrix(string FakeMatrix[9][9]) {
    string GameMatrix = "";

    GameMatrix += "-------------------------------------------------------\n";
    GameMatrix += "|  1    2    3     4    5    6     7    8    9        |\n";
    GameMatrix += "_________________________________________________     |\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[0]) + "  A  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[1]) + "  B  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[2]) + "  C  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += "_________________________________________________     |\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[3]) + "  D  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[4]) + "  E  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[5]) + "  F  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += "_________________________________________________     |\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[6]) + "  G  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[7]) + "  H  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += GetLine(FakeMatrix[8]) + "  I  *\n";
    GameMatrix += "|               |               |               |     |\n";
    GameMatrix += "-------------------------------------------------------\n";

    cout << GameMatrix;
}

// Function to fill a row with 0s
void FillRowWith0(int Row) {
    for (int i = 0; i < 9; i++)
        Matrix[Row][i] = 0;
}

// Function to fill the game matrix with 0s
void FillGameMatrixWith0() {
    for (int i = 0; i < 9; i++)
        FillRowWith0(i);
}

// Function to fill a row with random numbers
void FillRowWithRand(int Row, int& TryingCounter) {
    int Retry;

    do {
        FillRowWith0(Row);

        for (int Colm = 0; Colm < 9; Colm++) {
            Retry = GetAllowedRandNum(Row, Colm);

            TryingCounter--;

            if (Retry != 0)
                Matrix[Row][Colm] = Retry;
            else
                break;
        }

    } while (Retry == 0 || TryingCounter > 0);
}

// Function to fill the game matrix with random numbers
void FillGameMatrixWithRandNum() {
    int TryingCounter;

    for (int i = 0; i < 9; i++) {
        TryingCounter = 20;
        FillRowWithRand(i, TryingCounter);

        if (TryingCounter == 0)
            i = 0;
    }
}

// Function to check if a cell is found in the hide list
bool isFoundInHideList(int Row, int Colm) {
    for (stIndex Index : vHidenValues)
        if (Index.Row == Row && Index.Colm == Colm)
            return true;

    return false;
}


// Function to hide a random value in the matrix
void HideRandValue() {
    stIndex Index;

    do {
        Index.Row = RandomNumber(0, 8);
        Index.Colm = RandomNumber(0, 8);

    } while (isFoundInHideList(Index.Row, Index.Colm));

    vHidenValues.push_back(Index);
}

// Function to get a line of the game matrix
string GetLine(string FM[9]) {
    string Line = "";

    Line += "#  " + FM[0] + "    " + FM[1] + "    " + FM[2] + "  #";
    Line += "  " + FM[3] + "    " + FM[4] + "    " + FM[5] + "  #";
    Line += "  " + FM[6] + "    " + FM[7] + "    " + FM[8] + "  #";

    return Line;
}

// Function to check if a row character is valid
bool isValiedRowChar(char Row) {
    return (((int)toupper(Row)) >= 65) && (((int)toupper(Row)) <= 64 + 9);
}

// Function to check if a column character is valid
bool isValiedColm(char Colm) {
    return (isdigit(Colm) && Colm != 0);
}

// Function to convert a row or column character to an index
short IndexInInt(char RowOrColm) {
    return (isdigit(RowOrColm)) ? ((short)RowOrColm - 49) : ((short)RowOrColm - 65);
}

// Function to check if an index is accepted
bool isAcceptedIndex(string Index) {
    if (!(isValiedRowChar(toupper(Index[0])) && isValiedColm(Index[1]))) {
        cout << "\nInvalid Index. Please enter a valid one.";
        return false;
    }

    if (!isFoundInHideList(IndexInInt(toupper(Index[0])), IndexInInt(Index[1]))) {
        cout << "\nYou can't change this index's value.";
        return false;
    }

    return true;
}

// Function to get an index from input
stIndex GetIndex(string In) {
    stIndex Index;

    Index.Row = IndexInInt(In[0]);
    Index.Colm = IndexInInt(In[1]);

    return Index;
}

// Function to read an index from input
stIndex ReadIndex() {
    string Index;
    do {
        cout << "\nEnter Index To Change Slot >> ";
        getline(cin >> ws, Index);

    } while (!isAcceptedIndex(Index));

    return GetIndex(Index);
}

// Function to read a new value from input
int ReadNewValue() {
    return ReadNum("\nEnter Number between 1 and 9 >> ", 1, 9);
}

// Function to update a value in the matrix
void UpdateValueInMatrix(string FakeMatrix[9][9], stIndex Index, short Value) {
    FakeMatrix[Index.Row][Index.Colm] = to_string(Value);
}

// Function to check if a position in the matrix is equal
bool isEquel(string FM[9][9], short Pos) {
    return to_string(Matrix[vHidenValues[Pos].Row][vHidenValues[Pos].Colm]) == FM[vHidenValues[Pos].Row][vHidenValues[Pos].Colm];
}

// Function to check if the game is won
bool CheckWin(string FakeMatrix[9][9]) {
    for (int i = 0; i < vHidenValues.size(); i++)
        if (!isEquel(FakeMatrix, i))
            return false;

    return true;

}

// Function to check if a solution is valid
bool CheckSolution(string FakeMatrix[9][9]) {
    // Check each row
    for (int i = 0; i < 9; i++) {
        bool found[9] = {false};
        for (int j = 0; j < 9; j++) {
            if (FakeMatrix[i][j] != " ") {
                int num = stoi(FakeMatrix[i][j]);
                if (found[num - 1]) {
                    return false; // Duplicate number found in row
                }
                found[num - 1] = true;
            }
        }
    }

    // Check each column
    for (int i = 0; i < 9; i++) {
        bool found[9] = {false};
        for (int j = 0; j < 9; j++) {
            if (FakeMatrix[j][i] != " ") {
                int num = stoi(FakeMatrix[j][i]);
                if (found[num - 1]) {
                    return false; // Duplicate number found in column
                }
                found[num - 1] = true;
            }
        }
    }

    // Check each 3x3 grid
    for (int k = 0; k < 9; k += 3) {
        for (int l = 0; l < 9; l += 3) {
            bool found[9] = {false};
            for (int i = k; i < k + 3; i++) {
                for (int j = l; j < l + 3; j++) {
                    if (FakeMatrix[i][j] != " ") {
                        int num = stoi(FakeMatrix[i][j]);
                        if (found[num - 1]) {
                            return false; // Duplicate number found in 3x3 grid
                        }
                        found[num - 1] = true;
                    }
                }
            }
        }
    }

    return true; // Solution is valid
}

// Function to copy the fake matrix
void CopyFakeMatrix(string FakeMatrix[9][9]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!isFoundInHideList(i, j))
                FakeMatrix[i][j] = to_string(Matrix[i][j]);
            else
                FakeMatrix[i][j] = " ";
}

// Function to hide random values in the matrix
void HideRandomValues(int HiddenValues) {
    for (int i = 1; i <= HiddenValues; i++)
        HideRandValue();
}

// Function to reset the screen
void ResetScreen() {
    system("cls");
    system("color 0F");
}

// Function to show the game over screen
void GameOverScreen() {
    cout << "********************************************************\n";
    cout << "*                 Game Over                            *\n";
    cout << "********************************************************\n";
}

// Main Sudoku function
void Sudoku() {
    bool GameOver = false;
    int NewValue;
    string FakeMatrix[9][9];
    stIndex Index;

    FillGameMatrixWith0();
    FillGameMatrixWithRandNum();
    HideRandomValues(3);
    CopyFakeMatrix(FakeMatrix);
    DrawGameMatrix(FakeMatrix);

    while (!GameOver) {
        Index = ReadIndex();
        NewValue = ReadNewValue();
        UpdateValueInMatrix(FakeMatrix, Index, NewValue);
        GameOver = CheckWin(FakeMatrix); // التحقق من الفوز بعد كل خطوة

        ResetScreen();
        DrawGameMatrix(FakeMatrix);

        if (GameOver) {
            cout << "Congratulations! You've solved the Sudoku puzzle!" << endl;
            // لا تعود إلى القائمة الرئيسية بعد الفوز
            return;
        }

        // التحقق من انتهاء اللعبة بالتعادل
        // (يمكنك تنفيذ ذلك باختبار ملء الخانات دون وجود قيمة 0)
        // إذا انتهت اللعبة بالتعادل، يمكنك طباعة رسالة والعودة إلى القائمة الرئيسية

        // إذا كانت اللعبة لم تنته بالفوز، يمكنك الاستمرار في لعبها
    }

    // إذا وصلنا هنا، فقد خسر اللاعب
    cout << "Try again next time!" << endl;
    // العودة إلى القائمة الرئيسية بعد الخسارة

    GameOverScreen();

    GameOverScreen();
}
