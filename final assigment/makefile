ifeq ($(OS), Windows_NT)
	CXX = g++
else
	CXX = /usr/bin/i686-w64-mingw32-g++
endif

OBJS = ./Common/border.o ./Common/borderStrategy.o ./Common/button.o ./Common/checkBox.o ./Common/checkList.o ./Common/comboBox.o ./Common/control.o ./Common/eventEngine.o ./Common/graphics.o ./Common/messageBox.o ./Common/numericBox.o ./Common/panel.o ./Common/radioBox.o ./Common/textBox.o ./Controls/label.o ./FinalProject/source.o

all: $(OBJS)
	$(CXX) $(OBJS) -o main.exe -static