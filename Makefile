.RECIPEPREFIX +=

# Variables
CXX = gcc
CXXFLAGS = -Wall -g -lm
SRC_DIR = src
REPORT_DIR = report
BIN_DIR = bin

# Get a list of all the .cpp files in the src directory
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Derive the names of the executable files from the names of the .cpp files
EXECS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SRCS))

# Variables
IMAGES_DIR = output
PNG_DIR = $(IMAGES_DIR)/png

# Get a list of all the .pgm and .ppm files in the images directory
IMAGES := $(wildcard $(IMAGES_DIR)/*.pgm) $(wildcard $(IMAGES_DIR)/*.ppm)

# Derive the names of the .png files from the names of the .pgm and .ppm files
PNGS := $(patsubst $(IMAGES_DIR)/%.pgm,$(PNG_DIR)/%.png,$(IMAGES))
PNGS += $(patsubst $(IMAGES_DIR)/%.ppm,$(PNG_DIR)/%.png,$(IMAGES))

# Targets
.PHONY: all dirs clean report

all: dirs $(EXECS) pngs report 

dirs:
		mkdir -p $(SRC_DIR)
		mkdir -p $(REPORT_DIR)
		mkdir -p $(BIN_DIR)
		mkdir -p $(PNG_DIR)

# Build each executable from its corresponding .cpp file
$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Rule to convert .pgm and .ppm files to .png files
$(PNG_DIR)/%.png: $(IMAGES_DIR)/%.pgm
	convert $< $@
$(PNG_DIR)/%.png: $(IMAGES_DIR)/%.ppm
	convert $< $@

# Target to convert all .pgm and .ppm files to .png files
pngs: $(PNGS)

# Build the report
report: $(REPORT_DIR)/report.tex
		pdflatex -output-directory=$(REPORT_DIR) $<; \

clean:
		rm -f $(EXECS) $(REPORT_DIR)/report.pdf

