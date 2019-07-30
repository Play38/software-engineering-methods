ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = ./Common/Border.o ./Common/BorderStrategy.o ./Common/Button.o ./Common/CheckBox.o ./Common/CheckList.o ./Common/ComboBox.o ./Common/Control.o ./Common/EventEngine.o ./Common/Graphics.o ./Common/MessageBox.o ./Common/NumericBox.o ./Common/Panel.o ./Common/RadioBox.o ./Common/TextBox.o ./Controls/Label.o ./FinalProject/Source.o

all: $(OBJS)
	$(CXX) $(OBJS) -o Source.exe -static