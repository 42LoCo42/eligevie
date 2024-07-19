#include <raylib.h>
#include <raymath.h>
#include <time.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#ifndef FONT
// clang-format off
#define FONT /usr/share/fonts/TTF/IosevkaNerdFontMono-Regular.ttf
// clang-format on
#endif

#define QUOTE(x) #x
#define FONT_STR(x) QUOTE(x)

int main() {
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Eligevie");
	SetWindowState(FLAG_WINDOW_UNDECORATED);

	SetTargetFPS(24);

	int fontSize = 40;
	int spacing  = 1;
	int padding  = 10;

	Font font = LoadFontEx(FONT_STR(FONT), fontSize, NULL, 128);

	time_t now_raw = time(NULL);

	while(!WindowShouldClose()) {
		Vector2 windowSize = (Vector2){
			GetScreenWidth(),
			GetScreenHeight(),
		};

		if(IsKeyDown(KEY_SPACE)) now_raw += 86400;

		struct tm* now = localtime(&now_raw);

		int year  = now->tm_year % 100;
		int month = now->tm_yday / 14;
		int day   = now->tm_yday % 14;

		int box_width  = windowSize.x - 2 * padding;
		int box_height = windowSize.y - 2 * padding;

		int month_x = (month + 1) * box_width / 28;
		int day_y   = (day + 1) * box_height / 15;

		const char* date_text =
			month < 26 ? TextFormat("%02d%c%02d", year, month + 'A', day)
					   : TextFormat("%02d+%02d", year, day);

		Vector2 text_mes = MeasureTextEx(font, date_text, fontSize, spacing);
		Vector2 text_pos = Vector2Subtract(
			(Vector2){month_x, day_y}, Vector2Divide(text_mes, (Vector2){2, 2})
		);

		BeginDrawing();
		{
			ClearBackground(BLANK);

			DrawRectangleLines(
				padding, padding, windowSize.x - 2 * padding,
				windowSize.y - 2 * padding, WHITE
			);

			DrawLine(month_x, padding, month_x, box_height + padding, WHITE);
			DrawLine(padding, day_y, box_width + padding, day_y, WHITE);

			DrawRectangle(
				month_x - text_mes.x / 2, day_y - text_mes.y / 2, text_mes.x,
				text_mes.y, ColorAlpha(BLACK, 0.9)
			);

			DrawTextEx(font, date_text, text_pos, fontSize, spacing, WHITE);
		}
		EndDrawing();
	}

	CloseWindow();
}
