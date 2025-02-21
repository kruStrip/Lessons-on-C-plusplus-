#include <wapi_oop.h>
#include <random>
#include <string>

class MainWindow : public Window
{
	std::unique_ptr<Button> b[10][10];
	int soder[10][10];

public:
	MainWindow(HINSTANCE hInstance) : Window(hInstance)
	{
		int x = 10;
		int y = 10;
		std::random_device dev;
		std::mt19937 rand(dev());
		std::uniform_int_distribution<int> dist(0, 1);
		InitComponent(nullptr);
		for (int i = 0; i < 9; i++) {
			for (int g = 0; g < 9; g++) {
				b[i][g] = std::make_unique<Button>(hInstance, i*10+g, this);
				b[i][g]->SetPosition(x, y);
				soder[i][g] = dist(rand);
				b[i][g]->SetSize(50, 50);
				b[i][g]->SetText(L"*");
				x += 50;
			}
			y += 50;
			x = 10;
		}

		SetText(L"Сапер");
		SetSize(500, 510);
	}
	

	LRESULT OnCommand(WPARAM wp, LPARAM lp) override
	{
		WORD id = LOWORD(wp), state = HIWORD(wp);
		int i = id / 10;
		int g = id % 10;
		int count = 0;
		std::random_device dev;
		std::mt19937 rand(dev());
		std::uniform_int_distribution<int> dist(0, 8);
		if (id == b[i][g]->GetId() && state == BN_CLICKED)
		{	
			if (g > 0 && soder[i][g - 1] == 1) {count++;}
			if(g < 9 && soder[i][g + 1] == 1) {count++;}
			if (i > 0 && soder[i+1][g] == 1) { count++; }
			if (i < 9 && soder[i - 1][g] == 1) { count++; }
			MessageBoxW(hwnd,(L"Вы нажали кнопку!" + std::to_wstring(count)).c_str(), L"Оповещение", MB_OK | MB_ICONINFORMATION);
		}
		return 0;
	}

	LRESULT OnPaint(HDC& hdc, PAINTSTRUCT& ps, WPARAM wp, LPARAM lp) override
	{
		FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));
		return 0;
	}

protected:
	DECLARE_CLASS_NAME(MainWindow);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR cmdline, int nCmdShow)
{
	RegisterControl(MainWindow, hInstance);

	MainWindow mw(hInstance);
	mw.Show();

	mw.ProcessMessages();

	return 0;
}

