#include "ConsoleRenderer.h"

ConsoleRenderer::ConsoleRenderer(int w, int h) :
	width(w),
	heigth(h),
	pixelCount(w*h),
	screenBuffer(new char[pixelCount]),
	pixelBuffer(new int[pixelCount]),
	sc_screenBuffer(pixelCount),
	//grayRamp(" .'`^',:;Il!i><~+_-?][}{1)(|\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$")
	grayRamp(" .:-=+*#%@")
{

	GetConsoleScreenBufferInfo(console, &screen);

	for (int px = 0; px < pixelCount; px++)
	{
		//screenBuffer[px] = GetCharCodeFromColor(pixelBuffer[px], pixelBuffer[px], pixelBuffer[px]);
		sc_screenBuffer.SetAt(px, GetCharCodeFromColor(pixelBuffer[px], pixelBuffer[px], pixelBuffer[px]));
	}

	fixedRandA = rand() % 256;
	fixedRandB = rand() % 256;
	fizedRandC = rand() % 256;

	ratio = (float)(grayRamp.length() - 1) / (float)255;
}

void ConsoleRenderer::Draw(float dt)
{
	//CleanScreen();
	SetConsoleCursorPosition(console, topLeft);

	float p, r, g, b;
	
	int px = 0;
	for (int v = 0; v < heigth; v++)
	{
		for (int u = 0; u < width; u++)
		{
			if (u == width - 1)
			{
				//screenBuffer[px] = '\n';
				sc_screenBuffer.SetAt(px, '\n');
			}
			else
			{
				//screenBuffer[px] = GetCharCodeFromColor(pixelBuffer[px], pixelBuffer[px], pixelBuffer[px]);
				
				// weird noise
				//r = 2 * (u * abs(sin(std::chrono::system_clock::now().time_since_epoch().count()))) * (255 / width);
				//g = 3 * (v * abs(sin(std::chrono::system_clock::now().time_since_epoch().count()))) * (255 / heigth);
				//b = 0;

				// just noise
				//float r = rand() % 256;
				//float g = rand() % 256;
				//b = rand() % 256;

				p = 3.14 / 256;

				//r = u * 256/120;
				//g = v * 256/60;
				//b = 128;

				//r = abs(sin(5 * u * p)) * 255 + rand() % 64 - 64;
				//g = abs(sin(10 * v * p)) * 255 + rand() % 64 - 64;
				//b = sin(lifeTime) * 255;

				r = cos(lifeTime) * abs(sin(5 *u * p)) * 255;
				g = abs(sin(10 * v * p)) * 255;
				b = sin(lifeTime) * 255 + (rand() % 32 - 32);

				//r = cos(lifeTime) * abs(sin(2.3 * u * p)) * 255;
				//g = abs(sin(7.5 * v * p)) * 255;
				//b = sin(lifeTime) * 255;
				//b = 0;

				//b = rand() % 16 - 16;

				//screenBuffer[px] = GetCharCodeFromColor(r, g, b);
				sc_screenBuffer.SetAt(px, GetCharCodeFromColor(r, g, b));

				//std::cout << screenBuffer[px];
			}
			++px;
		}
	}
	
	SetConsoleTextAttribute(console, FOREGROUND_GREEN | 0);
	//fwrite(screenBuffer, 1, pixelCount, stderr);
	fwrite(sc_screenBuffer.GetArray(), 1, pixelCount, stderr);
	SetConsoleTextAttribute(console, 0 | (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE));
	//std::cout << " " << rand() % 128 - 128 << " " << lifeTime;
	lifeTime += dt;
}

ConsoleRenderer::~ConsoleRenderer()
{
	delete[] screenBuffer;
	delete[] pixelBuffer;
}

void ConsoleRenderer::CleanScreen()
{
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

char ConsoleRenderer::GetCharCodeFromColor(const int& r, const int& g, const int& b)
{
	/*
	float m = (float)(r + g + b) / 3.0f;

	const int black_l = 50;
	const int lgrey_l = 100;
	const int grey_l = 150;
	const int dgrey_l = 200;
	const int white_l = 255;
	

	//float ratio = (float)(grayRamp.length()-1) / (float)255;
	//int pos = ceil(m * ratio);

	if (pos >= grayRamp.length()) return ' ';

	return (char)grayRamp[pos];
	*/

	int pos = ceil(((float)(r + g + b) * ratio) / 3.0f);
	if (pos >= grayRamp.length()) return grayRamp[grayRamp.length() - 1];
	return (char)grayRamp[pos];

	/*
	if (m < black_l)
	{
		return 255;
	}
	if (m < lgrey_l)
	{
		return 176;
	}
	if (m < grey_l)
	{
		return 177;
	}
	if (m < dgrey_l)
	{
		return 178;
	}
	else // white_l
	{
		return 219;
	}
	*/
}
