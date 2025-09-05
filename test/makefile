TARGET = test
CFLAGS := -O0 -g3

default: iris.csv
	gcc main.c -I../include ../build/libcsv.a -lm $(CFLAGS) -o $(TARGET)

iris.csv:
	curl -O https://gist.githubusercontent.com/curran/a08a1080b88344b0c8a7/raw/0e7a9b0a5d22642a06d3d5b9bcbad9890c8ee534/iris.csv

clean:
	rm -f $(TARGET)
