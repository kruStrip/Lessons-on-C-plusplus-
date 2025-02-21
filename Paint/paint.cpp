#include <wapi_oop.h>

class MainWindow : public Window
{
	std::unique_ptr<Button> b;

public:
	MainWindow(HINSTANCE hInstance) : Window(hInstance)
	{
		InitComponent(nullptr);

		b = std::make_unique<Button>(hInstance, 10, this);
		b->SetPosition(10, 10);
		b->SetSize(200, 50);
		b->SetText(L"Нажми меня");

		SetText(L"Мое окно");
		SetSize(500, 500);
	}

	LRESULT OnCommand(WPARAM wp, LPARAM lp) override
	{
		WORD id = LOWORD(wp), state = HIWORD(wp);
		if (id == b->GetId() && state == BN_CLICKED)
		{
			MessageBoxW(hwnd, L"Вы нажали кнопку!", L"Оповещение", MB_OK);
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

class PaintingWindow : public Window {
	std::unique_ptr<PaintBox> pb;
protected:
	DECLARE_CLASS_NAME(PaintingWindow);
public:
	PaintingWindow(HINSTANCE hInstance) : Window(hInstance) {
		InitComponent(nullptr);
		pb = std::make_unique<PaintBox>(hInstance, 10, this);
		pb->SetSize(512, 512);
		pb->SetPosition(10, 10);

		SetText(L"Паинт");
		SetSize(550, 550);
		//SetStyle(WS_OVERLAPPEDWINDOW | ~WS_THICKFRAME | ~WS_MAXIMIZE);
	}

	void Draw() {
		pb->SetPen(PaintBox::Solid, 3, Color{ 252,15,192 });
		pb->Draw<Figure::ELLIPSE>(20, 113, 80, 50);
		pb->Draw<Figure::ELLIPSE>(145, 113, 80, 50);
		pb->Draw<Figure::LINE>(25, 100, 100, 180);
		pb->Draw<Figure::LINE>(137, 100, 100, 180);
		pb->Update();
	}
	LRESULT OnPaint(HDC& hdc, PAINTSTRUCT& ps, WPARAM wp, LPARAM lp) override {
		return 0;
	}
	/*void fill(int x1, int y1, int x2, int y2) {
		if (pen == nullptr) throw std::logic_error("Pen is not set");

		PaintParams pp{ f, x1, y1, x2, y2 };
		paintEvents.push_back(pp);
	}*/
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR cmdline, int nCmdShow)
{
	REGISTER_DEFAULT(hInstance);
	RegisterControl(PaintingWindow, hInstance);

	PaintingWindow mw(hInstance);
	mw.Show();
	mw.Draw();
	mw.ProcessMessages();

	return 0;
}