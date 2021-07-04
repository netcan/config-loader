# for Catch2
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.6)
FetchContent_MakeAvailable(Catch2)

# for tinyxml2
FetchContent_Declare(
        tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG        9.0.0)
FetchContent_MakeAvailable(tinyxml2)