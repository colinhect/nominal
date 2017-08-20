include_directories(
    "${PROJECT_SOURCE_DIR}/Library/Include"
    )

set(INCLUDE_FILES
    "${PROJECT_SOURCE_DIR}/Library/Include/Nominal.hpp"
    "${PROJECT_SOURCE_DIR}/Library/Include/Nominal/Lexer.hpp"
    "${PROJECT_SOURCE_DIR}/Library/Include/Nominal/Export.hpp"
    )

set(SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/Library/Source/Lexer.cpp"
    )

if(WIN32)
    add_definitions("/D_CRT_SECURE_NO_WARNINGS /DNOM_EXPORTS")
    include(CheckIncludeFiles)
    check_include_files(vld.h NOM_USE_VLD)
elseif(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -pedantic -Wno-missing-braces -Wno-missing-field-initializers")
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/Library/Config.hpp.in"
    "${PROJECT_SOURCE_DIR}/Library/Include/Nominal/Config.hpp"
    )

add_library(NominalLibrary SHARED ${INCLUDE_FILES} ${SOURCE_FILES})

set(REG_INCLUDE ".*/Include/")
set(REG_INCLUDE_NOMINAL ".*/Include/Nominal/")
set(REG_SOURCE ".*/Source/")
set(REG_EXT "[^/]*([.]cpp|[.]hpp)$")

source_group("Include" REGULAR_EXPRESSION "${REG_INCLUDE}${REG_EXT}")
source_group("Include\\Nominal" REGULAR_EXPRESSION "${REG_INCLUDE_NOMINAL}${REG_EXT}")
source_group("Source" REGULAR_EXPRESSION "${REG_SOURCE}${REG_EXT}")

set_target_properties(NominalLibrary PROPERTIES
    PROJECT_LABEL Library
    OUTPUT_NAME nominal-${NOM_VERSION}
    LINKER_LANGUAGE CXX
    )
