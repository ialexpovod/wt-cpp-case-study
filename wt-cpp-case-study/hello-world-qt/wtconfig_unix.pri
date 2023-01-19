# Author: Alex Povod 2023-01-19 10:36

DEFINES      -= QT_NO_KEYWORDS WT_NO_SLOT_MACROS
INCLUDEPATH  += /usr/local/include/
LIBS         += -L/usr/local/lib/

				
CONFIG(debug, debug|release) {
        LIBS += -lwt           \
                -lwthttp
} else {

OBJECTS_DIR  += release
        LIBS += -lwt           \
                -lwthttp
}

