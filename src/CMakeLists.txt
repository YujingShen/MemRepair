set(FOLDER_NAME "src")

ADD_SUBDIRECTORY(include)

INCLUDE_DIRECTORIES(include)

set(SOURCE_FILES
    MemRepairBaselineDemo.cpp
)

ADD_EXECUTABLE(RepairExe SOURCE_FILES)

TARGET_LINK_LIBRARIES(RepairExe MemRepairLib)


