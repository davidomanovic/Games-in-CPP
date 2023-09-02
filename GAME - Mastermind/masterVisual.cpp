#include "masterVisual.h"
#include "mastermind.h"
#include "utilities.h"

void addGuess(MastermindWindow &mwin, const string code, const char startLetter)
{
	mwin.guesses.push_back({code, startLetter});
}

void addFeedback(MastermindWindow &mwin, const int correctPosition, const int correctCharacter)
{
	mwin.feedbacks.push_back({correctPosition, correctCharacter});
}

void MastermindWindow::drawCodeHider()
{
	if(code_hidden) {
		draw_rectangle(Point{padX, 3 * padY}, winW - size * padX, padY, Color::black);
	}
}

MastermindWindow::MastermindWindow(int x, int y, int w, int h, int size, const string &title) 
: AnimationWindow(x, y, w, h, title),
guessBtn{{upperLeftCornerBtn.x, upperLeftCornerBtn.y}, btnW, btnH, "Add"}, 
guess{{upperLeftCornerInBox.x, upperLeftCornerInBox.y}, inBoxW, inBoxH, ""},
size(size)
{
	add(guess);
	add(guessBtn);
	guessBtn.setCallback(std::bind(&MastermindWindow::cb_guess, this)); 
};

string MastermindWindow::wait_for_guess()
{
std::map<int, Color> colorConverter{
	{1, Color::red},
	{2, Color::green},
	{3, Color::yellow},
	{4, Color::blue},
	{5, Color::blue_violet},
	{6, Color::dark_cyan}
};

	while (!button_pressed && !should_close())
	{
		for(int guessIndex = 0; guessIndex < static_cast<int>(guesses.size()); guessIndex++) {
			// Legger til et gjett i grafikkvinduet i form av fargede rektangler.
			// xPos initialiseres likt hver gang denne funksjonen kalles, mens yPos er avhengig av round,
			// slik at gjetningene vises under hverandre.
			Guess guess = guesses.at(guessIndex);
			int xPos = padX;
			const int yPos = 3 * padY + 2 * padY * guessIndex;
			for (int i = 0; i < size; i++)
			{
				draw_rectangle(Point{xPos, yPos}, padX, padY, colorConverter.at(guess.code[i] - guess.startLetter + 1));
				xPos += 2 * padX;
			}
		}

		for(int feedbackIndex = 0; feedbackIndex < static_cast<int>(feedbacks.size()); feedbackIndex++) {
			Feedback feedback = feedbacks.at(feedbackIndex);
			int xPos = 9 * padX + radCircle;
			const int yPos = 3.5 * padY + 2 * padY * (feedbackIndex + 1);
			for (int i = 0; i < size; i++)
			{
				Color indicatorColour = Color::beige;
				if (i < feedback.correctPosition)
				{
					indicatorColour = Color::black;
				}
				else if (i < (feedback.correctPosition + std::max<int>(0, feedback.correctCharacter - feedback.correctPosition)))
				{
					indicatorColour = Color::grey;
				}
				draw_circle(Point{xPos, yPos}, radCircle, indicatorColour);
			
				xPos += 2 * radCircle;
			}
		}

		// Should be drawn last as it has to be on top
		drawCodeHider();

		next_frame();
	}
	button_pressed = false;
	string newGuess = guess.getText(); 
	guess.setText("");

	return newGuess;
}

string MastermindWindow::getInput(unsigned int n, char lower, char upper)
{
	bool validInput = false;
	string guess;
	while (!validInput && !should_close())
	{
		guess.clear();
		string input = wait_for_guess();
		if (input.size() == n)
		{
			for (unsigned int i = 0; i < n; i++)
			{
				char ch = input.at(i);
				if (isalpha(ch) && toupper(ch) <= upper && lower <= toupper(ch))
				{
					guess += toupper(ch);
				}
				else
					break;
			}
		}
		if (guess.size() == n)
		{
			validInput = true;
		}
		else
		{
			cout << "Invalid input guess again" << endl;
		}
	}
	return guess;
}

void MastermindWindow::setCodeHidden(bool hidden) {
	code_hidden = hidden;
}

void playMastermindVisual()
{
	constexpr int size = 4;
	constexpr int letters = 6;
	constexpr char startLetter = 'A';
	constexpr int maxTries = 6;
	/*Vi bruker constexpr og ikke const her fordi vi vet verdien til variablene før vi kjører koden.
    constexpr er konstanter der verdien blir bestemt i kompileringstid, og const er konstanter der 
    verdien blir bestemt i kjøretid. Du kan lese mer om const og constexpr i kapittel 4.3.1 i læreboka
    */

	
	bool playAgain = false;
	do {
		MastermindWindow mwin{900, 20, winW, winH, size, "Mastermind"};
		string code = randomizeString(size, startLetter, startLetter + letters - 1);
		string guess;
		int round = 0;
		cout << "*** Mastermind ***" << endl;
		
		// Viser CODE. addGuess brukes til å vise den hemmelige koden med parameter round = 0
		addGuess(mwin, code, startLetter);
		mwin.setCodeHidden(false);
		
	
		while (round != maxTries) {
			cout << "Colors: a = red, b = green, c = yellow, d = blue, e = lilac, f = cyan" << endl;
			cout << "What's your guess? (" << size << " chars)" << endl;
			guess = mwin.getInput(size, startLetter, startLetter + letters - 1);
			cout << "Your guess: " << guess << endl;
			++round;
			if(mwin.should_close()) {
				break;
			}

			int correct = checkCharactersAndPosition(code, guess);
			int correctChars = checkCharacters(code, guess);

			// Det nyeste gjettet legges til i grafikkvinduet sammen med riktig tilbakemelding.
			addGuess(mwin, guess, startLetter);
			addFeedback(mwin, correct, correctChars);
			mwin.next_frame();
			
			// Hopp ut av løkken dersom spiller har gjettet koden.
			if (correct == size) {
				break;
			}

			cout << "Correct characters: " << correctChars << endl
				 << "Correct positions: " << correct << endl << "You have " << maxTries - round
				 << " tries left." << endl << endl;
		}
		
		mwin.wait_for_close();
		
		if (guess == code) {
			cout << "Congratulations, you cracked the code!" << endl;
			mwin.setCodeHidden(false);
		} else {
			cout << "You didn't manage to crack the code..." << endl;
		}
		playAgain = askYesNoQuestion("Do you want to play again?");
	} while (playAgain);
}