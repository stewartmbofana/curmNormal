# add the library that runs
add_library(CumFunctions univar.cpp bivar.cpp trivar.cpp utilities.cpp)

# state that anybody linking to us needs to include the current source dir
# to find CumNorm.h, while we don't.
target_include_directories(CumFunctions
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                           )

# should we use our own math functions
option(USE_CUMNORM "Use tutorial provided math implementation" ON)

target_link_libraries(CumFunctions PUBLIC cumnorm_compiler_flags)

# define the symbol stating we are using the declspec(dllexport) when
# building on windows
target_compile_definitions(CumFunctions PRIVATE "EXPORTING_CUMNORM")

# setup the version numbering
set_property(TARGET CumFunctions PROPERTY VERSION "1.0.0")
set_property(TARGET CumFunctions PROPERTY SOVERSION "1")

# install rules
install(TARGETS CumFunctions cumnorm_compiler_flags
        DESTINATION lib
        EXPORT CumFunctionsTargets)
install(FILES univar.h bivar.h trivar.h utilities.h DESTINATION include)
