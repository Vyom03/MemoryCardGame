/*********************************************************************************
Name			: Vyom Trivedi
Student Number 	: 040980601
Course Name		: C++
Course Number	: CST8219
Lab Section		: 302
Due Date		: April 16, 2021
Submission Date	: April 16, 2021
*********************************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <vector>
#include <algorithm>



int count = 0;


//Funtion for counting the clicks and keeping track of the card clicked
void clicked(int a)
{
	std::cout << "Card# : " << a << std::endl;
	//Counting clicks
	count++;
	
}

int main()
{
	//Variables
	int counter = 0, first = 0, second = 0, pairs = 0, tries = 0;
	
	using namespace nana;

	//Image
	nana::paint::image back, img;

	//Audio
	nana::audio::player clicks("chime.wav");
	nana::audio::player wrong("boing_x.wav");
	nana::audio::player right("blip.wav");
	nana::audio::player win("bomb_x.wav");

	nana::threads::pool pool(1);

	form fm{ API::make_center(900, 600) };

	fm.caption(("Vyom C++ 2021 CST8219 - Final Project"));

	static place place(fm);
	drawing dw(fm);

	place.div("<Mycard grid=[5, 4] margin=[5,110,5,110] gap=20 >");
	static std::map<char, button*> cards;
	std::list<button> buttons;
	back = nana::paint::image("back.bmp");
	
	//Setting background color
	fm.bgcolor(colors::dark_khaki);
	//Pointer for the previous card
	button* cardPointer1;
	//Pointer for the current card
	button* cardPointer2;
	int iterate[20] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

	//Vector used for storing pictures as integer
	std::vector<int> pics;
	pics = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };

	//Random Shuffler
	srand(time(NULL));
	std::random_shuffle(pics.begin(), pics.end());

	//Exit Label when game is won
	label exitStatus(fm, nana::rectangle(0, 0, 100, 20));
	nana::msgbox exitMess(fm, "Want To Play Agian?", nana::msgbox::yes_no);

	
	for (auto i : iterate) {
		buttons.emplace_front((fm).handle());

		auto& card_btn = buttons.front();
		cards[i] = &card_btn;
		card_btn.icon(back);
		place["Mycard"] << card_btn;

		card_btn.events().click(pool_push(pool, [&, i]()
			
			{
				//Assigning pictures per the vector name (i.e numbers)
				if (pics[i] == 0 || pics[i] == 10) {
					img = nana::paint::image("circle.bmp");
				}
				else if (pics[i] == 1 || pics[i] == 11) {
					img = nana::paint::image("triangle.bmp");
				}
				else if (pics[i] == 2 || pics[i] == 12) {
					img = nana::paint::image("diamond.bmp");
				}
				else if (pics[i] == 3 || pics[i] == 13) {
					img = nana::paint::image("rtriangle.bmp");
				}
				else if (pics[i] == 4 || pics[i] == 14) {
					img = nana::paint::image("pentagon.bmp");
				}
				else if (pics[i] == 5 || pics[i] == 15) {
					img = nana::paint::image("hexagon.bmp");
				}
				else if (pics[i] == 6 || pics[i] == 16) {
					img = nana::paint::image("lArrow.bmp");
				}
				else if (pics[i] == 7 || pics[i] == 17) {
					img = nana::paint::image("rArrow.bmp");
				}
				else if (pics[i] == 8 || pics[i] == 18) {
					img = nana::paint::image("star.bmp");
				}
				else if (pics[i] == 9 || pics[i] == 19) {
					img = nana::paint::image("square.bmp");
				}
				
				//Calling clicked
				clicked(i);
				card_btn.icon(img);
				
				if (first <= 9) {
					first += 10;
				}
				else if (first > 9 ) {
					first -= 10;
				}

				//First Click
				if (counter % 2 == 0) {
					
					cardPointer1 = &card_btn;
					first = pics[i];
					//Click Audio
					clicks.play();
				}

				//Second Click
				else if (counter % 2 == 1) {
					
					//Storing current click to the pointer
					cardPointer2 = &card_btn;

					//Storing vector number to compare images
					second = pics[i];
					tries++;

					//Comparing images
					if (first == second) {
						
						cardPointer1->hide();
						cardPointer2->hide();
						
						//Matches Audio
						right.play();

						//Increments a pair by 1 as we found correct pair above
						pairs++;

						//As soon as we find 10 pair game is won and dialog box should appear
						if (pairs == 10) {
							
							win.play();
							
							std::cout << "Number of Clicks: " << count << std::endl;
							std::cout << "Number of Tries: " << tries << std::endl;
							exitMess << "Game Over" << std::endl;
							exitMess << "Number of Clicks: " << count << std::endl;
							exitMess << "Number of Tries: " << tries << std::endl;
							exitMess << "Play Again!! YES or NO?" << std::endl;
							exitMess();
						}

					}

					//When not matches
					else if (first != second) {
						
						//Wrong Audio
						wrong.play();

						//Hides the card
						cardPointer2->icon(back);
						cardPointer1->icon(back);
					}
				}
				//Increments the counter variable to track the click(number: 1 or 2)
				counter++;
				
		}));
	}
	
		place.collocate();
		fm.show();
		exec();
	


}