#include "Controller.h"

using namespace std;

int main()
{
	do {
		bool secondPlayer = false;
		string answer;
		cout << "Would like to play againt other player OR against ai?\n";
		cout << "Or type exit to close this game\n";
		cin >> answer;
		Utils::clearInputBuffer();

		if (answer == "exit") {
			break;
		}
		else if (answer == "ai") {
			secondPlayer = true;
		}
		Controller controller(false, secondPlayer);
		controller.startGame();
		
		cout << "\n\n";
	} while (true);
	
	system("pause");
	return 0;
}
