#include "ImageButton.h"

ImageButton::ImageButton(std::string ButtonText, int Price) : Entity() {
	ButtonState = 0;
	SpriteFrame = 3;
	_CallbackFunction = NULL;
	
	if(ButtonText == "Firerate") {
		this->addSpriteSheet("assets/fireratebutton.tga", 4, 1);
	}
	if (ButtonText == "Rotation") {
		this->addSpriteSheet("assets/fireratebutton.tga", 4, 1);
	}
	if (ButtonText == "Piercing") {
		this->addSpriteSheet("assets/piercingbutton.tga", 4, 1);
	}
	if (ButtonText == "Speed") {
		this->addSpriteSheet("assets/piercingbutton.tga", 4, 1);
	}
	if (ButtonText == "") {
		this->addSpriteSheet("assets/startbutton.tga", 1, 4);
	}
	if (ButtonText == " ") {
		this->addSpriteSheet("assets/nextwavebutton.tga", 1, 4);
	}


	this->sprite()->pivot = Point2(0, 0);
	this->sprite()->frame(SpriteFrame);

	//Text* line = new Text();
	textbox = new Text();
	textbox->scale = Point2(0.35f, 0.35f);
	textbox->position = Point2(-5, -30);
	textbox->message(ButtonText, BLACK);

	pricetext = new Text();
	pricetext->scale = Point2(0.28f, 0.28f);
	pricetext->position = Point2(-5, -12);

	std::string prefix = "Price: ";
	std::ostringstream fullString;
	fullString << prefix << Price;
	pricetext->message(fullString.str(), BLUE);

	addChild(textbox);
	addChild(pricetext);

}

ImageButton::~ImageButton() {

}

void ImageButton::update(float deltaTime) {

	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();

	Point2 pos = worldposition();

	int left = pos.x;
	int right = pos.x + sprite()->size.x;
	int top = pos.y;
	int bottom = pos.y + +sprite()->size.y;

	if (ButtonState != 3) {
		if (mousex > left && mousex < right && mousey > top && mousey < bottom) {
			if (input()->getMouseDown(0)) {
				ButtonState = 2;

				if (_CallbackFunction != NULL) {
					_CallbackFunction();
				}
			}
			if (ButtonState == 0 || input()->getMouseUp(0)) {
				ButtonState = 1;

			}
		}
		else {
			ButtonState = 0;
		}
	}

	switch (ButtonState) {
		case 0: SpriteFrame = 3; break;	//Normal
		case 1: SpriteFrame = 1; break;	//MouseOver
		case 2: SpriteFrame = 2; break;	//MouseDown
		case 3: SpriteFrame = 0; break;	//Disabled
	}

	this->sprite()->frame(SpriteFrame);
}

void ImageButton::setCallbackFunction(std::function<void()> CallbackFunction) {
	_CallbackFunction = CallbackFunction;
}

void ImageButton::Disable() {
	ButtonState = 3;
}

void ImageButton::Enable() {
	ButtonState = 0;
}