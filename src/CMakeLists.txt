set(FOLDER_NAME "src")

ADD_SUBDIRECTORY(include)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(MemRepairBaselineDemo MemRepairBaselineDemo.cpp)

TARGET_LINK_LIBRARIES(MemRepairBaselineDemo MemRepair)




