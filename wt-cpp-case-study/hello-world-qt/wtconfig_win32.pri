# Author: Alex Povod 2023-01-19 10:36

DEFINES      += WIN32 HPDF_DLL 
DEFINES      -= QT_NO_KEYWORDS WT_NO_SLOT_MACROS

INCLUDEPATH  += .\
                C:\Users\povad_ad\AppData\Local\Programs\Wt\Wt_4_9_0_msvs2019_Windows_x64_SDK\include     \
                C:\Users\povad_ad\AppData\Local\Programs\Wt\Wt-4.9.0-msvs2022-Windows-x86-SDK\include

DEPENDPATH   += .

LIBS         += -LC:\Users\povad_ad\AppData\Local\Programs\Wt\Wt_4_9_0_msvs2019_Windows_x64_SDK\lib    \
		        -LC:\Users\povad_ad\AppData\Local\Programs\Wt\Wt-4.9.0-msvs2022-Windows-x86-SDK\lib

				
CONFIG(debug, debug|release) {

        LIBS += -lwt
                -lwthttp							
} else 

{OBJECTS_DIR  += release
        LIBS += -lwt \
                -lwthttp
}