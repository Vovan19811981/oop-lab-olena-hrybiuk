# Makefile для лабораторної роботи з ООП
# Автор: Олена Гриб'юк

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SOURCES = main.cpp Building.cpp AcademicBuilding.cpp DigitalDevice.cpp MobilePhone.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = lab_program

all: $(EXECUTABLE)
	@echo "Програма успішно скомпільована!"
	@echo "Запустіть: ./$(EXECUTABLE)"

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	@echo "Файли очищено!"

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run
