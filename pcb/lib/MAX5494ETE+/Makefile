ZIP = LIB_MAX5494ETE+.zip
URL = https://componentsearchengine.com/part-view/MAX5494ETE%2B/Analog%20Devices

TMP = tmp
TMP_DIR = $(TMP)/MAX5494ETE+
TMP_KICAD = $(TMP_DIR)/KiCad
TMP_3D = $(TMP_DIR)/3D

KICAD_MOD_SRC = $(TMP_KICAD)/QFN80P500X500X80-17N.kicad_mod
KICAD_SYM_SRC = $(TMP_KICAD)/MAX5494ETE+.kicad_sym
STP_SRC = $(TMP_3D)/MAX5494ETE+.stp

KICAD_PRETTY = MAX5494ETE+.pretty
KICAD_MOD = $(KICAD_PRETTY)/QFN80P500X500X80-17N.kicad_mod
KICAD_SYM = MAX5494ETE+.kicad_sym
STP = MAX5494ETE+.stp

SRC = $(KICAD_MOD_SRC) $(KICAD_SYM_SRC) $(STP_SRC)
DEST = $(KICAD_PRETTY) $(KICAD_MOD) $(KICAD_SYM) $(STP)

.PHONY: all clean

all: $(DEST)

clean:
	rm -rf $(TMP) $(DEST)

$(ZIP):
	@if [ ! -f $@ ]; then \
		echo "Download $@ from $(URL)"; \
		exit 1; \
	fi

$(TMP): $(ZIP)
	unzip -o $< -d $@

$(SRC): | $(TMP)
	@if [ ! -f $@ ]; then \
		echo "$@ not found. $(ZIP) may be updated."; \
		exit 1; \
	fi

$(KICAD_PRETTY):
	mkdir $@

$(KICAD_MOD): $(KICAD_MOD_SRC) $(KICAD_PRETTY)
	cp $< $@

$(KICAD_SYM): $(KICAD_SYM_SRC)
	cp $< $@

$(STP): $(STP_SRC)
	cp $< $@
