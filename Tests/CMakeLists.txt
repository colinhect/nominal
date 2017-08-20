include_directories(
    "${PROJECT_SOURCE_DIR}/Library/Include"
    )

set(SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/Tests/Source/Main.cpp"
    "${PROJECT_SOURCE_DIR}/Tests/Source/LexerTests.cpp"
)

if(WIN32)
    add_definitions("/D_CRT_SECURE_NO_WARNINGS")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion-null")
endif()

add_executable(NominalTests ${SOURCE_FILES})
target_link_libraries(NominalTests NominalLibrary)

set(REG_EXT "[^/]*([.]cpp|[.]hpp)$")

source_group("Source" REGULAR_EXPRESSION "${REG_SOURCE}${REG_EXT}")

set_target_properties(NominalTests PROPERTIES
    PROJECT_LABEL Tests
    OUTPUT_NAME nominaltests
    LINKER_LANGUAGE CXX
    )
