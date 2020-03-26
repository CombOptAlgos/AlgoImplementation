run: main.cpp
	g++ main.cpp -o main
	./main < input.txt > output.txt

debug: main.cpp
	g++ -g main.cpp -o main
	lldb ./main

.PHONY:
clean:
	rm main output.txt
