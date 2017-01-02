#include <signal.h>
#include <stdio.h>
#include <exception>

#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

bool sigintGot = false;

int main() {
	signal(SIGINT, [](int s) {
		printf("SIGINT got");
		sigintGot = true;
	});

	Bot bot("PLACE YOUR TOKEN HERE");

	// Thanks Pietro Falessi for code
	InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
	vector<InlineKeyboardButton::Ptr> row0;
	InlineKeyboardButton::Ptr checkButton(new InlineKeyboardButton);
	checkButton->text = "check";
	checkButton->callbackData = "check";
	row0.push_back(checkButton);
	keyboard->inlineKeyboard.push_back(row0);

	bot.getEvents().onCommand("start", [&bot, &keyboard](Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hi!", false, 0, keyboard);
	});
	bot.getEvents().onCommand("check", [&bot, &keyboard](Message::Ptr message) {
		string response = "ok";
		bot.getApi().sendMessage(message->chat->id, response, false, 0, keyboard, "Markdown");
	});
	bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
		if (StringTools::startsWith(query->data, "check")) {
			string response = "ok";
			bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard, "Markdown");
		}
	});

	try {
		printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

		TgLongPoll longPoll(bot);
		while (!sigintGot) {
			printf("Long poll started\n");
			longPoll.start();
		}
	} catch (exception& e) {
		printf("error: %s\n", e.what());
	}

	return 0;
}
