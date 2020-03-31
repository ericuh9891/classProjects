#include <string>
#include <iostream>

using namespace std;

class Window{
	public:
		Window(){width = 10;}
		int getWidth(){return width;}
	private:
		int width;
};

class WindowWithBorder : public Window{
	public:
		WindowWithBorder(int w){
			w = borderWidth;
		}
		int getUseableWidth(){
			return Window::getWidth() - borderWidth;
		}
	private:
		int borderWidth;
};


int main(){
	WindowWithBorder myWindow(1);

	cout << myWindow.getUseableWidth() << endl;
	return 0;
}
